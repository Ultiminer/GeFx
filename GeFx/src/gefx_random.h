#ifndef GEFX_RANDOM_H_
#define GEFX_RANDOM_H_
#include <glfw3.h>
#include <gcem.hpp>
#include "gefx_config.h"



struct GEFX_STD_RAND_STRUCT
{
private: 
constexpr double calculate()
{
    return gcem::fmod(seed*CONFNUM_GEFX_RAND_MAGIC_SCALAR+CONFNUM_GEFX_RAND_MAGIC_BIAS,CONFNUM_GEFX_RAND_WIDTH)/CONFNUM_GEFX_RAND_WIDTH;
}
public:
double seed; 
GEFX_STD_RAND_STRUCT(){seed=glfwGetTime()*1000;};
inline double operator()()
{
    seed= calculate();
    return seed; 
}
inline GEFX_STD_RAND_STRUCT& reset()
{
    seed=glfwGetTime()*1000;
    return *this; 
}
inline GEFX_STD_RAND_STRUCT& setSeed(const double& seed)
{
    this->seed=seed;
    return *this;
}
}GeFx_Rand;


#endif