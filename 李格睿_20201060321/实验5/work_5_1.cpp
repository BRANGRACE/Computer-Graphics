#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void putpixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void circlePoint(int x0,int y0,int x,int y)
{
	putpixel(x0+x, y0+y);
	putpixel(x0-x, y0+y);
	putpixel(x0+x, y0-y);
	putpixel(x0-x, y0-y);
	putpixel(y0+y, x0+x);
	putpixel(y0-y, x0+x);
	putpixel(y0+y, x0-x);
	putpixel(y0-y, x0-x);
}

void MidBresenhamcircle(int r)
{
    int x0,y0,x,y,d;
    x0 = r;
    y0 = r;
    x = 0;
    y = r;
    d = 1 - r;
    while(x<y)
    {
        circlePoint(x0,y0,x,y);
        if(d<0)
            d += 2 * x + 3;
        else{
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.4, 0.2);
    glBegin(GL_LINES);
    MidBresenhamcircle(50);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("An Example for BresenhamCircle");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
