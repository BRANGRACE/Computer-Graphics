#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define Pi 3.1415926

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

//图形平移函数
void translatePolygon(wcPt2D *verts, GLint nVerts, GLfloat tx, GLfloat ty)
{
    wcPt2D vertsRot[nVerts];
    GLint k;
    for(k = 0; k < nVerts; k++){
        vertsRot[k].x = verts[k].x + tx;
        vertsRot[k].y = verts[k].y + ty;
    }
    glBegin(GL_POLYGON);
    for(k = 0; k < nVerts; k++)
        glVertex2f(vertsRot[k].x, vertsRot[k].y);
    glEnd();
}

//图形旋转函数
void rotatePolygon(wcPt2D *verts, GLint nVerts, wcPt2D pivPt, GLdouble theta)
{
    wcPt2D vertsRot[nVerts];
    GLint k;
    for(k = 0; k < nVerts; k++){
        vertsRot[k].x = pivPt.x + (verts[k].x -pivPt.x) * cos(theta) - (verts[k].y - pivPt.y) * sin(theta);
        vertsRot[k].y = pivPt.y + (verts[k].x -pivPt.x) * sin(theta) + (verts[k].y - pivPt.y) * cos(theta);
    }
    glBegin(GL_POLYGON);
    for(k = 0; k < nVerts; k++)
        glVertex2f(vertsRot[k].x, vertsRot[k].y);
    glEnd();
}

//图形比例函数
void scalePolygon(wcPt2D *verts, GLint nVerts, wcPt2D fixedPt, GLfloat sx, GLfloat sy)
{
    wcPt2D vertsNew[nVerts];
    GLint k;

    for (k = 0; k < nVerts; k++){
        vertsNew[k].x = verts[k].x * sx + fixedPt.x * (1 - sx);
        vertsNew[k].y = verts[k].y * sy + fixedPt.y * (1 - sy);
    }
    glBegin(GL_POLYGON);
    for(k = 0; k < nVerts; k++)
        glVertex2f(vertsNew[k].x, vertsNew[k].y);
    glEnd();
}

void display(void){
    //初始化多边形顶点
    wcPt2D verts[4];
    verts[0].x = 100,verts[1].x = 100,verts[2].x = 200,verts[3].x = 200;
    verts[0].y = 100,verts[1].y = 200,verts[2].y = 200,verts[3].y = 100;
    //初始化旋转基准点
    wcPt2D pivPt;
    pivPt.x = 100, pivPt.y = 100;
    //初始化比例固定点
    wcPt2D fixedPt;
    fixedPt.x = 10, fixedPt.y = 10;

    GLfloat color[3] = {0.0, 0.0, 0.0};  //初始图形颜色为黑色
    GLfloat color1[3] = {1.0, 0.0, 0.0};  //平移图形颜色为红色
    GLfloat color2[3] = {0.0, 1.0, 0.0};  //旋转图形颜色为绿色
    GLfloat color3[3] = {0.0, 0.0, 1.0};  //缩放图形颜色为蓝色

    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 500, 500);

    glColor3fv(color);  //初始图形
    polygon(verts, 4);

    glColor3fv(color1);  //平移
    translatePolygon(verts, 4, 250, 250);

    glColor3fv(color2);  //旋转
    rotatePolygon(verts, 4, pivPt, Pi / 6);

    glColor3fv(color3);  //比例
    scalePolygon(verts, 4, fixedPt, 2, 1.5);

    glScalef(1, -1, 1);  //关于x轴对称
    polygon(verts, 4);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Translation");

    glClearColor(1, 1, 1, 0.0);
    glMatrixMode(GL_PROJECTION);//投影模型
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
