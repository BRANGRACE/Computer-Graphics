#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void setPixel(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void lineBres(int x0, int y0, int xEnd, int yEnd)
{
    glPointSize(3.0f);
    int x, y;
    int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
    if (dy * 1.0 / dx <= 1.0)
    {
        int p = 2 * dy - dx;
        int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
        if (x0 > xEnd){
            x = xEnd;
            y = yEnd;
            xEnd = x0;
        }
        else{
            x = x0;
            y = y0;
        }
        setPixel(x,y);

        while (x < xEnd){
            x++;
            if (p < 0)
                p += twoDy;
            else{
                y++;
                p += twoDyMinusDx;
            }
        setPixel(x, y);

        }
    }

    else{
        int p = 2 * dx - dy;
        int twoDx = 2 * dx, twoDyMinusDy = 2 * (dx - dy);
        if (y0 > yEnd){
            x = xEnd;
            y = yEnd;
            yEnd = y0;
        }
        else{
            x = x0;
            y = y0;
        }
        setPixel(x,y);

        while (y < yEnd){
            y++;
            if (p < 0)
                p += twoDx;
            else{
                x++;
                p += twoDyMinusDy;
            }
            setPixel(x, y);
        }
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.4, 0.2);
    glBegin(GL_LINES);
    lineBres(15, 10, 230, 300);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("An Example for Bresenham");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
