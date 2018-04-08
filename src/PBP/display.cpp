#include "display.hpp"

namespace PBP
{
    ALLEGRO_DISPLAY*display = NULL;
    
    int init()
    {
        if(!al_init())
            return 1;
        return 0;
    }

    int initDisplay(int w,int h)
    {
        PBP::display = al_create_display(w,h);
        if(!display)
            return 1;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_flip_display();
        return 0;
    }

    void destroyDisplay()
    {
        al_destroy_display(PBP::display);
    }
}