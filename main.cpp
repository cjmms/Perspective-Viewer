#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

// #include "GL/freeglut.h"

#include <stdlib.h>
#include <stdio.h>

#define CLEAR 5
#define EXIT 6

float angle = 0.0f;

int clickX = 0;
int clickY = 0;

int deltaX = 0;
int deltaY = 0;

int oldTeapotX = 0;
int oldTeapotY = 0;

int teapotX = 0;
float teapotY = 0;

bool isRotating = false;
bool isMoving = false;



void init() 
{
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, 1 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);  // define the position of the light
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);  // specify the ambient RGBA intensity of the light
}


void moveTeapot() {
    int teapotDeltaY = teapotY - oldTeapotY;
    if (abs(teapotDeltaY) * 80 <= abs(deltaY)) {
        if (deltaY > 0) teapotY -= 0.01;
        else teapotY += 0.01;
    }

    printf("deltaY (%d)\n", deltaY);
    printf("teapotDeltaY (%d)\n\n", abs(teapotDeltaY));
           
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  // reset the current matrix to identity matrix

    // create a viewing matrix defined by an eye point and a reference point
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glViewport(0, 0, 480, 480);  // define a viewport and display in this viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1, 1.0, 20.0);  // specify a viewing frustum
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(  0.0, 0.0, 5.0, 
                0.0, 0.0, 0.0, 
                0.0, 1.0, 0.0);  

    glRotatef(angle, 0.0f, 1.0f, 0.0f);
                                              
    //printf("teapotX (%d, %d)\n", teapotX, teapotY);
    glTranslated(0, teapotY, 0);
    glutSolidTeapot(0.5);
    glutSwapBuffers();

    if (isRotating) angle += 1.0;
    if (isMoving) {
        //teapotY += 0.01;
        //if (teapotX - oldTeapotX != deltaX) teapotX += 0.01;
        //if (teapotY - oldTeapotY <= convertY()) teapotY += 0.01;
        moveTeapot();
    }
}

void mouseFunc(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // update click position
        clickX = x;
        clickY = y;

        printf("click (%d, %d)\n", clickX, clickY);
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {  // press shift and left click
            isMoving = true;
            isRotating = false;
        } 
        else {      // left click, no shift
            isMoving = false;     
            isRotating = true;
        }
    }
    else {
        isRotating = false;
        isMoving = false;
    }
}

void processNormalKey(unsigned char key, int x, int y) 
{
    if (key == 27)
        exit(0);
    if (key == 'r') {       // reset teapot
        angle = 0.0;
        teapotY = 0.0;
        teapotX = 0.0;
        display();
    }
}

void processMenuEvents(int option) {
    switch (option) {
        case CLEAR :
            angle = 0.0;
            teapotY = 0;
            teapotX = 0;
            display();
            break;
        case EXIT :
            exit(0);
            break;
    }
}

void createMenu() {
    int menu = glutCreateMenu(processMenuEvents);

    // add entries
    glutAddMenuEntry("CLEAR", CLEAR);
    glutAddMenuEntry("EXIT", EXIT);

    // menu pops up when right button is pressed
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void motion(int currentX, int currentY)
{
    // update deltaX and deltaY
    deltaX = currentX - clickX;
    deltaY = currentY - clickY;

    //printf("current (%d, %d)\n", currentX, currentY);
	//printf("delta (%d, %d)\n\n", deltaX, deltaY);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("viewer");

    init();

    createMenu();

    // register callback func
    glutDisplayFunc(display);
    glutKeyboardFunc(processNormalKey);
    glutIdleFunc(display);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}