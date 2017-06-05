#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

int offset = 0;

void render(sf::RenderWindow &window){
    window.clear();
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    glColor3ub(0,0,255);
    glBegin(GL_POLYGON);
    glVertex2f(offset,      50);
    glVertex2f(offset+100, 250);
    glVertex2f(offset,     450);
    glEnd();
}

bool processData(sf::RenderWindow &window){
    offset += 2;
    if(offset>500)
        offset=-100;
    sf::Event ev;
    while(window.pollEvent(ev));
    return true;
}

int main(){
    sf::RenderWindow window;
    window.create(sf::VideoMode(500,500),"Title");
    glOrtho(0,500,500,0,0,1);
    bool running=true;
    clock_t last = 0;
    
    while(running){
        render(window);
        
        window.display();
        while(clock()-last<25)
            this_thread::sleep_for(chrono::milliseconds(1));
        last = clock();
    }
}