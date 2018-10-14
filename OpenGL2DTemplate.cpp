#include <stdio.h>
#include <math.h>
#include <iostream>
#include <random>
#include <windows.h>
#include <string.h>
#include "glut.h"
//-----------------
int count = 1;
double plusX = 0;
double plusY = 0;

double redBG = 0;
double blueBG = 0.7;
double  greenBG = 0.5;
double rangeCharacterX;
double rangeCharacterXLOW;
double rangeCharacterY;
double rangeCharacterYLOW;

double positionObstacleY;
double rangeX ;
double rangeXLOW ;
double rangeY ; 
double rangeYLOW ;
double darkBlueY = 0;
float rotate = 0;

int score = 0;
double scoreX = 0;
double healthX = 0;
double healthOriginal = 1;

double positionObstacle = 0;

double bulletX = 8000 ;
double bulletY = 0;

double t = 0;

//enemy location
double enemyX = 0;
double enemyY = 0;

//enemy's obstacle location
double obstacleX = 800;
double obstacleY = 0;

bool shoot = false;
bool isDone = false;
bool inProgress = false;
bool isFired = false;
bool dead = false;
bool refreshHealth = false;
bool killed = false;

//enemyDefender location
double enemyDefenderX = 0;
double enemyDefenderY = 0;
// defending tool fired by enemy defender location
double defenderToolX = 0; 
double defenderToolY = 0;

double XH;
double XL;
double YL;
double	YH;

double P1X = -800;
double P1Y = 0;

double P2X = -1000;
double P2Y = 0;
int slide = 5;
int p0[2] = {-400,5};
int p1[2] = {190,54};
int p2[2] = {150,10};
int p3[2] = {300,39};
int* points = new int [2];
double n = count * enemyX;
void print(int x, int y, char *string);
void animatedBackground();

