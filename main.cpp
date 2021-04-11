#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "Object.h"
#include "ObjectScene.h"
#include "DrawScene.h"
#include "Controller.h"
#include "AI.h"

using namespace std;

int main() {

    ObjectScene scene;
    fstream file("levels/p.txt");
    scene.loadMap(file);
    file.close();
    
    AIScene ai_scene(&scene, 1);

    Time cycle_time = seconds(0.02);//0.02f);
    RenderWindow window(VideoMode(624, 624), "BattleCity");
    DrawScene draw_scene;


    Controller controller;
    controller.setStartXY(16 * 3 * 8, 24 * 3 * 8);
    draw_scene.synchronize(&scene);/**/

    Clock clock;
    Event event;
    while (window.isOpen()) 
    {
        while (window.pollEvent(event)) 
        {
            /**/
            if (event.type == sf::Event::KeyPressed){
                switch (event.key.code)
                {
                case sf::Keyboard::Up: {
                    controller.setUp();
                    break;
                }
                case sf::Keyboard::Down: {
                    controller.setDown();
                    break;
                }
                case sf::Keyboard::Left: {
                    controller.setLeft();
                    break;
                }
                case sf::Keyboard::Right: {
                    controller.setRight();
                    break;
                }
                }
            }


            else if (event.type == sf::Event::KeyReleased){
                switch (event.key.code)
                {
                case sf::Keyboard::Up:  {
                    controller.stop(UP);
                    break;
                }
                case sf::Keyboard::Down: {
                    controller.stop(DOWN);
                    break;
                }
                case sf::Keyboard::Left: {
                    controller.stop(LEFT);
                    break;
                }
                case sf::Keyboard::Right: {
                    controller.stop(RIGHT);
                    break;
                }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)){ controller.shoot(&scene);    }
            
            if (Keyboard::isKeyPressed(Keyboard::Q))    { window.close();       };
            if (event.type == Event::Closed)
                window.close();
            //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
               //scene.map_objects[5]->set
        }
        
        controller.manageTank(&scene);/* */
        ai_scene.setComands(&scene);
        ai_scene.synchronize(&scene);
        ai_scene.manageAllAITanks(&scene);
        scene.handleTickAll();
        scene.clearDead();
        draw_scene.synchronize(&scene); 
        window.clear();     // window.clear(sf::Color(34,15,6));
        draw_scene.draw(window, &scene);
    
        window.display();
        Time elapsed_time = clock.getElapsedTime() % cycle_time;
        //std::cout << "отрисовано за " << elapsed_time.asMilliseconds() << " миллисекунд\n";
        sleep(cycle_time - elapsed_time);
    }

    return 0;
} 
