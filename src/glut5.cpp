#include <stdlib.h>
#include <math.h>
#include <stdio.h>

using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// angle of rotation for the camera direction
float angle1 = 0.0f;
float angle2 = 0.0f;

// actual vector representing the camera's direction
float lx=-2.0f, ly=-2.0f, lz=-2.0f;

// XZ position of the camera
float x=20.0f, y= 20.0f, z=20.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle1 = 0.0f;
float deltaAngle2 = 0.0f;
float deltaMove = 0;
int xOrigin =-1;
int yOrigin =-1;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan() {

	glColor3f(0.0f, 0.0f, 0.0f);

// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(0.0f, 0.0f , 0.0f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void renderScene(void) {

	

	if (deltaMove)
		computePos(deltaMove);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, y, z,
			x+lx,  y+ly,  z+lz,
			0.0f, 1.0f,  0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(5.0);
    //X axis
    glBegin(GL_LINES);
	glVertex3f(500.0f, 0.0f, 0.0f);
    glVertex3f(-500.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    //Y axis
    glBegin(GL_LINES);
	glVertex3f(0.0f, -500.0f, 0.0f);
    glVertex3f(0.0f, 500.0f, 0.0f);

    //Z axis
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 50.0f);
    glVertex3f(0.0f, 0.0f, -50.0f);


// Draw ground

	// glColor3f(0.9f, 0.9f, 0.9f);
	// glBegin(GL_QUADS);
	// 	glVertex3f(-100.0f, 0.0f, -100.0f);
	// 	glVertex3f(-100.0f, 0.0f,  100.0f);
	// 	glVertex3f( 100.0f, 0.0f,  100.0f);
	// 	glVertex3f( 100.0f, 0.0f, -100.0f);
	// glEnd();

// Draw 36 SnowMen

	// for(int i = -3; i < 3; i++)
	// 	for(int j=-3; j < 3; j++) {
 //                     glPushMatrix();
 //                     glTranslatef(i*10.0,0,j * 10.0);
 //                     drawSnowMan();
 //                     glPopMatrix();
 //               }

//    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();  
    glColor3f(1.0f, 1.0f, 1.0f);
	int x = 0;
	int y = 0;
	int z = 0;
	int vx = 0;
	int vy = 1;
	int vz = 1;
	float nx = x;
	float ny = y;
	float nz = z;

	for(int i=0; i< 5; i++){
	   	nx = nx + vx;
	    ny = ny + vy;
	   	nz = nz + vz;
	   	glPushMatrix();
	   	glTranslated(nx, ny, nz);      
	    glutSolidCone(0.2f,0.8f,10,2);
	    glPopMatrix();
	 //   glutSwapBuffers();

	}
    glutSwapBuffers();

	// glEnd();

}


void processNormalKeys(unsigned char key, int xx, int yy) { 	

        if (key == 27)
              exit(0);
} 

void pressKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP : deltaMove = 0.5f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
       }
} 

void releaseKey(int key, int x, int y) { 	

        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
} 

void mouseMove(int x, int y) { 	

         // this will only be true when the left button is down
    if (xOrigin >= 0) {
		// update deltaAngle
		deltaAngle1 = (x - xOrigin) * 0.001f;
		// update camera's direction
		lx = sin(angle1 + deltaAngle1);
		lz = -cos(angle1 + deltaAngle1);
	}

	if (yOrigin >= 0) {
		// update deltaAngle
		deltaAngle2 = (y - yOrigin) * 0.001f;
		// update camera's direction
		ly = sin(angle2 + deltaAngle2);
		lz += -cos(angle2 + deltaAngle2);
	}

	//printf("%f %f %f\n",lx , ly, lz);
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle1 += deltaAngle1;
			angle2 += deltaAngle2;
			xOrigin = -1;
			yOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Boids");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}