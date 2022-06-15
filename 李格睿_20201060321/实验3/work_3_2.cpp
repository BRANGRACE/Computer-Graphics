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

void lineBres (int x0, int y0, int xEnd, int yEnd)
{
    int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
    float e = -0.5;
    int x = x0;
    int y = y0;
    float k = dy * 1.0 / dx;
    if(fabs(k) <1.0){
        while(x < xEnd){
            setPixel(x, y);
            e = e + k;
            if(e > 0){
                x +=1;
                y +=1;
                e -= 1;
            }
            else{
                x +=1;
            }
        }
    }
    else{
        while(y < yEnd){
            setPixel(x, y);
            e = e + 1/k;
            if(e > 0){
                x += 1;
                y += 1;
                e -= 1;
            }
            else{
                y += 1;
            }
        }
    }

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.4, 0.2);
    glBegin(GL_LINES);
    lineBres(10, 15, 150, 500);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("An Example for BresenhamPlus");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
