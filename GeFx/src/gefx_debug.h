#ifndef GEFX_DEBUG_H_
#define GEFX_DEBUG_H_
#include <fstream>

extern std::ofstream game; 
#ifdef RELEASE_MODE 
#define PRINT(x)
#else 
#define PRINT(x)game<<x<<std::endl;
#endif

#endif