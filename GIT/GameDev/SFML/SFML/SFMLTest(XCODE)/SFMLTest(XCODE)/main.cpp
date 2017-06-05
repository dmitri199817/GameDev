//
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GLUT/glut.h>
#include <math.h>

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

using namespace sf;

void Walls()
{
    //«ÂÏÎˇ
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    
    //—ÚÂÌ˚
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

void GLUTDraw()
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
    
    glutSwapBuffers();
}

int main()
{
    // создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default);
    
    // загружаем ресурсы, инициализируем состояния OpenGL
    RectangleShape rect;
    rect.setSize(Vector2f(100,100));
    rect.setPosition(400, 300);
    
    
    // запускаем главный цикл
    bool running = true;
    while (running)
    {
        // обрабатываем события
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // пора закрывать приложение
                running = false;
            }
            if (event.type == sf::Event::Resized)
            {
                // применяем область просмотра, когда изменены размеры окна
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        
        
        window.pushGLStates();
        
        window.draw(rect);
        
        window.popGLStates();
        
        // конец текущего кадра (меняем местами передний и задний буферы)
        window.display();
    }
    
    // освобождаем ресурсы
    
    return 0;
}