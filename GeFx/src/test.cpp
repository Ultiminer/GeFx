//SYSTEM DEFINES 
#define GEFX_WINDOW_CENTERED
#define GEFX_WINDOW_TITLE "SandboxApp"
#define GEFX_IMMEDIATE_MODE

//HEADER INCLUDES 
#include "gefx.h"



int GEFX_MAIN()
{
    GEFX_Timer timer;  
    Circle circle{100,100,50};
    Rect rect{0,100,120,100,0};
    Polygon poly{200,200,50,5,0};

    GEFX_LOOP()
    {
        timer.reset();
        pollEvents();
        StartDrawing();
        SetColor(RED).DrawCircle(circle).FillRect(rect);
    
        SetColor(ANTIQUE_WHITE).DrawLine({0,0,0,100},2);
        SetColor(LAWN_GREEN).FillPolygon(poly);
        
        InterMove(poly.pos,{500,500},500,timer());
        EndDrawing();
        rect.angle+=0.00002;
        poly.angle+=0.00005;
        timer.calcEllapsed();
    }

    return 0;
}