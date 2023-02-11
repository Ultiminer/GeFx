#ifndef GEFX_GFX_RENDER_H_
#define GEFX_GFX_RENDER_H_
#include <glad/glad.h>
#include <glfw3.h>
#include "gefx_debug.h"
#include "gefx_config.h"
#include "gefx_compile_shaders.h"
#include <vector>
#include "gefx_geometry.h"
#include "gefx_gfx_window.h"

namespace Fx{
enum class OBJ_DEPTH{
FOREGROUND,
MID_FOREGROUND,
MID_MID_FOREGROUND,
MIDGROUND,
MID_BACKGROUND,
MID_MID_BACKGROUND,
BACKGROUND
};



inline void SecureShader(unsigned int shader, const char* msg=0)
{
    
int success;
char infoLog[512];
glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
if(!success)
{
glGetShaderInfoLog(shader, 512, NULL, infoLog);
game << "ERROR::SHADER::COMPILATION_FAILED\n" <<
infoLog << msg<<std::endl;
}

}
inline void SecureProgram(unsigned int program)
{
int success;
char infoLog[512];
glGetProgramiv(program, GL_LINK_STATUS, &success);
if(!success) {
glGetProgramInfoLog(program, 512, NULL, infoLog);
game << "ERROR::PROGRAM::COMPILATION_FAILED\n" <<
infoLog << std::endl;
}

}


inline std::vector<size_t> GetRectInd(const size_t& offset)
{
    return {0+offset,1+offset,2+offset,0+offset,2+offset,3+offset};
}


class Renderer{
public:
Renderer(Window& window);
~Renderer();
Renderer& StartDrawing();
Renderer& EndDrawing();
Renderer& SetColor(const float r, const float g, const float b, const float a);
Renderer& SetColor(const RGB& rgb);
Renderer& DrawOutline(const std::vector<Ge::Vec2D>& points);
Renderer& DrawShape(const std::vector<Ge::Vec2D>& points);
Renderer& DrawLineSeg(const std::vector<Ge::Vec2D>& points);
Renderer& DrawTriangleSeg(const std::vector<Ge::Vec2D>& points);
Renderer& FillBox(const Ge::Box2D& rect);
Renderer& FillCircle(const Ge::Circle& circle);
Renderer& DrawBox(const Ge::Box2D& rect);
Renderer& DrawCircle(const Ge::Circle& circle);
Renderer& FillRect(const Ge::Rect& rect);
Renderer& DrawRect(const Ge::Rect& rect);
Renderer& DrawLine(const Ge::Line2D& line);
Renderer& DrawLine(float x1, float y1, float x2, float y2);
Renderer& DrawLine(float x1, float y1, float x2, float y2, const float height);
Renderer& DrawLine(const Ge::Line2D& line, const float height);
Renderer& DrawPolygon(const Ge::Polygon& polygon);
Renderer& FillPolygon(const Ge::Polygon& polygon);
Renderer& DrawLines(const std::vector<Ge::Vec2D>& _points, const float height);

Renderer& UseAbsoluteCoordinates();
Renderer& UseRealtiveCoordinates();
Renderer& UsePolarCoordinates();
Renderer& UseAbsolutePolarCoordinates();
Renderer& SetOffset(const Ge::Vec2D& offset);
Renderer& SetDepth(const OBJ_DEPTH& depth);
Renderer& SetFinalCordScale(const Ge::Vec2D& scale);
Renderer& SetInitialCordScale(const Ge::Vec2D& scale);

private:


void SetNormWidth(unsigned int width);
void SetNormHeight(unsigned int height);

bool OnTime; 
double currentTime=0.0f; 
Window& window;

unsigned int shaderProgram;
unsigned int vertexBuffer; 
unsigned int vertexArray;
unsigned int elementBuffer;

int tempWinWidth=0, tempWinHeight=0;
int colorLocation;
int winWidthLocation; 
int winHeightLocation;
int cordSysLocation;
int offsetLocation;
int depthLocation;
int finalScaleLocation;
int initScaleLocation;

const unsigned int rectInd[6]={0,1,2,0,2,3};
const unsigned int rectOulineInd[8]={0,3,3,2,2,1,1,0};
};

Renderer::Renderer(Window& passWindow): window{passWindow}
{
//MAking the shaderProgram
unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);
const char* vertexSrc=CompileShader("../shaders/vertex.glsl").c_str();
glShaderSource(vertexShader,1,&vertexSrc,NULL);
glCompileShader(vertexShader); 
SecureShader(vertexShader,vertexSrc);

unsigned int fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
const char* fragmentSrc=CompileShader("../shaders/fragment.glsl").c_str();
glShaderSource(fragmentShader,1,&fragmentSrc,NULL);
glCompileShader(fragmentShader); 
SecureShader(fragmentShader,fragmentSrc);

shaderProgram=glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
SecureProgram(shaderProgram);

glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
//Getting the color location from the shader
colorLocation=glGetUniformLocation(shaderProgram, "ourColor");
glUseProgram(shaderProgram);
SetColor(GEFX_GFX_RENDERER_STD_OBJ_COLOR);

//Getting the windowWidth location
winWidthLocation=glGetUniformLocation(shaderProgram,"windowWidth");
glUseProgram(shaderProgram);
SetNormWidth(window.GetWindowWidth());

//Getting the windowHeight location
winHeightLocation=glGetUniformLocation(shaderProgram,"windowHeight");
glUseProgram(shaderProgram);
SetNormHeight(window.GetWindowHeight());

//Getting the cordSys location
cordSysLocation=glGetUniformLocation(shaderProgram,"cordSys");
glUseProgram(shaderProgram);
UseAbsoluteCoordinates();

//Getting the offset location
offsetLocation=glGetUniformLocation(shaderProgram,"offset");
glUseProgram(shaderProgram);
SetOffset(GEFX_GFX_RENDERER_STD_OBJ_OFFSET);

//Getting the depth location
depthLocation=glGetUniformLocation(shaderProgram,"depth");
glUseProgram(shaderProgram);
SetDepth(OBJ_DEPTH::FOREGROUND);

//Getting the location of the final coordinate Scaling - after transform
finalScaleLocation=glGetUniformLocation(shaderProgram,"finalScale");
glUseProgram(shaderProgram);
SetFinalCordScale(GEFX_GFX_RENDERER_STD_FINAL_OBJ_SCALE);

//Getting the location of the final coordinate Scaling - after transform
initScaleLocation=glGetUniformLocation(shaderProgram,"initScale");
glUseProgram(shaderProgram);
SetInitialCordScale(GEFX_GFX_RENDERER_STD_INITIAL_OBJ_SCALE);

//Buffering
glGenBuffers(1,&vertexBuffer);
glGenBuffers(1,&elementBuffer);
glGenVertexArrays(1,&vertexArray);


//Readying the buffers to be filled to the brim with tasty white
glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);

