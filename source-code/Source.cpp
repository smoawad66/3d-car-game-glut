#include <bits/stdc++.h>
#include <Windows.h>
#include <gl/glut.h>
#include "Car.h"
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION
#include <gl/stb_image.h>
#include <irrKlang.h>
#define ESC 27
using namespace std;
using namespace irrklang;

ISoundEngine* soundEngine = createIrrKlangDevice();

string projectPath = "C:\\Users\\Elsayed\\source\\repos\\GraphicsProject\\";
string texturesPath = projectPath + "textures\\";
string soundsPath = projectPath + "sounds\\";

int screenWidth, screenHeight;
float aspect;
float carX = 0.15, carZ = 1, carSpeed = 0.4;
float cameraX, cameraY, cameraZ;
float roadRight = 2, roadLeft = -2.5, roadStart = 7, roadEnd = -500;
int mouselastX, mouselastY;
bool buffer[256];
unsigned int textures[10];
int collectedCoins;
bool win, gameover;
float coinAngle;

struct Coin {
	float x, z;
	bool colided = false, special = false;
};

struct Obstacle {
	float x1, x2, z;
};

vector<Coin>coins;
vector<Obstacle>obstacles;

void delay(float sec) {
	auto start = chrono::steady_clock::now();
	chrono::milliseconds duration((int)(1000 * sec));
	while (chrono::steady_clock::now() - start < duration);
}


