#include<stdlib.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#define SCENE 10

int pageArray[9] = {0}, pageOfBuffer[3] = {0}, fault[9]={0}, counter[3]={0}, colour[9]={1,1,1,1,1,1,1,1,1}, pagecolour[3]={1,1,1};
float pagePosition[9] = {-5.5,-5.5,-5.5,-5.5,-5.5,-5.5,-5.5,-5.5,-5.5};
int hit = 0, step = -1, destination = 0, startAnimation = 0;
int showresult=0, faults =0;
char res[]="No. of Page Faults are :  ";


//Colours
float backgroundColor[][3]={{1,0,0}, {0,1,0}, {0,0,1}}, tileColor[][3]={{1,1,0}, {1,0.7,0.7}, {0,1,1}};
int bcPointer = 0, tcPointer = 0;
void *fonts[]=
{
GLUT_BITMAP_9_BY_15,
GLUT_BITMAP_TIMES_ROMAN_10,
GLUT_BITMAP_TIMES_ROMAN_24,
GLUT_BITMAP_HELVETICA_12,
GLUT_BITMAP_HELVETICA_10,
GLUT_BITMAP_HELVETICA_18,
};


void init()
{
  glColor3f(1,0,0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,800,0,600);
  glMatrixMode(GL_MODELVIEW);
}

void output(int x,int y,char *string,int j)
{
int len,i;
glColor3f(1.0f,0.0f,0.0f);
glRasterPos2f(x,y);
len=(int) strlen(string);
for(i=0;i<len;i++)
glutBitmapCharacter(fonts[j],string[i]);
}


void front_page()
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
glPushMatrix();

output(200,550,"SAPTHAGIRI COLLEGE OF ENGINEERING",2);
output(280,500," Dept of Computer Science ",2);
output(240,450,"Subject: Computer Graphics (18CSL67)",2);
output(320,400,"  CSE 6 A   ",2);
output(280,350,"MINI PROJECT ON",2);

output(220,300,"PAGE REPLACEMENTS ALGORITHMS:",2);
output(220,270,"1.FIFO(FIRST IN FIRST OUT)",2);
output(220,240,"2.LRU(LEAST RECENTLY USED)",2);


output(220,180,"By:",2);
output(275,150,"KOUSHIK V UPPULURI [1SG18CS038]",5);
output(275,130,"M LAKSHMI NAVEEN REDDY [1SG18CS042]",5);
output(275,90,"-> PRESS F to FIFO",2);
output(275,70,"-> PRESS L to LRU",2);
output(275,50,"-> PRESS Q to QUIT",2);

glFlush();
glCallList(SCENE);
glPopMatrix();
glutSwapBuffers();
}


void tile(float x, float y, char n)
{

  float size = 20;
  //Colour of frame buffer
  //glColor3f(1,1,1);

  glBegin(GL_POLYGON);
  glVertex2f(x-size, y-size);
  glVertex2f(x+size, y-size);
  glVertex2f(x+size, y+size);
  glVertex2f(x-size, y+size);
  glEnd();

  glColor3f(0,0,0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(x-size, y-size);
  glVertex2f(x+size, y-size);
  glVertex2f(x+size, y+size);
  glVertex2f(x-size, y+size);
  glEnd();
  glRasterPos2f(x-size/2, y);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, n);
}

//for fault count
void draw_flag()
{
  glColor3fv(backgroundColor[bcPointer]);
  glBegin(GL_POLYGON);
  glVertex2f(-10,-10);
  glVertex2f(10,-10);
  glVertex2f(10,10);
  glVertex2f(-10,10);
  glEnd();
}

void setInput()
{
  glColor3fv(backgroundColor[bcPointer]);

  glBegin(GL_POLYGON);
  glVertex2f(0,0);
  glVertex2f(700,0);
  glVertex2f(700,100);
  glVertex2f(0,100);
  glEnd();


  glPushMatrix();
  glTranslatef(-10, 40, 0);
  int i;
  for(i=0; i<9; i++)
  {
    glColor3fv(tileColor[tcPointer]);
    glTranslatef(70, 0, 0);
    glPushMatrix();

    if(pagePosition[i] > -4.5)
    {
      //Moving right
      glTranslatef(70*step-70*i,0,0);
    }
      //Input positions
    glTranslatef(0, -250-(45*pagePosition[i]), 0);

    if((int)pagePosition[i]==destination && pagePosition[i]>=0)
    glColor3f(1,0.3,0.3);
    else
    glColor3fv(tileColor[tcPointer]);
    //glColor3f(0.1,0.5,0.1);

    tile(10,10,pageArray[i]+'0');
    glPopMatrix();

    if(fault[i])
    {
      glPushMatrix();
      glTranslatef(0, -385, 0);
      draw_flag();
      glPopMatrix();
    }

  }
  glPopMatrix();
}

