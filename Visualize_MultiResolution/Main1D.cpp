#include "headers/Main1D.h"

using namespace std;

/**
* 
*/
void renderMain() {
    // Clear screen before re-rendering
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Intial setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, 0, window_height, 0, 1);
    glEnable(GL_POINT_SMOOTH);

    // Draw lines to separare different areas
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
        glVertex2f(button_width, 0);
        glVertex2f(button_width, window_height);
        glVertex2f(originalStartX, originalStartY);
        glVertex2f(originalStartX+originalWidth, originalStartY);
        glVertex2f(coarseStartX, coarseStartY);
        glVertex2f(coarseStartX+coarseWidth, coarseStartY);
    glEnd();
        
    // Render the buttons
    glViewport(0, 0, button_width, window_height);
    renderButtons(false);

    // Render the original curve
    glViewport(originalStartX, originalStartY, originalWidth, originalHeight);
    renderOriginal(false);

    // Render the coarse approximation
    glViewport(coarseStartX, coarseStartY, coarseWidth, coarseHeight);
    renderCoarse(false);

    // Render the details
    glViewport(detailStartX, detailStartY, detailWidth, detailHeight);
    renderDetail(false);
}
/**
* Draw buttons
*/
void renderButtons(bool coloured) {
    // Initial setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, button_width, 0, window_height, 0, 1);

    // Variables to keep track of different buttons
    double numButtons = 9.0;
    double button_size = window_height/numButtons;
    int count = 1;

   // Draw button to ...
    if (coloured) {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        glLineWidth(1);
        if (closedCurve) {
            char string1[64] = "Closed";
            // Write to the screen
            glColor3f(1.0f, 1.0f, 1.0f);
            glRasterPos2f(button_width/4, window_height - button_size*(count-1) - (button_size/2));
            int len1 = (int) strlen(string1);
            for (int i = 0; i < len1; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
            }
        } else {
            char string1[64] = "Open";
            // Write to the screen
            glColor3f(1.0f, 1.0f, 1.0f);
            glRasterPos2f(button_width/3, window_height - button_size*(count-1) - (button_size/2));
            int len1 = (int) strlen(string1);
            for (int i = 0; i < len1; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
            }
        }
    }
    count++;

   // Draw button to ...
    if (coloured) {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        glLineWidth(1);
        if (hideOriginal) {
            char string1[64] = "Show Original";
            // Write to the screen
            glColor3f(1.0f, 1.0f, 1.0f);
            glRasterPos2f(button_width/12, window_height - button_size*(count-1) - (button_size/2));
            int len1 = (int) strlen(string1);
            for (int i = 0; i < len1; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
            }
        } else {
            char string1[64] = "Hide Original";
            // Write to the screen
            glColor3f(1.0f, 1.0f, 1.0f);
            glRasterPos2f(button_width/12, window_height - button_size*(count-1) - (button_size/2));
            int len1 = (int) strlen(string1);
            for (int i = 0; i < len1; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
            }
        }
    }
    count++;

   // Draw button to ...
    if (coloured) {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        glLineWidth(1);
        if (hideGeo) {
            char string1[64] = "Show Geometric";
            // Write to the screen
            glColor3f(1.0f, 1.0f, 1.0f);
            glRasterPos2f(button_width/12, window_height - button_size*(count-1) - (button_size/2));
            int len1 = (int) strlen(string1);
            for (int i = 0; i < len1; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
            }
        } else {
            char string1[64] = "Hide Geometric";
            // Write to the screen
            glColor3f(1.0f, 1.0f, 1.0f);
            glRasterPos2f(button_width/12, window_height - button_size*(count-1) - (button_size/2));
            int len1 = (int) strlen(string1);
            for (int i = 0; i < len1; i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
            }
        }
    }
    count++;

   // Draw button to ...
    if (coloured) {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        glLineWidth(1);
        char string1[64] = "Order +";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/4, window_height - button_size*(count-1) - (button_size/2));
        int len1 = (int) strlen(string1);
        for (int i = 0; i < len1; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
        }
    }
    count++;

   // Draw button to ...
    if (coloured) {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        glLineWidth(1);
        char string1[64] = "Order -";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/4, window_height - button_size*(count-1) - (button_size/2));
        int len1 = (int) strlen(string1);
        for (int i = 0; i < len1; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
        }
    }
    count++;

   // Draw button to ...
    if (coloured) {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        glLineWidth(1);
        int len;
        char string[64] = "Haar";
        char string2[64] = "Chaikin";
        char string3[64] = "Cubic";
        switch (decompDegree) {
            case 2:
                    // Write to the screen
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glRasterPos2f(button_width/4, window_height - button_size*(count-1) - (button_size/2));
                    len = (int) strlen(string2);
                    for (int i = 0; i < len; i++) {
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string2[i]);
                    }
                    break;
            case 3:
                    // Write to the screen
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glRasterPos2f(button_width/3, window_height - button_size*(count-1) - (button_size/2));
                    len = (int) strlen(string3);
                    for (int i = 0; i < len; i++) {
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string3[i]);
                    }
                    break;
            default:
                    // Write to the screen
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glRasterPos2f(button_width/3, window_height - button_size*(count-1) - (button_size/2));
                    len = (int) strlen(string);
                    for (int i = 0; i < len; i++) {
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
                    }
                    break;
        };
    }
    count++;

   // Draw button to ...
    if (coloured) {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        glLineWidth(1);
        char string[64] = "Decompose";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/6, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    }
    count++;

   // Draw button to ...
    if (coloured) {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        glLineWidth(1);
        char string[64] = "Reconstruct";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/6, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    }
    count++;

   // Draw button to ...
    if (coloured) {
        glColor3f((count/256.0), 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count-1));
            glVertex2f(button_width, window_height - button_size*(count));
            glVertex2f(0, window_height - button_size*(count));
        glEnd();
        glLineWidth(1);
        char string[64] = "Clear";
        // Write to the screen
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(button_width/4, window_height - button_size*(count-1) - (button_size/2));
        int len = (int) strlen(string);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
        }
    }
    count++;
}

/**
* 
*/
void renderOriginal(bool coloured) {
    // Initial setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    // Write the order to the screen
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.99, 0.9);
    char string1[64] = "Order (k): ";
    char integer_string1[32];
    sprintf(integer_string1, "%d", order);
    strcat(string1, integer_string1);
    int len1 = (int) strlen(string1);
    for (int i = 0; i < len1; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
    }

    if (!hideOriginal) {
        // Draw all points
        glColor3f(1, 1, 1);
        glPointSize(10);
        glBegin(GL_POINTS);
            for (int i = 0; i < originalX.size(); i++) {
                glVertex2f(originalX[i], originalY[i]);
            }
        glEnd();
    } else {
        // Draw all points
        glColor3f(0.5, 0.5, 0.5);
        glPointSize(5);
        glBegin(GL_POINTS);
            for (int i = 0; i < originalX.size(); i++) {
                glVertex2f(originalXRec[i], originalYRec[i]);
            }
        glEnd();
    }

    double yVal, xVal;
    if (closedCurve) {
        // Draw curve if enough points are available
        if (originalX.size() > order && order > 1) {

            // Draw the line segments for the B-Spline
            yVal = 0.0;
            xVal = 0.0;
            int dVal = 0;
            double uVal;
            if (!hideOriginal) {
                glColor3f(1, 1, 1);
                glLineWidth(3);
                glBegin(GL_LINE_STRIP);
                for (int i = 0; i <= u; i++) {
                    uVal = originalKnotsClosed[order-1] + (i*1.0/u)*(originalKnotsClosed[originalXClosed.size()] - originalKnotsClosed[order-1]);
                    while (uVal < originalKnotsClosed[dVal] || uVal >= originalKnotsClosed[dVal+1]) {
                        dVal += 1;
                        if ((i*1.0/u) == 1) {
                            dVal -= 1;
                            break;
                        }
                    }
                    tie(xVal, yVal) = getCurveValue(uVal, originalXClosed.size() - 1, order, dVal, originalXClosed, originalYClosed, originalKnotsClosed);
                    glVertex2f(xVal, yVal); 
                }
                glEnd();
                glLineWidth(1);
            }

            //cout << originalXRecClosed.size() << "  " << originalYRecClosed.size() << ";   " << originalXClosed.size() << "  " << originalYClosed.size() << ";   " << originalRecKnotsClosed.size() << "  " << originalKnotsClosed.size() << endl;

            // Draw the newly constructed curve
            yVal = 0.0;
            xVal = 0.0;
            dVal = 0;
            uVal = 0.0;
            glColor3f(0.3, 0.3, 0.3);
            glLineWidth(1);
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i <= u; i++) {
                uVal = originalRecKnotsClosed[order-1] + (i*1.0/u)*(originalRecKnotsClosed[originalXClosed.size()] - originalRecKnotsClosed[order-1]);
                while (uVal < originalRecKnotsClosed[dVal] || uVal >= originalRecKnotsClosed[dVal+1]) {
                    dVal += 1;
                    if ((i*1.0/u) == 1) {
                        dVal -= 1;
                        break;
                    }
                }
                tie(xVal, yVal) = getCurveValue(uVal, originalXClosed.size() - 1, order, dVal, originalXRecClosed, originalYRecClosed, originalRecKnotsClosed);
                glVertex2f(xVal, yVal); 
            }
            glEnd();
        }

    } else {
        // Draw curve if enough points are available
        if (originalX.size() >= order && order > 1) {

            // Draw the line segments for the B-Spline
            yVal = 0.0;
            xVal = 0.0;
            int dVal = 0;
            if (!hideOriginal) {
                glLineWidth(3);
                glColor3f(1, 1, 1);
                glBegin(GL_LINE_STRIP);
                for (int i = 0; i <= u; i++) {
                    while ((i*1.0/u) < originalKnots[dVal] || (i*1.0/u) >= originalKnots[dVal+1]) {
                        dVal += 1;
                        if ((i*1.0/u) == 1 && originalKnots[dVal] == 1) {
                            dVal -= 1;
                            break;
                        }
                    }
                    tie(xVal, yVal) = getCurveValue(i*1.0/u, originalX.size() - 1, order, dVal, originalX, originalY, originalKnots);
                    glVertex2f(xVal, yVal);
                }
                glEnd();
                glLineWidth(1);
            }

            // Draw the newly constructed curve
            yVal = 0.0;
            xVal = 0.0;
            glColor3f(0.3, 0.3, 0.3);
            glLineWidth(1);
            glBegin(GL_LINE_STRIP);
            dVal = 0;
            for (int i = 0; i <= u; i++) {
                while ((i*1.0/u) < originalKnots[dVal] || (i*1.0/u) >= originalKnots[dVal+1]) {
                    dVal += 1;
                    if ((i*1.0/u) == 1 && originalKnots[dVal] == 1) {
                        dVal -= 1;
                        break;
                    }
                }
                tie(xVal, yVal) = getCurveValue(i*1.0/u, originalX.size() - 1, order, dVal, originalXRec, originalYRec, originalKnots);
                glVertex2f(xVal, yVal);
            }
            glEnd();
        }
    }
}

