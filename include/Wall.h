#ifndef WALL_H
#define WALL_H

#include <GL/glut.h>


class Wall
{

public:
    float x1, x2, z;

	Wall(float x1, float x2, float z);
	void draw(float wallHeight, float wallDepth);
};

#endif