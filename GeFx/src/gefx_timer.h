#ifndef GEFX_TIMER_H_
#define GEFX_TIMER_H_
#include <glfw3.h>

struct GEFX_Timer
{
    private:
    double ticks;
    double diff;
    public: 
    GEFX_Timer(){ticks=glfwGetTime();};
    inline GEFX_Timer& reset(){ticks=glfwGetTime();return *this;};
    inline GEFX_Timer& calcEllapsed(){diff=glfwGetTime()-ticks; return *this;};
    inline double getEllapsed(){return diff;};
    inline double operator()()
    {
        return diff;
    }

};
#endif