/**
* 
*/
void renderCoarse(bool coloured) {
    // Initial setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    // Write to the screen
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.99, 0.9);
    char string1[64] = "Points";
    int len1 = (int) strlen(string1);
    for (int i = 0; i < len1; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
    }

    // Draw previous points if they exist
    glColor3f(148/255.0, 0, 211/255.0);
    glPointSize(5);
    glBegin(GL_POINTS);
        for (int i = 0; i < coarseXOld.size(); i++) {
            glVertex2f(coarseXOld[i], coarseYOld[i]);
        }
    glEnd();    

    viewX.clear();
    viewY.clear();

    // Draw visualization if possible and if a point is selected
    if (coarseView > -1) {

        // Previous opperation was reconstruction
        if (previousOpp == 'R' && closedCurve) {

            double xM, yM, xN, yN, xP, yP, xQ, yQ, xV, yV, xW, yW;
            // Determine the degree of the reconstruction
            switch (previousDegree) {
                case 0:
                        if (detailXOld.size() <= 0)  {
                            break;
                        }
                        // Draw the points used during this reconstruction
                        glColor3f(1, 0, 0);
                        glPointSize(10);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(coarseView/2, coarseXOld.size())], coarseYOld[mod(coarseView/2, coarseYOld.size())]);
                        glEnd();

                        if (movedCoarse || hideGeo) {
                            break;
                        }

                        // Draw the final vectors
                        glColor3f(0, 0, 1);
                        glLineWidth(3);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(coarseView/2, coarseXOld.size())], coarseYOld[mod(coarseView/2, coarseYOld.size())]);
                            glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                        glEnd();
                        glLineWidth(1);
                        break;
                case 2:
                        if (detailXOld.size() <= 0)  {
                            break;
                        }
                        // Draw the points used during this reconstruction
                        glColor3f(1, 0, 0);
                        glPointSize(10);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(coarseView/2, coarseXOld.size())], coarseYOld[mod(coarseView/2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView/2+1, coarseXOld.size())], coarseYOld[mod(coarseView/2+1, coarseYOld.size())]);
                        glEnd();

                        if (movedCoarse || hideGeo) {
                            break;
                        }

                        // Draw line connecting the points
                        glColor3f(1, 0, 0);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(coarseView/2, coarseXOld.size())], coarseYOld[mod(coarseView/2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView/2+1, coarseXOld.size())], coarseYOld[mod(coarseView/2+1, coarseYOld.size())]);
                        glEnd();

                        if (coarseView%2 == 0) {
                            xM = 0.75*coarseXOld[mod(coarseView/2, coarseXOld.size())] + 0.25*coarseXOld[mod(coarseView/2+1, coarseXOld.size())];
                            yM = 0.75*coarseYOld[mod(coarseView/2, coarseYOld.size())] + 0.25*coarseYOld[mod(coarseView/2+1, coarseYOld.size())];

                            xN = 0.75*detailXOld[mod(coarseView/2, detailXOld.size())];
                            yN = 0.75*detailYOld[mod(coarseView/2, detailYOld.size())];

                            xP = -0.25*detailXOld[mod(coarseView/2+1, detailXOld.size())];
                            yP = -0.25*detailYOld[mod(coarseView/2+1, detailYOld.size())];
                        } else {
                            xM = 0.25*coarseXOld[mod(coarseView/2, coarseXOld.size())] + 0.75*coarseXOld[mod(coarseView/2+1, coarseXOld.size())];
                            yM = 0.25*coarseYOld[mod(coarseView/2, coarseYOld.size())] + 0.75*coarseYOld[mod(coarseView/2+1, coarseYOld.size())];

                            xN = 0.25*detailXOld[mod(coarseView/2, detailXOld.size())];
                            yN = 0.25*detailYOld[mod(coarseView/2, detailYOld.size())];

                            xP = -0.75*detailXOld[mod(coarseView/2+1, detailXOld.size())];
                            yP = -0.75*detailYOld[mod(coarseView/2+1, detailYOld.size())];
                        }

                        // Draw the points on the way to the new point
                        glColor3f(1, 0, 0);
                        glPointSize(5);
                        glBegin(GL_POINTS);
                            glVertex2f(xM, yM);
                            glVertex2f(xM + xN, yM + yN);
                            glVertex2f(xM + xN + xP, yM + yN + yP);
                        glEnd();

                        // Draw the final vectors
                        glColor3f(0, 0, 1);
                        glLineWidth(3);
                        glBegin(GL_LINES);
                            glVertex2f(xM, yM);
                            glVertex2f(xM + xN, yM + yN);
                            glVertex2f(xM + xN, yM + yN);
                            glVertex2f(xM + xN + xP, yM + yN + yP);
                        glEnd();
                        glLineWidth(1);

                        break;
                case 3:
                        if (coarseView%2 == 0) {
                            // Draw the points used during this reconstruction
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[mod(coarseView/2, coarseXOld.size())], coarseYOld[mod(coarseView/2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView/2+1, coarseXOld.size())], coarseYOld[mod(coarseView/2+1, coarseYOld.size())]);
                            glEnd();

                            if (movedCoarse || hideGeo) {
                                break;
                            }

                            // Draw line connecting the points
                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[mod(coarseView/2, coarseXOld.size())], coarseYOld[mod(coarseView/2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView/2+1, coarseXOld.size())], coarseYOld[mod(coarseView/2+1, coarseYOld.size())]);
                            glEnd();
  
                            xM = 0.5*coarseXOld[mod(coarseView/2, coarseXOld.size())] + 0.5*coarseXOld[mod(coarseView/2+1, coarseXOld.size())];
                            yM = 0.5*coarseYOld[mod(coarseView/2, coarseYOld.size())] + 0.5*coarseYOld[mod(coarseView/2+1, coarseYOld.size())];

                            xN = 0.5*detailXOld[mod(coarseView/2-1, detailXOld.size())];
                            yN = 0.5*detailYOld[mod(coarseView/2-1, detailYOld.size())];

                            xP = -1*detailXOld[mod(coarseView/2, detailXOld.size())];
                            yP = -1*detailYOld[mod(coarseView/2, detailYOld.size())];

                            xQ = 0.5*detailXOld[mod(coarseView/2+1, detailXOld.size())];
                            yQ = 0.5*detailYOld[mod(coarseView/2+1, detailYOld.size())];

                            // Draw the points on the way to the new point
                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(xM, yM);
                                glVertex2f(xM + xN, yM + yN);
                                glVertex2f(xM + xN + xP, yM + yN + yP);
                                glVertex2f(xM + xN + xP + xQ, yM + yN + yP + yQ);
                            glEnd();

                            // Draw the final vectors
                            glColor3f(0, 0, 1);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(xM, yM);
                                glVertex2f(xM + xN, yM + yN);
                                glVertex2f(xM + xN, yM + yN);
                                glVertex2f(xM + xN + xP, yM + yN + yP);
                                glVertex2f(xM + xN + xP, yM + yN + yP);
                                glVertex2f(xM + xN + xP + xQ, yM + yN + yP + yQ);
                            glEnd();
                            glLineWidth(1);

                        } else {
                            // Draw the points used during this reconstruction
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[mod(coarseView/2, coarseXOld.size())], coarseYOld[mod(coarseView/2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView/2+1, coarseXOld.size())], coarseYOld[mod(coarseView/2+1, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView/2+2, coarseXOld.size())], coarseYOld[mod(coarseView/2+2, coarseYOld.size())]);
                            glEnd();

                            if (movedCoarse || hideGeo) {
                                break;
                            }

                            xM = 0.5*coarseXOld[mod(coarseView/2, coarseXOld.size())] + 0.5*coarseXOld[mod(coarseView/2+2, coarseXOld.size())];
                            yM = 0.5*coarseYOld[mod(coarseView/2, coarseYOld.size())] + 0.5*coarseYOld[mod(coarseView/2+2, coarseYOld.size())];

                            xN = 0.125*coarseXOld[mod(coarseView/2, coarseXOld.size())] + 0.75*coarseXOld[mod(coarseView/2+1, coarseXOld.size())] + 
                                 0.125*coarseXOld[mod(coarseView/2+2, coarseXOld.size())];
                            yN = 0.125*coarseYOld[mod(coarseView/2, coarseYOld.size())] + 0.75*coarseYOld[mod(coarseView/2+1, coarseYOld.size())] +
                                 0.125*coarseYOld[mod(coarseView/2+2, coarseYOld.size())];

                            // Draw line connecting the points
                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[mod(coarseView/2, coarseXOld.size())], coarseYOld[mod(coarseView/2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView/2+2, coarseXOld.size())], coarseYOld[mod(coarseView/2+2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView/2+1, coarseXOld.size())], coarseYOld[mod(coarseView/2+1, coarseYOld.size())]);
                                glVertex2f(xM, yM);
                            glEnd();

                            xP = 0.125*detailXOld[mod(coarseView/2-1, detailXOld.size())];
                            yP = 0.125*detailYOld[mod(coarseView/2-1, detailYOld.size())];

                            xQ = 0.375*detailXOld[mod(coarseView/2, detailXOld.size())];
                            yQ = 0.375*detailYOld[mod(coarseView/2, detailYOld.size())];

                            xV = 0.375*detailXOld[mod(coarseView/2+1, detailXOld.size())];
                            yV = 0.375*detailYOld[mod(coarseView/2+1, detailYOld.size())];

                            xW = 0.125*detailXOld[mod(coarseView/2+2, detailXOld.size())];
                            yW = 0.125*detailYOld[mod(coarseView/2+2, detailYOld.size())];

                            // Draw the points on the way to the new point
                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(xM, yM);
                                glVertex2f(xN, yN);
                                glVertex2f(xN + xP, yN + yP);
                                glVertex2f(xN + xP + xQ, yN + yP + yQ);
                                glVertex2f(xN + xP + xQ + xV, yN + yP + yQ + yV);
                                glVertex2f(xN + xP + xQ + xV + xW, yN + yP + yQ + yV + yW);
                            glEnd();

                            // Draw the final vectors
                            glColor3f(0, 0, 1);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(xN, yN);
                                glVertex2f(xN + xP, yN + yP);
                                glVertex2f(xN + xP, yN + yP);
                                glVertex2f(xN + xP + xQ, yN + yP + yQ);
                                glVertex2f(xN + xP + xQ, yN + yP + yQ);
                                glVertex2f(xN + xP + xQ + xV, yN + yP + yQ + yV);
                                glVertex2f(xN + xP + xQ + xV, yN + yP + yQ + yV);
                                glVertex2f(xN + xP + xQ + xV + xW, yN + yP + yQ + yV + yW);
                            glEnd();
                            glLineWidth(1);
                        }

                        break;
            };

        // Previous opperation was decompostion
        } else if (previousOpp == 'D' && closedCurve) {

            double xM, yM, xN, yN, xP, yP, xQ, yQ, xV, yV;
            char string1[10] = "0.5";
            char string2[10] = "0.25";
            char string3[10] = "0.75";
            char string4[10] = "-0.25";
            char string5[10] = "-0.75";
            char string6[10] = "0.125";
            char string7[10] = "0.375";
            char string8[10] = "-0.125";
            char string9[10] = "-0.375";
            char string10[10] = "1";
            char string11[10] = "-0.5";
            // Determine the degree of the decomposition
            switch (previousDegree) {
                case 0:
                        // Draw the original points responsible for the new point
                        glColor3f(1, 0, 0);
                        glPointSize(10);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                        glEnd();

                        viewX.push_back(coarseXOld[mod(coarseView*2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2+1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);

                        // Write to the screen
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glRasterPos2f(coarseXOld[mod(coarseView*2, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < len1; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2+1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < len1; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
                        }

                        if (movedCoarse || hideGeo) {
                            break;
                        }

                        // Draw line between two points used to construct the selected point
                        glColor3f(1, 0, 0);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                        glEnd();

                        // Draw the new point
                        glColor3f(1, 0, 0);
                        glPointSize(5);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                        glEnd();
                        break;
                case 2:
                        // Draw the original points responsible for the new point
                        glColor3f(1, 0, 0);
                        glPointSize(10);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(coarseView*2-2, coarseXOld.size())], coarseYOld[mod(coarseView*2-2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())], coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                        glEnd();

                        viewX.push_back(coarseXOld[mod(coarseView*2-2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2-2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2-1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2+1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);

                        // Write to the screen
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glRasterPos2f(coarseXOld[mod(coarseView*2-2, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2-2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2-1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2+1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                        }

                        if (movedCoarse || hideGeo) {
                            break;
                        }
                        xM = 0.5*coarseXOld[mod(coarseView*2 - 2, coarseXOld.size())] + 0.5*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())];
                        yM = 0.5*coarseYOld[mod(coarseView*2 - 2, coarseYOld.size())] + 0.5*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())];
                        xN = 0.5*coarseXOld[mod(coarseView*2, coarseXOld.size())] + 0.5*coarseXOld[mod(coarseView*2 + 1, coarseXOld.size())];
                        yN = 0.5*coarseYOld[mod(coarseView*2, coarseYOld.size())] + 0.5*coarseYOld[mod(coarseView*2 + 1, coarseYOld.size())];
                        glColor3f(1, 0, 0);
                        glPointSize(5);
                        glBegin(GL_POINTS);
                            glVertex2f(xM, yM);
                            glVertex2f(xN, yN);
                            glVertex2f(2*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())] - xM, 2*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())] - yM);
                            glVertex2f(2*coarseXOld[mod(coarseView*2, coarseXOld.size())] - xN, 2*coarseYOld[mod(coarseView*2, coarseYOld.size())] - yN);
                        glEnd();

                        glColor3f(1, 1, 0);
                        glLineWidth(3);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(coarseView*2-2, coarseXOld.size())], coarseYOld[mod(coarseView*2-2, coarseYOld.size())]);
                            glVertex2f(xM, yM);
                            glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                            glVertex2f(xN, yN);
                            glVertex2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())], coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                            glVertex2f(2*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())] - xM, 2*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())] - yM);
                            glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                            glVertex2f(2*coarseXOld[mod(coarseView*2, coarseXOld.size())] - xN, 2*coarseYOld[mod(coarseView*2, coarseYOld.size())] - yN);
                        glEnd();
                        glLineWidth(1);

                        // Draw the new point
                        glColor3f(1, 0, 0);
                        glPointSize(5);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                        glEnd();

                        glColor3f(1, 0, 0);
                        glBegin(GL_LINES);
                            glVertex2f(2*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())] - xM, 2*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())] - yM);
                            glVertex2f(2*coarseXOld[mod(coarseView*2, coarseXOld.size())] - xN, 2*coarseYOld[mod(coarseView*2, coarseYOld.size())] - yN);
                            glVertex2f(coarseXOld[mod(coarseView*2 - 2, coarseXOld.size())], coarseYOld[mod(coarseView*2 - 2, coarseYOld.size())]);
                            glVertex2f(2*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())] - xM, 2*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())] - yM);
                            glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                            glVertex2f(2*coarseXOld[mod(coarseView*2, coarseXOld.size())] - xN, 2*coarseYOld[mod(coarseView*2, coarseYOld.size())] - yN);
                        glEnd();
                        break;
                case 3:
                        // Draw the original points responsible for the new point
                        glColor3f(1, 0, 0);
                        glPointSize(10);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(coarseView*2-4, coarseXOld.size())], coarseYOld[mod(coarseView*2-4, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2-3, coarseXOld.size())], coarseYOld[mod(coarseView*2-3, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2-2, coarseXOld.size())], coarseYOld[mod(coarseView*2-2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())], coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2+2, coarseXOld.size())], coarseYOld[mod(coarseView*2+2, coarseYOld.size())]);
                        glEnd();

                        viewX.push_back(coarseXOld[mod(coarseView*2-4, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2-4, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2-3, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2-3, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2-2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2-2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2-1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2+1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(coarseView*2+2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(coarseView*2+2, coarseYOld.size())]);

                        // Write to the screen
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glRasterPos2f(coarseXOld[mod(coarseView*2-4, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2-4, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string6[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2-3, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2-3, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string11[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2-2, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2-2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string7[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2-1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string10[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string7[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2+1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string11[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(coarseView*2+2, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2+2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string6[i]);
                        }

                        if (movedCoarse || hideGeo) {
                            break;
                        }
                        xM = 0.5*coarseXOld[mod(coarseView*2 - 4, coarseXOld.size())] + 0.5*coarseXOld[mod(coarseView*2 + 2, coarseXOld.size())];
                        yM = 0.5*coarseYOld[mod(coarseView*2 - 4, coarseYOld.size())] + 0.5*coarseYOld[mod(coarseView*2 + 2, coarseYOld.size())];
                        xN = 0.5*coarseXOld[mod(coarseView*2 - 2, coarseXOld.size())] + 0.5*coarseXOld[mod(coarseView*2, coarseXOld.size())];
                        yN = 0.5*coarseYOld[mod(coarseView*2 - 2, coarseYOld.size())] + 0.5*coarseYOld[mod(coarseView*2, coarseYOld.size())];
                        xP = 0.5*coarseXOld[mod(coarseView*2 - 3, coarseXOld.size())] + 0.5*coarseXOld[mod(coarseView*2 + 1, coarseXOld.size())];
                        yP = 0.5*coarseYOld[mod(coarseView*2 - 3, coarseYOld.size())] + 0.5*coarseYOld[mod(coarseView*2 + 1, coarseYOld.size())];
                        xQ = 0.25*xM + 0.75*xN;
                        yQ = 0.25*yM + 0.75*yN;
                        xV = xQ - xP;
                        yV = yQ - yP;
                        glColor3f(1, 0, 0);
                        glPointSize(5);
                        glBegin(GL_POINTS);
                            glVertex2f(xM, yM);
                            glVertex2f(xN, yN);
                            glVertex2f(xP, yP);
                            glVertex2f(xQ, yQ);
                        glEnd();

                        // Draw the new point
                        glColor3f(1, 0, 0);
                        glPointSize(5);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                        glEnd();

                        glColor3f(1, 0, 0);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(coarseView*2-4, coarseXOld.size())], coarseYOld[mod(coarseView*2-4, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2+2, coarseXOld.size())], coarseYOld[mod(coarseView*2+2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2-2, coarseXOld.size())], coarseYOld[mod(coarseView*2-2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(coarseView*2-3, coarseXOld.size())], coarseYOld[mod(coarseView*2-3, coarseYOld.size())]);
                            glVertex2f(xM, yM);
                            glVertex2f(xN, yN);
                        glEnd();

                        // Draw the final vectors
                        glColor3f(1, 1, 0);
                        glLineWidth(3);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())], coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                            glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                            glVertex2f(xP, yP);
                            glVertex2f(xQ, yQ);
                        glEnd();
                        glLineWidth(1);
                        break;
            };
        } else if (previousOpp == 'D' && !closedCurve) {
            double xM, yM, xN, yN, xP, yP, xQ, yQ, xV, yV;
            char string1[10] = "0.5";
            char string2[10] = "0.25";
            char string3[10] = "0.75";
            char string4[10] = "-0.25";
            char string5[10] = "-0.75";
            char string6[10] = "0.125";
            char string7[10] = "0.375";
            char string8[10] = "-0.125";
            char string9[10] = "-0.375";
            char string10[10] = "1";
            char string11[10] = "-0.5";

            char cubic1[10] = "1";
            char cubic2[10] = "-0.352518";
            char cubic3[10] =  "0.705036";
            char cubic4[10] =  "0.971223";
            char cubic5[10] = "-0.431655";
            char cubic6[10] =  "0.107914";
            char cubic7[10] = "0.18";
            char cubic8[10] = "-0.36";
            char cubic9[10] = "-0.08";
            char cubic10[10] = "1.28";
            char cubic11[10] = "0.43";
            char cubic12[10] = "-0.6";
            char cubic13[10] = "0.15";
            char cubic14[10] = "0.117347";
            char cubic15[10] = "-0.469388";
            char cubic16[10] = "0.321429";
            char cubic17[10] = "1.061224";
            // Determine the degree of the decomposition
            switch (previousDegree) {
                case 0:
                        if (coarseView == 0 || (coarseView == coarseX.size() - 1)) {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                            glEnd();

                            viewX.push_back(coarseX[coarseView]);
                            viewY.push_back(coarseY[coarseView]);

                            // Write to the screen
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseX[coarseView]+0.01, coarseY[coarseView]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string10[i]);
                            }

                        } else {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())], coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                            glEnd();

                            viewX.push_back(coarseXOld[mod(coarseView*2, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                            viewX.push_back(coarseXOld[mod(coarseView*2-1, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);

                            // Write to the screen
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[mod(coarseView*2, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2, coarseYOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2-1, coarseYOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
                            }

                            if (movedCoarse || hideGeo) {
                                break;
                            }

                            // Draw line between two points used to construct the selected point
                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())], coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                            glEnd();

                            // Draw the new point
                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                            glEnd();
                        }
                        break;
                case 2:
                        if (coarseView == 0 || coarseView == (coarseX.size() - 1)) {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                            glEnd();

                            viewX.push_back(coarseX[coarseView]);
                            viewY.push_back(coarseY[coarseView]);

                            // Write to the screen
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseX[coarseView]+0.01, coarseY[coarseView]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string10[i]);
                            }

                        } else if (coarseView == 1) {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[0], coarseYOld[0]);
                                glVertex2f(coarseXOld[1], coarseYOld[1]);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                                glVertex2f(coarseXOld[3], coarseYOld[3]);
                            glEnd();

                            viewX.push_back(coarseXOld[0]);
                            viewY.push_back(coarseYOld[0]);
                            viewX.push_back(coarseXOld[1]);
                            viewY.push_back(coarseYOld[1]);
                            viewX.push_back(coarseXOld[2]);
                            viewY.push_back(coarseYOld[2]);
                            viewX.push_back(coarseXOld[3]);
                            viewY.push_back(coarseYOld[3]);

                            // Write to the screen
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[0]+0.01, coarseYOld[0]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string11[i]);
                            }
                            glRasterPos2f(coarseXOld[1]+0.01, coarseYOld[1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string10[i]);
                            }
                            glRasterPos2f(coarseXOld[2]+0.01, coarseYOld[2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                            }
                            glRasterPos2f(coarseXOld[3]+0.01, coarseYOld[3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                            }

                            if (movedCoarse || hideGeo) {
                                break;
                            }

                            xM = coarseXOld[1] + (coarseXOld[1] - coarseXOld[0]);
                            yM = coarseYOld[1] + (coarseYOld[1] - coarseYOld[0]);
                            xN = coarseXOld[2] + 0.5*(coarseXOld[2] - coarseXOld[3]);
                            yN = coarseYOld[2] + 0.5*(coarseYOld[2] - coarseYOld[3]);
                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(xM, yM);
                                glVertex2f(xN, yN);
                                glVertex2f(0.5*xM + 0.5*xN, 0.5*yM + 0.5*yN);
                            glEnd();

                            glColor3f(1, 1, 0);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[1], coarseYOld[1]);
                                glVertex2f(xM, yM);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                                glVertex2f(xN, yN);
                                glVertex2f(coarseXOld[0], coarseYOld[0]);
                                glVertex2f(coarseXOld[0] + (coarseXOld[1] - coarseXOld[0]), coarseYOld[0] + (coarseYOld[1] - coarseYOld[0]));
                                glVertex2f(coarseXOld[3], coarseYOld[3]);
                                glVertex2f(coarseXOld[3] + 0.5*(coarseXOld[2] - coarseXOld[3]), coarseYOld[3] + 0.5*(coarseYOld[2] - coarseYOld[3]));
                            glEnd();
                            glLineWidth(1);

                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[0], coarseYOld[0]);
                                glVertex2f(xM, yM);
                                glVertex2f(coarseXOld[3], coarseYOld[3]);
                                glVertex2f(xN, yN);
                                glVertex2f(xN, yN);
                                glVertex2f(xM, yM);
                            glEnd();

                        }  else if (coarseView == (coarseX.size() - 2)) {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[coarseXOld.size() - 1], coarseYOld[coarseXOld.size() - 1]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 2], coarseYOld[coarseXOld.size() - 2]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 3], coarseYOld[coarseXOld.size() - 3]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 4], coarseYOld[coarseXOld.size() - 4]);
                            glEnd();

                            viewX.push_back(coarseXOld[coarseXOld.size() - 1]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 1]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 2]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 2]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 3]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 3]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 4]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 4]);

                            // Write to the screen
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 1]+0.01, coarseYOld[coarseXOld.size() - 1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string11[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 2]+0.01, coarseYOld[coarseXOld.size() - 2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string10[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 3]+0.01, coarseYOld[coarseXOld.size() - 3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 4]+0.01, coarseYOld[coarseXOld.size() - 4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                            }

                            if (movedCoarse || hideGeo) {
                                break;
                            }

                            xM = coarseXOld[coarseXOld.size() - 2] + (coarseXOld[coarseXOld.size() - 2] - coarseXOld[coarseXOld.size() - 1]);
                            yM = coarseYOld[coarseXOld.size() - 2] + (coarseYOld[coarseXOld.size() - 2] - coarseYOld[coarseXOld.size() - 1]);
                            xN = coarseXOld[coarseXOld.size() - 3] + 0.5*(coarseXOld[coarseXOld.size() - 3] - coarseXOld[coarseXOld.size() - 4]);
                            yN = coarseYOld[coarseXOld.size() - 3] + 0.5*(coarseYOld[coarseXOld.size() - 3] - coarseYOld[coarseXOld.size() - 4]);
                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(xM, yM);
                                glVertex2f(xN, yN);
                                glVertex2f(0.5*xM + 0.5*xN, 0.5*yM + 0.5*yN);
                            glEnd();

                            glColor3f(1, 1, 0);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[coarseXOld.size()-2], coarseYOld[coarseXOld.size()-2]);
                                glVertex2f(xM, yM);
                                glVertex2f(coarseXOld[coarseXOld.size()-3], coarseYOld[coarseXOld.size()-3]);
                                glVertex2f(xN, yN);
                                glVertex2f(coarseXOld[coarseXOld.size()-1], coarseYOld[coarseXOld.size()-1]);
                                glVertex2f(coarseXOld[coarseXOld.size()-1] + (coarseXOld[coarseXOld.size()-2] - coarseXOld[coarseXOld.size()-1]), 
                                           coarseYOld[coarseXOld.size()-1] + (coarseYOld[coarseXOld.size()-2] - coarseYOld[coarseXOld.size()-1]));
                                glVertex2f(coarseXOld[coarseXOld.size()-4], coarseYOld[coarseXOld.size()-4]);
                                glVertex2f(coarseXOld[coarseXOld.size()-4] + 0.5*(coarseXOld[coarseXOld.size()-3] - coarseXOld[coarseXOld.size()-4]), 
                                           coarseYOld[coarseXOld.size()-4] + 0.5*(coarseYOld[coarseXOld.size()-3] - coarseYOld[coarseXOld.size()-4]));
                            glEnd();
                            glLineWidth(1);

                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[coarseXOld.size() - 1], coarseYOld[coarseXOld.size() - 1]);
                                glVertex2f(xM, yM);
                                glVertex2f(coarseXOld[coarseXOld.size() - 4], coarseYOld[coarseXOld.size() - 4]);
                                glVertex2f(xN, yN);
                                glVertex2f(xN, yN);
                                glVertex2f(xM, yM);
                            glEnd();

                        } else {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[mod(coarseView*2-2, coarseXOld.size())], coarseYOld[mod(coarseView*2-2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())], coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                            glEnd();

                            viewX.push_back(coarseXOld[mod(coarseView*2-2, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(coarseView*2-2, coarseYOld.size())]);
                            viewX.push_back(coarseXOld[mod(coarseView*2-1, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                            viewX.push_back(coarseXOld[mod(coarseView*2, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                            viewX.push_back(coarseXOld[mod(coarseView*2+1, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);

                            // Write to the screen
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[mod(coarseView*2-2, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2-2, coarseYOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2-1, coarseYOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(coarseView*2, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2, coarseYOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(coarseView*2+1, coarseYOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                            }

                            if (movedCoarse || hideGeo) {
                                break;
                            }

                            xM = 0.5*coarseXOld[mod(coarseView*2 - 2, coarseXOld.size())] + 0.5*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())];
                            yM = 0.5*coarseYOld[mod(coarseView*2 - 2, coarseYOld.size())] + 0.5*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())];
                            xN = 0.5*coarseXOld[mod(coarseView*2, coarseXOld.size())] + 0.5*coarseXOld[mod(coarseView*2 + 1, coarseXOld.size())];
                            yN = 0.5*coarseYOld[mod(coarseView*2, coarseYOld.size())] + 0.5*coarseYOld[mod(coarseView*2 + 1, coarseYOld.size())];
                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(xM, yM);
                                glVertex2f(xN, yN);
                                glVertex2f(2*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())] - xM, 2*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())] - yM);
                                glVertex2f(2*coarseXOld[mod(coarseView*2, coarseXOld.size())] - xN, 2*coarseYOld[mod(coarseView*2, coarseYOld.size())] - yN);
                            glEnd();

                            // Draw the new point
                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                            glEnd();

                            glColor3f(1, 1, 0);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[mod(coarseView*2-2, coarseXOld.size())], coarseYOld[mod(coarseView*2-2, coarseYOld.size())]);
                                glVertex2f(xM, yM);
                                glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                                glVertex2f(xN, yN);
                                glVertex2f(coarseXOld[mod(coarseView*2-1, coarseXOld.size())], coarseYOld[mod(coarseView*2-1, coarseYOld.size())]);
                                glVertex2f(2*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())] - xM, 2*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())] - yM);
                                glVertex2f(coarseXOld[mod(coarseView*2, coarseXOld.size())], coarseYOld[mod(coarseView*2, coarseYOld.size())]);
                                glVertex2f(2*coarseXOld[mod(coarseView*2, coarseXOld.size())] - xN, 2*coarseYOld[mod(coarseView*2, coarseYOld.size())] - yN);
                            glEnd();
                            glLineWidth(1);

                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(2*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())] - xM, 2*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())] - yM);
                                glVertex2f(2*coarseXOld[mod(coarseView*2, coarseXOld.size())] - xN, 2*coarseYOld[mod(coarseView*2, coarseYOld.size())] - yN);
                                glVertex2f(coarseXOld[mod(coarseView*2 - 2, coarseXOld.size())], coarseYOld[mod(coarseView*2 - 2, coarseYOld.size())]);
                                glVertex2f(2*coarseXOld[mod(coarseView*2 - 1, coarseXOld.size())] - xM, 2*coarseYOld[mod(coarseView*2 - 1, coarseYOld.size())] - yM);
                                glVertex2f(coarseXOld[mod(coarseView*2+1, coarseXOld.size())], coarseYOld[mod(coarseView*2+1, coarseYOld.size())]);
                                glVertex2f(2*coarseXOld[mod(coarseView*2, coarseXOld.size())] - xN, 2*coarseYOld[mod(coarseView*2, coarseYOld.size())] - yN);
                            glEnd();
                        }
                        break;
                case 3:
                        if (coarseView == 0 || coarseView == (coarseX.size() - 1)) {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseX[coarseView], coarseY[coarseView]);
                            glEnd();

                            viewX.push_back(coarseX[coarseView]);
                            viewY.push_back(coarseY[coarseView]);

                            // Write to the screen
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseX[coarseView]+0.01, coarseY[coarseView]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic1[i]);
                            }

                        } else if (coarseView == 1) {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[0], coarseYOld[0]);
                                glVertex2f(coarseXOld[1], coarseYOld[1]);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                                glVertex2f(coarseXOld[3], coarseYOld[3]);
                                glVertex2f(coarseXOld[4], coarseYOld[4]);
                            glEnd();

                            viewX.push_back(coarseXOld[0]);
                            viewY.push_back(coarseYOld[0]);
                            viewX.push_back(coarseXOld[1]);
                            viewY.push_back(coarseYOld[1]);
                            viewX.push_back(coarseXOld[2]);
                            viewY.push_back(coarseYOld[2]);
                            viewX.push_back(coarseXOld[3]);
                            viewY.push_back(coarseYOld[3]);
                            viewX.push_back(coarseXOld[4]);
                            viewY.push_back(coarseYOld[4]);

                            // Write to the screen
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[0]+0.01, coarseYOld[0]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic2[i]);
                            }
                            glRasterPos2f(coarseXOld[1]+0.01, coarseYOld[1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic3[i]);
                            }
                            glRasterPos2f(coarseXOld[2]+0.01, coarseYOld[2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic4[i]);
                            }
                            glRasterPos2f(coarseXOld[3]+0.01, coarseYOld[3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic5[i]);
                            }
                            glRasterPos2f(coarseXOld[4]+0.01, coarseYOld[4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic6[i]);
                            }

                        } else if (coarseView == coarseX.size() - 2) {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[coarseXOld.size() - 1], coarseYOld[coarseXOld.size() - 1]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 2], coarseYOld[coarseXOld.size() - 2]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 3], coarseYOld[coarseXOld.size() - 3]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 4], coarseYOld[coarseXOld.size() - 4]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 5], coarseYOld[coarseXOld.size() - 5]);
                            glEnd();

                            viewX.push_back(coarseXOld[coarseXOld.size() - 1]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 1]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 2]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 2]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 3]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 3]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 4]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 4]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 5]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 5]);

                            // Write to the screen
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 1]+0.01, coarseYOld[coarseXOld.size() - 1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic2[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 2]+0.01, coarseYOld[coarseXOld.size() - 2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic3[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 3]+0.01, coarseYOld[coarseXOld.size() - 3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic4[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 4]+0.01, coarseYOld[coarseXOld.size() - 4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic5[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 5]+0.01, coarseYOld[coarseXOld.size() - 5]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic6[i]);
                            }

                        } else if (coarseView == 2) {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[(coarseView - 2)*2], coarseYOld[(coarseView - 2)*2]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 1], coarseYOld[(coarseView - 2)*2 + 1]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 2], coarseYOld[(coarseView - 2)*2 + 2]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 3], coarseYOld[(coarseView - 2)*2 + 3]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 4], coarseYOld[(coarseView - 2)*2 + 4]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 5], coarseYOld[(coarseView - 2)*2 + 5]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 6], coarseYOld[(coarseView - 2)*2 + 6]);
                            glEnd();

                            viewX.push_back(coarseXOld[(coarseView - 2)*2]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 1]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 1]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 2]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 2]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 3]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 3]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 4]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 4]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 5]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 5]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 6]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 6]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2]+0.01, coarseYOld[(coarseView - 2)*2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic7[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+1]+0.01, coarseYOld[(coarseView - 2)*2+1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic8[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+2]+0.01, coarseYOld[(coarseView - 2)*2+2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic9[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+3]+0.01, coarseYOld[(coarseView - 2)*2+3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic10[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+4]+0.01, coarseYOld[(coarseView - 2)*2+4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic11[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+5]+0.01, coarseYOld[(coarseView - 2)*2+5]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic12[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+6]+0.01, coarseYOld[(coarseView - 2)*2+6]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic13[i]);
                            }


                        } else if (coarseView == coarseX.size() - 3) {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[coarseXOld.size() - 1], coarseYOld[coarseXOld.size() - 1]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 2], coarseYOld[coarseXOld.size() - 2]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 3], coarseYOld[coarseXOld.size() - 3]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 4], coarseYOld[coarseXOld.size() - 4]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 5], coarseYOld[coarseXOld.size() - 5]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 6], coarseYOld[coarseXOld.size() - 6]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 7], coarseYOld[coarseXOld.size() - 7]);
                            glEnd();

                            viewX.push_back(coarseXOld[coarseXOld.size() - 1]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 1]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 2]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 2]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 3]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 3]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 4]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 4]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 5]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 5]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 6]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 6]);
                            viewX.push_back(coarseXOld[coarseXOld.size() - 7]);
                            viewY.push_back(coarseYOld[coarseXOld.size() - 7]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 7]+0.01, coarseYOld[coarseXOld.size() - 7]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic13[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 6]+0.01, coarseYOld[coarseXOld.size() - 6]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic12[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 5]+0.01, coarseYOld[coarseXOld.size() - 5]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic11[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 4]+0.01, coarseYOld[coarseXOld.size() - 4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic10[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 3]+0.01, coarseYOld[coarseXOld.size() - 3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic9[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 2]+0.01, coarseYOld[coarseXOld.size() - 2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic8[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 1]+0.01, coarseYOld[coarseXOld.size() - 1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic7[i]);
                            }

                        } else {
                            // Draw the original points responsible for the new point
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[(coarseView - 2)*2], coarseYOld[(coarseView - 2)*2]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 1], coarseYOld[(coarseView - 2)*2 + 1]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 2], coarseYOld[(coarseView - 2)*2 + 2]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 3], coarseYOld[(coarseView - 2)*2 + 3]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 4], coarseYOld[(coarseView - 2)*2 + 4]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 5], coarseYOld[(coarseView - 2)*2 + 5]);
                                glVertex2f(coarseXOld[(coarseView - 2)*2 + 6], coarseYOld[(coarseView - 2)*2 + 6]);
                            glEnd();

                            viewX.push_back(coarseXOld[(coarseView - 2)*2]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 1]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 1]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 2]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 2]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 3]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 3]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 4]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 4]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 5]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 5]);
                            viewX.push_back(coarseXOld[(coarseView - 2)*2 + 6]);
                            viewY.push_back(coarseYOld[(coarseView - 2)*2 + 6]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2]+0.01, coarseYOld[(coarseView - 2)*2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic14[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+1]+0.01, coarseYOld[(coarseView - 2)*2+1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic15[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+2]+0.01, coarseYOld[(coarseView - 2)*2+2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic16[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+3]+0.01, coarseYOld[(coarseView - 2)*2+3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic17[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+4]+0.01, coarseYOld[(coarseView - 2)*2+4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic16[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+5]+0.01, coarseYOld[(coarseView - 2)*2+5]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic15[i]);
                            }
                            glRasterPos2f(coarseXOld[(coarseView - 2)*2+6]+0.01, coarseYOld[(coarseView - 2)*2+6]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic14[i]);
                            }
                        }

                        break;
            };
        }
    }

    // Draw visualization for vector
    if (detailView > -1) {
        if (previousOpp == 'D' && closedCurve) {

            double xM, yM, xN, yN, xP, yP;
            char string1[10] = "1";
            char string2[10] = "0.75";
            char string3[10] = "-0.75";
            char string4[10] = "0.5";
            char string5[10] = "-0.5";
            char string6[10] = "0.375";
            char string7[10] = "-0.375";
            char string8[10] = "0.25";
            char string9[10] = "-0.25";
            char string10[10] = "0.125";
            char string11[10] = "-0.125";
            // Determine the degree of the decomposition
            switch (previousDegree) {
                case 0:
                        // Draw the original points that have an impact on the vector
                        glPointSize(10);
                        glColor3f(1, 0, 0);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                        glEnd();

                        viewX.push_back(coarseXOld[mod(detailView*2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2+1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2+1, coarseYOld.size())]);

                        glColor3f(1.0f, 1.0f, 1.0f);
                        glRasterPos2f(coarseXOld[mod(detailView*2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string5[i]);
                        }

                        if (movedDetail || hideGeo) {
                            break;
                        }

                        // Draw line between two points used to construct the selected vector
                        glColor3f(1, 0, 0);
                        xM = 0.5*coarseXOld[mod(detailView*2, coarseXOld.size())] - 0.5*coarseXOld[mod(detailView*2 + 1, coarseXOld.size())];
                        yM = 0.5*coarseYOld[mod(detailView*2, coarseYOld.size())] - 0.5*coarseYOld[mod(detailView*2 + 1, coarseYOld.size())];
                        glPointSize(5);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())] + xM, coarseYOld[mod(detailView*2+1, coarseYOld.size())] + yM);
                        glEnd();

                        // Draw the vector
                        glColor3f(0, 0, 1);
                        glLineWidth(3);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())] + xM, coarseYOld[mod(detailView*2+1, coarseYOld.size())] + yM);
                        glEnd();
                        glLineWidth(1);

                        glColor3f(1, 0, 0);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                        glEnd();
                        break;
                case 2:
                        // Draw the original points that have an impact on the vector
                        glColor3f(1, 0, 0);
                        glPointSize(10);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(detailView*2-2, coarseXOld.size())], coarseYOld[mod(detailView*2-2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2-1, coarseXOld.size())], coarseYOld[mod(detailView*2-1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                        glEnd();

                        viewX.push_back(coarseXOld[mod(detailView*2-2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2-2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2-1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2-1, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2+1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2+1, coarseYOld.size())]);

                        glColor3f(1.0f, 1.0f, 1.0f);
                        glRasterPos2f(coarseXOld[mod(detailView*2-2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2-2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string8[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(detailView*2-1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2-1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(detailView*2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string2[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string9[i]);
                        }

                        if (movedDetail || hideGeo) {
                            break;
                        }

                        xM = 0.75*coarseXOld[mod(detailView*2 - 1, coarseXOld.size())] + 0.25*coarseXOld[mod(detailView*2 + 1, coarseXOld.size())];
                        yM = 0.75*coarseYOld[mod(detailView*2 - 1, coarseYOld.size())] + 0.25*coarseYOld[mod(detailView*2 + 1, coarseYOld.size())];
                        xN = 0.75*coarseXOld[mod(detailView*2, coarseXOld.size())] + 0.25*coarseXOld[mod(detailView*2 - 2, coarseXOld.size())];
                        yN = 0.75*coarseYOld[mod(detailView*2, coarseYOld.size())] + 0.25*coarseYOld[mod(detailView*2 - 2, coarseYOld.size())];
                        glColor3f(1, 0, 0);
                        glPointSize(5);
                        glBegin(GL_POINTS);
                            glVertex2f(xM, yM);
                            glVertex2f(xN, yN);
                        glEnd();

                        // Draw the vector
                        glColor3f(0, 0, 1);
                        glLineWidth(3);
                        glBegin(GL_LINES);
                            glVertex2f(xM, yM);
                            glVertex2f(xN, yN);
                        glEnd();
                        glLineWidth(1);

                        // Draw the lines from which the new points were computed
                        glColor3f(1, 0, 0);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(detailView*2-1, coarseXOld.size())], coarseYOld[mod(detailView*2-1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2-2, coarseXOld.size())], coarseYOld[mod(detailView*2-2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                        glEnd();
                        break;
                case 3:
                        // Draw the original points that have an impact on the vector
                        glColor3f(1, 0, 0);
                        glPointSize(10);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(detailView*2-2, coarseXOld.size())], coarseYOld[mod(detailView*2-2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2-1, coarseXOld.size())], coarseYOld[mod(detailView*2-1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())], coarseYOld[mod(detailView*2+2, coarseYOld.size())]);
                        glEnd();

                        viewX.push_back(coarseXOld[mod(detailView*2-2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2-2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2-1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2-1, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2+1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2+2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2+2, coarseYOld.size())]);

                        glColor3f(1.0f, 1.0f, 1.0f);
                        glRasterPos2f(coarseXOld[mod(detailView*2-2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2-2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string11[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(detailView*2-1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2-1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(detailView*2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+1, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                        }
                        glRasterPos2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+2, coarseYOld.size())]-0.03);
                        for (int i = 0; i < 10; i++) {
                            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string11[i]);
                        }

                        if (movedDetail || hideGeo) {
                            break;
                        }

                        xM = 0.5*coarseXOld[mod(detailView*2 - 2, coarseXOld.size())] + 0.5*coarseXOld[mod(detailView*2 + 2, coarseXOld.size())];
                        yM = 0.5*coarseYOld[mod(detailView*2 - 2, coarseYOld.size())] + 0.5*coarseYOld[mod(detailView*2 + 2, coarseYOld.size())];
                        xN = 0.75*coarseXOld[mod(detailView*2, coarseXOld.size())] + 0.25*xM;
                        yN = 0.75*coarseYOld[mod(detailView*2, coarseYOld.size())] + 0.25*yM;
                        xP = 0.5*coarseXOld[mod(detailView*2 - 1, coarseXOld.size())] + 0.5*coarseXOld[mod(detailView*2 + 1, coarseXOld.size())];
                        yP = 0.5*coarseYOld[mod(detailView*2 - 1, coarseYOld.size())] + 0.5*coarseYOld[mod(detailView*2 + 1, coarseYOld.size())];
                        glColor3f(1, 0, 0);
                        glPointSize(5);
                        glBegin(GL_POINTS);
                            glVertex2f(xM, yM);
                            glVertex2f(xN, yN);
                            glVertex2f(xP, yP);
                        glEnd();

                        // Draw the vector
                        glColor3f(0, 0, 1);
                        glLineWidth(3);
                        glBegin(GL_LINES);
                            glVertex2f(xP, yP);
                            glVertex2f(xN, yN);
                        glEnd();
                        glLineWidth(1);

                        // Draw the lines from which the new points were computed
                        glColor3f(1, 0, 0);
                        glBegin(GL_LINES);
                            glVertex2f(coarseXOld[mod(detailView*2-2, coarseXOld.size())], coarseYOld[mod(detailView*2-2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())], coarseYOld[mod(detailView*2+2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2-1, coarseXOld.size())], coarseYOld[mod(detailView*2-1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                            glVertex2f(xM, yM);
                        glEnd();
                        break;
            };
        } else if (previousOpp == 'D' && !closedCurve) {
            double xM, yM, xN, yN, xP, yP;
            char string1[10] = "1";
            char string2[10] = "0.75";
            char string3[10] = "-0.75";
            char string4[10] = "0.5";
            char string5[10] = "-0.5";
            char string6[10] = "0.375";
            char string7[10] = "-0.375";
            char string8[10] = "0.25";
            char string9[10] = "-0.25";
            char string10[10] = "0.125";
            char string11[10] = "-0.125";

            char cubic1[10] = "-0.323741";
            char cubic2[10] = "0.647582";
            char cubic3[10] = "-0.485612";
            char cubic4[10] = "0.215827";
            char cubic5[10] = "-0.053957";
            char cubic6[10] = "0.116327";
            char cubic7[10] = "-0.465306";
            char cubic8[10] = "0.697959";
            char cubic9[10] = "0.132653";
            char cubic10[10] = "-0.530612";
            char cubic11[10] = "0.795918";
            // Determine the degree of the decomposition
            switch (previousDegree) {
                case 0:
                        if (detailView == 0) {
                            // Draw the original points that have an impact on the vector
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[0], coarseYOld[0]);
                            glEnd();

                            viewX.push_back(coarseXOld[0]);
                            viewY.push_back(coarseYOld[0]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[0]+0.01, coarseYOld[0]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
                            }
                        } else if (detailView == detailX.size() - 1) {
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[coarseXOld.size() - 1], coarseYOld[coarseYOld.size() - 1]);
                            glEnd();

                            viewX.push_back(coarseXOld[coarseXOld.size() - 1]);
                            viewY.push_back(coarseYOld[coarseYOld.size() - 1]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[coarseXOld.size() - 1]+0.01, coarseYOld[coarseXOld.size() - 1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
                            }
                        } else {
                            // Draw the original points that have an impact on the vector
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2-1, coarseXOld.size())], coarseYOld[mod(detailView*2-1, coarseYOld.size())]);
                            glEnd();

                            viewX.push_back(coarseXOld[mod(detailView*2, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(detailView*2, coarseYOld.size())]);
                            viewX.push_back(coarseXOld[mod(detailView*2-1, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(detailView*2-1, coarseYOld.size())]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[mod(detailView*2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2-1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2-1, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string5[i]);
                            }

                            if (movedDetail || hideGeo) {
                                break;
                            }

                            // Draw line between two points used to construct the selected vector
                            glColor3f(1, 0, 0);
                            xM = -0.5*coarseXOld[mod(detailView*2, coarseXOld.size())] + 0.5*coarseXOld[mod(detailView*2 - 1, coarseXOld.size())];
                            yM = -0.5*coarseYOld[mod(detailView*2, coarseYOld.size())] + 0.5*coarseYOld[mod(detailView*2 - 1, coarseYOld.size())];
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())] + xM, coarseYOld[mod(detailView*2, coarseYOld.size())] + yM);
                            glEnd();

                            // Draw the vector
                            glColor3f(0, 0, 1);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())] + xM, coarseYOld[mod(detailView*2, coarseYOld.size())] + yM);
                            glEnd();
                            glLineWidth(1);

                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2-1, coarseXOld.size())], coarseYOld[mod(detailView*2-1, coarseYOld.size())]);
                            glEnd();
                        }
                        break;
                case 2:
                        // Draw the original points that have an impact on the vector
                        glColor3f(1, 0, 0);
                        glPointSize(10);
                        glBegin(GL_POINTS);
                            glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())], coarseYOld[mod(detailView*2+2, coarseYOld.size())]);
                            glVertex2f(coarseXOld[mod(detailView*2+3, coarseXOld.size())], coarseYOld[mod(detailView*2+3, coarseYOld.size())]);
                        glEnd();

                        viewX.push_back(coarseXOld[mod(detailView*2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2+1, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2+2, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2+2, coarseYOld.size())]);
                        viewX.push_back(coarseXOld[mod(detailView*2+3, coarseXOld.size())]);
                        viewY.push_back(coarseYOld[mod(detailView*2+3, coarseYOld.size())]);

                        if (detailView == 0) {

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[mod(detailView*2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string5[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+1, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+3, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+3, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string8[i]);
                            }

                            if (movedDetail || hideGeo) {
                                break;
                            }

                            xM = 0.5*coarseXOld[0] + 0.5*coarseXOld[2];
                            yM = 0.5*coarseYOld[0] + 0.5*coarseYOld[2];

                            xN = coarseXOld[3] - coarseXOld[2];
                            yN = coarseYOld[3] - coarseYOld[2]; 

                            xP = coarseXOld[1] - xM;
                            yP = coarseYOld[1] - yM;

                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(xM, yM);
                                glVertex2f(xM + 0.25*xN + xP, yM + 0.25*yN + yP);
                                glVertex2f(coarseXOld[2] + 0.25*xN, coarseYOld[2] + 0.25*yN);
                            glEnd();
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[0], coarseYOld[0]);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                            glEnd();

                            // Draw the vector components
                            glColor3f(1, 1, 0);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(xM, yM);
                                glVertex2f(xM + xP, yM + yP);
                                glVertex2f(xM + xP, yM + yP);
                                glVertex2f(xM + 0.25*xN + xP, yM + 0.25*yN + yP);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                                glVertex2f(coarseXOld[2] + 0.25*xN, coarseYOld[2] + 0.25*yN);
                            glEnd();
                            glLineWidth(1);

                            // Draw the vector
                            glColor3f(0, 0, 1);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(xM, yM);
                                glVertex2f(xM + 0.25*xN + xP, yM + 0.25*yN + yP);
                            glEnd();
                            glLineWidth(1);

                            // Draw lines for vectors
                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[3], coarseYOld[3]);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                            glEnd();


                        } else if (detailView == 1) {

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[mod(detailView*2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string9[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+1, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string2[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+3, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+3, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string8[i]);
                            }

                            if (movedDetail || hideGeo) {
                                break;
                            }

                            xM = coarseXOld[5] - coarseXOld[2];
                            yM = coarseYOld[5] - coarseYOld[2];

                            xN = coarseXOld[3] - coarseXOld[4];
                            yN = coarseYOld[3] - coarseYOld[4];

                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[4] + 0.75*xN, coarseYOld[4] + 0.75*yN);
                                glVertex2f(coarseXOld[2] + 0.25*xM, coarseYOld[2] + 0.25*yM);
                                glVertex2f(coarseXOld[4] + 0.75*xN + 0.25*xM, coarseYOld[4] + 0.75*yN + 0.25*yM);
                            glEnd();

                            // Draw the vector components
                            glColor3f(1, 1, 0);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[4], coarseYOld[4]);
                                glVertex2f(coarseXOld[4] + 0.75*xN, coarseYOld[4] + 0.75*yN);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                                glVertex2f(coarseXOld[2] + 0.25*xM, coarseYOld[2] + 0.25*yM);
                                glVertex2f(coarseXOld[4] + 0.75*xN, coarseYOld[4] + 0.75*yN);
                                glVertex2f(coarseXOld[4] + 0.75*xN + 0.25*xM, coarseYOld[4] + 0.75*yN + 0.25*yM);
                            glEnd();
                            glLineWidth(1);

                            // Draw the vector
                            glColor3f(0, 0, 1);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[4], coarseYOld[4]);
                                glVertex2f(coarseXOld[4] + 0.75*xN + 0.25*xM, coarseYOld[4] + 0.75*yN + 0.25*yM);
                            glEnd();
                            glLineWidth(1);

                            // Draw lines for vectors
                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[4], coarseYOld[4]);
                                glVertex2f(coarseXOld[3], coarseYOld[3]);
                                glVertex2f(coarseXOld[5], coarseYOld[5]);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                            glEnd();


                        } else if (detailView == detailX.size() - 1) {

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[mod(detailView*2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string8[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+1, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+3, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+3, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string5[i]);
                            }

                            if (movedDetail || hideGeo) {
                                break;
                            }

                            xM = 0.5*coarseXOld[coarseXOld.size() - 1] + 0.5*coarseXOld[coarseXOld.size() - 3];
                            yM = 0.5*coarseYOld[coarseXOld.size() - 1] + 0.5*coarseYOld[coarseXOld.size() - 3];

                            xN = coarseXOld[coarseXOld.size() - 4] - coarseXOld[coarseXOld.size() - 3];
                            yN = coarseYOld[coarseXOld.size() - 4] - coarseYOld[coarseXOld.size() - 3]; 

                            xP = coarseXOld[coarseXOld.size() - 2] - xM;
                            yP = coarseYOld[coarseXOld.size() - 2] - yM;

                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(xM, yM);
                                glVertex2f(xM + 0.25*xN + xP, yM + 0.25*yN + yP);
                                glVertex2f(coarseXOld[coarseXOld.size() - 3] + 0.25*xN, coarseYOld[coarseXOld.size() - 3] + 0.25*yN);
                            glEnd();

                            // Draw the vector components
                            glColor3f(1, 1, 0);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(xM, yM);
                                glVertex2f(xM + xP, yM + yP);
                                glVertex2f(xM + xP, yM + yP);
                                glVertex2f(xM + 0.25*xN + xP, yM + 0.25*yN + yP);
                                glVertex2f(coarseXOld[coarseXOld.size() - 3], coarseYOld[coarseXOld.size() - 3]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 3] + 0.25*xN, coarseYOld[coarseXOld.size() - 3] + 0.25*yN);
                            glEnd();
                            glLineWidth(1);

                            // Draw the vector
                            glColor3f(0, 0, 1);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(xM, yM);
                                glVertex2f(xM + 0.25*xN + xP, yM + 0.25*yN + yP);
                            glEnd();
                            glLineWidth(1);

                            // Draw lines for vectors
                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[coarseXOld.size() - 4], coarseYOld[coarseXOld.size() - 4]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 3], coarseYOld[coarseXOld.size() - 3]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 1], coarseYOld[coarseXOld.size() - 1]);
                                glVertex2f(coarseXOld[coarseXOld.size() - 3], coarseYOld[coarseXOld.size() - 3]);
                            glEnd();

                        } else {

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[mod(detailView*2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string8[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+1, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string2[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+3, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+3, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string9[i]);
                            }

                            if (movedDetail || hideGeo) {
                                break;
                            }

                            xM = 0.75*coarseXOld[mod(detailView*2+1, coarseXOld.size())] + 0.25*coarseXOld[mod(detailView*2+3, coarseXOld.size())];
                            yM = 0.75*coarseYOld[mod(detailView*2+1, coarseYOld.size())] + 0.25*coarseYOld[mod(detailView*2+3, coarseYOld.size())];
                            xN = 0.75*coarseXOld[mod(detailView*2+2, coarseXOld.size())] + 0.25*coarseXOld[mod(detailView*2, coarseXOld.size())];
                            yN = 0.75*coarseYOld[mod(detailView*2+2, coarseYOld.size())] + 0.25*coarseYOld[mod(detailView*2, coarseYOld.size())];
                            glColor3f(1, 0, 0);
                            glPointSize(5);
                            glBegin(GL_POINTS);
                                glVertex2f(xM, yM);
                                glVertex2f(xN, yN);
                            glEnd();

                            // Draw the vector
                            glColor3f(0, 0, 1);
                            glLineWidth(3);
                            glBegin(GL_LINES);
                                glVertex2f(xM, yM);
                                glVertex2f(xN, yN);
                            glEnd();
                            glLineWidth(1);

                            // Draw the lines from which the new points were computed
                            glColor3f(1, 0, 0);
                            glBegin(GL_LINES);
                                glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2+3, coarseXOld.size())], coarseYOld[mod(detailView*2+3, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())], coarseYOld[mod(detailView*2+2, coarseYOld.size())]);
                            glEnd();
                        }
                        break;
                case 3:
                        // Draw the original points that have an impact on the vector
                        if (detailView == detailX.size() - 1) {
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[coarseXOld.size()-1], coarseYOld[coarseYOld.size()-1]);
                                glVertex2f(coarseXOld[coarseXOld.size()-2], coarseYOld[coarseYOld.size()-2]);
                                glVertex2f(coarseXOld[coarseXOld.size()-3], coarseYOld[coarseYOld.size()-3]);
                                glVertex2f(coarseXOld[coarseXOld.size()-4], coarseYOld[coarseYOld.size()-4]);
                                glVertex2f(coarseXOld[coarseXOld.size()-5], coarseYOld[coarseYOld.size()-5]);
                            glEnd();

                            viewX.push_back(coarseXOld[coarseXOld.size()-1]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-1]);
                            viewX.push_back(coarseXOld[coarseXOld.size()-2]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-2]);
                            viewX.push_back(coarseXOld[coarseXOld.size()-3]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-3]);
                            viewX.push_back(coarseXOld[coarseXOld.size()-4]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-4]);
                            viewX.push_back(coarseXOld[coarseXOld.size()-5]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-5]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[coarseXOld.size()-1]+0.01, coarseYOld[coarseXOld.size()-1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic1[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size()-2]+0.01, coarseYOld[coarseXOld.size()-2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic2[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size()-3]+0.01, coarseYOld[coarseXOld.size()-3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic3[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size()-4]+0.01, coarseYOld[coarseXOld.size()-4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic4[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size()-5]+0.01, coarseYOld[coarseXOld.size()-5]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic5[i]);
                            }

                        } else if (detailView == detailX.size() - 2) {
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[coarseXOld.size()-3], coarseYOld[coarseYOld.size()-3]);
                                glVertex2f(coarseXOld[coarseXOld.size()-4], coarseYOld[coarseYOld.size()-4]);
                                glVertex2f(coarseXOld[coarseXOld.size()-5], coarseYOld[coarseYOld.size()-5]);
                                glVertex2f(coarseXOld[coarseXOld.size()-6], coarseYOld[coarseYOld.size()-6]);
                                glVertex2f(coarseXOld[coarseXOld.size()-7], coarseYOld[coarseYOld.size()-7]);
                            glEnd();

                            viewX.push_back(coarseXOld[coarseXOld.size()-3]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-3]);
                            viewX.push_back(coarseXOld[coarseXOld.size()-4]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-4]);
                            viewX.push_back(coarseXOld[coarseXOld.size()-5]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-5]);
                            viewX.push_back(coarseXOld[coarseXOld.size()-6]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-6]);
                            viewX.push_back(coarseXOld[coarseXOld.size()-7]);
                            viewY.push_back(coarseYOld[coarseYOld.size()-7]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[coarseXOld.size()-3]+0.01, coarseYOld[coarseXOld.size()-3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic6[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size()-4]+0.01, coarseYOld[coarseXOld.size()-4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic7[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size()-5]+0.01, coarseYOld[coarseXOld.size()-5]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic8[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size()-6]+0.01, coarseYOld[coarseXOld.size()-6]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic7[i]);
                            }
                            glRasterPos2f(coarseXOld[coarseXOld.size()-7]+0.01, coarseYOld[coarseXOld.size()-7]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic6[i]);
                            }

                        } else if (detailView == 0) {
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[0], coarseYOld[0]);
                                glVertex2f(coarseXOld[1], coarseYOld[1]);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                                glVertex2f(coarseXOld[3], coarseYOld[3]);
                                glVertex2f(coarseXOld[4], coarseYOld[4]);
                            glEnd();

                            viewX.push_back(coarseXOld[0]);
                            viewY.push_back(coarseYOld[0]);
                            viewX.push_back(coarseXOld[1]);
                            viewY.push_back(coarseYOld[1]);
                            viewX.push_back(coarseXOld[2]);
                            viewY.push_back(coarseYOld[2]);
                            viewX.push_back(coarseXOld[3]);
                            viewY.push_back(coarseYOld[3]);
                            viewX.push_back(coarseXOld[4]);
                            viewY.push_back(coarseYOld[4]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[0]+0.01, coarseYOld[0]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic1[i]);
                            }
                            glRasterPos2f(coarseXOld[1]+0.01, coarseYOld[1]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic2[i]);
                            }
                            glRasterPos2f(coarseXOld[2]+0.01, coarseYOld[2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic3[i]);
                            }
                            glRasterPos2f(coarseXOld[3]+0.01, coarseYOld[3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic4[i]);
                            }
                            glRasterPos2f(coarseXOld[4]+0.01, coarseYOld[4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic5[i]);
                            }

                        } else if (detailView == 1) {
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[2], coarseYOld[2]);
                                glVertex2f(coarseXOld[3], coarseYOld[3]);
                                glVertex2f(coarseXOld[4], coarseYOld[4]);
                                glVertex2f(coarseXOld[5], coarseYOld[5]);
                                glVertex2f(coarseXOld[6], coarseYOld[6]);
                            glEnd();

                            viewX.push_back(coarseXOld[2]);
                            viewY.push_back(coarseYOld[2]);
                            viewX.push_back(coarseXOld[3]);
                            viewY.push_back(coarseYOld[3]);
                            viewX.push_back(coarseXOld[4]);
                            viewY.push_back(coarseYOld[4]);
                            viewX.push_back(coarseXOld[5]);
                            viewY.push_back(coarseYOld[5]);
                            viewX.push_back(coarseXOld[6]);
                            viewY.push_back(coarseYOld[6]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[2]+0.01, coarseYOld[2]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic6[i]);
                            }
                            glRasterPos2f(coarseXOld[3]+0.01, coarseYOld[3]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic7[i]);
                            }
                            glRasterPos2f(coarseXOld[4]+0.01, coarseYOld[4]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic8[i]);
                            }
                            glRasterPos2f(coarseXOld[5]+0.01, coarseYOld[5]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic7[i]);
                            }
                            glRasterPos2f(coarseXOld[6]+0.01, coarseYOld[6]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic6[i]);
                            }

                        } else {
                            glColor3f(1, 0, 0);
                            glPointSize(10);
                            glBegin(GL_POINTS);
                                glVertex2f(coarseXOld[mod(detailView*2, coarseXOld.size())], coarseYOld[mod(detailView*2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())], coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())], coarseYOld[mod(detailView*2+2, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2+3, coarseXOld.size())], coarseYOld[mod(detailView*2+3, coarseYOld.size())]);
                                glVertex2f(coarseXOld[mod(detailView*2+4, coarseXOld.size())], coarseYOld[mod(detailView*2+4, coarseYOld.size())]);
                            glEnd();

                            viewX.push_back(coarseXOld[mod(detailView*2, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(detailView*2, coarseYOld.size())]);
                            viewX.push_back(coarseXOld[mod(detailView*2+1, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(detailView*2+1, coarseYOld.size())]);
                            viewX.push_back(coarseXOld[mod(detailView*2+2, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(detailView*2+2, coarseYOld.size())]);
                            viewX.push_back(coarseXOld[mod(detailView*2+3, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(detailView*2+3, coarseYOld.size())]);
                            viewX.push_back(coarseXOld[mod(detailView*2+4, coarseXOld.size())]);
                            viewY.push_back(coarseYOld[mod(detailView*2+4, coarseYOld.size())]);

                            glColor3f(1.0f, 1.0f, 1.0f);
                            glRasterPos2f(coarseXOld[mod(detailView*2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic9[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+1, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+1, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic10[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+2, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+2, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic11[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+3, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+3, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic10[i]);
                            }
                            glRasterPos2f(coarseXOld[mod(detailView*2+4, coarseXOld.size())]+0.01, coarseYOld[mod(detailView*2+4, coarseXOld.size())]-0.03);
                            for (int i = 0; i < 10; i++) {
                                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cubic9[i]);
                            }
                        }

                        if (movedDetail || hideGeo) {
                            break;
                        }
                        break;
            };
        }
    }

    glColor3f(0.33, 0.33, 0.33);
    glPointSize(10);
    glBegin(GL_POINTS);
        for (int i = 0; i < viewXOld.size(); i++) {
            glVertex2f(viewXOld[i], viewYOld[i]);
        }
    glEnd();

    // Draw all points
    glPointSize(10);
    for (int i = 0; i < coarseX.size(); i++) {
        if (i == coarseView) {
            glColor3f(1, 1, 0);
        } else {
            glColor3f(1, 1, 1);
        }
        glBegin(GL_POINTS);
            glVertex2f(coarseX[i], coarseY[i]);
        glEnd();
    }

    glColor3f(1, 1, 1);
    double yVal, xVal;
    if (closedCurve) {
        // Draw curve if enough points are available
        if (coarseX.size() > order && order > 1) {

            // Draw the line segments for the B-Spline
            yVal = 0.0;
            xVal = 0.0;
            int dVal = 0;
            double uVal;
            glLineWidth(3);
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i <= u; i++) {
                uVal = coarseKnotsClosed[order-1] + (i*1.0/u)*(coarseKnotsClosed[coarseXClosed.size()] - coarseKnotsClosed[order-1]);
                while (uVal < coarseKnotsClosed[dVal] || uVal >= coarseKnotsClosed[dVal+1]) {
                    dVal += 1;
                    if ((i*1.0/u) == 1) {
                        dVal -= 1;
                        break;
                    }
                }
                tie(xVal, yVal) = getCurveValue(uVal, coarseXClosed.size() - 1, order, dVal, coarseXClosed, coarseYClosed, coarseKnotsClosed);
                glVertex2f(xVal, yVal); 
            }
            glEnd();
            glLineWidth(1);
        }

    } else {
        // Draw curve if enough points are available
        if (coarseX.size() >= order && order > 1) {

            // Draw the line segments for the B-Spline
            yVal = 0.0;
            xVal = 0.0;
            glLineWidth(3);
            glBegin(GL_LINE_STRIP);
            int dVal = 0;
            for (int i = 0; i <= u; i++) {
                while ((i*1.0/u) < coarseKnots[dVal] || (i*1.0/u) >= coarseKnots[dVal+1]) {
                    dVal += 1;
                    if ((i*1.0/u) == 1 && coarseKnots[dVal] == 1) {
                        dVal -= 1;
                        break;
                    }
                }
                tie(xVal, yVal) = getCurveValue(i*1.0/u, coarseX.size() - 1, order, dVal, coarseX, coarseY, coarseKnots);
                glVertex2f(xVal, yVal);
            }
            glEnd();
            glLineWidth(1);
        }
    }
}

/**
* 
*/
void renderDetail(bool coloured) {
    // Initial setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    double dist = 1.5/(detailX.size()-1);
    double offset = -0.75;

    // Write to the screen
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.99, 0.9);
    char string1[64] = "Detail";
    int len1 = (int) strlen(string1);
    for (int i = 0; i < len1; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
    }

    // Draw dots for vector end points
    glPointSize(10);
    for (int i = 0; i < detailX.size(); i++) {
        if (i == detailView) {
            glColor3f(1, 1, 0);
        } else {
            glColor3f(0, 0, 1);
        }
        glBegin(GL_POINTS);
            glVertex2f((offset + i*dist) + detailX[i], detailY[i]);
        glEnd();
    }

    glColor3f(0, 0, 1);
    glPointSize(5);
    glBegin(GL_POINTS);
        for (int i = 0; i < detailX.size(); i++) {
            glVertex2f((offset + i*dist), 0);
        }
    glEnd();

    // Draw lines from base line to vectors
    glColor3f(0, 0, 1);
    glLineWidth(3);
    glBegin(GL_LINES);
        for (int i = 0; i < detailX.size(); i++) {
            glVertex2f((offset + i*dist), 0);
            glVertex2f((offset + i*dist) + detailX[i], detailY[i]);
        }
    glEnd();
    glLineWidth(1);

    // Draw line from which detail vectors originate
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
        glVertex2f(offset, 0);
        glVertex2f(-1*offset, 0);
    glEnd();
}