//Setting the pointer to geometrical 3d Point data
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
}
Renderer::~Renderer()
{
}
Renderer& Renderer::DrawOutline(const std::vector<Ge::Vec2D>& points)
{
if(OnTime)return *this;

glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glUseProgram(shaderProgram);
glBufferData(GL_ARRAY_BUFFER, sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawArrays(GL_LINE_STRIP, 0, points.size());


return *this;
}
Renderer& Renderer::DrawTriangleSeg(const std::vector<Ge::Vec2D>& points)
{
if(OnTime)return *this;

glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glUseProgram(shaderProgram);
glBufferData(GL_ARRAY_BUFFER, sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawArrays(GL_TRIANGLES, 0, points.size());

return *this;
}
Renderer& Renderer::DrawLineSeg(const std::vector<Ge::Vec2D>& points)
{
if(OnTime)return *this;
glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glUseProgram(shaderProgram);
glBufferData(GL_ARRAY_BUFFER, sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawArrays(GL_LINES, 0, points.size());

return *this;
}
Renderer& Renderer::DrawShape(const std::vector<Ge::Vec2D>& points)
{
if(OnTime)return *this;

glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glUseProgram(shaderProgram);
glBufferData(GL_ARRAY_BUFFER, sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawArrays(GL_TRIANGLE_STRIP, 0, points.size());

return *this;
}
Renderer& Renderer::DrawLine(const Ge::Line2D& line)
{
if(OnTime)return *this;
std::vector<Ge::Vec2D> points{line.a,line.b};
glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glUseProgram(shaderProgram);
glBufferData(GL_ARRAY_BUFFER, sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawArrays(GL_LINES, 0, points.size());

return *this;
}
Renderer& Renderer::DrawLine(float x1, float y1, float x2, float y2)
{
if(OnTime)return *this;
std::vector<Ge::Vec2D> points{{x1,y1},{x2,y2}};
glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glUseProgram(shaderProgram);
glBufferData(GL_ARRAY_BUFFER, sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawArrays(GL_LINES, 0, points.size()); 

return *this;
}


Renderer&  Renderer::FillBox(const Ge::Box2D& rect)
{
if(OnTime)return *this;

const std::vector<Ge::Vec2D> points=Ge::ShapeOf(rect);

glBindVertexArray(vertexArray);

glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*4,points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectInd), rectInd,GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

return *this;
}
Renderer&  Renderer::DrawBox(const Ge::Box2D& rect)
{
if(OnTime)return *this;

const std::vector<Ge::Vec2D> points=Ge::ShapeOf(rect);

glBindVertexArray(vertexArray);

glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectOulineInd), rectOulineInd,GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

return *this;
}
Renderer&  Renderer::FillCircle(const Ge::Circle& circle)
{
if(OnTime)return *this;

const std::vector<Ge::Vec2D> points=Ge::ShapeOf(circle);
std::vector<unsigned int> indices;
//Determine indices 
for(size_t i=1; i<points.size();++i)
{
if((i+1)%2==0)
indices.push_back(0);
indices.push_back(i);
}
//DrawShape(points);
glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices)*indices.size(), indices.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);


return *this;
}
Renderer&  Renderer::DrawCircle(const Ge::Circle& circle)
{
if(OnTime)return *this;

const std::vector<Ge::Vec2D> points=Ge::ShapeOf(circle);
std::vector<unsigned int> indices;
//Determine indices 
for(size_t i=0; i<points.size();++i)
indices.push_back(i);

//DrawShape(points);
glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices)*indices.size(), indices.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_LINE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);

return *this;
}
Renderer&  Renderer::DrawPolygon(const Ge::Polygon& polygon)
{
if(OnTime)return *this;

const std::vector<Ge::Vec2D> points=Ge::ShapeOf(polygon);
std::vector<unsigned int> indices;
//Determine indices 
for(size_t i=0; i<points.size();++i)
indices.push_back(i);

//DrawShape(points);
glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices)*indices.size(), indices.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_LINE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);

