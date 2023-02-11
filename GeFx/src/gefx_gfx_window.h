#ifndef GEFX_GFX_WINDOW_H_
#define GEFX_GFX_WINDOW_H_
#include <glad/glad.h>
#include <glfw3.h>
#include "gefx_debug.h"
#include "gefx_config.h"
#include "gefx_geometry.h"

namespace Fx{
enum KEYMODE{
NONE,PRESS, RELEASE, REPEAT
};

static KEYMODE keymode=KEYMODE::NONE;
class Renderer;
class Window{

friend class Renderer; 
public:
Window();
~Window();
bool closes();
void pollEvents();
int GetWindowWidth();
int GetWindowHeight();
bool isPressed(int key);
Ge::Vec2D GetCursorPos();
void SetCursorPos(const Ge::Vec2D& pos);
Window& retWindow();
private:
void clear();
void swap();


GLFWwindow* window; 
GLFWmonitor* monitor;
int screen_w,screen_h;
double lastResize=0;
};
Window::Window()
{
    GLFWmonitor* monitor=glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(monitor, NULL,NULL,&screen_w,&screen_h);

    window=glfwCreateWindow(GEFX_GFX_WINDOW_STD_WIDTH,GEFX_GFX_WINDOW_STD_HEIGHT,GEFX_GFX_WINDOW_STD_TITLE,NULL,NULL);
    
    //Checking for the WINDOW_CENTERED flag
    #ifndef GEFX_WINDOW_CENTERED
    glfwSetWindowPos(window,GEFX_GFX_WINDOW_STD_X,GEFX_GFX_WINDOW_STD_Y);
    #else 
    glfwSetWindowPos(window,(screen_w-GEFX_GFX_WINDOW_STD_WIDTH)/2,(screen_h-GEFX_GFX_WINDOW_STD_HEIGHT)/2);
    #endif

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0,0,GEFX_GFX_WINDOW_STD_WIDTH,GEFX_GFX_WINDOW_STD_HEIGHT);
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window,int width, int height){glfwSwapBuffers(window);glViewport(0,0,width, height);});
    glfwSetKeyCallback(window,[](GLFWwindow* window, int key, int scancode, int action, int mods){
        if(action==GLFW_PRESS)keymode=KEYMODE::PRESS;
        else if(action==GLFW_RELEASE)keymode=KEYMODE::RELEASE;
        else if (action==GLFW_REPEAT)keymode=KEYMODE::REPEAT;
    });

    #ifdef GEFX_WINDOW_FULLSCREEN 
    glfwSetWindowSize(window,screen_w,screen_h);
    glfwSetWindowPos(window,0,0);
    swap();
    #endif
}
bool Window::closes()
{
    if(isPressed(GLFW_KEY_ESCAPE))return true; 
    return glfwWindowShouldClose(window);
}
void Window::swap()
{
    glfwSwapBuffers(window);
}
void Window::pollEvents()
{
    glfwPollEvents();
    
    if(!isPressed(GLFW_KEY_F11))return;
    if(lastResize+GEFX_GFX_WINDOW_STD_RESIZE_DELAY>glfwGetTime())return;
    swap();
    lastResize=glfwGetTime();
    int w,h;
    glfwGetWindowSize(window,&w,&h);
    if(w==screen_w&&h==screen_h)
    {
        glfwSetWindowSize(window,GEFX_GFX_WINDOW_STD_WIDTH,GEFX_GFX_WINDOW_STD_HEIGHT);
        glfwSetWindowPos(window,(screen_w-GEFX_GFX_WINDOW_STD_WIDTH)*0.5,(screen_h-GEFX_GFX_WINDOW_STD_HEIGHT)*0.5);
        swap();
        return;
    }
    glfwSetWindowSize(window,screen_w,screen_h);
    glfwSetWindowPos(window,0,0);
    swap();
}
Window::~Window()
{
    glfwTerminate();
    glfwDestroyWindow(window);
    game<<"Window gets deleted!!";
}
bool Window::isPressed(int key)
{
    return (glfwGetKey(window,key)==GLFW_PRESS);
}
void Window::clear()
{
 glClearColor(GEFX_GFX_WINDOW_STD_BG);
 glClear(GL_COLOR_BUFFER_BIT);
}

int Window::GetWindowWidth()
{
    int w; 
    glfwGetWindowSize(window,&w,NULL);
    return w;
}
int Window::GetWindowHeight()
{
    int h; 
    glfwGetWindowSize(window,NULL,&h);
    return h;
}
Ge::Vec2D Window::GetCursorPos()
{
    double cursorX, cursorY;
    glfwGetCursorPos(window,&cursorX,&cursorY);
    return {static_cast<float>(cursorX), static_cast<float>(cursorY)};
}
void Window::SetCursorPos(const Ge::Vec2D& pos)
{
    glfwSetCursorPos(window,pos.x,pos.y);
}
Window& Window::retWindow()
{
    return *this;
}

}


#endif