/**
* 
*/
void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_UP) {
            order++;
            computeClosedPoints();
        } else if (key == GLFW_KEY_DOWN) {
            if (order > 1) {
                order--;
                computeClosedPoints();
            }
        }
    }
}

/**
* 
*/
void mouseClick (GLFWwindow *sender, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Determine in which area the mouse is
        if (mouseX <= button_width) {
            // Buttons clicked
            cout << "Button block..." << endl;
            handleButtons();
        
        } else if (mouseY < window_height - originalStartY) {
            // Original block clicked
            cout << "Original block..." << endl;
            handleOriginal(1);

        } else if (mouseY < window_height - coarseStartY) {
            // Coarse block clicked
            cout << "Coarse block..." << endl;
            handleCoarse(1);

        } else {
            // Detail block clicked
            cout << "Detail block..." << endl;
            handleDetail(1);

        }
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        // Reset variables
        originalSelect = -1;
        coarseSelect = -1;
        detailSelect = -1;
        detailView = -1;
        coarseView = -1;
        viewXOld = viewX;
        viewYOld = viewY;

    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        // Determine in which area the mouse is
        if (mouseX <= button_width) {
            // Buttons clicked
            cout << "Button block..." << endl;
            handleButtons();
        
        } else if (mouseY < window_height - originalStartY) {
            // Original block clicked
            cout << "Original block..." << endl;
            handleOriginal(2);

        } else if (mouseY < window_height - coarseStartY) {
            // Coarse block clicked
            cout << "Coarse block..." << endl;
            handleCoarse(2);

        } else {
            // Detail block clicked
            cout << "Detail block..." << endl;
            handleDetail(2);

        } 

    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        // Determine in which area the mouse is
        if (mouseX <= button_width) {
            // Buttons clicked
            cout << "Button block..." << endl;
            handleButtons();
        
        } else if (mouseY < window_height - originalStartY) {
            // Original block clicked
            cout << "Original block..." << endl;
            handleOriginal(3);

        } else if (mouseY < window_height - coarseStartY) {
            // Coarse block clicked
            cout << "Coarse block..." << endl;
            handleCoarse(3);

        } else {
            // Detail block clicked
            cout << "Detail block..." << endl;
            handleDetail(3);

        } 
    }
}