return *this;
}
Renderer&  Renderer::FillPolygon(const Ge::Polygon& polygon)
{
if(OnTime)return *this;

const std::vector<Ge::Vec2D> points=Ge::ShapeOf(polygon);
std::vector<unsigned int> indices;
//Determine indices 
for(size_t i=1; i<points.size();++i)
{
if((i+1)%2==0)
indices.push_back(0);
indices.push_back(i);
}
//DrawShape(points);
glBindVertexArray(vertexArray);
glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices)*indices.size(), indices.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);

return *this;
}
Renderer&  Renderer::FillRect(const Ge::Rect& rect)
{
if(OnTime)return *this;

const std::vector<Ge::Vec2D> points=Ge::ShapeOf(rect);

glBindVertexArray(vertexArray);

glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*4,points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectInd), rectInd,GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

return *this;
}
Renderer&  Renderer::DrawRect(const Ge::Rect& rect)
{
if(OnTime)return *this;

const std::vector<Ge::Vec2D> points=Ge::ShapeOf(rect);

glBindVertexArray(vertexArray);

glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectOulineInd), rectOulineInd,GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

return *this;
}

Renderer& Renderer::SetColor(const float r, const float g, const float b, const float a=255)
{
    glUniform4f(colorLocation, r/255,g/255,b/255, a/255);
    return *this;
}
Renderer& Renderer::SetColor(const RGB& rgb)
{
    SetColor(rgb.r,rgb.g,rgb.b);
    return *this;
}
Renderer& Renderer::StartDrawing()
{
    if(currentTime+GEFX_GFX_RENDERER_STD_DELAY>glfwGetTime())return *this;
    tempWinWidth=window.GetWindowWidth();
    tempWinHeight=window.GetWindowHeight();
    SetNormWidth(tempWinWidth);
    SetNormHeight(tempWinHeight);
    OnTime=false;
    window.clear();
    return *this;
}
Renderer& Renderer::EndDrawing()
{
    if(OnTime)return *this;
    currentTime=glfwGetTime();
    window.swap();
    OnTime=true;
    return *this;
}
void Renderer::SetNormWidth(unsigned int width)
{
    glUniform1f(winWidthLocation,width);
}
void Renderer::SetNormHeight(unsigned int height)
{
    glUniform1f(winHeightLocation,height);
}

