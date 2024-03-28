#ifndef MAIN2D_H
#define MAIN2D_H

// C++ imports
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <tuple>
#include <string.h>
//#include <cstdlib>

// Project imports
#include "MultiRes2D.h"
#include "filters.h"
#include "SOIL.h"

/***** Variable declarations *****/
struct block {
    double value;
    double height;
    double currentColR;
    double currentColG;
    double currentColB;
    double renderColR;
    double renderColG;
    double renderColB;
    bool enableHeight;
};

struct history {
    char decRec;
    char rowCol;
    int degree;
    int size;
};

// Variables controlling the full screen
GLFWwindow *window;
int window_width, window_height, button_width;
double mouseX, mouseY;
double holdMouseX, holdMouseY;
bool pressed, zoom;

// Helper variables
bool enableEditing;
int decompDegree;
history lastOpp;
std::vector< std::vector<double> > img;
double presetR[7] = {1, 1, 1, 0, 0, 75/255.0, 148/255.0};
double presetG[7] = {0, 0.5, 1, 1, 0, 0, 0};
double presetB[7] = {0, 0, 0, 0, 1, 130/255.0, 211/255.0};
int countCurrent[256];
int countPrevious[256];

// Variables controlling the top left box (Current data)
MultiRes2D current;
std::vector< std::vector<block> > currentData;
std::vector<double> previousBasesX, previousBasesY;
double currentAngleX, currentAngleY, currentAngleZ, currentZoom, currentTransX, currentTransY, initTransX, initTransY;
double currentMax, currentMin;
double currentStartX, currentStartY, currentWidth, currentHeight;
int currentSelectedX, currentSelectedY;

// Variables controlling the top right box (Previous data)
std::vector< std::vector<block> > previousData;
std::vector<double> currentBasesX, currentBasesY;
double previousAngleX, previousAngleY, previousAngleZ;
double previousMax, previousMin;
double previousStartX, previousStartY, previousWidth, previousHeight;
int previousSelectedX, previousSelectedY;

/***** Function definitions *****/
// Rendering functions
void renderMain();
void renderButtons(bool coloured=false);
void renderCurrent(bool coloured=false);
void renderPrevious(bool coloured=false);
void renderBases(bool coloured=false);

// Input/Output functions
void mouseClick (GLFWwindow *sender, int button, int action, int mods);
void mouseMove (GLFWwindow *sender, double mX, double mY);
void mouseScroll(GLFWwindow *sender, double xOffset, double yOffset);

// Functions for handling keypresses
void handleButtons();
void handleCurrent();
void handlePrevious();

// Helper functions
void updateVariables();
void updateCurrent();
void updatePrevious();
void resetCurrent();
void resetPrevious();
int mod(int value1, int value2);

#endif
