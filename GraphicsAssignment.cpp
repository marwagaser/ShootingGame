#include <stdio.h>
#include <math.h>
#include <random>
#include "glut.h"
//-----------------

double plusX = 0;
double plusY = 0;

double redBG = 0;
double blueBG = 0.7;
double  greenBG = 0.5;

float rotate = 0;

double laserX = -50;
double laserY = -50;

double laserX1 = -1;
double laserY1 = -1;

// draws a circle using OpenGL's gluDisk, given (x,y) of its center and ITS radius
void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}
void KeyUp(unsigned char key, int x, int y) {
	// reset the selectedBar value to 0 to unselect the selected bar
	if (key == 'd' || key == 'a')
		rotate = 0;
	if (key == 'b') {
		laserX = -50;
		laserY = -50;
		laserX1 = -1;
		laserY1 = -1;
	}

	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)//keyboard function, takes 3 parameters
									// k is the key pressed from the keyboard
									// x and y are mouse postion when the key was pressed.
{
	if (k == 'd') {//if the letter d is pressed, then the object will be translated in the x axis by 10 (moving to the right).
		plusX += 5;
		greenBG = 0;
		rotate = -5;
	}

	if (k == 'a')//if the letter a is pressed, then the object will be translated in the x axis by -5 (moving to the left).
		if (plusX <= 0) {
		}
		else {
			plusX -= 5;
			greenBG = 0.5;
			rotate = 5;
		}
	if (k == 'b') {

		laserX = plusX + 50;
		laserY = 700;
		laserX1 = plusX + 50;
		laserY1 = 141;
	}

	glutPostRedisplay();//redisplay to update the screen with the changes
}

void drawEnemy() {
	glPushMatrix();
	//glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glColor3f(0.98, 0.86, 0.05);
	drawCircle(500, 500, 50);
	glPopMatrix();

	glBegin(GL_TRIANGLES);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(500.0f, 570.0f,0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(520.0f, 550.0f,0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(480.0f, 550.0f,0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(480.0f, 450.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(520.0f, 450.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(500.0f, 430.0f, 0.0f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(550.0f, 520.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(570.0f, 500.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(550.0f, 480.0f, 0.0f);
	glEnd();



	glBegin(GL_TRIANGLES);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(430.0f, 500.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(450.0f, 520.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(450.0f, 480.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(480.0f, 480.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(520.0f, 480.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(480.0f, 480.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(520.0f, 480.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(460.0f, 520.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(480, 520.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(520.0f, 520.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(540, 520.0f, 0.0f);
	glEnd();
}


void Display() {
	glClearColor(redBG, blueBG, greenBG, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	/*glPushMatrix();
		glTranslated(plusX, plusY, 0);*/

		//largest circle
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glTranslated(plusX, plusY, 0);
	glColor3f(1, 1, 1);
	drawCircle(50, 20, 30);
	glPopMatrix();

	//middle circle
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glTranslated(plusX, plusY, 0);
	glColor3f(1, 1, 1);
	//glTranslated(plusX, plusY, 0);

	drawCircle(50, 60, 25);
	glPopMatrix();
	//small circle
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glColor3f(1, 1, 1);
	glTranslated(plusX, plusY, 0);
	drawCircle(50, 100, 20); //draw circle
	glPopMatrix();
	/////////////////FIRST EYE	
	//	glPushMatrix();
	//	glColor3f(0, 0, 0);
	//	drawCircle(45, 110, 2);
	//	glPushMatrix();s
	//
	//	///////// SECOND EYE
	//	glColor3f(0, 0, 0);
	//	drawCircle(55, 110, 2);
		/*glPopMatrix();
		glPopMatrix();
		glPopMatrix();*/

		//DRAW HIS HAT
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glTranslated(plusX, plusY, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(25.0f, 120.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(50.0f, 140.0f, 0.0f);
	glColor3f(1.f, 0.0f, 0.0f);
	glVertex3f(75.0f, 120.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//DRA HIS HANDS 
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glTranslated(plusX, plusY, 0);
	glBegin(GL_LINES);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(75.0f, 60.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(85.0f, 85.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();
	//HIS LEFT HAND
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glTranslated(plusX, plusY, 0);
	glBegin(GL_LINES);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(25.0f, 60.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(15.0f, 85.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();


	//THE LASER BEAM
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(laserX, laserY, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(laserX1, laserY1, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();
	////
	drawEnemy();
	glFlush();
}


void main(int argc, char** argr) {
	glutInit(&argc, argr);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Assignment 1");
	glutDisplayFunc(Display);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(KeyUp);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glPointSize(9.0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 1000.0, 0.0, 600.0);
	glutMainLoop();
}
