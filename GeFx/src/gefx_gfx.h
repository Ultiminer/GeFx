#ifndef GEFX_GFX_INIT_H
#define GEFX_GFX_INIT_H
#include "gefx_gfx_window.h"
#include "gefx_gfx_render.h"
namespace Fx{

inline void GEFX_GFX_OPENGL_INIT()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    #ifndef GEFX_WINDOW_RESIZABLE
    glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
    #endif
}

}
inline void GeFxInit()
{
    Fx::GEFX_GFX_OPENGL_INIT();
}

#endif