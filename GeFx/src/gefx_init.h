#ifndef GEFX_INIT_H_
#define GEFX_INIT_H_
#include "gefx_geometry.h"
#include "gefx_gfx.h"

#ifdef GEFX_IMMEDIATE_MODE 
using namespace Ge;
using namespace Fx; 

class GeFxMain:public Fx::Window ,public Fx::Renderer{
    public:
    GeFxMain():Renderer::Renderer(retWindow()){};
    int Main();
};

#define GEFX_MAIN() GeFxMain::Main()
int main(int argc, char* argv[])
{
GeFxInit();
GeFxMain mainClass;
return mainClass.Main();
}
#define GEFX_LOOP() while(!closes()) 


#endif



#endif