#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
using namespace std;


struct AABB {
    float minX, maxX;
    float minZ, maxZ;
};


enum GameState {
    MENU,
    PLAYING,
    GAME_OVER,
    WIN
};


// Game configurations
inline int screenWidth;
inline int screenHeight;
inline int frameRate = 60;
inline float aspect;

inline GameState gameState = MENU;

inline float carStep = 0.4f;
inline float roadRight = 2, roadLeft = -2.5, roadStart = 7, roadEnd = -500;


void delay(float sec);
float random(float min = 0, float max = RAND_MAX);

bool checkAABBCollision(AABB a, AABB b);

void overlay(float rectWidth, float rectHeight, float xPos, float yPos, string text, float alpha);
void renderBitmapString(float x, float y, void *font, const char *string);



#endif