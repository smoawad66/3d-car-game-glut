#ifndef MENU_H
#define MENU_H

#include <Utils.h>

class Menu
{
private:
    int windowWidth, windowHeight;
public:
    Menu(int windowWidth, int windowHeight);
    void draw(int selectedOption);
};

#endif