#include "headers/Main2D.h"

using namespace std;

/**
* Facilitates calls to the other render functions and draw to correct areas of screen
*/
void renderMain() {
    // Clear screen before re-rendering
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw lines between different areas
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, 0, window_height, 0, 1);
    glPointSize(10);
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(button_width, 0);
        glVertex2f(button_width, window_height);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(currentStartX, currentStartY);
        glVertex2f(window_width, currentStartY);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(previousStartX, previousStartY);
        glVertex2f(previousStartX, previousStartY + previousHeight);
    glEnd();

    // Draw buttons
    glViewport(0, 0, button_width, window_height);
    renderButtons(false);

    // Draw current data points
    glViewport(currentStartX, currentStartY, currentWidth, currentHeight);
    renderCurrent(false);

    // Draw previous data points
    glViewport(previousStartX, previousStartY, previousWidth, previousHeight);
    renderPrevious(false);

    // Draw basis function interaction
    glViewport(currentStartX, 0, currentWidth+previousWidth, currentStartY);
    renderBases(false);
}

/**
* Renders the current datastructure
*/
void renderCurrent(bool coloured) {
    // Set up transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(currentTransX, currentTransY, 0.0f);
    glRotatef(currentAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(currentAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(currentAngleZ, 0.0f, 0.0f, 1.0f);
    glScalef(currentZoom, currentZoom, currentZoom);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -10, 10);

    // Set up variables
    double quadSize;
    double xOffset, yOffset;
    if (currentData.size() > 0) {
        if (currentData[0].size() > 0) {
            quadSize = min(1.6/currentData.size(), 1.6/currentData[0].size());
        } else {
            return;
        }
    } else {
        return;
    }
    xOffset = 1 - (2 - quadSize*currentData.size())/2.0;
    yOffset = 1 - (2 - quadSize*currentData[0].size())/2.0;

    for (int i = 0; i < currentData.size(); i++) {
        for(int j = 0; j < currentData[i].size(); j++) {
            // Draw quad outlines
            if (!coloured) {
                glColor3f(0.0f, 0.0f, 0.0f);
                if (currentData[i][j].enableHeight) {
                    glBegin(GL_LINE_STRIP);

                        // Draw the initial quad
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);
                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);

                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);

                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                    glEnd();
                }
            }

            // Choose the correct colour whether rendering or using for selecting an item
            if (coloured) {
                glColor3f(currentData[i][j].renderColR, currentData[i][j].renderColG, currentData[i][j].renderColB);
            } else {
                glColor3f(currentData[i][j].currentColR, currentData[i][j].currentColG, currentData[i][j].currentColB);
            }


            // Fill quads
            glBegin(GL_QUADS);

                // Draw the initial quad
                glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);
                glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);
                glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);

                if (currentData[i][j].enableHeight) {
                    glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);

                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);
                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);

                    glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, currentData[i][j].value);
                }
            glEnd();
        }
    }
}

void renderPrevious(bool coloured) {
    // Set up transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(currentTransX, currentTransY, 0.0f);
    glRotatef(currentAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(currentAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(currentAngleZ, 0.0f, 0.0f, 1.0f);
    glScalef(currentZoom, currentZoom, currentZoom);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -10, 10);

    // Set up variables
    double quadSize;
    double xOffset, yOffset;
    if (previousData.size() > 0) {
        if (previousData[0].size() > 0) {
            quadSize = min(1.6/previousData.size(), 1.6/previousData[0].size());
        } else {
            return;
        }
    } else {
        return;
    }
    xOffset = 1 - (2 - quadSize*previousData.size())/2.0;
    yOffset = 1 - (2 - quadSize*previousData[0].size())/2.0;

    for (int i = 0; i < previousData.size(); i++) {
        for(int j = 0; j < previousData[i].size(); j++) {
            // Draw quad outlines
            if (!coloured) {
                glColor3f(0.0f, 0.0f, 0.0f);
                if (previousData[i][j].enableHeight) {
                    glBegin(GL_LINE_STRIP);

                        // Draw the initial quad
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);
                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);

                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);

                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                        glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                    glEnd();
                }
            }

            // Choose the correct colour whether rendering or using for selecting an item
            if (coloured) {
                glColor3f(previousData[i][j].renderColR, previousData[i][j].renderColG, previousData[i][j].renderColB);
            } else {
                glColor3f(previousData[i][j].currentColR, previousData[i][j].currentColG, previousData[i][j].currentColB);
            }


            // Fill quads
            glBegin(GL_QUADS);

                // Draw the initial quad
                glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);
                glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                if (previousData[i][j].enableHeight) {
                    glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                    glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);

                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);

                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, 0);
                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, 0);

                    glVertex3f(i*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-j*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f((i+1)*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);
                    glVertex3f(i*quadSize-xOffset, 1.5-(j+1)*quadSize-yOffset, previousData[i][j].value);

                }
            glEnd();
        }
    }
}

