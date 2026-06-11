#include <Road.h>


Road::Road(float roadRight, float roadLeft, float roadStart, float roadEnd) {
    this->roadRight = roadRight;
    this->roadLeft = roadLeft;
    this->roadStart = roadStart;
    this->roadEnd = roadEnd;
}

void Road::draw(unsigned int *textures) {
    
    glNormal3f(0, 1, 0);
    // Road
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0f, 10.0f);glVertex3f(roadRight, 0, roadEnd);
	glTexCoord2d(1.0f, 10.0f);glVertex3f(roadLeft, 0, roadEnd);
	glTexCoord2d(1.0f, 0.0f);glVertex3f(roadLeft, 0, roadStart);
	glTexCoord2d(0.0f, 0.0f);glVertex3f(roadRight, 0, roadStart);
	glEnd();

	// Right side
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0f, 1.0f);glVertex3f(roadRight, 0, roadStart);
	glTexCoord2d(0.0f, 0.0f);glVertex3f(roadRight, 3, roadStart);
	glTexCoord2d(30.0f, 0.0f);glVertex3f(roadRight, 3, roadEnd);
	glTexCoord2d(30.0f, 1.0f);glVertex3f(roadRight, 0, roadEnd);
	glEnd();

	// Left side
	glBegin(GL_POLYGON);
	glTexCoord2d(30.0f, 1.0f);glVertex3f(roadLeft, 0, roadEnd);
	glTexCoord2d(30.0f, 0.0f);glVertex3f(roadLeft, 3, roadEnd);
	glTexCoord2d(0.0f, 0.0f);glVertex3f(roadLeft, 3, roadStart);
	glTexCoord2d(0.0f, 1.0f);glVertex3f(roadLeft, 0, roadStart);
	glEnd();


	// Sky
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0f, 30.0f);glVertex3f(roadRight, 3, roadEnd);
	glTexCoord2d(1.0f, 30.0f);glVertex3f(roadLeft, 3, roadEnd);
	glTexCoord2d(1.0f, 0.0f);glVertex3f(roadLeft, 3, roadStart);
	glTexCoord2d(0.0f, 0.0f);glVertex3f(roadRight, 3, roadStart);
	glEnd();

	//the end
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(roadRight, 0, roadEnd);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(roadRight, 3, roadEnd);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(roadLeft, 3, roadEnd);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(roadLeft, 0, roadEnd);
	glEnd();
}



