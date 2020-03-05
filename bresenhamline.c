#include<stdio.h>
#include<GL/glut.h>

int x1,x2,y1,y2;

void myInit()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,500,0,500);
}

void draw_pixel(int x, int y)
{
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void draw_text(float x, float y, char *s)
{
	int i;
	glRasterPos2f(x,y);
	for(i=0;s[i]!='\0';i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
}

void draw_line(int x1, int x2, int y1, int y2)
{
	int dx,dy,i,d;
	int x,y;
	int incx,incy,inc1,inc2;
	dx=x2-x1;
	dy=y2-y1;
	if(dx<0)
		dx=-dx;
	if(dy<0)
		dy=-dy;
	incx=1;
	if(x2<x1)
		incx=-1;
	incy=1;
	if(y2<y1)
		incy=-1;
	x=x1;
	y=y1;
	
	if(dx>dy)
	{
		draw_pixel(x,y);
		d=2*dy-dx;
		inc1=2*(dy-dx);
		inc2=2*dy;
		
		for(i=0;i<dx;i++)
		{
			if(d>=0)
			{
				y+=incy;
				d+=inc1;
			}
			else
				d+=inc2;
			x+=incx;
			draw_pixel(x,y);
		}
	}
	
	else
	{
		draw_pixel(x,y);
		d=2*dx-dy;
		inc1=2*(dx-dy);
		inc2=2*dx;
		
		for(i=0;i<dy;i++)
		{
			if(d>=0)
			{
				x+=incx;
				d+=inc1;
			}
			else
				d+=inc2;
			y+=incy;
			draw_pixel(x,y);
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_line(x1,x2,y1,y2);
	draw_text(50,390,"USN : 1BI17CS060");
	draw_text(50,370,"NAME : HARSHITH GOWDA N");
	draw_text(50,350,"BATCH : A4");
	draw_text(x1,y1-10,"(40,50)");									
	draw_text(x2,y2+10,"(350,450)");
	glFlush();
}

int main(int argc, char** argv)
{
	printf("enter the endpoints x1,y1,x2,y2\n");
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham's line drawing");
	myInit();
	glutDisplayFunc(display);	
	glutMainLoop();
	return 0; 
}


















