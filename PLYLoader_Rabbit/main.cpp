#include "Loader.h"
CPLYLoader plyLoader;
static GLfloat xangle, yangle;
static GLfloat oldx, oldy; //old mouse coordinate
static GLfloat WinH, WinW; //window size
static GLint glOrthoscale = 50;
static GLdouble LookAtEye[] = { 0.0, 0.0, 20.0 }; /* initial viewer location */
static GLdouble LookAtCentery[] = { 0.0, 0.0, 0.0 }; /* initial viewer location */
static GLfloat scale = 1;
GLint m_load_type = 0; /* 0:Points  1:Grids  2:Triangles */

GLfloat L0_position[] = { 1.0, 1.0, -30.0,1.0 };
GLfloat L1_position[] = { 1.0, 1.0, 30.0,1.0 };
void init()
{
	glClearColor(0, 0, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glShadeModel(GL_SMOOTH);
	//plyLoader.LoadModel("NewYear.ply2");
	plyLoader.LoadModel("rabbit.ply2");

	//lighting
	glEnable(GL_DEPTH_TEST);

	//GLfloat L0_position[] = { 1.0, 1.0, -5.0,0.0 };
	GLfloat L0_ambient[] = { 0.0, 1.0, 0,0, 1.0 };
	GLfloat L0_diffuse[] = { 0.0, 1.0, 0,0, 1.0 }; //green
	GLfloat L0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, L0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, L0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, L0_specular);
	//GLfloat L1_position[] = { 1.0, 1.0,5.0,0.0 };
	GLfloat L1_ambient[] = { 1.0, 0.0, 0,0, 1.0 };
	GLfloat L1_diffuse[] = { 1.0, 0.0, 0,0, 1.0 }; //red
	GLfloat L1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, L1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, L1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, L1_specular);



	//GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.2f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(LookAtEye[0], LookAtEye[1], LookAtEye[2], 
		LookAtCentery[0], LookAtCentery[1], LookAtCentery[2],
		0.0, 1.0, 0.0);

	//glPushMatrix();
	glRotatef(xangle, 1.0, 0.0, 0.0);
	glRotatef(yangle, 0.0, 1.0, 0.0);
	glScalef(scale, scale, scale);

	if (m_load_type == 0)
		plyLoader.DrawPoints();
	else if (m_load_type == 1)
		plyLoader.DrawGrids();
	else if (m_load_type == 2)
		plyLoader.DrawTriangles();
	else if (m_load_type == 3)
		plyLoader.DrawFill();
	//glPopMatrix();
	
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0.0);
	if (L0_position[3] == 0)        /* 10.0 = 'infinite' light */
		glVertex3f(L0_position[0] * 10.0, L0_position[1] * 10.0, L0_position[2] * 10.0);
	else
		glVertex3f(L0_position[0], L0_position[1], L0_position[2]);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0.0);
	if (L0_position[3] == 0)        /* 10.0 = 'infinite' light */
		glVertex3f(L1_position[0] * 10.0, L1_position[1] * 10.0, L1_position[2] * 10.0);
	else
		glVertex3f(L1_position[0], L1_position[1], L1_position[2]);
	glEnd();

	glFlush();
	glutSwapBuffers();
}
void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		oldx = x;
		oldy = y;
	}
}
void motion(int x, int y)
{
	GLfloat deltax = oldx - x;
	GLfloat deltay = oldy - y;
	yangle += 360 * deltax / WinW;//根据屏幕上鼠标滑动的距离来设置旋转的角度
	xangle += 360 * deltay / WinH;
	//printf("xangle = %f \t yangle = %f\n", xangle, yangle);
	oldx = x;
	oldy = y;
	glutPostRedisplay();
}
void mykey(unsigned char key, int x, int y)
{

	/* gluLookAt eye coordinate */
	if (key == 'x') LookAtEye[0] -= 1.0;
	if (key == 'X') LookAtEye[0] += 1.0;
	if (key == 'y') LookAtEye[1] -= 1.0;
	if (key == 'Y') LookAtEye[1] += 1.0;
	if (key == 'z') LookAtEye[2] -= 1.0;
	if (key == 'Z') LookAtEye[2] += 1.0;
	/* gluLookAt camera coordinate */
	if (key == 'a') LookAtCentery[0] -= 1.0;
	if (key == 'A') LookAtCentery[0] += 1.0;
	if (key == 'b') LookAtCentery[1] -= 1.0;
	if (key == 'B') LookAtCentery[1] += 1.0;
	if (key == 'c') LookAtCentery[2] -= 100;
	if (key == 'C') LookAtCentery[2] += 100;
	/* enlargement factor */
	if (key == '+') scale += 0.1;
	if (key == '-') scale = scale < 0.2 ? 0.1 : scale - 0.1;

	printf("Scale = %.2f\n", scale);
	printf("Camera eyes = %.0f %.0f %.0f\n", LookAtEye[0], LookAtEye[1], LookAtEye[2]);
	printf("Camera Centery = %.0f %.0f %.0f\n\n", LookAtCentery[0], LookAtCentery[1], LookAtCentery[2]);
	display();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	WinW = w;
	WinH = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-glOrthoscale, glOrthoscale, -glOrthoscale * (GLfloat)h / (GLfloat)w,
		glOrthoscale * (GLfloat)h / (GLfloat)w, -glOrthoscale, glOrthoscale);
	glFrustum(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void load_type(int index) {
	m_load_type = index;
}
void main_menu(int index)
{

}
int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Display Model");
	init();
	int c_menu = glutCreateMenu(load_type);
	glutAddMenuEntry("Points", 0);
	glutAddMenuEntry("Grids", 1);
	glutAddMenuEntry("Triangles", 2);
	glutAddMenuEntry("Fill", 3);

	glutCreateMenu(main_menu);
	glutAddSubMenu("Load Types", c_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	//glutIdleFunc(spinCube);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(mykey);
	glutMainLoop();
	return 0;
}