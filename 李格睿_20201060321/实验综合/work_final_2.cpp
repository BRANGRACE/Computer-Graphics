#include <windows.h>
#include <GL/glut.h>

#define stripeImageWidth 32
GLubyte stripeImage[4*stripeImageWidth];
static GLuint texName;

//贴图纹理
void makeStripeImage(void)
{
    for (int j = 0; j < stripeImageWidth; j++) {
        stripeImage[4*j] = (GLubyte) ((j<=4) ? 255 : 0);
        stripeImage[4*j+1] = (GLubyte) ((j>4) ? 255 : 0);
        stripeImage[4*j+2] = (GLubyte) 255;
        stripeImage[4*j+3] = (GLubyte) 0;
    }
}

static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    makeStripeImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_1D, texName);

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
    /*设置纹理和物体表面颜色处理方式*/
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//和物体表面颜色做与运算

    /*设置自动生成纹理坐标的计算方式*/
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;
    //一维纹理，只有S坐标
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);//整形形式
    glTexGenfv(GL_S, currentPlane, currentCoeff);//向量形式

    glEnable(GL_TEXTURE_GEN_S);//激活s坐标的纹理坐标生成
    glEnable(GL_TEXTURE_1D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glMaterialf (GL_FRONT, GL_SHININESS, 64.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix ();
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glBindTexture(GL_TEXTURE_1D, texName);
    glutSolidTeapot(2.0);
    glPopMatrix ();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-3.5, 3.5, -3.5*(GLfloat)h/(GLfloat)w,
                 3.5*(GLfloat)h/(GLfloat)w, -3.5, 3.5);
    else
        glOrtho (-3.5*(GLfloat)w/(GLfloat)h,
                 3.5*(GLfloat)w/(GLfloat)h, -3.5, 3.5, -3.5, 3.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'e':
        case 'E':
            currentGenMode = GL_EYE_LINEAR;//视觉坐标系中计算纹理坐标
            currentPlane = GL_EYE_PLANE;//向量形式
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
            glTexGenfv(GL_S, currentPlane, currentCoeff);
            glutPostRedisplay();
            break;
        case 'o':
        case 'O':
            currentGenMode = GL_OBJECT_LINEAR;//模型坐标系中计算纹理坐标
            currentPlane = GL_OBJECT_PLANE;
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);//整数形式
            glTexGenfv(GL_S, currentPlane, currentCoeff);//模型坐标系中计算，计算系数由currentCoeff向量指定
            glutPostRedisplay();
            break;
        case 's':
        case 'S':
            currentCoeff = slanted;
            glTexGenfv(GL_S, currentPlane, currentCoeff);
            glutPostRedisplay();
            break;
        case 'x':
        case 'X':
            currentCoeff = xequalzero;
            glTexGenfv(GL_S, currentPlane, currentCoeff);
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(256, 256);
    glutInitWindowPosition(100, 100);
    glutCreateWindow ("纹理");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
