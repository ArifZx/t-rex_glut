#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>

using namespace std;

#define SOLID_TREX_TORSO			1
#define SOLID_TREX_CHEST			2
#define SOLID_TREX_ARM				3
#define SOLID_TREX_NECKLE			4
#define SOLID_TREX_HEAD				5
#define SOLID_TREX_JAW				6
#define SOLID_TREX_BODY_BACKWARD	7
#define SOLID_TREX_UPPER_LEG		8
#define SOLID_TREX_LOWER_LEG		9
#define SOLID_TREX_FOOT				10


#ifndef M_PI
#define M_PI 3.141592654
#endif // !M_PI

#define MAX_JAW_ANGLE 0
#define MIN_JAW_ANGLE -42

#define MAX_NECKLE_ANGLE 20
#define MIN_NECKLE_ANGLE -20

#define MAX_UPPER_LEG_ANGLE 70
#define MIN_UPPER_LEG_ANGLE -30

#define MAX_FOOT_ANGLE 30
#define MIN_FOOT_ANGLE -26

#define MAX_LOWER_LEG_ANGLE -30
#define MIN_LOWER_LEG_ANGLE -90

#define MAX_TAIL_Z_ANGLE 5
#define MIN_TAIL_Z_ANGLE -5

#define MAX_TAIL_Y_ANGLE 25
#define MIN_TAIL_Y_ANGLE -25

float frame = 500;

float	jaw_rate = (MAX_JAW_ANGLE - MIN_JAW_ANGLE) / frame,
		neckle_rate = (MAX_NECKLE_ANGLE - MIN_NECKLE_ANGLE) / frame,
		upperLeg_rate = 1.5 * (MAX_UPPER_LEG_ANGLE - MIN_UPPER_LEG_ANGLE) / frame,
		lowerLeg_rate = 1.5 * (MAX_LOWER_LEG_ANGLE - MIN_LOWER_LEG_ANGLE) / frame,
		foot_rate = (MAX_FOOT_ANGLE - MIN_FOOT_ANGLE) / frame,
		tailY_rate = (MAX_TAIL_Y_ANGLE - MIN_TAIL_Y_ANGLE) / (frame * 10),
		tailZ_rate = (MAX_TAIL_Z_ANGLE - MIN_TAIL_Z_ANGLE) / (frame * 10);



float xtp = 0.0, ytp = 0.0, ztp = 0.0, xrp = 0.0, yrp = 0.0, zrp = 0.0, xt = 0.0, yt = 0.0, zt = 0.0, xr = 0.0, yr = 0.0, zr = 0.0;
float	thighLeftAngle = 9, thighRightAngle = 9, 
		legLeftAngle = -30, legRightAngle = -30, 
		footRightAngle = -26, footLeftAngle = -26,
		chestAngle = 8, neckleAngle = 8, upperHandAngle = 8, lowerHandAngle = 8, 
		headAngleX = 0.0, headAngleY = 0.0, headAngleZ = -25.0, 
		jawAngle = 0.0, tailAngleZ = 0.0, tailAnngleY = 0.0;

bool revereseLeg = false, leftLeg = false, reverseJaw = false;

/* start of material definitions */
#ifdef LIGHT
GLfloat mat_specular[] =
{ 0.628281, 0.555802, 0.366065, 1.0 };
GLfloat mat_ambient[] =
{ 0.24725, 0.1995, 0.0745, 1.0 };
GLfloat mat_diffuse[] =
{ 0.75164, 0.60648, 0.22648, 1.0 };
GLfloat mat_shininess[] =
{ 128.0 * 0.4 };

GLfloat mat_specular2[] =
{ 0.508273, 0.508273, 0.508373 };
GLfloat mat_ambient2[] =
{ 0.19225, 0.19225, 0.19225 };
GLfloat mat_diffuse2[] =
{ 0.50754, 0.50754, 0.50754 };
GLfloat mat_shininess2[] =
{ 128.0 * 0.6 };

GLfloat mat_specular3[] =
{ 0.296648, 0.296648, 0.296648 };
GLfloat mat_ambient3[] =
{ 0.25, 0.20725, 0.20725 };
GLfloat mat_diffuse3[] =
{ 1, 0.829, 0.829 };
GLfloat mat_shininess3[] =
{ 128.0 * 0.088 };

GLfloat mat_specular4[] =
{ 0.633, 0.727811, 0.633 };
GLfloat mat_ambient4[] =
{ 0.0215, 0.1745, 0.0215 };
GLfloat mat_diffuse4[] =
{ 0.07568, 0.61424, 0.07568 };
GLfloat mat_shininess4[] =
{ 128 * 0.6 };

GLfloat mat_specular5[] =
{ 0.60, 0.60, 0.50 };
GLfloat mat_ambient5[] =
{ 0.0, 0.0, 0.0 };
GLfloat mat_diffuse5[] =
{ 0.5, 0.5, 0.0 };
GLfloat mat_shininess5[] =
{ 128.0 * 0.25 };

#endif
/* end of material definitions */

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

#ifdef NORM
void
Normalize(float v[3])
{
	GLfloat d = sqrt(v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);

	if (d == 0.0) {
		printf("zero length vector");
		return;
	}
	v[1] /= d;
	v[2] /= d;
	v[3] /= d;
}

void
NormXprod(float v1[3], float v2[3], float v[3], float out[3])
{
	GLint i, j;
	GLfloat length;

	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
	Normalize(out);
}

#endif

void
SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[])
{

	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, shin);
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}


void drawFoot(bool isLeft, char solid)
{
	glTranslatef(0.0f, -0.4f, 0.0f);

	if (isLeft)
		glRotatef(footLeftAngle, 0, 0, 1);
	else
		glRotatef(footRightAngle, 0, 0, 1);

	glTranslatef(0.2f, 0.0f, 0.0f);

	Box(0.8, 0.2, 0.5, solid);
}