/**
* Draws the buttons to the window
*/
void renderButtons(bool coloured) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, button_width, 0, window_height, 0, 1);
    int numButtons = 13;
    double button_size = (1.0*window_height)/numButtons;
    int count = 1;

    // Add buttons to add and delete rows/columns
    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Add row";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/4, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Add col";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/4, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Delete row";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/6, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Delete col";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/6, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    // Choose order/degree of decomposition
    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Haar";
        char string2[64] = "Chaikin";
        char string3[64] = "Cubic";
        int len;
        switch (decompDegree) {
            case 2:
                    // Write to the screen
                    glColor3f(1.0f, 1.0f, 1.0f);
                    len = (int) strlen(string2);
                    glRasterPos2f(button_width/3, window_height - button_size*(count-1) - (button_size/2));
                    for (int i = 0; i < len; i++) {
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string2[i]);
                    }
                    break;
            case 3:
                    // Write to the screen
                    glColor3f(1.0f, 1.0f, 1.0f);
                    len = (int) strlen(string3);
                    glRasterPos2f(button_width/3, window_height - button_size*(count-1) - (button_size/2));
                    for (int i = 0; i < len; i++) {
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string3[i]);
                    }
                    break;
            default:
                    // Write to the screen
                    glColor3f(1.0f, 1.0f, 1.0f);
                    len = (int) strlen(string);
                    glRasterPos2f(button_width/3, window_height - button_size*(count-1) - (button_size/2));
                    for (int i = 0; i < len; i++) {
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
                    }
                    break;
        };
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    // Add buttons to decompose
    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Decomp. row full";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/20.0, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Decomp. col full";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/20.0, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Decomp row part";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/20.0, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Decomp col part";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/20.0, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    // Add buttons to reconstruct
    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Reconstruct";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/6, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    // Add button to clear everything
    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Lena";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/3, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    // Add button to reset camera
    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Reset camera";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/10.0, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;

    // Add button to clear everything
    if (!coloured) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        char string[64] = "Clear";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/4, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    } else {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    }
    count++;
}

void renderBases(bool coloured) {
    // Initial setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1, 1);

    if (currentData.size() > 0 && currentData[0].size() > 0 && !currentData[0][0].enableHeight) {
        // Find higest values of histogram
        int maxC = 0;
        int maxP = 0;
        for (int i = 0; i < 256; i++) {
            maxC = max(maxC, countCurrent[i]);
            maxC = max(maxC, countPrevious[i]);
        }

        // Draw the histogram
        for (int i = 0; i < 256; i++) {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_QUADS);
                glVertex2f(-1.25 + i*(1.0/256), -1.25);
                glVertex2f(-1.25 + (i+1)*(1.0/256), -1.25);
                glVertex2f(-1.25 + (i+1)*(1.0/256), -1.25 + (countCurrent[i]*2.5)/maxC);
                glVertex2f(-1.25 + i*(1.0/256), -1.25 + (countCurrent[i]*2.5)/maxC);
            glEnd();
        }

        // Draw the histogram
        for (int i = 0; i < 256; i++) {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_QUADS);
                glVertex2f(0.25 + i*(1.0/256), -1.25);
                glVertex2f(0.25 + (i+1)*(1.0/256), -1.25);
                glVertex2f(0.25 + (i+1)*(1.0/256), -1.25 + (countPrevious[i]*2.5)/maxC);
                glVertex2f(0.25 + i*(1.0/256), -1.25 + (countPrevious[i]*2.5)/maxC);
            glEnd();
        }

        return;
        
    } else if (currentSelectedX < 0 || currentSelectedY < 0) {
        return;
    }

    glColor3f(1, 1, 1);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-1.4, 0);
        glVertex2f(1.4, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex2f(0, -1);
        glVertex2f(0, 1);
    glEnd();

    // Compute the width of the bases
    double width = 1.0/previousBasesX.size();
    double height;
    double xInit1 = 0.25;
    double xInit2 = -1.25;

    // Set up variables for the filters
    bool negs = false;
    double totalNeg = 0;
    int pos;
    vector< vector<double> > filt;
    if (lastOpp.decRec == 'D') {
        pos = 0;
        if (lastOpp.rowCol == 'R') {
            if (currentSelectedY >= lastOpp.size/2) {
                filt = getBFilter(lastOpp.degree);
            } else {
                filt = getAFilter(lastOpp.degree);
            }
        } else if (lastOpp.rowCol == 'C') {
            if (currentSelectedX >= lastOpp.size/2) {
                filt = getBFilter(lastOpp.degree);
            } else {
                filt = getAFilter(lastOpp.degree);
            }
        }
    } else if (lastOpp.decRec == 'R') {
        filt = getReconFilter(lastOpp.degree);
        if (lastOpp.rowCol == 'C') {
            pos = currentSelectedX%filt.size();
        } else if (lastOpp.rowCol == 'R') {
            pos = currentSelectedY%filt.size();
        }
    }

    // Draw the basis functions
    for (int i = 0; i < previousBasesX.size(); i++) {
        height = previousData[previousBasesX[i]][previousBasesY[i]].value * filt[pos][i];
        //pos = (pos+1)%filt.size();
        if (height < 0) {
            negs = true;
            totalNeg += height;
        }

        // Draw the partial value outline
        glColor3f(1, 1, 1);
        glLineWidth(2);
        glBegin(GL_LINE_STRIP);
            glVertex2f(xInit1 + width*i, 0);
            glVertex2f(xInit1 + width*(i+1), 0);
            glVertex2f(xInit1 + width*(i+1), height);
            glVertex2f(xInit1 + width*i, height);
            glVertex2f(xInit1 + width*i, 0);
        glEnd();

        // Draw the basis functions
        glColor3f(presetR[i], presetG[i], presetB[i]);
        glBegin(GL_QUADS);
            glVertex2f(xInit1 + width*i, 0);
            glVertex2f(xInit1 + width*(i+1), 0);
            glVertex2f(xInit1 + width*(i+1), previousData[previousBasesX[i]][previousBasesY[i]].value);
            glVertex2f(xInit1 + width*i, previousData[previousBasesX[i]][previousBasesY[i]].value);
        glEnd();
    }
    glLineWidth(1);

    // Draw the selected value
    double yBot = 0;
    double yTop = currentData[currentSelectedX][currentSelectedY].value - totalNeg;

    // Contains negative pieces
    if (negs) {
        // Draw stipple line
        glLineStipple(1, 0xEEEE);
        glEnable(GL_LINE_STIPPLE);
        glColor3f(0.9, 0.9, 0.9);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(xInit2 + 0.025, currentData[currentSelectedX][currentSelectedY].value);
            glVertex2f(xInit2 + 0.975, currentData[currentSelectedX][currentSelectedY].value);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1);

        glColor3f(1, 1, 0);
        glBegin(GL_QUADS);
            glVertex2f(xInit2 + 0.025, 0);
            glVertex2f(xInit2 + 0.325, 0);
            glVertex2f(xInit2 + 0.325, currentData[currentSelectedX][currentSelectedY].value);
            glVertex2f(xInit2 + 0.025, currentData[currentSelectedX][currentSelectedY].value);
        glEnd();

        //pos = 0;
        for (int i = 0; i < previousBasesX.size(); i++) {
            height = previousData[previousBasesX[i]][previousBasesY[i]].value * filt[pos][i];
            //pos = (pos+1)%filt.size();
            if (height >= 0) {
                // Draw the positive pieces
                glColor3f(presetR[i], presetG[i], presetB[i]);
                glBegin(GL_QUADS);
                    glVertex2f(xInit2 + 0.35, yBot);
                    glVertex2f(xInit2 + 0.65, yBot);
                    glVertex2f(xInit2 + 0.65, height + yBot);
                    glVertex2f(xInit2 + 0.35, height + yBot);
                glEnd();
                yBot += height;
            } else {
                // Draw the negative pieces
                glColor3f(presetR[i], presetG[i], presetB[i]);
                glBegin(GL_QUADS);
                    glVertex2f(xInit2 + 0.675, yTop);
                    glVertex2f(xInit2 + 0.975, yTop);
                    glVertex2f(xInit2 + 0.975, height + yTop);
                    glVertex2f(xInit2 + 0.675, height + yTop);
                glEnd();
                yTop += height;
            }
        }

    // Contains only positive pieces
    } else {
        // Draw stipple line
        glLineStipple(1, 0xEEEE);
        glEnable(GL_LINE_STIPPLE);
        glColor3f(0.9, 0.9, 0.9);
        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(xInit2, currentData[currentSelectedX][currentSelectedY].value);
            glVertex2f(xInit2 + 0.95, currentData[currentSelectedX][currentSelectedY].value);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1);

        glColor3f(1, 1, 0);
        glBegin(GL_QUADS);
            glVertex2f(xInit2, 0);
            glVertex2f(xInit2 + 0.45, 0);
            glVertex2f(xInit2 + 0.45, currentData[currentSelectedX][currentSelectedY].value);
            glVertex2f(xInit2, currentData[currentSelectedX][currentSelectedY].value);
        glEnd();

        // Draw the basis functions
        //pos = 0;
        for (int i = 0; i < previousBasesX.size(); i++) {
            height = previousData[previousBasesX[i]][previousBasesY[i]].value * filt[pos][i];
            //pos = (pos+1)%filt.size();
            glColor3f(presetR[i], presetG[i], presetB[i]);
            glBegin(GL_QUADS);
                glVertex2f(xInit2 + 0.5, yBot);
                glVertex2f(xInit2 + 0.95, yBot);
                glVertex2f(xInit2 + 0.95, height + yBot);
                glVertex2f(xInit2 + 0.5, height + yBot);
            glEnd();
            yBot += height;
        }
    }
}

