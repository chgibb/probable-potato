#pragma once
#include <allegro5/allegro.h>

namespace PBP
{
    extern ALLEGRO_DISPLAY*display;

    int init();
    int initDisplay(int,int);
    void destroyDisplay();
}