#include <SFML/Graphics.hpp>
#include <GLUT/GLUT.h>

using namespace sf;

void GLUTDraw()
{
    glutI
    
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_QUADS);
    glVertex2i(-1, -1);
    glVertex2i(-1, 1);
    glVertex2i(1, 1);
    glVertex2i(1, -1);
    glEnd();
    
    glutSwapBuffers();
}

int main()
{
    RenderWindow window(VideoMode(200,200),"GLUT+SFML Window");
    
    /*рисуем sfml*/
    CircleShape shape(10);
    
    
    bool run = true;
        while(run)
        {
            Event event;
            while(window.pollEvent(event));
            {
                if(event.type == Event::Closed)
                {
                    run = false;
                }
                
                if(event.type == Event::Resized)
                {
                    glViewport(0, 0, event.size.width, event.size.height);
                }
            }
            
            GLUTDraw();
            window.pushGLStates();
            window.draw(shape/*рисуем sfml*/);
            window.popGLStates();
            window.display();
        }
    return 1;
}