/**
* Listens for and handles mouse button clicks/releases
*/
void mouseClick (GLFWwindow *sender, int button, int action, int mods) {
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        // Check which part of the screen was clicked
        if (mouseX < button_width) {
            // Buttons were clicked
            cout << "(" << mouseX << "  " << mouseY << ") -> Button block clicked" << endl;
            resetCurrent();
            //resetPrevious();
            handleButtons();
            return;
        } else if (mouseX < previousStartX && mouseY < currentHeight) {
            // Current block was clicked
            cout << "(" << mouseX << "  " << mouseY << ") -> Current block clicked" << endl;
            if (enableEditing) {
                //resetPrevious();
                handleCurrent();
            }
            return;
        } else if (mouseX > previousStartX && mouseY < previousHeight) {
            // Previous block was clicked
            cout << "(" << mouseX << "  " << mouseY << ") -> Previous block clicked" << endl;
            if (enableEditing) {
            }
            return;
        } else {
            // Info block was clicked
            cout << "(" << mouseX << "  " << mouseY << ") -> Details block clicked" << endl;
            return;
        }
    } else if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {
        if ((mouseX > currentStartX && mouseY < previousHeight)) {
            pressed = true;
            holdMouseX = mouseX;
            holdMouseY = mouseY;
            initTransX = currentTransX;
            initTransY = currentTransY;
        }
    } else if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_RIGHT) {
        pressed = false;
    } else if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_MIDDLE) {
        if ((mouseX > currentStartX && mouseY < previousHeight)) {
            zoom = true;
            holdMouseX = mouseX;
            holdMouseY = mouseY;
        }
    } else if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_MIDDLE) {
        zoom = false;
    }
}

/**
* Listens for and handles mouse movement
*/
void mouseMove (GLFWwindow *sender, double mX, double mY) {
    mouseX = mX;
    mouseY = mY;
    if (pressed && enableEditing) {
        double xDif = holdMouseX - mouseX;
        double yDif = holdMouseY - mouseY;
        currentAngleX = mod((currentAngleX - yDif), 360);
        currentAngleY = mod((currentAngleY - xDif), 360);
        holdMouseX = mouseX;
        holdMouseY = mouseY;
    } else if (pressed && !enableEditing) {
        double xDif = holdMouseX - mouseX;
        double yDif = holdMouseY - mouseY;
        currentTransX = initTransX + xDif*-0.01;
        currentTransY = initTransY + yDif*0.01;
    }

    if (zoom) {
        double yDif = holdMouseY - mouseY;
        currentZoom += 0.01*yDif;
        currentZoom = max(0.1, min(10.0, currentZoom));
        holdMouseX = mouseX;
        holdMouseY = mouseY;
    }
}

