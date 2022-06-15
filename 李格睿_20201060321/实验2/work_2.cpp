#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

inline int round (const float a)
{
    return int (a + 0.5);
}

void setPixel(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void lineDDA(int x0, int y0, int xEnd, int yEnd)
{
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;

    if(fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    xIncrement = float (dx) / float (steps);
    yIncrement = float (dy) / float (steps);

    setPixel(round(x), round(y));
    for(k = 0; k < steps; k++){
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.4, 0.2);
    glBegin(GL_LINES);
    lineDDA(180, 15, 10, 145);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("An Example for DDA");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