//Writing text on the screen
void drawText(char *string, float x,float y,float z)
{
  char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++)
  {
    if(*c=='\n')
    glRasterPos3f(x, y-0.05,z);
    else
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void setFrame()
{
  glPushMatrix();

  tile(0,0,pageOfBuffer[0]==0?' ':pageOfBuffer[0]+'0');
  glTranslatef(0, -45, 0);

  tile(0,0,pageOfBuffer[1]==0?' ':pageOfBuffer[1]+'0');
  glTranslatef(0, -45, 0);

  tile(0,0,pageOfBuffer[2]==0?' ':pageOfBuffer[2]+'0');

  glPopMatrix();
}


void display()
{

  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glPushMatrix();
  //Frame Buffer position
  glTranslatef(120+(70*step),195,0);
  setFrame();
  glPopMatrix();

  glColor3f(1,0,0);
  glPushMatrix();
  //Input Red box position
  glTranslatef(50, 400, 0);
  setInput();
  glPopMatrix();

  glEnd();
  if(step==8)
  {
    glColor3f(0,1,1);
    res[24]=(9-hit)+'0';
    drawText(res, 50, 20, 0);
  }
  glColor3f(0,1,1);
  drawText("FIFO Page Replacement Algorithm", 250, 550, 0);
  glFlush();
  glutSwapBuffers();
}

void idle1()
{
  if(!startAnimation)
  return;
  printf("Idle called\n");
  printf("%d, %f\n",destination, pagePosition[step]);
  if(destination>pagePosition[step])
  pagePosition[step]+=0.10;

  if(destination<pagePosition[step])//It has reached its location...So stop animation
  {
    if(fault[step])
    pageOfBuffer[destination]=pageArray[step];

    startAnimation = 0;
    destination = -10;
  }
  display();
}

void mouse1(int btn,int state,int x, int y)
{
  printf("Mouse function called\n");
  int n,i,j;

  if(startAnimation==1){
    printf("Animating");
    return;
  }
  if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
    if(step<9)
    step++;
    else
    printf("%d\n", hit);


    for(i=0;i<3;i++)
    {
      if(pageArray[step]==pageOfBuffer[i])
      {
        hit++;
        fault[step] = 0;
        startAnimation = 1;
        destination = -5;
        glutPostRedisplay();
        return;
      }
    }
    destination = ((step-hit)%3);
    printf("%d\n", destination);
    startAnimation = 1;
    fault[step] = 1;

    glutPostRedisplay();
  }
}

int getLRU()
{
	if(counter[0]>=counter[1] && counter[0]>=counter[2]) return 0;
	if(counter[1]>=counter[0] && counter[1]>=counter[2]) return 1;
	//if(counter[2]>=counter[1] && counter[2]>=counter[3]) return 2;
	return 2;
}

void display2()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

        
	glPushMatrix();
	glTranslatef(120+70*step,200,0);
	setFrame();
	glPopMatrix();

	glColor3f(1,0,0);
	glPushMatrix();
	glTranslatef(50, 400, 0);
	setInput();
	glPopMatrix();


	glEnd();



	if(showresult && step==8)
	{
		glColor3f(0,1,1);
		res[24]=faults+'0';
		drawText(res, 50, 20, 0);
	}
	glColor3f(0,1,1);
		drawText("LRU Page Replacement Algorithm", 250, 550, 0);

	glFlush();
	glutSwapBuffers();
}

void idle2()
{

	if(!startAnimation)
		return;

	if(destination > pagePosition[step])
	pagePosition[step]+=0.01;

	if(destination <= pagePosition[step])
	{
		if(fault[step])
		pageOfBuffer[destination]=pageArray[step];	
		startAnimation=0;
		destination=-10;
		showresult=1;
	}

	display2();

}


void mouse2(int btn,int state,int x, int y)
{

	int n,i,j;

	if(startAnimation==1)
		return;

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&step<8)


	{


		if(step<9)
			step++;





		for(i=0;i<3;i++)
		{

			if(pageArray[step]==pageOfBuffer[i])
			{
				fault[step]=0;
				counter[i]=0;

				for(j=0;j<3;j++)
					if(j!=i) counter[j]++;
				//dest=i;
					destination=-5;
				startAnimation=1;
				colour[step]=0;
				glutPostRedisplay();
					return;

			}



		}


		n=getLRU();
		counter[n]=0;
		for(i=0;i<3;i++)
			if(i!=n)
			counter[i]++;
		//pagecolour[n]=0;
		//assign[step]=n;
			destination=n;
			startAnimation=1;

		fault[step]=1;
		faults++;



	}

	glutPostRedisplay();

}


void setBGColor(int action)
{
	bcPointer = action;
	glutPostRedisplay();
}

void setTileColor(int action)
{
	tcPointer = action;
	glutPostRedisplay();
}

void menu(int action)
{
	if(action==0)
	exit(0);
}


void addMenu()
{
	int submenu1, submenu2;

	submenu1 = glutCreateMenu(setBGColor);
	glutAddMenuEntry("Red",0);
	glutAddMenuEntry("Green",1);
	glutAddMenuEntry("Blue",2);


	submenu2 = glutCreateMenu(setTileColor);
	glutAddMenuEntry("Yellow",0);
	glutAddMenuEntry("Light Red",1);
	glutAddMenuEntry("Light Blue",2);


	glutCreateMenu(menu);
	glutAddSubMenu("Background Colour",submenu1);
	glutAddSubMenu("Tile Colour",submenu2);
	glutAddMenuEntry("Quit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display1()
{
glClearColor(0.0,0.0,0.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);
front_page();
glFlush();
glutSwapBuffers();
}

void key1(unsigned char key,int x,int y)
{
switch(key)
{
case 'F':
case 'f':glutDisplayFunc(display);
		 glutMouseFunc(mouse1);
  glutIdleFunc(idle1);
		
	
break;

case 'L':
case 'l':glutDisplayFunc(display2);
	 glutMouseFunc(mouse2);
  glutIdleFunc(idle2);
  
  break;

case 'Q':
case 'q':exit(0);
}
glutPostRedisplay();
}



int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  int j;
  char key;
  printf("Enter the page array of size 9\n");
  for(j=0; j<9; j++)
  scanf("%d", &pageArray[j]);
 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1380,800);
  glutCreateWindow("PAGE REPLACEMENT ALGORITHMS");
  init();
  addMenu();
  front_page();
  glutKeyboardFunc(key1);
  glutDisplayFunc(display1);
  glClearColor(1,1,1,1);
  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,800,0,600);
	glMatrixMode(GL_MODELVIEW);
  glutMainLoop();
 

 
 
 
  

  
  return 0;
}