/**
* Listens for and handles mouse scrolling
*/
void mouseScroll(GLFWwindow *sender, double xOffset, double yOffset) {
    if (currentSelectedX >= 0 && currentSelectedY >= 0) {
        if (yOffset < 0 && currentData[currentSelectedX][currentSelectedY].value > -1) {
            currentData[currentSelectedX][currentSelectedY].value += 0.05*yOffset;
            current.setCurrentValue(currentSelectedX, currentSelectedY, currentData[currentSelectedX][currentSelectedY].value);
        } else if (yOffset > 0 && currentData[currentSelectedX][currentSelectedY].value < 1) {
            currentData[currentSelectedX][currentSelectedY].value += 0.05*yOffset;
            current.setCurrentValue(currentSelectedX, currentSelectedY, currentData[currentSelectedX][currentSelectedY].value);
        }
    }

    /*if (previousSelectedX >= 0 && previousSelectedY >= 0) {
        previousData[previousSelectedX][previousSelectedY].value += 0.1*yOffset;
    }*/
}

/**
* Determines which button was clicked and performs the appropriate action
*/
void handleButtons() {
    // Render only the button scene and get the pixel colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, button_width, window_height);
    renderButtons(true);
    glFlush();
    glFinish();
    GLubyte buffer [1*4];
    glReadBuffer(GL_BACK);
    glReadPixels((int)mouseX, (int)(window_height - mouseY), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    cout << (int)buffer[0] << " " << (int)buffer[1] << " " << (int)buffer[2] << " " << (int)buffer[3] << endl;

    // Handle button clicks
    int red = (int)buffer[0];
    switch (red) {
        // Add a row
        case 1: 
                cout << "Add row" << endl;
                if (enableEditing) {
                    current.addRow();
                    updateCurrent();
                    updatePrevious();
                }
                break;

        // Add a column
        case 2:
                cout << "Add column" << endl;
                if (enableEditing) {
                    current.addColumn();
                    updateCurrent();
                    updatePrevious();
                }
                break;

        // Remove a row
        case 3:
                cout << "Remove row" << endl;
                if (enableEditing) {
                    current.deleteRow();
                    updateCurrent();
                    updatePrevious();
                }
                break;

        // Remove a column
        case 4:
                cout << "Remove column" << endl;
                if (enableEditing) {
                    current.deleteColumn();
                    updateCurrent();
                    updatePrevious();
                }
                break;

        // Select order of decomposition
        case 5:
                if (decompDegree == 0) {
                    decompDegree = 2;
                } else if (decompDegree == 2) {
                    decompDegree = 3;
                } else {
                    decompDegree = 0;
                }
                cout << "Select order of decomposition -> " << decompDegree << endl;
                break;

        // Deconstruct rows full 
        case 6:
                cout << "Deconstruct rows full" << endl;
                switch (decompDegree) {
                    case 0:
                            if (current.decompRowsHaar(false)) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 0;
                                lastOpp.rowCol = 'R';
                                lastOpp.size = currentData[0].size();
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                    case 2:
                            if (current.decompRowsChaikin(false)) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 2;
                                lastOpp.rowCol = 'R';
                                lastOpp.size = currentData[0].size();
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                    case 3:
                            if (current.decompRowsCubic(false)) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 3;
                                lastOpp.rowCol = 'R';
                                lastOpp.size = currentData[0].size();
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                }
                break;

        // Deconstruct columns full
        case 7:
                cout << "Deconstruct columns full" << endl;
                switch (decompDegree) {
                    case 0:
                            if (current.decompColsHaar(false)) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 0;
                                lastOpp.rowCol = 'C';
                                lastOpp.size = currentData.size();
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                    case 2:
                            if (current.decompColsChaikin(false)) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 2;
                                lastOpp.rowCol = 'C';
                                lastOpp.size = currentData.size();
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                    case 3:
                            if (current.decompColsCubic(false)) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 3;
                                lastOpp.rowCol = 'C';
                                lastOpp.size = currentData.size();
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                }
                break;

        // Deconstruct rows partial
        case 8:
                cout << "Deconstruct rows partial" << endl;
                switch (decompDegree) {
                    case 0:
                            if (current.decompRowsHaar()) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 0;
                                lastOpp.rowCol = 'R';
                                lastOpp.size = (int)(currentData[0].size()/pow(2.0, current.getRowDecomp()-1));
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                    case 2:
                            if (current.decompRowsChaikin()) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 2;
                                lastOpp.rowCol = 'R';
                                lastOpp.size = (int)(currentData[0].size()/pow(2.0, current.getRowDecomp()-1));
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                    case 3:
                            if (current.decompRowsCubic()) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 3;
                                lastOpp.rowCol = 'R';
                                lastOpp.size = (int)(currentData[0].size()/pow(2.0, current.getRowDecomp()-1));
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                }
                break;

        // Deconstruct columns partial
        case 9:
                cout << "Deconstruct columns partial" << endl;
                switch (decompDegree) {
                    case 0:
                            if (current.decompColsHaar()) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 0;
                                lastOpp.rowCol = 'C';
                                lastOpp.size = (int)(currentData.size()/pow(2.0, current.getColDecomp()-1));
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                    case 2:
                            if (current.decompColsChaikin()) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 2;
                                lastOpp.rowCol = 'C';
                                lastOpp.size = (int)(currentData.size()/pow(2.0, current.getColDecomp()-1));
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                    case 3:
                            if (current.decompColsCubic()) {
                                updateCurrent();
                                updatePrevious();
                                lastOpp.decRec = 'D';
                                lastOpp.degree = 3;
                                lastOpp.rowCol = 'C';
                                lastOpp.size = (int)(currentData.size()/pow(2.0, current.getColDecomp()-1));
                            } else {
                                cout << "No deconstruction" << endl;
                            }
                            break;
                }
                break;

        // Reconstruct once
        case 10:
                cout << "Reconstruct one level" << endl;
                int deg;
                deg = current.reconstruct();
                if (deg > -1) {
                    updateCurrent();
                    updatePrevious();
                    lastOpp.decRec = 'R';
                    lastOpp.degree = deg%10;
                    if (deg/10 == 1) {
                        lastOpp.rowCol = 'C';
                        lastOpp.size = (int)(previousData.size()/pow(2.0, current.getColDecomp()));
                    } else {
                        lastOpp.rowCol = 'R';
                        lastOpp.size = (int)(previousData[0].size()/pow(2.0, current.getRowDecomp()));
                    }
                    cout << "Reconstruction:" << endl;
                    cout << "Row/Col:" << lastOpp.rowCol << endl;
                    cout << "Degree : " << lastOpp.degree << endl;
                    cout << "Size   :" << lastOpp.size << endl;
                } else {
                    cout << "No reconstruction" << endl;
                }
                break;
        // Display image of Lena
        case 11:
                cout << "Lena" << endl;
                currentAngleX = 0;
                currentAngleY = 0;
                currentAngleZ = 0;
                currentZoom = 1.0;
                currentTransX = 0.0;
                currentTransY = 0.0;
                enableEditing = false;
                decompDegree = 0;
                currentSelectedX = -1;
                currentSelectedY = -1;
                previousSelectedX = -1;
                previousSelectedY = -1;
                lastOpp.decRec = ' ';
                lastOpp.rowCol = ' ';
                lastOpp.degree = -1;
                lastOpp.size = -1;
                pressed = false;
                decompDegree = 0;
                previousData.clear();
                currentData.clear();
                current = MultiRes2D(img);
                updateCurrent();
                updatePrevious();
                break;

        // Reset camera
        case 12:
                cout << "Reset camera" << endl;
                if (enableEditing) {
                    currentAngleX = -60;
                    currentAngleY = 15;
                    currentAngleZ = 45;
                    currentZoom = 1.0;
                    currentTransX = 0.0;
                    currentTransY = 0.0;
                } else {
                    currentAngleX = 0;
                    currentAngleY = 0;
                    currentAngleZ = 0;
                    currentZoom = 1.0;
                    currentTransX = 0.0;
                    currentTransY = 0.0;
                }
                break;

        // Clear all
        case 13:
                cout << "Clear everything" << endl;
                enableEditing = true;
                decompDegree = 0;
                currentAngleX = -60;
                currentAngleY = 15;
                currentAngleZ = 45;
                currentZoom = 1.0;
                currentTransX = 0.0;
                currentTransY = 0.0;
                currentSelectedX = -1;
                currentSelectedY = -1;
                previousSelectedX = -1;
                previousSelectedY = -1;
                lastOpp.decRec = ' ';
                lastOpp.rowCol = ' ';
                lastOpp.degree = -1;
                lastOpp.size = -1;
                pressed = false;
                decompDegree = 0;
                previousData.clear();
                currentData.clear();
                current = MultiRes2D(false);
                updateCurrent();
                updatePrevious();
                break;

        default: 
                break;
    }
}

/**
* 
*/
void handleCurrent() {
    // Render only the current scene and get the pixel colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(currentStartX, currentStartY, currentWidth, currentHeight);
    renderCurrent(true);
    glFlush();
    glFinish();
    GLubyte buffer [1*4];
    glReadBuffer(GL_BACK);
    glReadPixels((int)mouseX, (int)(window_height - mouseY), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    // Reset current selected point
    resetCurrent();
    updatePrevious();

    for (int i = 0; i < currentData.size(); i++) {
        for (int j = 0; j < currentData[i].size(); j++) {
            if (currentData[i][j].renderColR == (int)buffer[0]/255.0) {
                if (currentData[i][j].renderColG == (int)buffer[1]/255.0) {
                    if (currentData[i][j].renderColB == (int)buffer[2]/255.0) {
                        currentSelectedX = i;
                        currentSelectedY = j;
                        currentData[i][j].currentColR = 1;
                        currentData[i][j].currentColG = 1;
                        currentData[i][j].currentColB = 0;
                        break;
                    }
                }
            }
        }
    }

    if (currentSelectedX == -1 || currentSelectedY == -1) {
        return;
    }

    // Find values in previous that had an influence on the current selected value
    int numCols, numRows;
    vector<double> filts;
    previousBasesX.clear();
    previousBasesY.clear();
    numCols = ceil(previousData.size()/pow(2.0, current.getColDecomp()));
    if (previousData.size() > 0) {
        numRows = ceil(previousData[0].size()/pow(2.0, current.getRowDecomp()));
    }

    if (lastOpp.decRec == 'D') {
        if (lastOpp.rowCol == 'R') {
            numRows = lastOpp.size;

            // Check whether selected can be computed
            if (currentSelectedX < numCols && currentSelectedY < numRows) {
                switch (lastOpp.degree) {
                    case 0:
                            for (int i = 0; i < 2; i++) {
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY*2+i, numRows));
                            }
                            break;
                    case 2:
                            for (int i = -2; i < 2; i++) {
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY*2+i, numRows));
                            }
                            break;
                    case 3:
                            if (currentSelectedY < numRows/2) {
                                for (int i = -4; i < 3; i++) {
                                    previousBasesX.push_back(mod(currentSelectedX, numCols));
                                    previousBasesY.push_back(mod(currentSelectedY*2+i, numRows));
                                }
                            } else {
                                for (int i = -2; i < 3; i++) {
                                    previousBasesX.push_back(mod(currentSelectedX, numCols));
                                    previousBasesY.push_back(mod(currentSelectedY*2+i, numRows));
                                }
                            }
                            break;
                };
            }

        } else if (lastOpp.rowCol == 'C') {
            numCols = lastOpp.size;

            // Check whether selected can be computed
            if (currentSelectedX < numCols && currentSelectedY < numRows) {
                switch (lastOpp.degree) {
                    case 0:
                            for (int i = 0; i < 2; i++) {
                                previousBasesX.push_back(mod(currentSelectedX*2+i, numCols));
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                            }
                            break;
                    case 2:
                            for (int i = -2; i < 2; i++) {
                                previousBasesX.push_back(mod(currentSelectedX*2+i, numCols));
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                            }
                            break;
                    case 3:
                            if (currentSelectedX < numCols/2) {
                                for (int i = -4; i < 3; i++) {
                                    previousBasesX.push_back(mod(currentSelectedX*2+i, numCols));
                                    previousBasesY.push_back(mod(currentSelectedY, numRows));
                                }
                            } else {
                                for (int i = -2; i < 3; i++) {
                                    previousBasesX.push_back(mod(currentSelectedX*2+i, numCols));
                                    previousBasesY.push_back(mod(currentSelectedY, numRows));
                                }
                            }
                            break;
                };
            }
        }
    } else if (lastOpp.decRec == 'R') {
        if (lastOpp.rowCol == 'R') {
            numRows = lastOpp.size;

            // Check whether selected can be computed
            if (currentSelectedX < numCols && currentSelectedY < numRows) {
                switch (lastOpp.degree) {
                    case 0:
                            previousBasesX.push_back(mod(currentSelectedX, numCols));
                            previousBasesY.push_back(mod(currentSelectedY/2, numRows/2));
                            previousBasesX.push_back(mod(currentSelectedX, numCols));
                            previousBasesY.push_back(mod(currentSelectedY/2, numRows/2)+numRows/2);
                            break;
                    case 2:
                            // Coarse points
                            previousBasesX.push_back(mod(currentSelectedX, numCols));
                            previousBasesY.push_back(mod(currentSelectedY/2, numRows/2));
                            previousBasesX.push_back(mod(currentSelectedX, numCols));
                            previousBasesY.push_back(mod(currentSelectedY/2+1, numRows/2));

                            // Detail points
                            previousBasesX.push_back(mod(currentSelectedX, numCols));
                            previousBasesY.push_back(mod(currentSelectedY/2, numRows/2)+numRows/2);
                            previousBasesX.push_back(mod(currentSelectedX, numCols));
                            previousBasesY.push_back(mod(currentSelectedY/2+1, numRows/2)+numRows/2);
                            break;
                    case 3:
                            if (currentSelectedY%2 == 0) {
                                // Coarse points
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2, numRows/2));
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2+1, numRows/2));

                                // Detail points
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2-1, numRows/2)+numRows/2);
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2, numRows/2)+numRows/2);
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2+1, numRows/2)+numRows/2);
                            } else {
                                // Coarse points
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2, numRows/2));
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2+1, numRows/2));
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2+2, numRows/2));

                                // Detail points
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2-1, numRows/2)+numRows/2);
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2, numRows/2)+numRows/2);
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2+1, numRows/2)+numRows/2);
                                previousBasesX.push_back(mod(currentSelectedX, numCols));
                                previousBasesY.push_back(mod(currentSelectedY/2+2, numRows/2)+numRows/2);
                            }
                };
            }
        } else if (lastOpp.rowCol == 'C') {
            numCols = lastOpp.size;

            // Check whether selected can be computed
            if (currentSelectedX < numCols && currentSelectedY < numRows) {
                switch (lastOpp.degree) {
                    case 0:
                            previousBasesX.push_back(mod(currentSelectedX/2, numCols/2));
                            previousBasesY.push_back(mod(currentSelectedY, numRows));
                            previousBasesX.push_back(mod(currentSelectedX/2, numCols/2)+numCols/2);
                            previousBasesY.push_back(mod(currentSelectedY, numRows));
                            break;
                    case 2:
                            // Coarse points
                            previousBasesX.push_back(mod(currentSelectedX/2, numCols/2));
                            previousBasesY.push_back(mod(currentSelectedY, numRows));
                            previousBasesX.push_back(mod(currentSelectedX/2+1, numCols/2));
                            previousBasesY.push_back(mod(currentSelectedY, numRows));

                            // Detail points
                            previousBasesX.push_back(mod(currentSelectedX/2, numCols/2)+numCols/2);
                            previousBasesY.push_back(mod(currentSelectedY, numRows));
                            previousBasesX.push_back(mod(currentSelectedX/2+1, numCols/2)+numCols/2);
                            previousBasesY.push_back(mod(currentSelectedY, numRows));
                            break;
                    case 3:
                            if (currentSelectedY%2 == 0) {
                                // Coarse points
                                previousBasesX.push_back(mod(currentSelectedX/2, numCols/2));
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                                previousBasesX.push_back(mod(currentSelectedX/2+1, numCols/2));
                                previousBasesY.push_back(mod(currentSelectedY, numRows));

                                // Detail points
                                previousBasesX.push_back(mod(currentSelectedX/2-1, numCols/2)+numCols/2);
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                                previousBasesX.push_back(mod(currentSelectedX/2, numCols/2)+numCols/2);
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                                previousBasesX.push_back(mod(currentSelectedX/2+1, numCols/2)+numCols/2);
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                            } else {
                                // Coarse points
                                previousBasesX.push_back(mod(currentSelectedX/2, numCols/2));
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                                previousBasesX.push_back(mod(currentSelectedX/2+1, numCols/2));
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                                previousBasesX.push_back(mod(currentSelectedX/2+2, numCols/2));
                                previousBasesY.push_back(mod(currentSelectedY, numRows));

                                // Detail points
                                previousBasesX.push_back(mod(currentSelectedX/2-1, numCols/2)+numCols/2);
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                                previousBasesX.push_back(mod(currentSelectedX/2, numCols/2)+numCols/2);
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                                previousBasesX.push_back(mod(currentSelectedX/2+1, numCols/2)+numCols/2);
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                                previousBasesX.push_back(mod(currentSelectedX/2+2, numCols/2)+numCols/2);
                                previousBasesY.push_back(mod(currentSelectedY, numRows));
                            }
                };
            }
        }
    }

    for (int i = 0; i < previousBasesX.size(); i++) {
        previousData[previousBasesX[i]][previousBasesY[i]].currentColR = presetR[i];
        previousData[previousBasesX[i]][previousBasesY[i]].currentColG = presetG[i];
        previousData[previousBasesX[i]][previousBasesY[i]].currentColB = presetB[i];
    }
}

