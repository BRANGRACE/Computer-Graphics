#include <windows.h>
#include <GL/glut.h>

void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	GLfloat light0_ambient[]={1,0.0,0.0,0.0};
	GLfloat light0_diffuse[]={1,0.0,0.0,0.0};
	GLfloat light0_specular[]={1,0.0,0.0,0.0};
	GLfloat light0_position[] = {2.0,2.0,2.0,0.0};//(x 为正是右 y为正是上 z为正是前)
	glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);
	glLightfv(GL_LIGHT0,GL_POSITION,light0_position);

	glEnable(GL_LIGHT1);
	GLfloat light1_ambient[]={0.0,1,0.0,0.0};
	GLfloat light1_diffuse[]={0.0,1,0.0,0.0};
	GLfloat light1_specular[]={0.0,1,0.0,0.0};
	GLfloat light1_position[] = {-1.0,0.0,0.0,0.0};
	glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
	glLightfv(GL_LIGHT1,GL_POSITION,light1_position);

	glEnable(GL_LIGHT2);
	GLfloat light2_ambient[]={0.0,0.0,1,0.0};
	GLfloat light2_diffuse[]={0.0,0.0,1,0.0};
	GLfloat light2_specular[]={0.0,0.0,1,0.0};
	GLfloat light2_position[] = {-1.0,-1.0,1.0,0.0};
	glLightfv(GL_LIGHT2,GL_AMBIENT,light2_ambient);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,light2_diffuse);
	glLightfv(GL_LIGHT2,GL_SPECULAR,light2_specular);
	glLightfv(GL_LIGHT2,GL_POSITION,light2_position);

	glEnable(GL_DEPTH_TEST);
	glTranslatef(1.5,1.5,0);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidTeapot(0.5);
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10, 10 );
	else
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, 1.5, 1.5, -10,10 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300,300);
	glutInitWindowPosition(0,0);
	glutCreateWindow("色彩");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
