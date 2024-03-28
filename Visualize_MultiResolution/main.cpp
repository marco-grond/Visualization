/*
*
* Wavelet project - CPSC 689 - Marco Marten Grond
*
*/

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;

// Display window variables
GLFWwindow *window;
int window_width, window_height;
double angle = 0.0f;

// Function definitions
void render();
void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods);
void mouseClick (GLFWwindow *sender, int button, int action, int mods);

/*
* Function to render the scene
*/
void render() {
    // Initial setup for display
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -7.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glRotatef(angle, 1.0f, 1.0f, 1.0f);
    glScalef(1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);

    /*glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();*/

  glBegin(GL_QUADS);		// Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);	// Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);	// Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);	// Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);	// Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);	// Color Red	
    glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);	// Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);	// Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);	// Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);	// Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);	// Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);	// Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);	// Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Right)
  glEnd();	

    angle = angle + 1.0f;
}

/*
* Function to listen for keyboard input
*/
void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods) {

}

/*
* Function to listen for mouse button clicks
*/
void mouseClick (GLFWwindow *sender, int button, int action, int mods) {

}

/*
* Function to listen for mouse movement
*/
void mouseMove (GLFWwindow *sender, double mX, double mY) {

}

/*
* Function to listen for mouse scrolling
*/
void mouseScroll(GLFWwindow *sender, double xOffset, double yOffset) {

}

/*
* Main function to run the program
*/
int main() {
    // Try to initialize GLFW
    if (!glfwInit()) {
        return 1;
    }

    // Create rendering window
    window = glfwCreateWindow(640, 480, "Wavelet Tool", NULL, NULL);

    // Check whether a valid pointer to the window was generated
    if (!window) {
        return 1;
    }

    // Tell OpenGL which window to draw to
    glfwMakeContextCurrent(window);

    // Functions to handle user input
    glfwSetKeyCallback(window, keyboard);
    glfwSetMouseButtonCallback(window, mouseClick);
    glfwSetCursorPosCallback(window, mouseMove);
    glfwSetScrollCallback(window, mouseScroll);

    // Loop to check whether window should open or close
    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glViewport(0, 0, window_width, window_height);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
