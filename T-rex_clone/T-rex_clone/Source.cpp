#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>

using namespace std;

#ifndef M_PI
#define M_PI 3.141592654
#endif // !M_PI

#define MAX_JAW_ANGLE 0
#define MIN_JAW_ANGLE -42

#define MAX_NECKLE_ANGLE 20
#define MIN_NECKLE_ANGLE -20

#define MAX_THIGH_ANGLE 70
#define MIN_THIGH_ANGLE 0

#define MAX_TAIL_Z_ANGLE 5
#define MIN_TAIL_Z_ANGLE -5

#define MAX_TAIL_Y_ANGLE 25
#define MIN_TAIL_Y_ANGLE -25





float xtp = 0.0, ytp = 0.0, ztp = 0.0, xrp = 0.0, yrp = 0.0, zrp = 0.0, xt = 0.0, yt = 0.0, zt = 0.0, xr = 0.0, yr = 0.0, zr = 0.0;
float thighAngle = 9, legAngle = 50, footAngle = -26, chestAngle = 8, neckleAngle = 8,
upperHandAngle = 8, lowerHandAngle = 8, headAngleX = 0.0, headAngleY = 0.0, headAngleZ = -16.0, jawAngle = 0.0, tailAngleZ = 0.0, tailAnngleY = 0.0;

void
Cylinder(float width, float height, float diameter, char slice, char solid)
{
	char i, j = 0;
	float x = width / 2.0, y = height / 2.0, z = diameter / 2;
}

void
Box(float width, float height, float depth, char solid)
{
	char i, j = 0;
	float x = width / 2.0, y = height / 2.0, z = depth / 2.0;

	for (i = 0; i < 4; i++) {
		glRotatef(90.0, 0.0, 0.0, 1.0);
		if (j) {
			if (!solid)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-x, y, z);
			glVertex3f(-x, -y, z);
			glVertex3f(-x, -y, -z);
			glVertex3f(-x, y, -z);
			glEnd();
			if (solid) {
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(0.0, 0.0, z);
				glVertex3f(-x, y, z);
				glVertex3f(-x, -y, z);
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(0.0, 0.0, -z);
				glVertex3f(-x, -y, -z);
				glVertex3f(-x, y, -z);
				glEnd();
			}
			j = 0;
		}
		else {
			if (!solid)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-y, x, z);
			glVertex3f(-y, -x, z);
			glVertex3f(-y, -x, -z);
			glVertex3f(-y, x, -z);
			glEnd();
			if (solid) {
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(0.0, 0.0, z);
				glVertex3f(-y, x, z);
				glVertex3f(-y, -x, z);
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(0.0, 0.0, -z);
				glVertex3f(-y, -x, -z);
				glVertex3f(-y, x, -z);
				glEnd();
			}
			j = 1;
		}
	}
}



void drawLeg(bool isLeft, char solid)
{
	if (isLeft)
		glTranslatef(-0.3, -0.7, -0.9);
	else
		glTranslatef(-0.3, -0.7, 0.9);

	glRotatef(thighAngle, 0, 0, 1);
	glTranslatef(0.0, -0.2, 0.0);
	Box(0.8, 1.0, 0.5, solid);

	glPushMatrix();
	glTranslatef(-0.2, -0.3, 0.0);
	glRotatef(-33, 0, 0, 1);
	glTranslatef(0.0, -0.325, 0.0);
	Box(0.5, 0.65, 0.5, solid);

	glPushMatrix(); // draw leg
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(legAngle, 0, 0, 1);
	glTranslatef(0.0, -0.4, 0.0);
	Box(0.3, 0.8, 0.5, solid);

	glPushMatrix(); // draw foot
	glTranslatef(0.2, -0.5, 0.0);
	glRotatef(footAngle, 0, 0, 1);
	Box(0.8, 0.2, 0.5, solid);
	glPopMatrix(); // end of draw foot

	glPopMatrix(); // end of draw leg

	glPopMatrix();
}

void drawBackwardBody(float width, float height, float depth, char solid)
{
	glTranslatef(-1.0, 0.0, 0.0);
	for (unsigned char i = 0; i < 5; i++)
	{
		glPushMatrix();
		if (i < 3)
		{
			width += 0.1;
		}
		else
		{
			width += 0.25;
			height -= 0.05;
		}
		height -= 0.2;
		depth -= 0.2;
		glRotatef(tailAngleZ, 0, 0, 1);
		glRotatef(tailAnngleY, 0, 1, 0);
		glTranslatef(-width / 2, 0.0, 0.0);
		Box(width, height, depth, solid);
	}
	glTranslatef(width / 2, 0.0, 0.0);
	for (unsigned char i = 0; i < 5; i++)
	{
		glPopMatrix();
	}
}

void drawJaw(char solid)
{
	glTranslatef(1.3, 0.0, 0.0);
	Box(1.25, 0.5, 1.0, solid);

	glTranslatef(-0.7, -0.5, 0.0);
	glRotatef(jawAngle, 0, 0, 1);
	glTranslatef(0.5, 0.15, 0.0);
	Box(1.2, 0.3, 0.7, solid);
}

