#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include "../include/Flock.h"
#include "../include/Boid.h"
// #include <thread>

using namespace std;

Flock birds; 


int refreshMillis = 1;

// angle of rotation for the camera direction
float angle1 = 0.0f;
float angle2 = 0.0f;

// actual vector representing the camera's direction
float lx=-2.0f, ly=0.0f, lz=-2.0f;

// XZ position of the camera
float x=60.0f, y= 6.0f, z=60.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle1 = 0.0f;
float deltaAngle2 = 0.0f;
float deltaMove = 0;
int xOrigin =-1;
int yOrigin =-1;

float xb = 0;
float yb = 0;
float zb = 0;

float vx = 0.1;
float vy = 0.2;
float vz = 0.3;

int xb_max = 10;
int yb_max = 20;
int zb_max = 10;


int xb_min = -10;
int yb_min = 5;
int zb_min = -10;

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
    glLineWidth(2.0);
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
	glVertex3f(0.0f, 0.0f, 500.0f);
    glVertex3f(0.0f, 0.0f, -500.0f);


   

	// int vx = 0;
	// int vy = 1;
	// int vz = 1;
	// float nx = x;
	// float ny = y;
	// float nz = z;

	// for(int i=0; i< 5; i++){
	//    	nx = nx + vx;
	//     ny = ny + vy;
	//    	nz = nz + vz;
   	//Show the birds
   	vector<Position> new_pos;
   	for(int i=0;i< birds.Boids.size();i++){
   		float x1,y1,z1;
   		x1 = ((birds.Boids)[i].location).x + (((birds.Boids)[i].direction).i)*0.3; 
   		y1 = ((birds.Boids)[i].location).y + (((birds.Boids)[i].direction).j)*0.3; 
   		z1 = ((birds.Boids)[i].location).z + (((birds.Boids)[i].direction).k)*0.3; 
	   // cout << x1 << "|" << y1 << "|"<< z1 <<"\n";
	    Position temp;
	    temp.x=x1;
	    temp.y=y1;
	    temp.z=z1;
	    new_pos.push_back(temp);
	 	// Check if the ball exceeds the edges
		// if (x1 > xb_max) {
		//    x1 = xb_max;
		// } else if (x1 < xb_min) {
		//    x1 = xb_min;
		// }
		// if (y1 > yb_max) {
		//    y1 = yb_max;
		// } else if (y1 < yb_min) {
		//    y1 = yb_min;
		// }
		// if (z1 > zb_max) {
		//    z1 = zb_max;
		// } else if (z1 < zb_min) {
		//    z1 = zb_min;
		// }
	    // cout << x1 << "|"<< y1 << "|"<< z1 << "\n";
	    
	    glBegin(GL_POINTS);
    	glVertex3f(0.0f, 0.0f, 0.0f);
   		glEnd();  
    	glColor3f(1.0f, 1.0f, 1.0f);
	   	glPushMatrix();
	   	glTranslated(x1, y1, z1);      
    	// glRotatef(((birds.Boids)[i].direction).i, ((birds.Boids)[i].direction).j , ((birds.Boids)[i].direction).k );
    	// glutSolidCone(0.2f,0.8f,10,2);
   		glutSolidSphere(0.2f,20,20);
    	glPopMatrix();

   	}
   	// glPushMatrix();
   	// glTranslated(xb, yb, zb);      
    // //glutSolidCone(0.2f,0.8f,10,2);
   	// glutSolidSphere(0.15f,20,20);
    // glPopMatrix();
	 //   glutSwapBuffers();
	
	//put swapbuffers in loop if does not work
	
    glutSwapBuffers();

   // 	// Animation Control - compute the location for the next refresh
   // 	xb += vx*(0.3);
   // 	yb += vy*(0.3);
   // 	zb += vz*(0.3);
  	// // Check if the ball exceeds the edges
   // if (xb > xb_max) {
   //    xb = xb_max;
   //    vx = -vx;
   // } else if (xb < xb_min) {
   //    xb = xb_min;
   //    vx = -vx;
   // }
   // if (yb > yb_max) {
   //    yb = yb_max;
   //    vy = -vy;
   // } else if (yb < yb_min) {
   //    yb = yb_min;
   //    vy = -vy;
   // }
   // if (zb > zb_max) {
   //    zb = zb_max;
   //    vz = -vz;
   // } else if (zb < zb_min) {
   //    zb = zb_min;
   //    vz = -vz;
   // }
    // cout << "shuru\n";
    // for(int i=0;i< new_pos.size();i++){
    // 	cout << new_pos[i].x << "|" << new_pos[i].y << "|" << new_pos[i].z << "\n";
    // }
    // cout << "khatam\n";
    birds.update_positions(new_pos);
    birds.update_directions();

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

/* Called back when the timer expired */
void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

int main(int argc, char **argv) {
	
	// Position first;
	// Position second;
	// Position third;

	// first.x=0;
	// first.y=10;
	// first.z=0;

	// second.x=1;
	// second.y=10;
	// second.z=1;

	// third.x=1;
	// third.y=10;
	// third.z=0;
	
	// birds.addBoid(first);
	// birds.addBoid(second);
	// birds.addBoid(third);
	srand(time(0));
	for(int i=0;i<250;i++){
		Position temp_position;	
		Direction temp_direction;	
		int flag;
		temp_position.x = (rand()%5);
		temp_position.y = (rand()%5) + 7;
		temp_position.z = (rand()%5);
		
		flag = rand()%2;
		if(flag==1){
			temp_direction.i = (rand()%10)+1;
		}else{	temp_direction.i = -(rand()%10)-1;}

		flag = rand()%2;
		if(flag==1){
			temp_direction.j = (rand()%10)+1;
		}else{temp_direction.j = -(rand()%10)-1;}

		flag = rand()%2;
		if(flag==1){
			temp_direction.k = (rand()%10)+1;
		}else{temp_direction.k = -(rand()%10)-1;}

		birds.addBoid(temp_position, temp_direction);
		// cout << temp.x << "|"<< temp.y << "|"<< temp.z << "\n";
	
	}
	// cout << birds.Boids.size();
	// for(int i=0;i<birds.Boids.size();i++){
	// 	cout << "Neigbhours of Bird No-" << i << "\n";
	// 	cout << (birds.Boids[i].neighbours).size();
	// 	for(int j=0;j< (birds.Boids[i].neighbours).size();j++){
	// 		cout << ((((birds.Boids[i]).neighbours)[j])->location).x << "|" << ((((birds.Boids[i]).neighbours)[j])->location).y << "|" << ((((birds.Boids[i]).neighbours)[j])->location).z << "\n";
	// 	}

	// 	cout << "\n";
	// }



/////////////////////////////////////////////////////////////////////////////////
//DISPLAY PART

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1000,720);
	glutCreateWindow("Boids");

	// register callbacks
	// glutDisplayFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutTimerFunc(0, Timer, 0);   // First timer call immediately


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