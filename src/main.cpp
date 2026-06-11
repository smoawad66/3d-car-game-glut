#include <Utils.h>
#include <Car.h>
#include <Coin.h>
#include <Wall.h>
#include <Road.h>
#include <SoundEngine.h>
#include <Menu.h>
#ifdef _WIN32
#include <windows.h>
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define ENTER 13
#define ESC 27
using namespace std;
namespace fs = filesystem;


string assetsPath = (fs::current_path() / "assets").string();
string texturesPath = assetsPath + "/textures/";
string soundsPath = assetsPath + "/sounds/";


float carX = 0.15, carZ = 1;
float cameraX, cameraY, cameraZ;
int mouseLastX, mouseLastY;
bool buffer[256];
unsigned int textures[10];
int collectedCoins;
float coinAngle;



int selectedOption = 0; // 0 = New Game, 1 = Exit
Road *road;
Car *car;
Menu *menu;
SoundEngine *soundEngine;
vector<Coin>coins;
vector<Wall>walls;


// Texture
bool loadTexture(const string& filename, int textureIndex) {
	
	string fullPath = texturesPath + filename;

	int width, height, channels;
	unsigned char* image = stbi_load(fullPath.c_str(), &width, &height, &channels, 4); // 4 = STBI_rgb_alpha

	if (!image) {
		cout << "Failed to load texture: " <<fullPath<< endl;
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



// Coins  & Walls handling
void setCoins(int n = 20) {
	n = max(n, 20);

	int special = 10; 
	n -= special;
	while (n--) {
		Coin coin(random(roadLeft + 0.2, roadRight - 0.2), random(roadStart - 5, roadEnd + 5));
		coins.push_back(coin);
	}
	while (special--) {
		Coin specialCoin(random(roadLeft + 0.2, roadRight - 0.2), random(roadStart - 5, roadEnd + 5), true, false);
		coins.push_back(specialCoin);
	}
}

void setWalls(int n = 20) {
	while (n--) {
		float x1 = random(roadLeft + 0.1, roadRight - 0.1), x2;
		x2 = x1 + 1;
		if (x2 > roadRight) {
			x2 -= 2;
		}
		if (x1 > x2) {
			swap(x1, x2);
		}
		Wall wall(x1, x2, random(roadStart - 10, roadEnd + 5));
		walls.push_back(wall);
	}
}



// Drawing
void drawCoins() {
	glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT | GL_CURRENT_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	for (int i = 0; i < coins.size(); i++) {
		if (coins[i].colided) {
			continue;
		}
		coins[i].draw(coinAngle);
	}
	glPopAttrib();
}

void drawWalls() {
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	float wallHeight = 0.5, wallDepth = 0.3;
	for (int i = 0; i < walls.size(); i++) {
		walls[i].draw(wallHeight, wallDepth);
	}

}


// Collision detection
int coinsCollided() {
	AABB carBox;
	carBox.minX = carX - 0.558f;  
	carBox.maxX = carX - 0.162f;          
	carBox.minZ = carZ + 0.117f;  
	carBox.maxZ = carZ + 1.308f;  

	for (int i = 0; i < coins.size(); i++) {
		if (!coins[i].colided) {			
			AABB coinBox;
			float coinRadius = 0.13f;
			
			coinBox.minX = coins[i].x - coinRadius;
			coinBox.maxX = coins[i].x + coinRadius;
			coinBox.minZ = coins[i].z - coinRadius;
			coinBox.maxZ = coins[i].z + coinRadius;

			if (checkAABBCollision(carBox, coinBox)) {
				string filename = coins[i].special ? "special-coin.wav" : "coin.wav";
				soundEngine->playSound(filename);				
				coins[i].colided = true;
				
				return 1 + (coins[i].special * 9);
			}
		}
	}
	return 0;
}

bool wallsCollided() {
    AABB carBox;
	carBox.minX = carX - 0.558f;  
	carBox.maxX = carX - 0.162f;
	carBox.minZ = carZ + 0.117f;  
	carBox.maxZ = carZ + 1.308f;

    for (int i = 0; i < walls.size(); i++) {
        AABB wallBox;
        
        wallBox.minX = min(walls[i].x1, walls[i].x2);
        wallBox.maxX = max(walls[i].x1, walls[i].x2);
        
        float wallDepth = 0.3f;
        wallBox.minZ = walls[i].z - wallDepth;
        wallBox.maxZ = walls[i].z;

        if (checkAABBCollision(carBox, wallBox)) {
            return true;
        }
    }
    
    return false;
}



void roadEndReached() {
	if (carZ < roadEnd + 1) {
		gameState = WIN;
	}	
}	



// Camera
void defaultCamera() { 
	cameraX = carX - 0.4, cameraY = 1.5, cameraZ = carZ + 2; 
}


void resetGame() {
	carX = 0.15;
	carZ = 1;
	collectedCoins = 0;
	coinAngle = 0;

	coins.clear();
	walls.clear();

	setCoins(100);
	setWalls(40);

	defaultCamera();
}	


void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameState == MENU) {
		menu->draw(selectedOption);
		glutSwapBuffers();
		return;
	}	
	
	if (gameState == GAME_OVER) {
		soundEngine->playSound("car-crash.wav");
		// soundEngine->playSound("gameover.wav");
		delay(4.5);
		menu->draw(selectedOption);
		gameState = MENU;
		glutSwapBuffers();
		return;
	}	
	
	if (gameState == WIN) {
		soundEngine->playSound("celebration.wav");
		delay(4.2);
		menu->draw(selectedOption);
		gameState = MENU;
		glutSwapBuffers();
		return;
	}	

	glLoadIdentity();

	gluLookAt(
		cameraX, cameraY, cameraZ + 2,
		carX, 0, carZ,
		0, 1, 0
	);
	
	road->draw(textures);

	drawWalls();
	glDisable(GL_TEXTURE_2D);
	drawCoins();

	collectedCoins += coinsCollided();

	float rectWidth = 250.0f;
	float rectHeight = 60.0f;

	float xPos = screenWidth - rectWidth - 100.0f;
	float yPos = screenHeight - rectHeight - 100.0f;
	overlay(rectWidth, rectHeight, xPos, yPos, "Score: " + to_string(collectedCoins), 0.7f);

	if (wallsCollided()) {
		gameState = GAME_OVER;
		float rectWidth = 300.0f;
		float rectHeight = 80.0f;

		float xPos = int(screenWidth / 2);
		float yPos = int(screenHeight / 2);

		overlay(rectWidth, rectHeight, xPos, yPos, "Game Over!", 0.7f);
	}	

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glColor3f(1, 1, 1);
    glPushMatrix();

	glTranslatef(carX, -0.088, carZ);
	car->draw();
    glPopMatrix();

	glutSwapBuffers();
}	



