/* To run:
g++ main.cpp -lGL -lGLU -lglfw -lGLEW
./a.out
*/

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Global variable of pointer to GLFW window
GLFWwindow *window;

// Create global variables to store width and height of window
int w, h;

// Variables to hold information with regards to mouse controls
// Mouse coordinates;
double mouseX, mouseY;

// Vector to store locations of control points
vector<double> x, y, x2, y2;

// Variable to store the point that was clicked or selected (-1 means no point is selected)
int selected = -1;

// Size of the point and the area that we can click on to select a point (Rather than a single pixel)
float selectedDistance = 0.05f;

double convertX() {
    
}

double convertY() {

}

/*
Create rendering function
*/
void render1 () {
    // Set transformation matrices
    // Any transformation calls will effect the modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // Initialize to identity
    glLoadIdentity();

    // Second matrix to set is the projection matrix - how does scene get projected onto screen
    glMatrixMode(GL_PROJECTION);

    //Initialize to identity
    glLoadIdentity();

    // Put orthographic projection matrix in there - just flatten anything
    // View volume is a cube where x, y and z goes from -1 to 1
    // Anything drawn with coordinates outside of view volume won't be drawn
    glOrtho(-10, 10, -10, 10, -10, 10);

    // When working in 3D, need perspective matrix - Perspective projection
    // gluPerspective(fov, aspect_ratio, near_plane, far_plane);
    // if not using glu, can use: glFrustum(...);

    //Increase size of points being drawn
    glPointSize(5);
    glBegin(GL_POINTS);

    glColor3f(1.0f, 1.0f, 1.0f);
    // Iterate over all control points and draw them
    for (int i = 0; i < x.size(); i++) {
        glVertex2f(x[i], y[i]);
    }

    glEnd();
}

/*
Create rendering function
*/
void render2 () {
    // Set transformation matrices
    // Any transformation calls will effect the modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // Initialize to identity
    glLoadIdentity();

    // Second matrix to set is the projection matrix - how does scene get projected onto screen
    glMatrixMode(GL_PROJECTION);

    //Initialize to identity
    glLoadIdentity();

    // Put orthographic projection matrix in there - just flatten anything
    // View volume is a cube where x, y and z goes from -1 to 1
    // Anything drawn with coordinates outside of view volume won't be drawn
    glOrtho(-10, 10, -10, 10, -10, 10);

    // When working in 3D, need perspective matrix - Perspective projection
    // gluPerspective(fov, aspect_ratio, near_plane, far_plane);
    // if not using glu, can use: glFrustum(...);

    //Increase size of points being drawn
    glPointSize(5);
    glBegin(GL_POINTS);

    glColor3f(1.0f, 1.0f, 1.0f);
    // Iterate over all control points and draw them
    for (int i = 0; i < x2.size(); i++) {
        glVertex2f(x2[i], y2[i]);
    }

    glEnd();
}

void renderMain() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, h/2, w/2, h/2);
    render1();

    glViewport(w/2, h/2, w/2, h/2);
    render2();
}


/*
Doing keyboard input with glfw.
GLFW has callback functions which are used to get keyboard input.
First parameter - Pointer to GLFWwindow that has had keyboard input happened
Second parameter - Key that was pressed or released
Fourth parameter - Indicates whether key is being pressed, released or held
Fifth parameter - Indicates whether a modifier key is being held down (CTRL, SHIFT etc)
*/
void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods) {
    // Different constants for different keys in GLFW - can look those up.
    // Different constants for different actions - in this case a key press (won't do anything if key is held down
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        //Just print something out to console if A is pressed
        cout << "A was pressed" << endl;
    }

    // Holding down the key
    if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
        //Just print something out to console if A is pressed
        cout << "A is held down" << endl;
    }
}

double convertMouseX(double mousePos, double left, double width, double innerDim) {
    double hold = (mousePos - left)/width; // Convert to be between 0 and 1
    hold = (2*innerDim*hold) - 1*innerDim;
    return hold;
}

double convertMouseY(double mousePos, double top, double height, double innerDim) {
    double hold = (mousePos - top)/height; // Convert to be between 0 and 1
    hold = (-2*innerDim*hold) + 1*innerDim;
    return hold;
}