/**
* 
*/
void mouseMove (GLFWwindow *sender, double mX, double mY) {
    mouseX = mX;
    mouseY = mY;

    // Check if any of the points were selected
    double xVal, yVal;
    if (originalSelect != -1 && !decomposed) {
        xVal = convertMouseX(mouseX, originalStartX, originalWidth, 1);
        yVal = convertMouseY(mouseY, 0, originalHeight, 1);
        originalX[originalSelect] = xVal;
        originalY[originalSelect] = yVal;

        // Check to see if the movements should be mirrored in the coarse view
        if (!decomposed) {
            coarseX[originalSelect] = xVal;
            coarseY[originalSelect] = yVal;
            originalXRec[originalSelect] = xVal;
            originalYRec[originalSelect] = yVal;
            current.movePoint(xVal, yVal, originalSelect);
        }
        computeClosedPoints();
        
    } else if (coarseSelect != -1) {
        xVal = convertMouseX(mouseX, coarseStartX, coarseWidth, 1);
        yVal = convertMouseY(mouseY, originalHeight, coarseHeight, 1);
        coarseX[coarseSelect] = xVal;
        coarseY[coarseSelect] = yVal;
        current.movePoint(xVal, yVal, coarseSelect);

        reconstructed = current;
        int deg = 0;
        while (deg >= 0) {
            if (closedCurve) {
                deg = reconstructed.reconstructClosed();
            } else {
                deg = reconstructed.reconstructOpen();
            }
        }

        originalXRec = reconstructed.getCoarseX();
        originalYRec = reconstructed.getCoarseY();
        movedCoarse = true;

        // Check to see if the movements should be mirrored in the original view
        if (!decomposed) {
            originalX[coarseSelect] = xVal;
            originalY[coarseSelect] = yVal;
        }
        computeClosedPoints();

    } else if (detailSelect != -1) {
        xVal = convertMouseX(mouseX, detailStartX, detailWidth, 1);
        yVal = convertMouseY(mouseY, originalHeight+coarseHeight, detailHeight, 1);
        double detailSpace = 1.5/(detailX.size()-1);
        detailX[detailSelect] = xVal + 0.75 - (detailSpace*detailSelect);
        detailY[detailSelect] = yVal;
        movedDetail = true;

        // Update the current object with the new value
        current.movePoint((xVal + 0.75 - (detailSpace*detailSelect)), yVal, coarseX.size() + detailSelect);

        reconstructed = current;
        int deg = 0;
        while (deg >= 0) {
            if (closedCurve) {
                deg = reconstructed.reconstructClosed();
            } else {
                deg = reconstructed.reconstructOpen();
            }
        }

        originalXRec = reconstructed.getCoarseX();
        originalYRec = reconstructed.getCoarseY();
        computeClosedPoints();
    }
}