// Texture
bool loadTexture(const string& filename, int textureIndex) {
	
	int width, height, channels;
	unsigned char* image = stbi_load((texturesPath + filename).c_str(), &width, &height, &channels, 4); // 4 = STBI_rgb_alpha

	if (!image) {
		cout << "Failed to load texture: " << endl;
		return false;
	}

	glGenTextures(1, &textures[textureIndex]);
	glBindTexture(GL_TEXTURE_2D, textures[textureIndex]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(image);

	return true;
}



// Coins  & Obstacles handling
float random(float min = 0, float max = RAND_MAX) {
	if (min > max) swap(max, min);
	return min + float (rand()) / (float (RAND_MAX / (max - min)));
}

void setCoins(int n = 20) {
	if (n < 20) { n = 20; }
	int special = 10; n -= special;
	while (n--) {
		coins.push_back({ random(roadLeft + 0.2, roadRight - 0.2), random(roadStart - 5, roadEnd + 5)});
	}
	while (special--) {
		coins.push_back({ random(roadLeft + 0.2, roadRight - 0.2), random(roadStart - 5, roadEnd + 5), false, true});
	}
}

void setObstacles(int n = 20) {
	while (n--) {
		float x1 = random(roadLeft + 0.1, roadRight - 0.1), x2;
		x2 = x1 + 1;
		if (x2 > roadRight) {
			x2 -= 2;
		}
		if (x1 > x2) {
			swap(x1, x2);
		}
		obstacles.push_back({ x1, x2, random(roadStart - 10, roadEnd + 5) });
	}
}



// Collision handling
float calculateDistance(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrtf(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

bool intersect(float a1, float b1, float a2, float b2) {

	/*
		a1---------------b1 
				  a2---------b2 
	*/

	if (a1 > b2 || a2 > b1) {
		return false;
	}
	else {
		return true;
	}
}

int coinsCollision() {
	for (int i = 0; i < coins.size(); i++) {
		if (!coins[i].colided) {
			float coinCenterX = coins[i].x, coinCenterZ = coins[i].z, coinRadius = 0.13;
			float X[2] = { 0, 0.4};
			for (int j = 0; j < 2; j++) {
				float distance = calculateDistance(carX - X[j], 0, carZ, coinCenterX, 0, coinCenterZ);
				float distance2 = calculateDistance(carX - X[j], 0, carZ + 0.4, coinCenterX, 0, coinCenterZ);
				float distance3 = calculateDistance(carX - X[j], 0, carZ + 0.63, coinCenterX, 0, coinCenterZ);

				if (distance <= X[j] + coinRadius - 0.07 || distance2 <= X[j] + coinRadius - 0.06 || distance3 <= X[j] + coinRadius-0.05) {
					if (soundEngine) {
						string filename = coins[i].special ? "specialCoin.wav" : "coin.wav";
						 soundEngine->play2D((soundsPath + filename).c_str(), false);
					}
					coins[i].colided = true;
					return 1 + coins[i].special * 9;
				}
			}
		}
	}
	return 0;
}

bool obstaclesCollision() {
	for (int i = 0; i < obstacles.size(); i++) {
		float obstacleRight = obstacles[i].x1, obstacleLeft = obstacles[i].x2, obstacleZ = obstacles[i].z;
		float carRight = carX, carLeft = carX - 0.54;

		if (obstacleLeft > obstacleRight) {
			swap(obstacleLeft, obstacleRight);
		}
		obstacleZ -= 0.3;
		if (abs(obstacleZ - carZ) <= 0.80001 && intersect(obstacleLeft, obstacleRight, carLeft, carRight)) {
			return true;
		}
	}
	return false;
}



// Drawing
void drawCoins() {
	glEnable(GL_LIGHTING);      // Enable lighting
	glEnable(GL_LIGHT0);
	for (int i = 0; i < coins.size(); i++) {
		if (coins[i].colided) {
			continue;
		}
		glPushMatrix();

		glTranslatef(coins[i].x, 0.3, coins[i].z);
		glRotatef(coinAngle, 0, 1, 0);

		if (coins[i].special) {
			GLfloat mat_ambient[] = { 0.8f, 0.2f, 0.2f, 1.0f };
			GLfloat mat_diffuse[] = { 0.8f, 0.2f, 0.2f, 1.0f };
			GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat mat_shininess[] = { 50.0f };

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

			glColor3f(0.8, 0.2, 0.2);
			glutSolidTorus(0.07, 0.13, 70, 70);
		}
		else {

			GLfloat torusAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
			GLfloat torusDiffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			GLfloat torusSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat torusShininess[] = { 50.0f };

			glMaterialfv(GL_FRONT, GL_AMBIENT, torusAmbient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, torusDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, torusSpecular);
			glMaterialfv(GL_FRONT, GL_SHININESS, torusShininess);

			glColor3f(1, 1, 0);
			glutSolidTorus(0.059, 0.13, 50, 50);
		}

		coinAngle += coinAngle < 360 ? 0.1 : -360;

		glPopMatrix();

	}
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

void drawObstacles() {
	float blockSize = 0.5;
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	for (int i = 0; i < obstacles.size(); i++) {
		float x1 = obstacles[i].x1, x2 = obstacles[i].x2, z = obstacles[i].z; x1 -= 0.19;
		glBegin(GL_QUADS);

		//back
		glTexCoord2f(0, 0); glVertex3f(x1, 0, z);
		glTexCoord2f(1, 0); glVertex3f(x2, 0, z);
		glTexCoord2f(1, 1); glVertex3f(x2, blockSize, z);
		glTexCoord2f(0, 1); glVertex3f(x1, blockSize, z);
		float wallDepth = 0.3;
		//front
		glTexCoord2f(0, 0); glVertex3f(x1, 0, z-wallDepth);
		glTexCoord2f(1, 0); glVertex3f(x2, 0, z-wallDepth);
		glTexCoord2f(1, 1); glVertex3f(x2, blockSize, z-wallDepth);
		glTexCoord2f(0, 1); glVertex3f(x1, blockSize, z-wallDepth);
		
		//left
		glTexCoord2f(1, 1); glVertex3f(x1, 0, z);
		glTexCoord2f(1, 0); glVertex3f(x1, blockSize, z);
		glTexCoord2f(0, 0); glVertex3f(x1, blockSize, z-wallDepth);
		glTexCoord2f(0, 1); glVertex3f(x1, 0, z-wallDepth);
		
		//right
		glTexCoord2f(0, 0); glVertex3f(x2, 0, z);
		glTexCoord2f(0, 1); glVertex3f(x2, blockSize, z);
		glTexCoord2f(1, 1); glVertex3f(x2, blockSize, z-wallDepth);
		glTexCoord2f(1, 0); glVertex3f(x2, 0, z-wallDepth);

		
		//top
		glTexCoord2f(1, 1); glVertex3f(x2, blockSize, z - wallDepth);
		glTexCoord2f(1, 0); glVertex3f(x2, blockSize, z);
		glTexCoord2f(0, 0); glVertex3f(x1, blockSize, z);
		glTexCoord2f(0, 1); glVertex3f(x1, blockSize, z-wallDepth);

		glEnd();
	}

}

void drawRoad() {

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
	float textXPos = xPos + rectWidth / 2 - rectWidth / 7, textYPos = yPos + rectHeight / 2 - 10;
	glRasterPos2f(textXPos, textYPos);
	for (char c : text) { 
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void roadEndReached() {
	if (carZ < roadEnd + 1) {
		win = true;
	}
}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ + 2, carX, 0, carZ, 0, 1, 0);
	
	drawRoad();
	drawObstacles();
	glDisable(GL_TEXTURE_2D);

	drawCoins();

	collectedCoins += coinsCollision();
	overlay(250, 60, 1186, 704, "Score: " + to_string(collectedCoins), 0.7);

	if (obstaclesCollision()) {
		overlay(330, 100, 336, 564, "Game Over!", 0.8);
		gameover = true;
	}
	glColor3f(1, 1, 1);
    glPushMatrix();

	glTranslatef(carX, -0.088, carZ);
	(new Car)->draw(0.0f, 1.0f, 0.5f);
    glPopMatrix();

	glutSwapBuffers();
}



// Camera
void defaultCamera() { cameraX = carX -0.45, cameraY = 1.3, cameraZ = carZ + 1.5; }



// Keyboard handling
void keyboardUp(unsigned char key, int, int) { // reset the buffer of a key if it is released
	buffer[tolower(key)] = false;
}

void keyboard(unsigned char key, int, int) {// set the buffer of a key if it is pressed
	if (key == ESC) {
		exit(0); 
	}
	unsigned char k = tolower(key);
	buffer[k] = true;
}

void movement() { // if any key is pressed, an action occurs
	float spd;
	if (buffer['w']) { // move forward
		spd = carSpeed;
		if (carZ - spd >= roadEnd) {
			carZ -= spd;
			cameraZ -= spd;
		}
	}
	

	if (buffer['s']) { // move backward
		spd = carSpeed / 2;
		if (carZ + spd <= roadStart - 5) {
			carZ += spd;
			cameraZ += spd;
		}
	}

	if (buffer['d']) { // move right
		spd = carSpeed / 6;
		if (carX + spd <= roadRight + 0.11) {
			carX += spd;
			cameraX += spd;
		}
	}

	if (buffer['a']) { // move left
		spd = carSpeed / 6;
		if (carX - spd >= roadLeft + 0.7) {
			carX -= spd;
			cameraX -= spd;
		}
		
	}

	if (buffer['+']) {
		if (cameraZ - 0.2 > roadEnd) {
			cameraZ -= 0.2;
		}
	}

	else if (buffer['-']) {
		if (cameraZ + 0.2 < roadStart) {
			cameraZ += 0.2;
		}
	}

}

void specialKeys(int key, int, int) {
	
	if (key == GLUT_KEY_HOME) {
		defaultCamera();
	}
}




// Mouse handling
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouselastX = x;
		mouselastY = y;
	}
}

void motion(int x, int y) {
	int dx = x - mouselastX;
	int dy = y - mouselastY;

	float tx = cameraX - dx * 0.02;
	float ty = cameraY + dy * 0.02;

	if (tx <= roadRight-0.1 && tx >= roadLeft+0.1) {
		cameraX = tx;
	}
	if (ty <= 3 && ty >= 0.1) {
		cameraY = ty;
	}


	mouselastX = x;
	mouselastY = y;
}



// Lighting
void initLighting() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPosition[] = { 0.2, -0.8, 0.3, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}



// Basic functions
void init() {
	
	defaultCamera();

	srand(time(0));
	setCoins(100);
	setObstacles(40);

	glClearColor(0,0,0, 1.0f);
	glEnable(GL_DEPTH_TEST);

	initLighting();

	loadTexture("road.bmp", 1);
	loadTexture("summer-scene.jpg", 2);
	loadTexture("sky.jpg", 3);
	loadTexture("obstacle.jpg", 4);
	loadTexture("win2.jpg", 5);

	glutFullScreen();
	ShowWindow(GetConsoleWindow(), 0);
}

void reshape(int width, int height) {
	
	if(height == 0) height=1;
	aspect = float(width) / height;

	screenWidth = width;
	screenHeight = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 200);
	glMatrixMode(GL_MODELVIEW);

}

void timer(int) {

	movement();
	roadEndReached();
	glEnable(GL_TEXTURE_2D);
	glutPostRedisplay();

	if (gameover) {
		if (soundEngine) {
			soundEngine->play2D((soundsPath + "gameover.wav").c_str(), false);
		}
		delay(6);
		exit(0);
	}
	
	if (win) {
		if (soundEngine) {
			soundEngine->play2D((soundsPath + "celebration.wav").c_str(), false);
		}
		delay(4.2);
		exit(0);
	}

	glutTimerFunc(5, timer, 0);
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutCreateWindow("Car driving");
	
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutSpecialFunc(specialKeys);

	glutMainLoop();

	if (soundEngine) {
		soundEngine->drop();
	}

	system("pause");
	return 0;
}