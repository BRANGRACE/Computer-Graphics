#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>


const int POINTNUM=6;      //多边形点数.

typedef struct XET
{
    float x;
    float dx,ymax;
    XET* next;
} AET,NET;

struct point
{
    float x;
    float y;
}
polypoint[POINTNUM]= {250,50,450,150,450,400,250,250,100,350,200,250}; //多边形顶点

void PolyScan()
{
    int MaxY=0;
    int i;
    for(i=0; i<POINTNUM; i++)
        if(polypoint[i].y>MaxY)
            MaxY=polypoint[i].y;

    AET *pAET=new AET;
    pAET->next=NULL;

    NET *pNET[1024];
    for(i=0; i<=MaxY; i++)
    {
        pNET[i]=new NET;
        pNET[i]->next=NULL;
    }
    glClear(GL_COLOR_BUFFER_BIT);        //赋值的窗口显示.
    glColor3f(1.0,0.0,0.0);             //设置直线的颜色红色
    glBegin(GL_POINTS);
    for(i=0; i<=MaxY; i++)
    {
        for(int j=0; j<POINTNUM; j++)
            if(polypoint[j].y==i)
            {
                if(polypoint[(j-1+POINTNUM)%POINTNUM].y>polypoint[j].y)
                {
                    NET *p=new NET;
                    p->x=polypoint[j].x;
                    p->ymax=polypoint[(j-1+POINTNUM)%POINTNUM].y;
                    p->dx=(polypoint[(j-1+POINTNUM)%POINTNUM].x-polypoint[j].x)/(polypoint[(j-1+POINTNUM)%POINTNUM].y-polypoint[j].y);
                    p->next=pNET[i]->next;
                    pNET[i]->next=p;

                }
                if(polypoint[(j+1+POINTNUM)%POINTNUM].y>polypoint[j].y)
                {
                    NET *p=new NET;
                    p->x=polypoint[j].x;
                    p->ymax=polypoint[(j+1+POINTNUM)%POINTNUM].y;
                    p->dx=(polypoint[(j+1+POINTNUM)%POINTNUM].x-polypoint[j].x)/(polypoint[(j+1+POINTNUM)%POINTNUM].y-polypoint[j].y);
                    p->next=pNET[i]->next;
                    pNET[i]->next=p;
                }
            }
    }
    for(i=0; i<=MaxY; i++)
    {
        NET *p=pAET->next;
        while(p)
        {
            p->x=p->x + p->dx;
            p=p->next;
        }
        AET *tq=pAET;
        p=pAET->next;
        tq->next=NULL;
        while(p)
        {
            while(tq->next && p->x >= tq->next->x)
                tq=tq->next;
            NET *s=p->next;
            p->next=tq->next;
            tq->next=p;
            p=s;
            tq=pAET;
        }
        AET *q=pAET;
        p=q->next;
        while(p)
        {
            if(p->ymax==i)
            {
                q->next=p->next;
                delete p;
                p=q->next;
            }
            else
            {
                q=q->next;
                p=q->next;
            }
        }
        p=pNET[i]->next;
        q=pAET;
        while(p)
        {
            while(q->next && p->x >= q->next->x)
                q=q->next;
            NET *s=p->next;
            p->next=q->next;
            q->next=p;
            p=s;
            q=pAET;
        }

        p=pAET->next;
        while(p && p->next)
        {
            for(float j=p->x; j<=p->next->x; j++)
                glVertex2i(static_cast<int>(j),i);
            p=p->next->next;//考虑端点情况
        }


    }
    glEnd();
    glFlush();
}
void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
//窗口的背景颜色设置为白色
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,700.0,0.0,450.0);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);                //I初始化 GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //设置显示模式：单个缓存和使用RGB模型
    glutInitWindowPosition(50,100);        //设置窗口的顶部和左边位置
    glutInitWindowSize(400,300);        //设置窗口的高度和宽度
    glutCreateWindow("An Example OpenGL Program");    //创建显示窗口

    init();                                //调用初始化过程
    glutDisplayFunc(PolyScan);        //图形的定义传递给我window.
    glutMainLoop();                        //显示所有的图形并等待

    return 0;
}
