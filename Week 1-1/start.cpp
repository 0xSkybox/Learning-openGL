#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h> 
#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// *************** CONSTANTS *************************
inline constexpr unsigned int SCREEN_WIDTH = 1280;
inline constexpr unsigned int SCREEN_HEIGHT = 720;

// --------------- WINDOW VARIABLES -----------------
int windowID;  // Glut window ID (for display)
int Win[2];   // window (x,y) size

// Wireframe or filled
bool fill_enabled = true;

// ***********  FUNCTION HEADER DECLARATIONS ****************
// Initialization functions
void initGlut(char* winName);
void initGl();

// Callbacks for handling events in glut
void myReshape(int w, int h);
void display(void);
void keyboardFunc(unsigned char, int, int);


// ******************** FUNCTIONS ************************

// main() function
// Initializes the user interface (and any user variables)
// then hands over control to the event handler, which calls
// display() whenever the GL window needs to be redrawn.
int main(int argc, char** argv) {
    // Process program arguments
    if (argc != 3) {
        printf("Usage: demo [width] [height]\n");
        printf("Using %u,%u window by default...\n", SCREEN_WIDTH, SCREEN_HEIGHT);
        Win[0] = SCREEN_WIDTH;
        Win[1] = SCREEN_HEIGHT;
    } else {
        Win[0] = atoi(argv[1]);
        Win[1] = atoi(argv[2]);
    }

    // Initialize glut, and opengl
    glutInit(&argc, argv);
    initGlut(argv[0]);
    initGl();

    // Invoke the standard GLUT main event loop
    glutMainLoop();

    return 0;  // never reached
}

// Initialize glut and create a window with the specified caption
void initGlut(char* winName) {
    // Set video mode: double-buffered, color, depth-buffered
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(Win[0], Win[1]);
    windowID = glutCreateWindow(winName);

    // Setup callback functions to handle events
    glutReshapeFunc(myReshape); // Call myReshape whenever window resized
    glutDisplayFunc(display);   // Call display whenever new frame needed

    glutKeyboardFunc(keyboardFunc);
}

// Quit button handler.  Called when the "quit" button is pressed.
void quitButton(int) {
    exit(0);
}

// Performs most of the OpenGL intialization
void initGl(void) {
    // glClearColor (red, green, blue, alpha)
    // Ignore the meaning of the 'alpha' value for now
    glClearColor(0.7f, 0.7f, 0.9f, 1.0f);
}


// Handles the window being resized by updating the viewport
// and projection matrices
void myReshape(int w, int h) {
    // Setup projection matrix for new window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    // Update OpenGL viewport and internal variables
    glViewport(0, 0, w, h);
    Win[0] = w;
    Win[1] = h;
}

void keyboardFunc(unsigned char key, int, int) {
    std::cout << "key : " << key;
    switch (key) {
    case 27:  // Escape key
        glutDestroyWindow(windowID);
        break;
    }

    fill_enabled = !fill_enabled;
}


void drawTriangle(const glm::vec2& v1, const glm::vec2& v2, const glm::vec2& v3) {
    glVertex2d(v1.x, v1.y);
    glVertex2d(v2.x, v2.y);
    glVertex2d(v3.x, v3.y);
}


void drawRect(const glm::vec2& top_left, const glm::vec2& bottom_right, const glm::ivec2& subdivisions) {
    // TODO(PART1) DRAW A SQUARE MESH 
    (void)top_left;
    (void)bottom_right;
    (void)subdivisions;
}


void drawCircle(const glm::vec2& center, float radius, const glm::ivec2& subdivisions) {
    // TODO(PART2) DRAW A CIRCULAR MESH
    (void)center;
    (void)radius;
    (void)subdivisions;
}


// display callback
//
// This gets called by the event handler to draw
// the scene, so this is where you need to build
// your scene -- make your changes and additions here.
// All rendering happens in this function.  For Assignment 1,
// updates to geometry should happen in the "animate" function.
void display(void) {
    if (fill_enabled) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    // glClearColor (red, green, blue, alpha)
    // Ignore the meaning of the 'alpha' value for now
    glm::vec4 clear_color(0.7, 0.7, 0.9, 1.0);
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);

    // OK, now clear the screen with the background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup the model-view transformation matrix 
    // Coordinates are in (0,0,width,height) space
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the colour to green (r,g,b)
    glColor3f(0.0, 1.0, 0.0);

    // Draw multiple triangles with drawTriangle
    glBegin(GL_TRIANGLES);
    {
        drawTriangle(glm::vec2(50.0, 50.0), glm::vec2(50.0, 100.0), glm::vec2(100.0, 100.0));


    }
    glEnd();

    // Execute any GL functions that are in the queue just to be safe
    glFlush();

    // Now, show the frame buffer that we just drew into.
    // (this prevents flickering).
    glutSwapBuffers();
    glutPostRedisplay();
}