/**
* 
*/
void mouseScroll(GLFWwindow *sender, double xOffset, double yOffset) {

}

/**
* 
*/
void handleButtons() {
    // Reset selection variables
    originalSelect = -1;
    coarseSelect = -1;
    detailSelect = -1;
    detailView = -1;
    coarseView = -1;
    viewXOld.clear();
    viewYOld.clear();

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
        // Switch open/closed flag
        case 1:
                if (!decomposed) {
                    closedCurve = !closedCurve;
                    computeClosedPoints();
                }
                break;

        // Hide/show original curve
        case 2:
                if (decomposed) {
                    hideOriginal = !hideOriginal;
                }
                break;

        // Hide/show geometric interpretation
        case 3:
                if (decomposed) {
                    hideGeo = !hideGeo;
                }
                break;

        // Increase the order
        case 4:
                order++;
                computeClosedPoints();
                break;

        // Decrease the order
        case 5:
                if (order > 1) {
                    order--;
                    computeClosedPoints();
                }
                break;

        // Cycle the decomposition type
        case 6:
                switch(decompDegree) {
                    case 0:
                            decompDegree = 2;
                            break;
                    case 2:
                            decompDegree = 3;
                            break;
                    case 3:
                            decompDegree = 0;
                            break;
                    default:
                            decompDegree = 0;
                            break;
                };
                cout << "Decomposition degree: " << decompDegree << endl;
                break;

        // Copy object from current to previous and decompose one level
        case 7:
                decomposed = true;
                movedDetail = false;
                movedCoarse = false;
                previous = current;
                previousDegree = decompDegree;
                previousOpp = 'D';
                if (closedCurve) {
                    switch(decompDegree) {
                        case 0:
                                current.decompHaarClosed(true);
                                break;
                        case 2:
                                current.decompChaikinClosed(true);
                                break;
                        case 3:
                                current.decompCubicClosed(true);
                                break;
                    };
                    
                } else {
                    switch(decompDegree) {
                        case 0:
                                current.decompHaarOpen(true);
                                break;
                        case 2:
                                current.decompChaikinOpen(true);
                                break;
                        case 3:
                                current.decompCubicOpen(true);
                                break;
                    };
                }

                // Copy points over to display vectors
                coarseX = current.getCoarseX();
                coarseY = current.getCoarseY();
                detailX = current.getDetailX();
                detailY = current.getDetailY();
                coarseXOld = previous.getCoarseX();
                coarseYOld = previous.getCoarseY();
                if (coarseXOld.size() % 2 == 1) {
                    coarseXOld.push_back(coarseXOld[coarseXOld.size() - 1]);
                    coarseYOld.push_back(coarseYOld[coarseYOld.size() - 1]);
                }
                computeClosedPoints();

                break;

        // Copy object from current to previous and reconstruct one level
        case 8:
                previous = current;
                movedDetail = false;
                movedCoarse = false;
                previousOpp = 'R';
                if (closedCurve) {
                    previousDegree = current.reconstructClosed();
                } else {
                    previousDegree = current.reconstructOpen();
                }

                // Copy points over to display vectors
                if (previousDegree > -1) {
                    detailXOld = detailX;
                    detailYOld = detailY;
                    coarseX = current.getCoarseX();
                    coarseY = current.getCoarseY();
                    detailX = current.getDetailX();
                    detailY = current.getDetailY();
                    coarseXOld = previous.getCoarseX();
                    coarseYOld = previous.getCoarseY();
                    computeClosedPoints();
                }

                for (int i = 0; i < coarseX.size(); i++) {
                    cout << coarseX[i] << " = " << originalX[i] << "     " << coarseY[i] << " = " << originalY[i] << endl;
                }

                break;

        // Clear everything
        case 9:
                resetAll();
                break;
    };
}

