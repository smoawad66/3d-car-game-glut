#include <Menu.h>
#include <Utils.h>
#include <GL/glut.h>

Menu::Menu(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
};
   
void Menu::draw(int selectedOption) {

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST); 
    glDisable(GL_LIGHTING);

    // Draw the sky background texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    glColor3f(1.0f, 1.0f, 1.0f); 

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 0);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(windowWidth, 0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(windowWidth, windowHeight);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0, windowHeight);
    glEnd();

    glDisable(GL_TEXTURE_2D); 

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float centerX = windowWidth / 2.0f;
	GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float realPixelWidth = (float)viewport[2]; 
    float scaleX = (float)windowWidth / realPixelWidth;

	
    // Draw Title Box and Text
    float titleY = windowHeight * 0.7f;
    float titleBoxWidth = 240.0f;
    float titleBoxHeight = 50.0f;
    float titleBoxX = centerX - (titleBoxWidth / 2.0f);
    // Draw Title Box
    glColor4f(1.0f, 1.0f, 1.0f, 0.7f); 
    glBegin(GL_QUADS);
        glVertex2f(titleBoxX, titleY);
        glVertex2f(titleBoxX + titleBoxWidth, titleY);
        glVertex2f(titleBoxX + titleBoxWidth, titleY + titleBoxHeight);
        glVertex2f(titleBoxX, titleY + titleBoxHeight);
    glEnd();

    // Draw Title Text
    glColor3f(0.0f, 0.0f, 0.0f); 
    const char* titleText = "CAR GAME";
    int rawTitleWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)titleText);
    float adjustedTitleWidth = rawTitleWidth * scaleX; 
    float titleTextY = titleY + (titleBoxHeight / 2.0f) - (24.0f * 0.35f);
    renderBitmapString(centerX - (adjustedTitleWidth / 2.0f), titleTextY, GLUT_BITMAP_TIMES_ROMAN_24, titleText);



    float btnWidth = 160.0f;
    float btnHeight = 40.0f;
    float btnX = centerX - (btnWidth / 2.0f);


    // Draw "New Game" Box and Text
    float newGameY = windowHeight * 0.5f;
    
    if (selectedOption == 0) {
        glColor4f(1.0f, 1.0f, 0.0f, 0.8f); // Yellow
    } else {
        glColor4f(0.7f, 0.7f, 0.7f, 0.6f); // Light Gray
    }
    
    // Draw Box
    glBegin(GL_QUADS);
        glVertex2f(btnX, newGameY); 
        glVertex2f(btnX + btnWidth, newGameY); 
        glVertex2f(btnX + btnWidth, newGameY + btnHeight); 
        glVertex2f(btnX, newGameY + btnHeight); 
    glEnd();

    // Draw "New Game" Text
    glColor3f(0.0f, 0.0f, 0.0f);
    const char* newGameText = "New Game";
    int rawNewGameWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)newGameText);
    float adjustedNewGameWidth = rawNewGameWidth * scaleX;
    float newGameTextY = newGameY + (btnHeight / 2.0f) - (18.0f * 0.35f);
    renderBitmapString(centerX - (adjustedNewGameWidth / 2.0f), newGameTextY, GLUT_BITMAP_HELVETICA_18, newGameText);



    // Draw "Exit" Box and Text
    float exitY = windowHeight * 0.4f;
    
    if (selectedOption == 1) {
        glColor4f(1.0f, 1.0f, 0.0f, 0.8f); // Yellow
    } else {
        glColor4f(0.7f, 0.7f, 0.7f, 0.6f); // Light Gray
    }
    
    // Draw Box
    glBegin(GL_QUADS);
        glVertex2f(btnX, exitY); 
        glVertex2f(btnX + btnWidth, exitY); 
        glVertex2f(btnX + btnWidth, exitY + btnHeight); 
        glVertex2f(btnX, exitY + btnHeight); 
    glEnd();

    // Draw "Exit" Text
    glColor3f(0.0f, 0.0f, 0.0f);
    const char* exitText = "Exit";    
    int rawExitWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)exitText);
    float adjustedExitWidth = rawExitWidth * scaleX;
    float exitTextY = exitY + (btnHeight / 2.0f) - (18.0f * 0.35f);
    renderBitmapString(centerX - (adjustedExitWidth / 2.0f), exitTextY, GLUT_BITMAP_HELVETICA_18, exitText);


    glDisable(GL_BLEND); 
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

}