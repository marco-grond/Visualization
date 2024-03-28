#ifndef MAIN1D_H
#define MAIN1D_H

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

// Project imports
#include "MultiRes1D.h"
#include "filters.h"

/***** Variable declarations *****/

// Variables controlling the full screen
GLFWwindow *window;
int window_width, window_height, button_width;
double mouseX, mouseY;

// Variables for different parts of the screen
double originalStartX, originalStartY, originalWidth, originalHeight;
double coarseStartX, coarseStartY, coarseWidth, coarseHeight;
double detailStartX, detailStartY, detailWidth, detailHeight;

// Variables to store data
// Original data
std::vector<double> originalX, originalY, originalKnots, originalXClosed, originalYClosed, originalKnotsClosed, 
                    originalXRec, originalYRec, originalRecKnots, originalXRecClosed, originalYRecClosed, originalRecKnotsClosed;
int originalSelect;

// Coarse data
std::vector<double> coarseX, coarseY, coarseKnots, coarseXClosed, coarseYClosed, coarseKnotsClosed;
std::vector<double> coarseXOld, coarseYOld;//, coarseKnotsOld;//, coarseXClosedOld, coarseYClosedOld, coarseKnotsClosedOld;
int coarseSelect, coarseView;
MultiRes1D current, previous, reconstructed;

// Detail data
std::vector<double> detailX, detailY, detailXOld, detailYOld;
std::vector<double> viewX, viewY, viewXOld, viewYOld;
int detailSelect, detailView;

// Helper variables
bool closedCurve;
double clickDistance = 0.05;
bool decomposed;
char previousOpp = ' ';
bool movedCoarse = false;
bool movedDetail = false;
bool hideOriginal = false;
bool hideGeo = false;
int decompDegree, previousDegree;
int order;
int u = 1000;


/***** Function declarations *****/

// Rendering functions
void renderMain();
void renderButtons(bool coloured);
void renderOriginal(bool coloured);
void renderCoarse(bool coloured);
void renderDetail(bool coloured);

// Input/Output functions
void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods);
void mouseClick (GLFWwindow *sender, int button, int action, int mods);
void mouseMove (GLFWwindow *sender, double mX, double mY);
void mouseScroll(GLFWwindow *sender, double xOffset, double yOffset);

// Functions for handling button clicks
void handleButtons();
void handleOriginal(int button);
void handleCoarse(int button);
void handleDetail(int button);

// Helper functions
int delta(double uVal, int mVal, int kVal, std::vector<double> knotSequence);
std::tuple<double, double> getCurveValue(double uVal, int mVal, int kVal, int dVal, std::vector<double> xPoint, std::vector<double> yPoint, std::vector<double> knotSequence);
double convertMouseX(double mousePos, double left, double width, double innerDim);
double convertMouseY(double mousePos, double top, double height, double innerDim);
int mod(int value1, int value2);
void computeOriginalKnots();
void computeCoarseKnots();
void computeClosedPoints();
void resetAll();

#endif