void drawLeg(bool isLeft, char solid)
{
	if (isLeft)
	{
		glTranslatef(-0.3, -0.7, -0.9);
		glRotatef(thighLeftAngle, 0, 0, 1);
	}
	else
	{
		glTranslatef(-0.3, -0.7, 0.9);
		glRotatef(thighRightAngle, 0, 0, 1);
}

	glTranslatef(0.0, -0.2, 0.0);
	Box(0.8, 1.0, 0.5, solid);

	glPushMatrix();
	glTranslatef(-0.2, -0.3, 0.0);
	if (isLeft)
		glRotatef(legLeftAngle, 0, 0, 1);
	else
		glRotatef(legRightAngle, 0, 0, 1);
	glTranslatef(0.0, -0.325, 0.0);
	Box(0.5, 0.65, 0.5, solid);

	glPushMatrix(); // draw calf
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(50, 0, 0, 1);
	glTranslatef(0.0, -0.4, 0.0);
	Box(0.3, 0.8, 0.5, solid);

	glPushMatrix(); // draw foot
	drawFoot(isLeft, solid);
	glPopMatrix(); // end of draw foot

	glPopMatrix(); // end of draw calf

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
	#ifdef LIGHT
		SetMaterial(mat_specular4, mat_ambient4, mat_diffuse4, mat_shininess4);
	#endif
	glShadeModel(GL_SMOOTH);
	// Base body
	glRotatef(10, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
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

void
lighting(void)
{

	GLfloat position[] =
	{ 0.0, 2.0, 5.0, 1.0 };

#ifdef MOVE_LIGHT
	glRotatef((GLfloat)lightturn1, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)lightturn, 0.0, 1.0, 0.0);
	glRotatef(0.0, 1.0, 0.0, 0.0);
#endif
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);

	glTranslatef(0.0, 0.0, 2.0);
	glDisable(GL_LIGHTING);
	Box(0.1, 0.1, 0.1, 0);
	glEnable(GL_LIGHTING);
}

void
disable(void)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void display(void)
{
	char solid = 1;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (solid) {
		glPushMatrix();
		lighting();
		glPopMatrix();
	}
	else
		disable();

	

	glPushMatrix();
	glTranslatef(xt, yt, zt);
	
	glRotatef(yr, 0, 1, 0);
	glRotatef(xr, 1, 0, 0);
	glRotatef(zr, 0, 0, 1);

	drawTrex(solid);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void walkAnimation()
{
	if (!leftLeg)
	{
		if (!revereseLeg)
		{
			thighRightAngle += upperLeg_rate;
			legRightAngle -= lowerLeg_rate;
			//footRightAngle -= foot_rate;
			tailAnngleY -= tailY_rate;
		}
		else
		{
			thighRightAngle -= upperLeg_rate;
			legRightAngle += lowerLeg_rate;
			//footRightAngle += foot_rate;
			tailAnngleY += tailY_rate;
		}

		if (thighRightAngle >= MAX_UPPER_LEG_ANGLE)
		{
			revereseLeg = true;
		}
		else if (thighRightAngle <= MIN_UPPER_LEG_ANGLE)
		{
			revereseLeg = false;
			leftLeg = true;
			thighRightAngle = MIN_UPPER_LEG_ANGLE;
		}
	}
	else
	{
		if (!revereseLeg)
		{
			thighLeftAngle += upperLeg_rate;
			legLeftAngle -= lowerLeg_rate;
			//footLeftAngle -= foot_rate;
			tailAnngleY += tailY_rate;
		}
		else
		{
			thighLeftAngle -= upperLeg_rate;
			legLeftAngle += lowerLeg_rate;
			//footLeftAngle += foot_rate;
			tailAnngleY -= tailY_rate;
		}

		

		if (thighLeftAngle >= MAX_UPPER_LEG_ANGLE)
		{
			revereseLeg = true;
		}
		else if (thighLeftAngle <= MIN_UPPER_LEG_ANGLE)
		{
			revereseLeg = false;
			leftLeg = false;
			thighLeftAngle = MIN_UPPER_LEG_ANGLE;
		}
	}
}

void biteAnimation()
{
	if (!reverseJaw)
		jawAngle += jaw_rate;
	else
		jawAngle -= jaw_rate;

	if (jawAngle >= MAX_JAW_ANGLE) reverseJaw = true;
	else if (jawAngle <= MIN_JAW_ANGLE) reverseJaw = false;

}

void animation()
{
	walkAnimation();
	biteAnimation();
	glutPostRedisplay();
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
	//cout << "xtp = " << xtp << " ytp = " << ytp << " ztp = " << ztp << "\nxrp = " << xrp << " yrp = " << yrp << " zrp = " << zrp << "\n";
}

void displayManual()
{
	cout << "w untuk rotasi atas\ns untuk rotasi bawah\na untuk rotasi kiri\nd untuk rotasi kanan\ni untuk trranslalsi atas \nk untuk translasi bawah\nj untuk translalsi kiri\nl untuk translasi kanan\nu untuk translasi jauh\no untuk translalsi dekat\n";
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i':
		yt = (int)yt % 360;
		yt += 0.1f;
		break;
	case 'k':
		yt += -0.1f;
		break;
	case 'j':
		xt += -0.1f;
		break;
	case 'l':
		xt += 0.1f;
		break;
	case 'u':
		zt += -0.1f;
		break;
	case 'o':
		zt += 0.1f;
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

	//displayAtrib();
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

//	displayAtrib();
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
	displayManual();

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
	glutIdleFunc(animation);

	glutMainLoop();
	return 0;

}
