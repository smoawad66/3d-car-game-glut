#ifndef ROAD_H
#define ROAD_H

#include <GL/glut.h>

class Road
{

public:
	float roadRight, roadLeft, roadStart, roadEnd;

	Road(float roadRight, float roadLeft, float roadStart, float roadEnd);
	void draw(unsigned int *textures);
};

#endif