/*
Callback functions for mouse - One for mouse clicked
Pointer to glfw window
integer for which button was clicked or released
integer for whether button was clicked or released
*/
void mouseClick (GLFWwindow *sender, int button, int action, int mods) {
    if (mouseX < w/2) {
        if (mouseY < h/2) {
            cout << "Top left" << endl;
        } else {
            cout << "Bottom left" << endl;
        }
    } else {
        if (mouseY < h/2) {
            cout << "Top right" << endl;
        } else {
            cout << "Bottom right" << endl;
        }
    }
    // Check whether the mouse button was clicked
    if (action == GLFW_PRESS) {
        // Check if a point was selected (clicked close enough to a point)
        for (int i = 0; i < x.size(); i++) {
            // Compute L1 norm - L2 norm might be better
            if (abs(x[i] - mouseX) < selectedDistance && abs(y[i] - mouseY) < selectedDistance) {
                selected = i;
            }
        }

        // Add a control point if nothing is selected and we clicked the left mouse button
        if (button == GLFW_MOUSE_BUTTON_LEFT && selected == -1) {
            // Push x and y coordinates to respective vectors
            double holdX, holdY;
            if (mouseX < w/2 && mouseY < h/2) {
                cout << convertMouseX(mouseX, 0.0, w/2.0, 10.0) << endl;
                cout << convertMouseY(mouseY, 0.0, h/2, 10.0) << endl;
                x.push_back(convertMouseX(mouseX, 0.0, w/2.0, 10.0));
                y.push_back(convertMouseY(mouseY, 0.0, h/2, 10.0));
            } else if (w/2 < mouseX < w && mouseY < h/2) {
                x2.push_back(convertMouseX(mouseX, w/2.0, w/2.0, 10.0));
                y2.push_back(convertMouseY(mouseY, 0.0, h/2, 10.0));            }
        }

        // Check if right mouse button was clicked to delete a point
        if (button == GLFW_MOUSE_BUTTON_RIGHT && selected != -1) {
            // Remove the selected index from the vectors
            x.erase(x.begin() + selected);
            y.erase(y.begin() + selected);
            selected = -1;
        }
    }

    // Check whether the mouse button was released
    if (action == GLFW_RELEASE) {
        // Unselect a point
        selected = -1;
    }
}

/*
Callback function for mouse - One for when mouse cursor position changes
sender - Pointer to glfw window
mX - new coordinated of mouse x-position - given in screen coordinates - goes from 0 to width -> Need to convert to world coordinates [-1, 1]
mY - new coordinates of mouse y-position - given in screen coordinates - goes from 0 to height -> Need to convert to world coordinates [-1, 1]
*/
void mousePos (GLFWwindow *sender, double mX, double mY) {
    // Convert to world coordinated
    mouseX = mX;//(2 * mX/w) - 1;
    mouseY = mY;//(-2 * mY/h) + 1; // Need to flip, because 0 is at top and h is at bottom, but we want 1 at top and -1 at bottom

    // Moving points - point was clicked and was not deleted
    if (selected != -1) {
        x[selected] = mouseX;
        y[selected] = mouseY;
    }
}


/*
Main function
*/
int main () {
    // Try to initialize GLFW
    if (!glfwInit()) {
        return 1;
    }

    // Create window to do all renderings in
    // First two args width and height
    // Third arg name of window
    window = glfwCreateWindow(640, 480, "My window", NULL, NULL);
    
    // Check if we got a valid pointer to a window
    if (!window) {
        return 1;
    }

    // Tell OpenGL which window to draw to (All OpenGL stuff gets rendered in this window
    glfwMakeContextCurrent(window);

    // Tell GLFW about the callback for the keypresses
    // The first argument is the window on which it is used, the second is the callback function
    glfwSetKeyCallback(window, keyboard);

    // Callback functions for the mouse clicks
    glfwSetMouseButtonCallback(window, mouseClick);

    // Callback functions for the mouse movement
    glfwSetCursorPosCallback(window, mousePos);

    // Check whether window should close (Clicking the x-button, sets a flag which you have to check for)
    while (!glfwWindowShouldClose(window)) {
        // Done every loop in case user changes window size

        // Get the size of the window and store it into w and h
        glfwGetFramebufferSize(window, &w, &h);

        // Tell OpenGL where to draw (This is to draw in entire window)
        // First args top left corner, second 2 args width and heigth
        glViewport(0, 0, w, h);

        renderMain();

        // First rendering is sent to a buffer that isn't displayed, and calling this displays it ???
        glfwSwapBuffers(window);

        // Detect any input events (keyboard/mouse) - needed to check if window closed
        glfwPollEvents();
    }


    // Destroy window at end of main function
    glfwDestroyWindow(window);
    // Terminate GLFW at end of main function
    glfwTerminate();
    return 0;
}
