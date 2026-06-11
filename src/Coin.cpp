#include <Coin.h>


Coin::Coin(float x, float z, bool special, bool colided) {
    this->x = x;
    this->z = z;
    this->special= special;
    this->colided = colided;
}


void Coin::draw(float &coinAngle) {

    glPushMatrix();
    glTranslatef(x, 0.3, z);
    glRotatef(coinAngle, 0, 1, 0);

    if (this->special) {
        GLfloat mat_ambient[] = { 0.8f, 0.2f, 0.2f, 1.0f };
        GLfloat mat_diffuse[] = { 0.8f, 0.2f, 0.2f, 1.0f };
        GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat mat_shininess[] = { 50.0f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

        glColor3f(0.8, 0.2, 0.2);
        glutSolidTorus(0.07, 0.13, 70, 70);
    }
    else {

        GLfloat torusAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat torusDiffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
        GLfloat torusSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat torusShininess[] = { 50.0f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, torusAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, torusDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, torusSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, torusShininess);

        glColor3f(1, 1, 0);
        glutSolidTorus(0.059, 0.13, 50, 50);
    }

    // coinAngle += coinAngle < 360 ? 0.1 : -360;
    if (coinAngle + 0.07 < 360) {
        coinAngle += 0.07;
    }
    else {
        coinAngle = 0;
    }

	glPopMatrix();
}



