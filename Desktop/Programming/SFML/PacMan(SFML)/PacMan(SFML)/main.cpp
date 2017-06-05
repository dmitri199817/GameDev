#include <SFML/Graphics.hpp>
using namespace sf;

const int H = 25;
const int W = 37;

String TileMap[H] = {
"0000000000000000000000000000000000000",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0                                   0",
"0000000000000000000000000000000000000",
};

int main()
{
    RenderWindow window(VideoMode(700, 500), "SFML WINDOW");
    Clock clock;

    Texture herotexture;
    herotexture.loadFromFile("/Users/dns/Desktop/programming/SFML/PacMan(SFML)/PacMan(SFML)/images/hero.png");

    Sprite hero;
    hero.setTexture(herotexture);
    hero.setTextureRect(IntRect(27,16,16,16));

//    Image map_image;
//    map_image.loadFromFile("images/2_map.png");

//    Texture map_texture;
//    map_texture.loadFromImage(map_image);

//    Sprite s_map;
//    s_map.setTexture(map_texture);

    RectangleShape rect(Vector2f(16,16));
    rect.setFillColor(Color::White);

    int dir;
    float dx=0,dy=0,speed=0;
    float x=30,y=30;
    float CurrentFrame = 0;
    float w,h;
    w = W; h = H;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        x += dx*time;
        y += dy*time;

        hero.setPosition(x,y);

        CurrentFrame += 0.005*time;
        if (CurrentFrame > 2) CurrentFrame -=2;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        { dir = 0; speed = 0.1; }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        { dir = 1; speed = 0.1; }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        { dir = 2; speed = 0.1; }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        { dir = 3; speed = 0.1; }

        switch(dir)
        {
        case 0:
            dx = -speed; dy = 0;
            hero.setTextureRect(IntRect(16*int(CurrentFrame),0,16,16));
            break;
        case 1:
            dx = speed; dy = 0;
            hero.setTextureRect(IntRect(16*int(CurrentFrame)+16,0,-16,16));
            break;
        case 2:
            dx = 0; dy = -speed;
            hero.setTextureRect(IntRect(16*int(CurrentFrame),16,16,16));
            break;
        case 3:
            dx = 0; dy = speed;
            hero.setTextureRect(IntRect(16*int(CurrentFrame),16+16,16,-16));
            break;
        }

        window.clear(Color::Black);

        for (int i=0; i<H; i++)
            for (int j=0; j<W; j++)
            {
                if (TileMap[i][j] == ' ') continue;//s_map.setTextureRect(IntRect(0,0,16,16));

                if (TileMap[i][j] == '0')  rect;

                //s_map.setPosition(j*16,i*16);
                rect.setPosition(j*16,i*16);
                //window.draw(s_map);
                window.draw(rect);
            };

        for (int i=y/16; i<(y+h)/16; i++)
            for (int j=x/16; j<(x+w)/16; j++)
            {
                if (TileMap[i][j] == '0')
                {
                 if (dy>0) y=i*16+h;
                 if (dy<0) y=i*16+16;//
                 if (dx>0) x=j*16-w;
                 if (dx<0) x=j*16+16;
                }

                if (TileMap[i][j] == ' ') continue;
            };

        window.draw(hero);
        
        window.display();
    }

    return 0;
}
