#include <bits/stdc++.h>
#include <GL/glut.h>
#include <Wall.h>


Wall::Wall(float x1, float x2, float z) {
    this->x1 = x1;
    this->x2 = x2;
    this->z = z;
}


void Wall::draw(float wallHeight, float wallDepth) {
    glBegin(GL_QUADS);
    //back
    glTexCoord2f(0, 0); glVertex3f(x1, 0, z);
    glTexCoord2f(1, 0); glVertex3f(x2, 0, z);
    glTexCoord2f(1, 1); glVertex3f(x2, wallHeight, z);
    glTexCoord2f(0, 1); glVertex3f(x1, wallHeight, z);

    //front
    glTexCoord2f(0, 0); glVertex3f(x1, 0, z-wallDepth);
    glTexCoord2f(1, 0); glVertex3f(x2, 0, z-wallDepth);
    glTexCoord2f(1, 1); glVertex3f(x2, wallHeight, z-wallDepth);
    glTexCoord2f(0, 1); glVertex3f(x1, wallHeight, z-wallDepth);
    
    //left
    glTexCoord2f(1, 1); glVertex3f(x1, 0, z);
    glTexCoord2f(1, 0); glVertex3f(x1, wallHeight, z);
    glTexCoord2f(0, 0); glVertex3f(x1, wallHeight, z-wallDepth);
    glTexCoord2f(0, 1); glVertex3f(x1, 0, z-wallDepth);
    
    //right
    glTexCoord2f(0, 0); glVertex3f(x2, 0, z);
    glTexCoord2f(0, 1); glVertex3f(x2, wallHeight, z);
    glTexCoord2f(1, 1); glVertex3f(x2, wallHeight, z-wallDepth);
    glTexCoord2f(1, 0); glVertex3f(x2, 0, z-wallDepth);

    
    //top
    glTexCoord2f(1, 1); glVertex3f(x2, wallHeight, z - wallDepth);
    glTexCoord2f(1, 0); glVertex3f(x2, wallHeight, z);
    glTexCoord2f(0, 0); glVertex3f(x1, wallHeight, z);
    glTexCoord2f(0, 1); glVertex3f(x1, wallHeight, z-wallDepth);

    glEnd();
}



