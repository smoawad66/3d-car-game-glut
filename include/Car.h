#ifndef CAR_H
#define CAR_H

#include <cmath>
#include <GL/glut.h>

class Car
{
private:
	float r, g, b;
public:
	Car(float r, float g, float b);
	void draw();
};

#endif