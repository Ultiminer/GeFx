#version 330 core
layout (location = 0) in vec2 aPos;
uniform float windowWidth; 
uniform float windowHeight; 
uniform int cordSys;
uniform vec2 offset;
uniform int depth;
uniform vec2 finalScale;
uniform vec2 initScale;

void main()
{
    
    switch(cordSys)
    {
        case 0:
            gl_Position = vec4(finalScale.x*2*(initScale.x*aPos.x-offset.x)/windowWidth-1, 1-finalScale.y*2*(initScale.y*aPos.y-offset.y)/windowHeight, depth, 1.0);
        break;
        case 1:
            gl_Position = vec4(finalScale.x*(initScale.x*aPos.x-offset.x), finalScale.y*(initScale.y*aPos.y-offset.y), depth, 1.0);
        break;
        case 2: 
            gl_Position= vec4(finalScale.x*2*(initScale.x*aPos.x*cos(aPos.y)-offset.x)/windowWidth,finalScale.y*2*(initScale.y*aPos.x*sin(aPos.y)-offset.y)/windowHeight,depth,1.0);
        break;
        case 3: 
            gl_Position= vec4(finalScale.x*2*(initScale.x*aPos.x*cos(aPos.y)-offset.x)/windowWidth-1,1-finalScale.y*2*(initScale.y*aPos.x*sin(aPos.y)-offset.y)/windowHeight,depth,1.0);
        break;
    }   
}