/**
* 
*/
void handleOriginal(int button) {
    //cout << mouseX << " " << mouseY << " - " << originalStartX << " " << originalStartY << endl;
    double xVal = convertMouseX(mouseX, originalStartX, originalWidth, 1);
    double yVal = convertMouseY(mouseY, 0, originalHeight, 1);
    cout << "Original - (" << xVal << ", " << yVal << ")" << endl;

    // Reset variables
    originalSelect = -1;
    coarseSelect = -1;
    detailSelect = -1;
    coarseView = -1;
    detailView = -1;
    viewXOld.clear();
    viewYOld.clear();

    // Check whether a point was clicked
    for (int i = 0; i < originalX.size(); i++) {
        if (sqrt(pow(xVal - originalX[i], 2) + pow(yVal - originalY[i], 2)) < clickDistance) {
            originalSelect = i;
        }
    }

    switch (button) {
        // Left mouse button
        case 1:
                if (originalSelect == -1 && !decomposed) {
                    originalX.push_back(xVal);
                    originalY.push_back(yVal);
                    originalXRec.push_back(xVal);
                    originalYRec.push_back(yVal);
                    coarseX.push_back(xVal);
                    coarseY.push_back(yVal);
                    current.addPoint(xVal, yVal);
                    originalSelect = originalX.size() - 1;
                    computeClosedPoints();
                }

                // Handle case where the curve has been decomposed
                if (decomposed) {

                }

                break;

        // Right mouse button
        case 2:
                if (originalSelect > -1 && !decomposed) {
                    originalX.erase(originalX.begin() + originalSelect);
                    originalY.erase(originalY.begin() + originalSelect);
                    originalXRec = originalX;
                    originalYRec = originalY;
                    coarseX.erase(coarseX.begin() + originalSelect);
                    coarseY.erase(coarseY.begin() + originalSelect);
                    current.deletePoint(originalSelect);
                    computeClosedPoints();
                }
                originalSelect = -1;

                // Handle case where the curve has been decomposed
                if (decomposed) {

                }

                break;

        // Center mouse button
        case 3:
                originalSelect = -1;
                break;
    };

    // Recompute the knots to reflect the changes
    computeOriginalKnots();
    computeCoarseKnots();
}

