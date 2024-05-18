#include "Car.h"
#include <bits/stdc++.h>
#include <gl/glut.h>



void Car::draw(float r, float g, float b){


	glRotatef(-90, 0, 1, 0);
	glScalef(0.62, 0.99, 0.9);


	// front lights
	glPushMatrix();
	glColor3f(1, 1, 1);
	glPointSize(12);
	glBegin(GL_POINTS);
	glVertex3f(0.19, 0.3, 0.3);
	glVertex3f(0.19, 0.3, 0.5);
	glEnd();
	glPopMatrix();

	// back lights
	glColor3f(0.439, 0.035, 0.035);
	glBegin(GL_POLYGON);
	glVertex3f(2.11, 0.34, 0.53);
	glVertex3f(2.11, 0.34, 0.45);
	glVertex3f(2.11, 0.29, 0.45);
	glVertex3f(2.11, 0.29, 0.53);
	glEnd();
	
	glColor3f(0.439, 0.035, 0.035);
	glBegin(GL_POLYGON);
	glVertex3f(2.11, 0.34, 0.33);
	glVertex3f(2.11, 0.34, 0.25);
	glVertex3f(2.11, 0.29, 0.25);
	glVertex3f(2.11, 0.29, 0.33);
	glEnd();


	// borders
	glColor3f(0.29,0.2,0.3);
	glBegin(GL_LINE_LOOP);
	glVertex3f(2.1, 0.4, 0.6);
	glVertex3f(2.1, 0.4, 0.2);
	glVertex3f(2.1, 0.2, 0.2);
	glVertex3f(2.1, 0.2, 0.6);
	glEnd();

	glColor3f(0.4, 0.2, 0.3);
	glBegin(GL_LINE_LOOP);
	glVertex3f(1.8, 0.5, 0.6);
	glVertex3f(1.8, 0.5, 0.2);
	glVertex3f(2.1, 0.4, 0.2);
	glVertex3f(2.1, 0.4, 0.6);
	glEnd();


	glBegin(GL_QUADS);

	/* top of cube*/
	//************************FRONT BODY****************************************
	glColor3f(0, 0, 0);
	glVertex3f(0.2, 0.4, 0.6);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.2, 0.4, 0.2);


	/* bottom of cube*/
	glVertex3f(0.2, 0.4, 0.6);
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(0.6, 0.2, 0.2);
	glVertex3f(0.2, 0.2, 0.2);


	// front of cube (for collision)
	glVertex3f(0.2, 0.2, 0.6);
	glVertex3f(0.2, 0.4, 0.6);
	glVertex3f(0.2, 0.4, 0.2);
	glVertex3f(0.2, 0.2, 0.2);




	glColor3f(r, g, b);
	/* back of cube.*/
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.6, 0.2, 0.2);

	/* left of cube*/
	glVertex3f(0.2, 0.2, 0.6);
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.2, 0.4, 0.6);

	/* Right of cube */
	glVertex3f(0.2, 0.2, 0.2);
	glVertex3f(0.6, 0.2, 0.2);
	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.2, 0.4, 0.2);
	//****************************************************************************
	glColor3f(0, 0, 0);
	glVertex3f(0.7, 0.65, 0.6);
	glVertex3f(0.7, 0.65, 0.2);
	glVertex3f(1.7, 0.65, 0.2);        //top cover
	glVertex3f(1.7, 0.65, 0.6);
	//***************************back guard******************************
	

	glColor3f(r, g, b);            /* Set The Color To Blue*/
	glVertex3f(1.8, 0.5, 0.6);
	glVertex3f(1.8, 0.5, 0.2);
	glVertex3f(2.1, 0.4, 0.2);
	glVertex3f(2.1, 0.4, 0.6);

	/* bottom of cube*/
	glVertex3f(2.1, 0.2, 0.6);
	glVertex3f(2.1, 0.2, 0.2);
	glVertex3f(1.8, 0.2, 0.6);
	glVertex3f(1.8, 0.2, 0.6);	


	/* back of cube.*/
	glVertex3f(2.1, 0.4, 0.6);
	glVertex3f(2.1, 0.4, 0.2);
	glVertex3f(2.1, 0.2, 0.2);
	glVertex3f(2.1, 0.2, 0.6);

	/* left of cube*/
	glVertex3f(1.8, 0.2, 0.2);
	glVertex3f(1.8, 0.5, 0.2);
	glVertex3f(2.1, 0.4, 0.2);
	glVertex3f(2.1, 0.2, 0.2);

	

	/* Right of cube */
	glVertex3f(1.8, 0.2, 0.6);
	glVertex3f(1.8, 0.5, 0.6);
	glVertex3f(2.1, 0.4, 0.6);
	glVertex3f(2.1, 0.2, 0.6);
	//******************MIDDLE BODY************************************
	glColor3f(r, g, b);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(1.8, 0.2, 0.6);
	glVertex3f(1.8, 0.5, 0.6);

	/* bottom of cube*/
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(0.6, 0.2, 0.2);
	glVertex3f(1.8, 0.2, 0.2);
	glVertex3f(1.8, 0.2, 0.6);

	/* back of cube.*/
	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.6, 0.2, 0.2);
	glVertex3f(1.8, 0.2, 0.2);
	glVertex3f(1.8, 0.5, 0.2);
	//*********************ENTER WINDOW**********************************
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.77, 0.63, 0.2);
	glVertex3f(0.75, 0.5, 0.2);        //quad front window
	glVertex3f(1.2, 0.5, 0.2);
	glVertex3f(1.22, 0.63, 0.2);

	glVertex3f(1.27, 0.63, .2);
	glVertex3f(1.25, 0.5, 0.2);        //quad back window
	glVertex3f(1.65, 0.5, 0.2);
	glVertex3f(1.67, 0.63, 0.2);

	glColor3f(r, g, b);
	glVertex3f(0.7, 0.65, 0.2);
	glVertex3f(0.7, 0.5, .2);       //first separation
	glVertex3f(0.75, 0.5, 0.2);
	glVertex3f(0.77, 0.65, 0.2);

	glVertex3f(1.2, 0.65, 0.2);
	glVertex3f(1.2, 0.5, .2);       //second separation
	glVertex3f(1.25, 0.5, 0.2);
	glVertex3f(1.27, 0.65, 0.2);

	glVertex3f(1.65, 0.65, 0.2);
	glVertex3f(1.65, 0.5, .2);     //3d separation
	glVertex3f(1.7, 0.5, 0.2);
	glVertex3f(1.7, 0.65, 0.2);

	glVertex3f(0.75, 0.65, 0.2);
	glVertex3f(0.75, 0.63, 0.2);        //line strip
	glVertex3f(1.7, 0.63, 0.2);
	glVertex3f(1.7, 0.65, 0.2);

	glVertex3f(0.75, 0.65, 0.6);
	glVertex3f(0.75, 0.63, 0.6);        //line strip
	glVertex3f(1.7, 0.63, 0.6);
	glVertex3f(1.7, 0.65, 0.6);

	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.77, 0.63, 0.6);
	glVertex3f(0.75, 0.5, 0.6);        //quad front window
	glVertex3f(1.2, 0.5, 0.6);
	glVertex3f(1.22, 0.63, 0.6);

	glVertex3f(1.27, 0.63, .6);
	glVertex3f(1.25, 0.5, 0.6);        //quad back window
	glVertex3f(1.65, 0.5, 0.6);
	glVertex3f(1.67, 0.63, 0.6);

	glColor3f(r, g, b);
	glVertex3f(0.7, 0.65, 0.6);
	glVertex3f(0.7, 0.5, .6);       //first separation
	glVertex3f(0.75, 0.5, 0.6);
	glVertex3f(0.77, 0.65, 0.6);

	glVertex3f(1.2, 0.65, 0.6);
	glVertex3f(1.2, 0.5, .6);       //second separation
	glVertex3f(1.25, 0.5, 0.6);
	glVertex3f(1.27, 0.65, 0.6);

	glVertex3f(1.65, 0.65, 0.6);
	glVertex3f(1.65, 0.5, .6);
	glVertex3f(1.7, 0.5, 0.6);
	glVertex3f(1.7, 0.65, 0.6);
	glEnd();

	//**************************************************************
	glBegin(GL_QUADS);

	/* top of cube*/
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.6, 0.5, 0.2);        //quad front window
	glVertex3f(0.7, 0.65, 0.2);
	glVertex3f(0.7, 0.65, 0.6);

	glVertex3f(1.7, 0.65, .6);
	glVertex3f(1.7, 0.65, 0.2);        //quad back window
	glVertex3f(1.8, 0.5, 0.2);
	glVertex3f(1.8, 0.5, 0.6);

	glEnd();

	
	glBegin(GL_TRIANGLES);                /* start drawing the cube.*/

	/* top of cube*/
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.6, 0.5, 0.6);
	glVertex3f(0.7, 0.65, 0.6);       //tri front window
	glVertex3f(0.7, 0.5, 0.6);

	glVertex3f(0.6, 0.5, 0.2);
	glVertex3f(0.7, 0.65, 0.2);       //tri front window
	glVertex3f(0.7, 0.5, 0.2);

	glVertex3f(1.7, 0.65, 0.2);
	glVertex3f(1.8, 0.5, 0.2);       //tri back window
	glVertex3f(1.7, 0.5, 0.2);

	glVertex3f(1.7, 0.65, 0.6);
	glVertex3f(1.8, 0.5, 0.6);       //tri back window
	glVertex3f(1.7, 0.5, 0.6);

	glEnd();


	/*glColor3f(0.7, 0.7, 0.7);*/
	glBegin(GL_LINE_STRIP);
	float angle = 0.0, theta;
	for (theta = 0; theta < 360; theta = theta + 40)
	{
		glVertex3f(0.6, 0.2, 0.62);
		glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (theta = 0; theta < 360; theta = theta + 40)
	{
		glVertex3f(0.6, 0.2, 0.18);
		glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (theta = 0; theta < 360; theta = theta + 40)
	{
		glVertex3f(1.7, 0.2, 0.18);
		glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (theta = 0; theta < 360; theta = theta + 40)
	{
		glVertex3f(1.7, 0.2, 0.62);
		glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
	}
	glEnd();

	// Tires
	glTranslatef(0.6, 0.2, 0.6);
	glColor3f(0, 0, 0);
	glutSolidTorus(0.033, 0.07, 10, 25);

	glTranslatef(0, 0, -0.4);
	glutSolidTorus(0.033, 0.07, 10, 25);

	glTranslatef(1.1, 0, 0);
	glutSolidTorus(0.033, 0.07, 10, 25);

	glTranslatef(0, 0, 0.4);
	glutSolidTorus(0.033, 0.07, 10, 25);

	
	glColor3f(1, 1, 1);
	glLoadIdentity();

}