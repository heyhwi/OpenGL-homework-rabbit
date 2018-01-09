#include "Loader.h"
CPLYLoader plyLoader;
static GLfloat xangle, yangle;
static GLfloat oldx, oldy; //old mouse coordinate
static GLfloat WinH, WinW; //window size
static GLint glOrthoscale = 50;
static GLdouble LookAtEye[] = { 0.0, 0.0, 20.0 }; /* initial viewer location */
static GLdouble LookAtCentery[] = { 0.0, 0.0, 0.0 }; /* initial viewer location */
static GLfloat scale = 1;
//GLfloat position[] = { 50, 50, -50,1 };
GLfloat position[] = { 1.0, 1.0, -1.0,1.0 };
GLint m_load_type = 0; /* 0:Points  1:Grids  2:Triangles */
void init()
{
	glClearColor(0, 0, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_COLOR_ARRAY);
	//plyLoader.LoadModel("NewYear.ply2");
	plyLoader.LoadModel("rabbit.ply2");

	//lighting
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(LookAtEye[0], LookAtEye[1], LookAtEye[2], 
		LookAtCentery[0], LookAtCentery[1], LookAtCentery[2],
		0.0, 1.0, 0.0);
	glRotatef(xangle, 1.0, 0.0, 0.0);
	glRotatef(yangle, 0.0, 1.0, 0.0);
	glScalef(scale, scale, scale);

	if(m_load_type == 0)
		plyLoader.DrawPoints();
	else if(m_load_type == 1)
		plyLoader.DrawGrids();
	else if(m_load_type == 2)
		plyLoader.DrawTriangles();

	//glutSolidTeapot(0.4);
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
	//glFrustum(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
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