/**
* 
*/
void handleCoarse(int button) {
    double xVal = convertMouseX(mouseX, coarseStartX, coarseWidth, 1);
    double yVal = convertMouseY(mouseY, originalHeight, coarseHeight, 1);
    cout << "Coarse - (" << xVal << ", " << yVal << ")" << endl;

    // Reset variables
    originalSelect = -1;
    coarseSelect = -1;
    detailSelect = -1;
    coarseView = -1;
    detailView = -1;
    viewXOld = viewX;
    viewYOld = viewY;

    // Check whether a point was clicked
    for (int i = 0; i < coarseX.size(); i++) {
        if (sqrt(pow(xVal - coarseX[i], 2) + pow(yVal - coarseY[i], 2)) < clickDistance) {
            coarseSelect = i;
        }
    }

    switch (button) {
        // Left mouse button
        case 1:
                coarseView = coarseSelect;
                break;

        // Right mouse button
        case 2:
                coarseSelect = -1;
                break;

        // Center mouse button
        case 3:
                coarseView = coarseSelect;
                coarseSelect = -1;
                break;
    };

    // Recompute the knots to reflect the changes
    computeOriginalKnots();
    computeCoarseKnots();
}

/**
* 
*/
void handleDetail(int button) {
    double xVal = convertMouseX(mouseX, detailStartX, detailWidth, 1);
    double yVal = convertMouseY(mouseY, originalHeight+coarseHeight, detailHeight, 1);
    cout << "Detail - (" << xVal << ", " << yVal << ")" << endl;

    // Reset variables
    originalSelect = -1;
    coarseSelect = -1;
    detailSelect = -1;
    coarseView = -1;
    detailView = -1;
    viewXOld = viewX;
    viewYOld = viewY;

    // Check whether a point was clicked
    double actX, actY;
    double detailSpace = 1.5/(detailX.size()-1);
    for (int i = 0; i < detailX.size(); i++) {
        actX = detailX[i] - 0.75 + (i*detailSpace);
        actY = detailY[i];
        if (sqrt(pow(xVal - actX, 2) + pow(yVal - actY, 2)) < clickDistance) {
            detailSelect = i;
        }
    }

    int deg = 0;
    switch (button) {
        // Left mouse button
        case 1:
                detailView = detailSelect;
                break;

        // Right mouse button
        case 2:
                if (detailSelect >= 0) {
                    current.movePoint(0, 0, coarseX.size() + detailSelect);
                    detailX[detailSelect] = 0;
                    detailY[detailSelect] = 0;
                    detailSelect = -1;
                }

                reconstructed = current;
                while (deg >= 0) {
                    if (closedCurve) {
                        deg = reconstructed.reconstructClosed();
                    } else {
                        deg = reconstructed.reconstructOpen();
                    }
                }

                originalXRec = reconstructed.getCoarseX();
                originalYRec = reconstructed.getCoarseY();
                break;

        // Center mouse button
        case 3:
                detailView = detailSelect;
                detailSelect = -1;
                break;
    };
}

