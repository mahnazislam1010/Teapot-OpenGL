#include <windows.h>
#include "GL/freeglut.h"
#include <cmath>
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include<conio.h>
#include <math.h>
#include <sstream>
#include <vector>
using namespace std;

// Global variables
//GLuint stands for gl unsigned integer
GLuint changeColor = 0;
//GLfloat changeColor = 0;
GLuint angle=0;
GLfloat lightXPos = 0.0f;
GLfloat lightYPos = 0.0f;

//GLuint color=0;
GLfloat initialValue;



void mouse();
void MouseWheel();

// Global Variables

double rotate_y=0; 
double rotate_x=0;
double zoom=0.5;
// This is the list of points (3D vectors)
// This function is called whenever a "Normal" key press is received.
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
        // code to change color here
		changeColor += 1.0;
		if(changeColor>8.0)
            changeColor=0.0;
        break;
   case 't':
        // code for color transitioncol
		   changeColor=8;
			if(initialValue>=1.0)
				initialValue=0.1;
			initialValue+=0.01;
        break;

    case 'r':
        angle++;
        break;


    default:
        cout << "Wrong key press " << key << "." << endl;
    }
	// this will refresh the screen so that the user sees the color change
    glutPostRedisplay();
}
// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:
        // code to change light in up position
		lightYPos += 0.5f;
		break;
    case GLUT_KEY_DOWN:
        // code to change light in down position
		lightYPos += -0.5f;
		break;
    case GLUT_KEY_LEFT:
        // code to change light in left position
		lightXPos += -0.5f;
		break;
    case GLUT_KEY_RIGHT:
        // code to change light in right position
		lightXPos += 0.5f;
		break;
    }
	// this will refresh the screen so that the user sees the light position
    glutPostRedisplay();
}
// This function is responsible for displaying the object.
void drawScene(void)
{
    int i;
    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Rotate the image
    glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
    glLoadIdentity();              // Initialize to the identity

	
	// Rotate when user changes rotate_x and rotate_y
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
	
	
	//Zoom in and out according to mouse wheel movement
    glScalef(zoom, zoom, 1.0f);


    // Position the camera at [0,0,4], looking at [0,0,0],
    // with [0,1,0] as the up direction.
    gluLookAt(0.0, 0.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Set material properties of object
	// Here, are some colors you might use - feel free to add more
	//{red, green, blue, alpha}
    GLfloat diffColors[9][4] = { {initialValue, 0.5, 0.9, 1.0},
                                 {initialValue, 1.0, 0.0, 0.0},
                                 {initialValue, 0.0, 1.0, 0.0},
                                 {initialValue, 0.8, 0.5, 0.8},
                                 {initialValue, 0.5, 0.5, 0.9},
                                 {initialValue, 0.9, 0.9, 0.5},
                                 {initialValue, 0.5, 0.7, 0.9},
                                 {initialValue, 0.9, 0.5, 0.5},
                                 {initialValue, 0.7, 0.3, 0.5}};




    //glMaterialfv specifies material parameters for the lighting model
	//The first parameter tells whether the material property
    //value for both front face, the back face.
    //The second parameter tells which material property is being set.
    // Here, we use the first color entry as the diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[changeColor]);

	//specular color and shininess
    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};

	//specular color and shininess can stay constant
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    // Set light properties
    // Light color (RGBA)
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0}; //intensity??
	//GLfloat ambient0[]={0.2, 0.2, 0.2, 1.0}; // Farbdefinitionen

    // Light position
	GLfloat Lt0pos[] = {1.0f + lightXPos, 1.0f + lightYPos, 5.0f, 1.0f}; //???????????????

	//glLightfv returns light source parameter values.
	//GL_DIFFUSE specifies the diffuse RGBA intensity of the light
	//glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

    //rotate "angle" on Y axis
    glRotatef(angle,0,1,0);

	//draws a teapot.
	glutSolidTeapot(1.0);

    // Dump the image to the screen.
    glutSwapBuffers();

}
//OpenGL's rendering modes
void initRendering()
{
    glEnable(GL_DEPTH_TEST);   // Depth testing turned on
    glEnable(GL_LIGHTING);     // Enable lighting calculations
    glEnable(GL_LIGHT0);       // Turn on light #0.
}



void mouse(int button, int state, int mousex, int mousey)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        angle += 1;
    }


    else if (GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        angle -= 1;
		
	}
	glutPostRedisplay();
}

void MouseWheel(int wheel, int direction, int x, int y)
{
    wheel=0;
    if (direction==-1)
    {
        zoom -= 0.5;
        
    }
    else if (direction==+1)
    {
        zoom += 0.5;
    }

 glutPostRedisplay();

}




// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
    // Always use the largest square viewport possible
    if (w > h) {
        glViewport((w - h) / 2, 0, h, h);
    } else {
        glViewport(0, (h - w) / 2, w, w);
    }
    // Set up a perspective view, with square aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //50 degree fov, uniform aspect ratio, near = 1, far = 100
    gluPerspective(50.0, 1.0, 1.0, 100.0);
}


// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    //loadInput();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 500, 500 );
    glutCreateWindow("Teapot Assignment");
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    // Initialize OpenGL parameters.
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

    // Set up the callback function for resizing windows
    glutReshapeFunc(reshapeFunc);


	// Call this whenever window needs redrawing
    glutDisplayFunc(drawScene);


	glutMouseFunc(mouse);
    glutMouseWheelFunc(MouseWheel);
	

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );



    return 0;	// This line is never reached.
}