void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}
void drawPlayer() {
	//largest circle
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(plusX, plusY, 0);
	glColor3f(1, 1, 1);
	drawCircle(50, 20, 30);
	glPopMatrix();

	//middle circle
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(plusX, plusY, 0);
	glColor3f(1, 1, 1);
	//glTranslated(plusX, plusY, 0);

	drawCircle(50, 60, 25);
	glPopMatrix();
	//small circle
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glColor3f(1, 1, 1);
	glTranslatef(plusX, plusY, 0);
	drawCircle(50, 100, 20); //draw circle
	glPopMatrix();

	//DRAW HIS HAT
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(plusX, plusY, 0);
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
	glTranslatef(plusX, plusY, 0);
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
	glTranslatef(plusX, plusY, 0);
	glBegin(GL_LINES);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(25.0f, 60.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(15.0f, 85.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();
}
// draws a circle using OpenGL's gluDisk, given (x,y) of its center and ITS radius
void drawScore() {
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0f);
	glVertex3f(0.0f, 500.0f, 0.0f);
	glColor3f(1.0, 1.0, 0.0f);
	glVertex3f(200.0f, 500.0f, 0.0f);
	glColor3f(1.0, 1.0, 0.0f);
	glVertex3f(200.0f, 480.0f, 0.0f);
	glColor3f(1.0, 1.0, 0.0f);
	glVertex3f(0.0f, 480.0f, 0.0f);
	glEnd();
	glPopMatrix();
}


void drawHealth() {
	glPushMatrix();
	glTranslatef(healthX, 0.0f, 0.0f);
	glScalef(healthOriginal,1,1);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 1.0f);
	glVertex3f(0.0f, 525.0f, 0.0f);
	glColor3f(0.00f, 1.0f, 1.0f);
	glVertex3f(200.0f, 525.0f, 0.0f);
	glColor3f(0.00f, 1.0f, 1.0f);
	glVertex3f(200.0f, 505.0f, 0.0f);
	glColor3f(0.00f, 1.0f, 1.0f);
	glVertex3f(0.0f, 505.0f, 0.0f);
	glEnd();
	glPopMatrix();
}

 
void drawEnemy() {
	//draw sun base
	glPushMatrix();
	 n = count * enemyX;
	glTranslatef(n,enemyY,0.0f);
	if (count < 0) {
		glRotated(1, 0.0f, 0.0f, 1.0f);
	}
	else {
		glRotated(-5, 0.0f, 0.0f, 1.0f);
	}
	glColor3f(0.98, 0.86, 0.05);
	drawCircle(500, 500, 50);

	//draw sun rays #up
	glBegin(GL_TRIANGLES);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(500.0f, 570.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(520.0f, 550.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(480.0f, 550.0f, 0.0f);
	glEnd();

	//sun rays #down
	glBegin(GL_TRIANGLES);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(480.0f, 450.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(520.0f, 450.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(500.0f, 430.0f, 0.0f);
	glEnd();

	//sun rays #right
	glBegin(GL_TRIANGLES);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(550.0f, 520.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(570.0f, 500.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(550.0f, 480.0f, 0.0f);
	glEnd();


	//sun rays #left
	glBegin(GL_TRIANGLES);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(430.0f, 500.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(450.0f, 520.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(450.0f, 480.0f, 0.0f);
	glEnd();


	//sun mouth
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(480.0f, 480.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(520.0f, 480.0f, 0.0f);
	glEnd();
	//sun eyes
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(460.0f, 520.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(480, 520.0f, 0.0f);
	glEnd();
	//sun eyes
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(520.0f, 520.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(540, 520.0f, 0.0f);
	glEnd();

	glPopMatrix();
}

void enemyDefender() {
	glPushMatrix();
	glTranslatef(enemyDefenderX, enemyDefenderY, 0.0f);

	glColor3f(0.37, 0.46, 0.37); //middle
	drawCircle(530, 300, 40);

	glColor3f(0.37, 0.46, 0.37); //left
	drawCircle(470, 300, 40); 

	glColor3f(0.37, 0.46, 0.37); //right
	drawCircle(590, 300, 40);
	glPopMatrix();

}

void drawBullets() {
	glPushMatrix();
	glTranslatef(bulletX, bulletY, 0.0f);
	glColor3f(1, 1, 1);
	drawCircle(50, 178, 7);
	////
	glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 1);
	glVertex3f(40.0f, 177.0f, 0.0f);
	glColor3f(1, 1, 1);
	glVertex3f(60.0f, 177.0f, 0.0f);
	glColor3f(1, 1, 1);
	glVertex3f(50.0f, 151.0f, 0.0f);
	glEnd();
	/////
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex3f(50.0f, 150.0f, 0.0f);
	glColor3f(1, 1, 1);
	glVertex3f(50, 144.0f, 0.0f);
	glEnd();


	glPopMatrix();
}

void drawObstacle() {
	glPushMatrix();
	glTranslatef(obstacleX, obstacleY, 0.0f);
	glColor3f(0.80, 0.0, 0.00);
	drawCircle(500, 428, 7);
	////
	glBegin(GL_TRIANGLES);
	glColor3f(0.80, 0.0, 0.00);
	glVertex3f(490.0f, 427.0f, 0.0f);
	glColor3f(0.80, 0.0, 0.00);
	glVertex3f(510.0f, 427.0f, 0.0f);
	glColor3f(0.80, 0.0, 0.00);
	glVertex3f(500.0f, 401.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.80, 0.0, 0.00);
	glVertex3f(500.0f, 400.0f, 0.0f);
	glColor3f(0.80, 0.0, 0.00);
	glVertex3f(500,394.0f, 0.0f);
	glEnd();

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
		shoot = true;
	}

	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)//keyboard function, takes 3 parameters
									// k is the key pressed from the keyboard
									// x and y are mouse postion when the key was pressed.
{
	if (k == 'd') {//if the letter d is pressed, then the object will be translated in the x axis by 10 (moving to the right).
		plusX += slide;
		greenBG = 0;
		rotate = -5;
	}

	if (k == 'a')//if the letter a is pressed, then the object will be translated in the x axis by -5 (moving to the left).
		if (plusX <= 0) {
		}
		else {
			plusX -= slide;
			greenBG = 0.5;
			rotate = 5;
		}
	glutPostRedisplay();//redisplay to update the screen with the changes
}



void drawPowerUp2() {
	glPushMatrix();
	glTranslatef(P2X, P2Y, 0.0f);
	glScalef(1.2, 1.2, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.18f, 0.83f, 0.70f);
	glVertex3f(480.0f, 450.0f, 0.0f);
	glColor3f(0.18f, 0.83f, 0.70f);
	glVertex3f(520.0f, 450.0f, 0.0f);
	glColor3f(0.98, 0.55, 0.05);
	glVertex3f(500.0f, 430.0f, 0.0f);
	glEnd();
	glPopMatrix();
}

void drawPowerUp1() {
	glPushMatrix();
	glTranslatef(P1X, P1Y, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.41, 0.70f);
	glVertex3f(110.0f, 300.0f, 0.0f);
	glColor3f(1.0f, 0.41, 0.70f);
	glVertex3f(130.0f, 300.0f, 0.0f);
	glColor3f(1.0f, 0.41, 0.70f);
	glVertex3f(130.0f, 350.0f, 0.0f);
	glColor3f(1.0f, 0.41, 0.70f);
	glVertex3f(110.0f, 350.0f, 0.0f);
	glEnd();
	glPopMatrix();
}
void Timer(int value) {
	// set the enemy defender y loctation anywhere between 10 an 780
	enemyDefenderY = rand() % 300 + 10; 
	P1X = rand() % 400 + 0;
	P1Y = rand() % 300 + 0;
	P2X = rand() % 600 + 50;
	P2Y = rand() % 500 + 3;

	//P1X = rand() % 400 + 0;
	//P1Y = rand() % 300 + 0;
	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	// recall the Timer function after 20 seconds (20,000 milliseconds)
	glutTimerFunc(20 * 1000, Timer, 0);
}
void print(int x, int y, char *string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void animatedBackground() {
	glPushMatrix();
	glTranslatef(darkBlueY,0, 0);
	glBegin(GL_POLYGON);
	
	glColor3f(0.16, 0.16, 50.0f);
	glVertex3f(0.0f, 600.0f, 0.0f);
	glColor3f(0.16, 0.16, 50.0f);
	glVertex3f(1000.0f, 600.0f, 0.0f);
	glColor3f(0.16, 0.16, 50.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);
	glColor3f(0.16, 0.16, 50.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.39, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.39, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.39, 0.0f);
	glVertex3f(1000.0f, -6000.0f, 0.0f);
	glColor3f(0.0f, 0.39, 0.0f);
	glVertex3f(0.0f, -600.0f, 0.0f);
	glEnd();
	glPopMatrix();

}

void Anim() {
	/*p2[0] = rand() %2;
	p2[1] = rand() % 10+5;
	p3[0] = rand() %6+4;
	p3[1]= rand() % 12+5;*/
    /*p2[0] = rand() % 900;
	p2[1]= rand() %570+500;*/
	/*p3[0] = rand() %900;
	p3[1]= rand() % 570;*/

	//std::cout << p1[0]<< "  point 0 X ";
	//std::cout << p1[1] << " point 0 Y ";
	//std::cout << p2[0] << " point 1 X ";
	/*darkBlueY += 8;
	lightBlueY += 8;*/
	
	if (t < 1) {
		int* points = bezier(t, p0, p1, p2, p3);
		enemyX = points[0];
		enemyY = points[1];	
		t = t + 0.001;
	}
	else {
		t = 0;
		count = count * -1;
	}

	if (isFired==false) {
		obstacleX = n;
		obstacleY = enemyY;
		isFired = true;
	}

	if (isFired)
		obstacleY -= 1;
	//std::cout << obstacleX << "\n";
	/*std::cout << "enemy X : "<< enemyX << "\n";
	std::cout << "bullet X : " << bulletX << "\n";*/
	if (obstacleY < -450) {
		isFired = false;
		
	}
	
	if (shoot==true & inProgress==false) {
		bulletX = plusX;
		isDone = true;
		inProgress = true;
	}
	double j = enemyY + 500;
	
		if (isDone & bulletY<470 & inProgress) {
			shoot = false;
			bulletY += 3;
		
	
		}
		else {
			isDone = false;
			inProgress = false;
			bulletY = 0;
			bulletX = -8000;
			if (refreshHealth == true) {
				healthX = 0;
				healthOriginal = healthOriginal*1.5;
				refreshHealth = false;
			}
		}
	     rangeY = enemyY + 570;
		 rangeYLOW = enemyY +430;

		 rangeX = enemyX + 570;
		 rangeXLOW = enemyX + 430;

	
		 double bulletYY = bulletY + 144;
		//double bulletXX = bulletX;
		if ( bulletYY >= rangeYLOW & bulletYY <= rangeY & bulletX<=rangeX & bulletX>=rangeXLOW) {
			std::cout << "DEAD\n";
			std::cout << "\n";
			std::cout << "\n";
			std::cout << "enemy X : " << rangeX << "\n";
			std::cout << "bullet X : " << bulletX << "\n";
			std::cout << "enemy Y : " << rangeY << "\n";
			std::cout << "bullet Y : " << bulletYY << "\n";
			std::cout << "\n";
		 dead = true;
		}
	
		if (dead==true) {
			healthX -= 0.5;
			score++;
				dead = false;
				if(healthX <=-200)
				refreshHealth = true;
		}
		positionObstacle = obstacleX + 500; // ;position in x 
		positionObstacleY = obstacleY + 394;
		rangeCharacterX = plusX + 85;
		rangeCharacterXLOW = plusX +15;
		rangeCharacterY = plusY + 140;
		rangeCharacterYLOW = plusY + 20;
		if (positionObstacle >= rangeCharacterXLOW & positionObstacle <= rangeCharacterX & positionObstacleY <=rangeCharacterY & positionObstacleY>=rangeCharacterYLOW) {
			
			killed = true;
		}
		if (killed) {
			killed = false;
			std::cout << "IM DYING\n";
			score=-1;
		}
		if (score == -1) {
			plusX = -10000;
			plusY = -20000;
		}
		darkBlueY = darkBlueY + 5;
		if (darkBlueY >=1000) {
			std::cout << "moving";
			darkBlueY = 0;
		}
		XH = 590 + enemyDefenderX;
		XL = 395 + enemyDefenderX;

		YH = 340 + enemyDefenderY;
		YL = 260 + enemyDefenderY;
		if (bulletYY >= YL & bulletYY <= YH & bulletX <= XH & bulletX >= XL) { // enemy Defender block bullet
			std::cout << "blocked";
			bulletX = -8000;
		}
		if (P1Y > -400) {
			P1Y = P1Y - 2;
		}
		if (P2Y > -600) {
			P2Y = P2Y - 4;
		}
	glutPostRedisplay();	
}
void bullet(void)
{
	obstacleY = obstacleY - 1;

	if (obstacleY <-429) {
		obstacleY = 0;
		obstacleX = 800;
		glutIdleFunc(NULL);     // This will stop the animation when 'obstacleY' exceeds -429.
	}
	glutPostRedisplay();
}

void Display() {
	glClearColor(redBG, blueBG, greenBG, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	/*glPushMatrix();
		glTranslated(plusX, plusY, 0);*/
		////////////////////////////////

	animatedBackground();
	

	if (score == -1)
		print(0, 500, "GAME OVER");
	glColor3f(1, 0, 0);
	char* theScore[20];

	//

	if (score >= 0) {
		sprintf((char *)theScore, "SCORE= %d", score);
		print(785, 450, (char *)theScore);

	}


	////
	if (score >= 0) {
		drawScore();
		drawHealth();
		drawBullets();
	}

	drawPlayer();

	drawEnemy();
	drawObstacle();
	enemyDefender();
	drawPowerUp1();
	drawPowerUp2();
	glFlush();
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Assignment 1");
	glutDisplayFunc(Display);
	glutKeyboardFunc(key);
	glutIdleFunc(Anim);
	glutKeyboardUpFunc(KeyUp);
	glutTimerFunc(0, Timer, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glPointSize(9.0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 1000.0, 0.0, 600.0);
	glutMainLoop();
}