/**
* Compute a point on the curve for a given u
*/
tuple<double, double> getCurveValue(double uVal, int mVal, int kVal, int dVal, vector<double> xPoint, vector<double> yPoint, vector<double> knotSequence) {
    vector<double> cX, cY;
    double omega = 0.0f;
    for (int i = 0; i < kVal; i++) {
        cX.push_back(xPoint[dVal - i]);
        cY.push_back(yPoint[dVal - i]);
    }

    for (int r = kVal; r > 1; r--) {
        int i = dVal;
        for (int s = 0; s < r - 1; s++) {
            omega = (uVal - knotSequence[i])/(knotSequence[i+r-1] - knotSequence[i]);
            cX[s] = omega*cX[s] + (1 - omega)*cX[s+1];
            cY[s] = omega*cY[s] + (1 - omega)*cY[s+1];
            i -= 1;
        }
    }
    return make_tuple(cX[0], cY[0]);
}

/**
* Computes the mouse x-coordinate in the block that is specified
*/
double convertMouseX(double mousePos, double left, double width, double innerDim) {
    double hold = (mousePos - left)/width; // Convert to be between 0 and 1
    hold = (2*innerDim*hold) - innerDim;
    return hold;
}

/**
* Computes the mouse y-coordinate in the block that is specified
*/
double convertMouseY(double mousePos, double top, double height, double innerDim) {
    double hold = (mousePos - top)/height; // Convert to be between 0 and 1
    hold = (-2*innerDim*hold) + innerDim;
    return hold;
}

/**
* 
*/
int mod(int value1, int value2) {
    int hold = value1 % value2;
    if (hold < 0) {
        hold += value2;
    }
    return hold;
}

/**
* Clears and recomputes the knot sequence for the original points
*/
void computeOriginalKnots() {
    if (!closedCurve) {
        int numVals = originalX.size();
        originalKnots.clear();
        for (int i = 1; i < order; i++) {
            originalKnots.push_back(0);
        }
        for (int i = 0; i <= (numVals - order + 1); i++) {
            originalKnots.push_back(i*1.0/(numVals - order + 1));
        }
        for (int i = 1; i < order; i++) {
            originalKnots.push_back(1);
        }
    } else {
        int numVals = originalXClosed.size();
        originalKnotsClosed.clear();
        for (int i = 0; i <= (numVals + order - 1); i++) {
            originalKnotsClosed.push_back(i*1.0/(numVals+order-1));
        }
    }
}

/**
* Clears and recomputes the knot sequence for the coarse points
*/
void computeCoarseKnots() {
    if (!closedCurve) {
        int numVals = coarseX.size();
        coarseKnots.clear();
        for (int i = 1; i < order; i++) {
            coarseKnots.push_back(0);
        }
        for (int i = 0; i <= (numVals - order + 1); i++) {
            coarseKnots.push_back(i*1.0/(numVals - order + 1));
        }
        for (int i = 1; i < order; i++) {
            coarseKnots.push_back(1);
        }

        numVals = originalXRec.size();
        originalRecKnots.clear();
        for (int i = 1; i < order; i++) {
            originalRecKnots.push_back(0);
        }
        for (int i = 0; i <= (numVals - order + 1); i++) {
            originalRecKnots.push_back(i*1.0/(numVals - order + 1));
        }
        for (int i = 1; i < order; i++) {
            originalRecKnots.push_back(1);
        }
    } else {
        int numVals = coarseXClosed.size();
        coarseKnotsClosed.clear();
        for (int i = 0; i <= (numVals + order - 1); i++) {
            coarseKnotsClosed.push_back(i*1.0/(numVals+order-1));
        }

        numVals = originalXRecClosed.size();
        originalRecKnotsClosed.clear();
        for (int i = 0; i <= (numVals + order - 1); i++) {
            originalRecKnotsClosed.push_back(i*1.0/(numVals+order-1));
        }
    }
}

/**
* 
*/
void computeClosedPoints() {
    // Compute the closed points for the original curve
    originalXClosed.clear();
    originalYClosed.clear();
    if (originalX.size() > 0) {
        for (int i = 0; i < originalX.size() + (order - 1); i++) {
            originalXClosed.push_back(originalX[mod(i, originalX.size())]);
            originalYClosed.push_back(originalY[mod(i, originalY.size())]);
        }
    }
    computeOriginalKnots();

    // Compute the closed points for the coarse curve
    coarseXClosed.clear();
    coarseYClosed.clear();
    originalXRecClosed.clear();
    originalYRecClosed.clear();
    if (coarseX.size() > 0) {
        for (int i = 0; i < coarseX.size() + (order - 1); i++) {
            coarseXClosed.push_back(coarseX[mod(i, coarseX.size())]);
            coarseYClosed.push_back(coarseY[mod(i, coarseY.size())]);
        }

        for (int i = 0; i < originalXRec.size() + (order - 1); i++) {
            originalXRecClosed.push_back(originalXRec[mod(i, originalX.size())]);
            originalYRecClosed.push_back(originalYRec[mod(i, originalY.size())]);
        }
    }
    computeCoarseKnots();
}

/**
* Clears the drawing and reset all variables
*/
void resetAll() {
    // Reset variables to original values
    closedCurve = false;
    originalSelect = -1;
    coarseSelect = -1;
    detailSelect = -1;
    detailView = -1;
    coarseView = -1;
    decomposed = false;
    order = 2;
    decompDegree = 0;
    previousDegree = -1;
    movedCoarse = false;
    movedDetail = false;
    hideOriginal = false;
    hideGeo = false;

    // Clear all vectors
    originalX.clear();
    originalY.clear();
    originalXRec.clear();
    originalYRec.clear();
    originalKnots.clear();
    originalXClosed.clear();
    originalYClosed.clear();
    originalXRecClosed.clear();
    originalYRecClosed.clear();
    originalKnotsClosed.clear();
    originalRecKnots.clear();
    originalRecKnotsClosed.clear();

    coarseX.clear();
    coarseY.clear();
    coarseXOld.clear();
    coarseYOld.clear();
    coarseKnots.clear();
    coarseXClosed.clear();
    coarseYClosed.clear();
    coarseKnotsClosed.clear();

    detailX.clear();
    detailY.clear();

    // Reset objects
    current = MultiRes1D();
    previous = MultiRes1D();
}

int main(int argc, char *argv[]) {
    // Try to initialize GLFW and GLUT
    if (!glfwInit()) {
        return 1;
    }
    glutInit( & argc, argv );

    // Create rendering window
    window = glfwCreateWindow(1600, 960, "1D Multiresolution", NULL, NULL);
    if (!window) {
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Variable initialization
    closedCurve = false;
    originalSelect = -1;
    coarseSelect = -1;
    detailSelect = -1;
    detailView = -1;
    coarseView = -1;
    decomposed = false;
    order = 2;
    decompDegree = 0;
    previousDegree = -1;

    // Create empty instances of objects
    current = MultiRes1D(false);
    previous = MultiRes1D(false);

    // User input functions
    glfwSetKeyCallback(window, keyboard);
    glfwSetMouseButtonCallback(window, mouseClick);
    glfwSetCursorPosCallback(window, mouseMove);
    glfwSetScrollCallback(window, mouseScroll);

    // Main window loop
    while (!glfwWindowShouldClose(window)) {

        // Recalculate width and height of different componenets
        glfwGetFramebufferSize(window, &window_width, &window_height);
        button_width = 0.1*window_width;

        originalStartX = button_width;
        originalStartY = 0.66*window_height;
        originalWidth = window_width - button_width;
        originalHeight = window_height - originalStartY;

        coarseStartX = button_width;
        coarseStartY = 0.33*window_height;
        coarseWidth = window_width - button_width;
        coarseHeight = originalStartY - coarseStartY;

        detailStartX = button_width;
        detailStartY = 0;
        detailWidth = window_width - button_width;
        detailHeight = coarseStartY - detailStartY;

        
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
