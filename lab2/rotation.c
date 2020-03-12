#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

GLfloat triangle[3][3]={{100.0,250.0,175.0},{100.0,100.0,300.0},{1.0,1.0,1.0}};
GLfloat rotatemat[3][3]={{0},{0},{0}};
GLfloat result[3][3]={{0},{0},{0}};
GLfloat arbitrary_x=0;
GLfloat arbitrary_y=0;  
float r_a;     //rotation_angle

void multiply()
{
    int i,j,k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            result[i][j]=0;
            for(k=0;k<3;k++)
            {
                result[i][j]=result[i][j]+rotatemat[i][k]*triangle[k][j];
            }
         }
      }
}

void rotate()
{
    GLfloat m,n;
    r_a=(3.14*r_a)/180;
    m=arbitrary_x*(cos(r_a)-1)+arbitrary_y*(sin(r_a));
    n=arbitrary_y*(cos(r_a))-arbitrary_x*(sin(r_a));      
    
    rotatemat[0][0]=cos(r_a);
    rotatemat[0][1]=-sin(r_a);
    rotatemat[0][2]=m;
    rotatemat[1][0]=sin(r_a);
    rotatemat[1][1]=cos(r_a);
    rotatemat[1][2]=n;
    rotatemat[2][0]=0;
    rotatemat[2][1]=0;
    rotatemat[2][2]=1;
    
    multiply();
}

void drawtriangle()
{
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(triangle[0][0],triangle[1][0]);
    glVertex2f(triangle[0][1],triangle[1][1]);
    glVertex2f(triangle[0][2],triangle[1][2]);
    glEnd();
}

void drawrotatedtriangle()
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(result[0][0],result[1][0]);
    glVertex2f(result[0][1],result[1][1]);
    glVertex2f(result[0][2],result[1][2]);
    glEnd();
}

void drawtext(float x,float y,char *s)
{
    int i;
    glRasterPos2f(x,y);
    for(i=0;s[i]!='\0';i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);
    }   
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawtriangle();
    drawtext(300,300,"USN:1BI17CS060");
    drawtext(300,250,"rotation_angle=30");
    drawtext(300,200,"about fixed point (50,60)");
    drawrotatedtriangle();
    glFlush();
}

void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-499.0,499.0,-499.0,499.0);
}

int main(int argc, char **argv)
{
    int ch;
    printf("enter the choice \n 1. to rotate about an origin \n 2. to rotate about fixed point \n");
    scanf("%d",&ch);
    
    switch(ch)
    {
        case 1: printf("enter the rotation angle in degrees\n");
                scanf("%f",&r_a);
                rotate();
                break;
                
        case 2: printf("enter the fixed points");
                scanf("%f%f",&arbitrary_x,&arbitrary_y);
                printf("enter the rotation angle in degrees\n");
                scanf("%f",&r_a);
                rotate();
                break;
     }
     
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(500,500);
     glutInitWindowPosition(0,0);
     glutCreateWindow("Rotation of a triangle");
     glutDisplayFunc(display);
     myinit();
     glutMainLoop();
     return 0;
}
