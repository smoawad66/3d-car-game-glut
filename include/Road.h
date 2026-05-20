#pragma once

class Road
{

public:
	float roadRight, roadLeft, roadStart, roadEnd;

	Road(float roadRight, float roadLeft, float roadStart, float roadEnd);
	void draw(unsigned int *textures);
};