/**
* 
*/
void handlePrevious() {
    // Render only the previous scene and get the pixel colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(previousStartX, previousStartY, previousWidth, previousHeight);
    renderPrevious(true);
    glFlush();
    glFinish();
    GLubyte buffer [1*4];
    glReadBuffer(GL_BACK);
    glReadPixels((int)mouseX, (int)(window_height - mouseY), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    // Reset previous selected point
    resetPrevious();

    for (int i = 0; i < previousData.size(); i++) {
        for (int j = 0; j < previousData[i].size(); j++) {
            if (previousData[i][j].renderColR == (int)buffer[0]/255.0) {
                if (previousData[i][j].renderColG == (int)buffer[1]/255.0) {
                    if (previousData[i][j].renderColB == (int)buffer[2]/255.0) {
                        previousSelectedX = i;
                        previousSelectedY = j;
                        previousData[i][j].currentColR = 1;
                        previousData[i][j].currentColG = 1;
                        previousData[i][j].currentColB = 0;
                        break;
                    }
                }
            }
        }
    }
}

/**
* 
*/
void updateCurrent() {
    // Clear the currentData vector and initialize variables
    currentData.clear();
    vector< vector<double> > hold = current.getCurrent();
    if (hold.size() <= 0 || hold[0].size() <= 0) {
        return;
    }
    currentMax = hold[0][0];
    currentMin = hold[0][0];
    int rR, rG, rB;
    rR = 1;
    rG = 1;
    rB = 1;
    
    // Populate the currentData vector
    for (int i = 0; i < hold.size(); i++) {
        vector<block> blocks;
        for (int j = 0; j < hold[i].size(); j++) {
            currentMax = max(currentMax, hold[i][j]);
            currentMin = min(currentMin, hold[i][j]);
            block temp;
            temp.value = hold[i][j];
            temp.renderColR = rR/255.0;
            temp.renderColG = rG/255.0;
            temp.renderColB = rB/255.0;
            temp.enableHeight = enableEditing;
            blocks.push_back(temp);
            rR++;
            if (rR >= 256) {
                rR = 1;
                rG++;
                if (rG >= 256)  {
                    rG = 1;
                    rB++;
                }
            }
        }
        currentData.push_back(blocks);
    }

    // Set the colour for each block
    double holdCol;
    for (int i = 0; i < currentData.size(); i++) {
        for (int j = 0; j < currentData[i].size(); j++) {
            holdCol = min(max((currentData[i][j].value + 1.0)/2.0, -1.0), 1.0);
            if (enableEditing) {
                if (holdCol <= 0.5) {
                    currentData[i][j].currentColR = (holdCol*510)/255.0;
                    currentData[i][j].currentColG = (holdCol*510)/255.0;
                    currentData[i][j].currentColB = (holdCol*254+128)/255.0;
                } else {
                    currentData[i][j].currentColR = (255 - (holdCol - 0.5)*254)/255.0;
                    currentData[i][j].currentColG = (255 - (holdCol - 0.5)*510)/255.0;
                    currentData[i][j].currentColB = (255 - (holdCol - 0.5)*510)/255.0;
                }
            } else {
                currentData[i][j].currentColR = holdCol;
                currentData[i][j].currentColG = holdCol;
                currentData[i][j].currentColB = holdCol;
            }
        }
    }

    // Compute histogram
    for (int i = 0; i < 256; i++) {
        countCurrent[i] = 0;
    }
    int indexC = 0;
    for (int i = 0; i < currentData.size(); i++) {
        for (int j = 0; j < currentData[i].size(); j++) {
            indexC = min(255, max(0, (int)(currentData[i][j].value*128+128)));
            countCurrent[indexC] += 1;
        }
    }
}

/**
* 
*/
void updatePrevious() {
    // Clear the previousData vector and initialize variables
    previousData.clear();
    vector< vector<double> > hold = current.getPrevious();
    if (hold.size() <= 0 || hold[0].size() <= 0) {
        return;
    }
    previousMax = hold[0][0];
    previousMin = hold[0][0];
    int rR, rG, rB;
    rR = 1;
    rG = 1;
    rB = 1;
    
    // Populate the previousData vector
    for (int i = 0; i < hold.size(); i++) {
        vector<block> blocks;
        for (int j = 0; j < hold[i].size(); j++) {
            previousMax = max(previousMax, hold[i][j]);
            previousMin = min(previousMin, hold[i][j]);
            block temp;
            temp.value = hold[i][j];
            temp.renderColR = rR/255.0;
            temp.renderColG = rG/255.0;
            temp.renderColB = rB/255.0;
            temp.enableHeight = enableEditing;
            blocks.push_back(temp);
            rR++;
            if (rR >= 256) {
                rR = 1;
                rG++;
                if (rG >= 256)  {
                    rG = 1;
                    rB++;
                }
            }
        }
        previousData.push_back(blocks);
    }

    // Set the colour for each block
    double holdCol;
    for (int i = 0; i < previousData.size(); i++) {
        for (int j = 0; j < previousData[i].size(); j++) {
            holdCol = min(max((previousData[i][j].value + 1.0)/2.0, -1.0), 1.0);
            if (enableEditing) {
                if (holdCol <= 0.5) {
                    previousData[i][j].currentColR = (holdCol*510)/255.0;
                    previousData[i][j].currentColG = (holdCol*510)/255.0;
                    previousData[i][j].currentColB = (holdCol*254+128)/255.0;
                } else {
                    previousData[i][j].currentColR = (255 - (holdCol - 0.5)*254)/255.0;
                    previousData[i][j].currentColG = (255 - (holdCol - 0.5)*510)/255.0;
                    previousData[i][j].currentColB = (255 - (holdCol - 0.5)*510)/255.0;
                }
            } else {
                previousData[i][j].currentColR = holdCol;
                previousData[i][j].currentColG = holdCol;
                previousData[i][j].currentColB = holdCol;
            }
        }
    }

    // Compute histogram
    for (int i = 0; i < 256; i++) {
        countPrevious[i] = 0;
    }
    int indexC = 0;
    for (int i = 0; i < previousData.size(); i++) {
        for (int j = 0; j < previousData[i].size(); j++) {
            indexC = min(255, max(0, (int)(previousData[i][j].value*128+128)));
            countPrevious[indexC] += 1;
        }
    }
}

/**
* 
*/
void resetCurrent() {
    if (currentSelectedX >= 0 && currentSelectedY >= 0) {
        double holdCol = min(max((currentData[currentSelectedX][currentSelectedY].value + 1.0)/2.0, -1.0), 1.0);
        if (holdCol <= 0.5) {
            currentData[currentSelectedX][currentSelectedY].currentColR = (holdCol*510)/255.0;
            currentData[currentSelectedX][currentSelectedY].currentColG = (holdCol*510)/255.0;
            currentData[currentSelectedX][currentSelectedY].currentColB = (holdCol*254+128)/255.0;
        } else {
            currentData[currentSelectedX][currentSelectedY].currentColR = (255 - (holdCol - 0.5)*254)/255.0;
            currentData[currentSelectedX][currentSelectedY].currentColG = (255 - (holdCol - 0.5)*510)/255.0;
            currentData[currentSelectedX][currentSelectedY].currentColB = (255 - (holdCol - 0.5)*510)/255.0;
        }
        currentSelectedX = -1;
        currentSelectedY = -1;
    }
}

/**
* 
*/
void resetPrevious() {
    if (previousSelectedX >= 0 && previousSelectedY >= 0) {
        double holdCol = min(max((previousData[previousSelectedX][previousSelectedY].value + 1.0)/2.0, -1.0), 1.0);
        if (holdCol <= 0.5) {
            previousData[previousSelectedX][previousSelectedY].currentColR = (holdCol*510)/255.0;
            previousData[previousSelectedX][previousSelectedY].currentColG = (holdCol*510)/255.0;
            previousData[previousSelectedX][previousSelectedY].currentColB = (holdCol*254+128)/255.0;
        } else {
            previousData[previousSelectedX][previousSelectedY].currentColR = (255 - (holdCol - 0.5)*254)/255.0;
            previousData[previousSelectedX][previousSelectedY].currentColG = (255 - (holdCol - 0.5)*510)/255.0;
            previousData[previousSelectedX][previousSelectedY].currentColB = (255 - (holdCol - 0.5)*510)/255.0;
        }
        previousSelectedX = -1;
        previousSelectedY = -1;
    }
}

int mod(int value1, int value2) {
    int hold = value1 % value2;
    if (hold < 0) {
        hold += value2;
    }
    return hold;
}

int main(int argc, char *argv[]) {
    // Try to initialize GLFW
    if (!glfwInit()) {
        return 1;
    }
    glutInit( & argc, argv );

    // Create rendering window
    window = glfwCreateWindow(1600, 960, "2D Multiresolution", NULL, NULL);
    if (!window) {
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Initialize variables
    vector< vector<double> > test;
    for (int i = 0; i < 11; i++) {
        vector<double> hold;
        for (int j = 0; j < 11; j++) {
            hold.push_back((rand()%10 + 1)/10.0);
        }
        test.push_back(hold);
    }

    // Set up initial variables
    enableEditing = true;
    decompDegree = 0;
    currentAngleX = -60;
    currentAngleY = 15;
    currentAngleZ = 45;
    currentZoom = 1.0;
    currentTransX = 0.0;
    currentTransY = 0.0;
    currentSelectedX = -1;
    currentSelectedY = -1;
    previousSelectedX = -1;
    previousSelectedY = -1;
    current = MultiRes2D(test, true);
    updateCurrent();
    updatePrevious();
    lastOpp.decRec = ' ';
    lastOpp.rowCol = ' ';
    lastOpp.degree = -1;
    lastOpp.size = -1;
    bool pressed = false;

    // Load image
    int width, height;
    unsigned char* image = SOIL_load_image("images/lena.bmp", &width, &height, 0, SOIL_LOAD_RGB);
    int pos = 0;
    for (int i = 0; i < width; i++) {
        vector<double> hold;
        img.push_back(hold);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            img[j].push_back(((0.11 * ((int)image[pos]-128)) + (0.59 * ((int)image[pos+1]-128)) + (0.3 * ((int)image[pos+2]-128)))/128.0);
            pos += 3;
        }
    }

    // User input functions
    glfwSetMouseButtonCallback(window, mouseClick);
    glfwSetCursorPosCallback(window, mouseMove);
    glfwSetScrollCallback(window, mouseScroll);

    // Main window loop
    while (!glfwWindowShouldClose(window)) {
        // Recalculate width and height of different componenets
        glfwGetFramebufferSize(window, &window_width, &window_height);
        button_width = 0.1*window_width;
        currentStartX = button_width;
        currentStartY = 0.2*window_height;
        currentWidth = (window_width - button_width)/2;
        currentHeight = 0.8*window_height;
        previousStartX = currentStartX + currentWidth;
        previousStartY = 0.2*window_height;
        previousWidth = currentWidth;
        previousHeight = 0.8*window_height;
        
        // Call to main rendering
        glViewport(0, 0, window_width, window_height);
        renderMain();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
