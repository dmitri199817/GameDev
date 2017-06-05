#include <iostream>
#include <math.h>
#include <GLUT/GLUT.h>

#define Game 1
#define Exit 3

////////////////////
float angle=0.0;
float lx=0.0f, lz=-1.0f;
float x=0.0f, z=5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
int h,w; 
float P = 1;
float p = 0.5;
////////////////////
int farValue = 1000/2;
 
void changeSize(int w, int h)
{
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(45.0f, ratio, 0.1f, farValue);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}
 
void computePos(float deltaMove) 
{
	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}
 
void computeDir(float deltaAngle)
{
	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

void setOrthographicProjection()
{
	//переключения режима проецирования
	glMatrixMode(GL_PROJECTION);
	//Сохраняем предыдущую матрицу, которая содержит
        //параметры перспективной проекции
	glPushMatrix();
	//обнуляем матрицу
	glLoadIdentity();
	//устанавливаем 2D ортогональную проекцию
	gluOrtho2D(0, w, h, 0);
	// возврата в режим обзора модели
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() 
{
	glMatrixMode(GL_PROJECTION);
	//восстановить предыдущую матрицу проекции
	glPopMatrix();
	//вернуться в режим модели
	glMatrixMode(GL_MODELVIEW);
}

void Walls()
{
	//Земля
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	//Стены
	glBegin(GL_QUADS);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0, 100.0f);
	glVertex3f(-100.0f, 25.0f, 100.0f);
	glVertex3f(-100.0f, 25.0f, -100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.7,0.7,0.7);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glVertex3f(100.0f, 0.0, 100.0f);
	glVertex3f(100.0f, 25.0f, 100.0f);
	glVertex3f(100.0f, 25.0f, -100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.6,0.6,0.6);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glVertex3f(100.0f, 25.0f, -100.0f);
	glVertex3f(-100.0f, 25.0f, -100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0.5);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 25.0f, 100.0f);
	glVertex3f(-100.0f, 25.0f, 100.0f);
	glEnd();
}

void Objects()
{
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glColor3f(0,0.5,0);
    glutSolidCube(1);
    glPopMatrix();
}

void DrawMenu()
{
    glColor3f(0.7,0.7,0.7);
	glBegin(GL_QUADS);
	glVertex2f(-P,-P);
	glVertex2f(-P,P);
	glVertex2f(P,P);
	glVertex2f(P,-P);
	glEnd();
}

void renderScene() 
{
	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	   x,	1.0f,	  z,
				x+lx,	1.0f,  z+lz,
				0.0f,   1.0f,  0.0f		);

	Walls();
    Objects();
    
	setOrthographicProjection(); 
	glPushMatrix();
	glLoadIdentity();

	//DrawMenu();
    
	glPopMatrix();
	restorePerspectiveProjection(); 

	glutSwapBuffers();
}

void pressKey(int key, int xx, int yy)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
			deltaAngle = -0.025f;
			break;
		case GLUT_KEY_RIGHT:
			deltaAngle = 0.025f;
			break;
		case GLUT_KEY_UP:
			deltaMove = 5;
			break;
		case GLUT_KEY_DOWN:
			deltaMove = -5;
			break;
	}
}
 
void releaseKey(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT: 
			deltaAngle = 0.0f;
			break;
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN: 
			deltaMove = 0;
			break;
	}
}

void MouseMenu(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		if (button == GLUT_LEFT_BUTTON)
			{
				if (x<=350 && x>=50)
					if (y<=350 && y>=50)
					std::cout<<"x= " << x << " y= " << y << std::endl;
			}
}

void NormalKeys(unsigned char key, int x, int y) 
{ if (key == 27) exit(0); }

void MenuCheck(int value) 
{
	if (value == 1) std::cout << "Game" << std::endl; P = 0; glutPostRedisplay();

	if (value == 3) exit(0);
}

void OptionsMenu(int value) {}

void FullScreen(int value)
{
	if (value == 1) glutFullScreen();

	if (value == 0) 
		{
			glutReshapeWindow(640,480);
			glutPositionWindow(100,100);
		}
}

void MenuFarValue(int value)
{
	switch (value)
	{
	case 1: farValue = 1000;  break;

	case 2: farValue = 500;  break;

	case 3: farValue = 100;  break;
	}
}

void MenuInit()
{
	int M = glutCreateMenu(MenuCheck);
	int Options = glutCreateMenu(OptionsMenu);
	int FarValueMenu = glutCreateMenu(MenuFarValue); 
	int FS = glutCreateMenu(FullScreen);

		glutSetMenu(Options);
		glutAddSubMenu("FarValue",FarValueMenu);
		glutAddSubMenu("FullScreen",FS);

			glutSetMenu(FarValueMenu);
			glutAddMenuEntry("1000",1);
			glutAddMenuEntry("500",2);
			glutAddMenuEntry("100",3);

			glutSetMenu(FS);
			glutAddMenuEntry("fullscreen",1);
			glutAddMenuEntry("not fullscreen",0);

	glutSetMenu(M);
	glutAddMenuEntry("Game",1);
	glutAddSubMenu("Options",Options);
	glutAddMenuEntry("Exit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Registration()
{
	// регистрация вызовов
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutSpecialFunc(pressKey);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
	glutMouseFunc(MouseMenu);
    glutKeyboardFunc(NormalKeys);
    MenuInit();
}

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("GLUT WINDOW");
	Registration();

	glEnable(GL_DEPTH_TEST);
 
	glutMainLoop();
 
	return 1;
}