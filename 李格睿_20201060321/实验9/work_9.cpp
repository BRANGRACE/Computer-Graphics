#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0, 100);
}

class wcPt2D{
public:
    GLfloat x,y;
};

void polygon(wcPt2D *verts, GLint nVerts){
    glBegin(GL_POLYGON);
    for (GLint i = 0; i < nVerts; i++){
        glVertex2f(verts[i].x, verts[i].y);
    }
    glEnd();
}

void display(void){
	//平移变换
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1, 0, -10);
	glColor3f(1, 0, 0);
	glutWireCube(1);

	glTranslatef(3, 0, 0);
	glColor3f(0, 1, 0);
	glutWireCube(1);

	//缩放变换
	glLoadIdentity();
	glTranslatef(-1, 0, -10);
	glColor3f(1, 0, 0);
	glutWireCube(1);

	glScalef(1.5, 1.5, 1.5);
	glColor3f(0, 1, 0);
	glutWireCube(1);

	//旋转变换
		glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1, -1, -20);
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	//绘制出旋转轴
	glVertex3f(-25, -30, -25);
	glVertex3f(20, 15, 20);
	glEnd();
	glColor3f(1, 0, 0);
	for (int i = 0; i < 36; i++)
	{
		//逆变换
		glTranslatef(5, 0, 5);
		glRotatef(-45, 0, 0, 1);
		glRotatef(45, 1, 0, 0);
		glRotatef(10, 0, 1, 0);
		//再绕x轴顺时针旋转45度使旋转轴与y轴重合
		glRotatef(-45, 1, 0, 0);
		//先绕z轴逆时针旋转45度使旋转轴位于yz平面上
		glRotatef(45, 0, 0, 1);
		//先将旋转轴平移至经过原点
		glTranslatef(-5, 0, -5);
		glutWireCube(1);
	}

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Translation");

    glClearColor(1, 1, 1, 0.0);
    glMatrixMode(GL_PROJECTION);//投影模型
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