void drawHead(char solid)
{
	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(headAngleX, 1, 0, 0);
	glRotatef(headAngleY, 0, 1, 0);
	glRotatef(headAngleZ, 0, 0, 1);
	glTranslatef(0.6, 0.0, 0.0);
	Box(1.4, 1.25, 1.25, solid);

	glPushMatrix();// jaw
	drawJaw(solid);
	glPopMatrix();
}

void drawNeckle(char solid)
{
	glTranslatef(0.5, 0.1, 0.0);
	glRotatef(neckleAngle, 0, 0, 1);
	glTranslatef(0.7, 0.0, 0.0);
	Box(1.4, 1.2, 1.2, solid);

	glPushMatrix();
	drawHead(solid);
	glPopMatrix();
}

void drawHand(bool isLeft, char solid)
{
	if (isLeft)
		glTranslatef(0.1, -0.5, -0.7);
	else
		glTranslatef(0.1, -0.5, 0.7);

	glRotatef(upperHandAngle, 0, 0, 1);
	glTranslatef(0.0, -0.25, 0.0);
	Box(0.3, 0.6, 0.3, solid);

	glPushMatrix();
	glTranslatef(0.1, -0.1, 0.0);
	glRotatef(lowerHandAngle, 0, 0, 1);
	glTranslatef(0.0, -0.2, 0.0);
	Box(0.15, 0.3, 0.3, solid);
	glPopMatrix();
}

void drawUpperBody(char solid)
{
	glTranslatef(0.7, 0.0, 0.0);
	glRotatef(chestAngle, 0, 0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	Box(1.4, 1.4, 1.4, solid);

	glPushMatrix();
	drawHand(true, solid);
	glPopMatrix();

	glPushMatrix();
	drawHand(false, solid);
	glPopMatrix();

	glPushMatrix(); // draw neckle
	drawNeckle(solid);
	glPopMatrix();
}

void drawTrex(char solid)
{
	// Base body
	glColor3f(0.8, 0.5, 0.25);
	Box(2.0, 1.5, 1.5, solid);

	glPushMatrix();
	drawLeg(false, solid);
	glPopMatrix();

	glPushMatrix();
	drawLeg(true, solid);
	glPopMatrix();

	glPushMatrix(); // draw upper body
	drawUpperBody(solid);
	glPopMatrix();

	glPushMatrix();
	drawBackwardBody(1.5, 1.5, 1.5, solid);
	glPopMatrix();
}

void display(void)
{
	float solid = 0;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(yr, 0, 1, 0);
	yr = 0.0;
	glRotatef(xr, 1, 0, 0);
	xr = 0.0;
	glRotatef(zr, 0, 0, 1);
	zr = 0.0;

	glTranslatef(xt, yt, zt);
	xt = 0;
	yt = 0;
	zt = 0;

	glPushMatrix();
	drawTrex(solid);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void
myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 1.2, -5.5);  /* viewing transform  */
}

void displayAtrib()
{
	cout << "xtp = " << xtp << " ytp = " << ytp << " ztp = " << ztp << "\nxrp = " << xrp << " yrp = " << yrp << " zrp = " << zrp << "\n";
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i':
		yt = 0.1;
		break;
	case 'k':
		yt = -0.1;
		break;
	case 'j':
		xt = -0.1;
		break;
	case 'l':
		xt = 0.1;
		break;
	case 'u':
		zt = -0.1;
		break;
	case 'o':
		zt = 0.1;
		break;
	case 'w':
		xr--;
		break;
	case 's':
		xr++;
		break;
	case 'a':
		yr++;
		break;
	case 'd':
		yr--;
		break;
	case 'q':
		zr--;
		break;
	case 'e':
		zr++;
		break;
	case 't':
		yrp++;
		break;
	case 'g':
		yrp--;
		break;
	case 'f':
		xrp--;
		break;
	case 'h':
		xrp++;
		break;
	case 'r':
		zrp--;
		break;
	case 'y':
		zrp++;
		break;
	}

	displayAtrib();
	glutPostRedisplay();
}

void mySpecial(int key, int k, int l)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ytp += 0.1;
		break;
	case GLUT_KEY_RIGHT:
		xtp += 0.1;
		break;
	case GLUT_KEY_DOWN:
		ytp += -0.1;
		break;
	case GLUT_KEY_LEFT:
		xtp += -0.1;
		break;
	case GLUT_KEY_PAGE_UP:
		ztp += 0.1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		ztp -= 0.1;
		break;
	}
	displayAtrib();
	glutPostRedisplay();
}

void mouseWheel(int button, int dir, int x, int y)
{

	//cout << "button =" << button << " dir = " << dir << " x = " << x << " y = " << y << "\n";

	glutPostRedisplay();
	return;
}


int
main(int argc, char **argv)
{
	/* start of glut windowing and control functions */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("T-rex");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutSpecialFunc(mySpecial);
	glutMouseFunc(mouseWheel);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();
	return 0;

}
