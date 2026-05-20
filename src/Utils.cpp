#include <Utils.h>


void delay(float sec) {
	auto start = chrono::steady_clock::now();
	chrono::milliseconds duration((int)(1000 * sec));
	while (chrono::steady_clock::now() - start < duration);
}

float random(float min, float max) {
	if (min > max) swap(max, min);
	return min + float (rand()) / (float (RAND_MAX / (max - min)));
}


bool checkAABBCollision(AABB a, AABB b) {
	bool collisionX = (a.maxX >= b.minX) && (a.minX <= b.maxX);    
	bool collisionZ = (a.maxZ >= b.minZ) && (a.minZ <= b.maxZ);
	return collisionX && collisionZ;
}


void renderBitmapString(float x, float y, void *font, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


void overlay(float rectWidth, float rectHeight, float xPos, float yPos, string text, float alpha) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, 0, screenHeight);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(0.0f, 0.0f, 0.0f, alpha);

	glBegin(GL_QUADS);
	glVertex2f(xPos, yPos);
	glVertex2f(xPos + rectWidth, yPos);
	glVertex2f(xPos + rectWidth, yPos + rectHeight);
	glVertex2f(xPos, yPos + rectHeight);
	glEnd();
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    int textWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.c_str());

    float textXPos = xPos + (rectWidth / 2.0f) - (textWidth / 2.0f);
    float textYPos = yPos + (rectHeight / 2.0f) - 8.0f;
    
	renderBitmapString(textXPos, textYPos, GLUT_BITMAP_TIMES_ROMAN_24, text.c_str());

    glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}