void exitGame() {
	delete soundEngine;
	delete car;
	delete road;
	delete menu;
	exit(0);
}


// Keyboard handling
void keyboardUp(unsigned char key, int, int) { // reset the buffer of a key if it is released
	buffer[tolower(key)] = false;
}

void keyboard(unsigned char key, int, int) {// set the buffer of a key if it is pressed
	if (key == ESC) {
		if(gameState == PLAYING) {
			gameState = MENU;
		}
		else {
			soundEngine->playSound("game-exit.wav");
			delay(0.6);
			exitGame();
		}
	}
	
	// Menu input
    if (gameState != PLAYING) {
		
		if (key == 'w' || key == 's') {
			selectedOption = (selectedOption + 1) % 2;
			soundEngine->playSound("menu-selection.wav");
		}
		
        if (key == ENTER) {
            if (selectedOption == 0) {
				resetGame();
                gameState = PLAYING;
				soundEngine->playSound("game-start.wav");
            }
            else {
				soundEngine->playSound("game-exit.wav");
				delay(0.6);
                exitGame();
            }
        }

        return;
    }

	unsigned char k = tolower(key);
	buffer[k] = true;
}

void movement() { // If any key is pressed, an action occurs
	float actStep;
	if (buffer['w']) { // move forward
		actStep = carStep;
		if (carZ - actStep >= roadEnd) {
			carZ -= actStep;
			cameraZ -= actStep;
		}
	}
	

	if (buffer['s']) { // move backward
		actStep = carStep / 2;
		if (carZ + actStep <= roadStart - 5) {
			carZ += actStep;
			cameraZ += actStep;
		}
	}

	if (buffer['d']) { // move right
		actStep = carStep / 6;
		if (carX + actStep <= roadRight + 0.11) {
			carX += actStep;
			cameraX += actStep;
		}
	}

	if (buffer['a']) { // move left
		actStep = carStep / 6;
		if (carX - actStep >= roadLeft + 0.7) {
			carX -= actStep;
			cameraX -= actStep;
		}
		
	}

	if (buffer['+']) { // zoom in
		if (cameraZ - 0.2 > roadEnd) {
			cameraZ -= 0.2;
		}
	}

	else if (buffer['-']) { // zoom out
		if (cameraZ + 0.2 < roadStart) {
			cameraZ += 0.2;
		}
	}

}

void specialKeys(int key, int, int) {
	
	if (gameState == MENU) {
        if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) {
			selectedOption = (selectedOption + 1) % 2;
			soundEngine->playSound("menu-selection.wav");
        }

    } else {
		if (key == GLUT_KEY_HOME) {
			defaultCamera();
		}

	}

}



// Mouse handling
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseLastX = x;
		mouseLastY = y;
	}
}

void motion(int x, int y) {
	int dx = x - mouseLastX;
	int dy = y - mouseLastY;

	float tx = cameraX - dx * 0.02;
	float ty = cameraY + dy * 0.02;

	if (tx <= roadRight-0.1 && tx >= roadLeft+0.1) {
		cameraX = tx;
	}
	if (ty <= 3 && ty >= 0.1) {
		cameraY = ty;
	}


	mouseLastX = x;
	mouseLastY = y;
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
	
	road = new Road(roadRight, roadLeft, roadStart, roadEnd);
	car = new Car(0.0f, 1.0f, 0.5f);
	menu = new Menu(800, 600);

	setCoins(100);
	setWalls(40);

	glClearColor(0,0,0, 1.0f);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	initLighting();

	loadTexture("road.bmp", 1);
	loadTexture("summer-scene.bmp", 2);
	loadTexture("sky.bmp", 3);
	loadTexture("obstacle.bmp", 4);
	loadTexture("win2.bmp", 5);

	soundEngine = new SoundEngine(soundsPath);
	soundEngine->initAudio();

	glutFullScreen();

#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), 0);
#endif

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

	if (gameState == PLAYING) {
        movement();
        roadEndReached();
    }

	glEnable(GL_TEXTURE_2D);
	glutPostRedisplay();

	glutTimerFunc(1000/frameRate, timer, 0);
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutCreateWindow("Car Game");
	
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

	// system("pause");
	return 0;
}