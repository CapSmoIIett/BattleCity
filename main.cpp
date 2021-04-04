#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "AbstractScene.h"
#include "Object.h"
#include "DrawScene.h"
#include "Controller.h"


using namespace std;

int main() {

    AbstractScene abstract_scene;
    fstream file("levels/1.txt");
    abstract_scene.loadMap(file);
    file.close();
    
    Time cycle_time = seconds(0.02);//0.02f);
    RenderWindow window(VideoMode(624, 624), "BattleCity");
    DrawScene draw_scene;


    Controller controller;
    controller.setStartXY(16 * 3 * 8, 24 * 3 * 8);
    draw_scene.synchronize(&abstract_scene);/**/

    Clock clock;
    Event event;
    while (window.isOpen()) 
    {
        while (window.pollEvent(event)) 
        {
            /**/
            if (Keyboard::isKeyPressed(Keyboard::Down)) { controller.setDown(); };
            if (Keyboard::isKeyPressed(Keyboard::Right)){ controller.setRight();};
            if (Keyboard::isKeyPressed(Keyboard::Up))   { controller.setUp();   };
            if (Keyboard::isKeyPressed(Keyboard::Left)) { controller.setLeft(); };

            if (event.type == Event::Closed)
                window.close();
            //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
               //abstract_scene.map_objects[5]->set
        }
        
        controller.manageTank(&abstract_scene);/* */
       
        draw_scene.synchronize(&abstract_scene); 
        window.clear();     // window.clear(sf::Color(34,15,6));
        draw_scene.draw(window, &abstract_scene);
    
        window.display();
        //Time elapsed_time = clock.getElapsedTime() % cycle_time;
        //std::cout << "отрисовано за " << elapsed_time.asMilliseconds() << " миллисекунд\n";
        //sleep(cycle_time - elapsed_time);
    }

    return 0;
} 
