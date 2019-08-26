#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include <stdlib.h>
#include <stdio.h>

float angle = 0.0f;
bool isRotating = false;

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

void resize(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0f * w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glViewport(0, 0, w, h);  // define a viewport and display in this viewport
	gluPerspective(60.0, ratio, 1.0, 1000.0);  // specify a viewing frustum
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  // def

    // glViewport(0, 0, w, h);
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	// glMatrixMode(GL_MODELVIEW);

    //printf("sdcdw\n");
}

void display() 
{
    //printf("display\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  // reset the current matrix to identity matrix

    // create a viewing matrix defined by an eye point and a reference point
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glutSolidTeapot(0.5);

    if (isRotating) angle += 1.0f;

    glutSwapBuffers();

    // glViewport(0, 0, 480, 480);  // define a viewport and display in this viewport
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// gluPerspective(60.0, 1, 1.0, 20.0);  // specify a viewing frustum
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	// gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  // def
}

void mouseFunc(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        isRotating = true;
    else 
        isRotating = false;
}

void processNormalKey(unsigned char key, int x, int y) 
{
    if (key == 27)
        exit(0);
    if (key == 'r') {       // reset teapot
        angle = 0.0;
        display();
    }
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("viewer");

    init();

    // register callback func
    glutDisplayFunc(display);
    glutKeyboardFunc(processNormalKey);
    glutIdleFunc(idle);
    glutMouseFunc(mouseFunc);
    //glutReshapeFunc(resize);

    glutMainLoop();
    return 0;
}


