#pragma once

class Coin
{

public:
	float x, z;
	bool special, colided;

	Coin(float x, float z, bool special = false, bool colided = false);
	void draw(float &coinAngle);
};