Renderer& Renderer::UseAbsoluteCoordinates()
{
    glUniform1i(cordSysLocation,0);
    return *this; 
}
Renderer& Renderer::UseRealtiveCoordinates()
{
    glUniform1i(cordSysLocation,1);
    return *this; 
}
Renderer& Renderer::UsePolarCoordinates()
{
    glUniform1i(cordSysLocation,2);
    return *this; 
}
Renderer& Renderer::UseAbsolutePolarCoordinates()
{
    glUniform1i(cordSysLocation,3);
    return *this; 
}

Renderer& Renderer::SetOffset(const Ge::Vec2D& offset)
{
    glUniform2f(offsetLocation,offset.x,offset.y);
    
    return *this;
}
Renderer&  Renderer::SetDepth(const OBJ_DEPTH& depth)
{
    glUniform1f(depthLocation,static_cast<int>(depth));

    return *this;
}
Renderer&  Renderer::SetFinalCordScale(const Ge::Vec2D& scale)
{
    glUniform2f(finalScaleLocation,scale.x,scale.y);

    return *this;
}
Renderer&  Renderer::SetInitialCordScale(const Ge::Vec2D& scale)
{
    glUniform2f(initScaleLocation,scale.x,scale.y);
    return *this;
}
Renderer&  Renderer::DrawLine(const Ge::Line2D& line, const float height)
{
if(OnTime)return *this;

const Ge::Vec2D offVec{Ge::UnitNormal(line.b-line.a)*height};
const std::vector<Ge::Vec2D> points={line.a-offVec,line.a+offVec,line.b+offVec,line.b-offVec};

glBindVertexArray(vertexArray);

glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*points.size(),points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectInd), rectInd,GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

   return *this;
}
Renderer&  Renderer::DrawLine(float x1, float y1, float x2, float y2, const float height)
{
if(OnTime)return *this;
const Ge::Vec2D offVec=Ge::UnitNormal({x2-x1,y2-y1})*height;
const Ge::Vec2D p1={x1,y1};
const Ge::Vec2D p2={x2,y2};
const std::vector<Ge::Vec2D> points={p1-offVec,p1+offVec,p2+offVec,p2-offVec};

glBindVertexArray(vertexArray);

glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(points)*4,points.data(),GEFX_GFX_RENDERER_STD_DRAWMODE);
glUseProgram(shaderProgram);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectInd), rectInd,GEFX_GFX_RENDERER_STD_DRAWMODE);
glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);

   return *this;
}



}
#endif