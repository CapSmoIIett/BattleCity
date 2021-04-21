#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "Object.h"
#include "ObjectScene.h"
#include "DrawScene.h"
#include "Controller.h"
#include "AI.h"

#define win
#ifndef win
    #include <unistd.h>
    #include <thread>
#endif

using namespace std;

int main() {

    ObjectScene scene;
    fstream file("levels/1.txt");
    scene.loadMap(file);
    file.close();
    
    AIScene ai_scene(&scene, 10);

    Time cycle_time = seconds(0.02);//0.02f);
    RenderWindow window(VideoMode(624, 624), "BattleCity");
    DrawScene draw_scene;


    Controller controller;
    Controller controller2;
    controller.setStartXY(16 * 3 * 8, 24 * 3 * 8);
    controller2.setStartXY(16 * 3 * 4, 24 * 3 * 8);
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
                case sf::Keyboard::W: {
                    controller2.setUp();
                    break;
                }
                case sf::Keyboard::A: {
                    controller2.setLeft();
                    break;
                }
                case sf::Keyboard::S: {
                    controller2.setDown();
                    break;
                }
                case sf::Keyboard::D: {
                    controller2.setRight();
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
                case sf::Keyboard::W: {
                    controller2.stop(UP);
                    break;
                }
                case sf::Keyboard::A: {
                    controller2.stop(RIGHT);
                    break;
                }
                case sf::Keyboard::S: {
                    controller2.stop(DOWN);
                    break;
                }
                case sf::Keyboard::D: {
                    controller2.stop(RIGHT);
                    break;
                }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)){ controller.shoot(&scene);    }
            
            if (Keyboard::isKeyPressed(Keyboard::Tab))  { controller2.shoot(&scene);    }

            if (Keyboard::isKeyPressed(Keyboard::Q))    { window.close();       };
            if (event.type == Event::Closed)
                window.close();
            //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
               //scene.map_objects[5]->set
        }
        
        //ai_scene.setComands(&scene);
        // ManageTank только устанавливает направление и скорость
        #ifndef win
            std::thread thManageTank (&Controller::manageTank, controller, &scene); 
            controller2.manageTank(&scene); 
            //std::thread thManageTank2(&Controller::manageTank, controller2, &scene);  
        #else
            controller.manageTank(&scene);/* */
            //controller2.manageTank(&scene);
        #endif

        #ifndef win
            thManageTank.join();
            //thManageTank2.join();
        #endif
        
        ai_scene.synchronize(&scene);
        ai_scene.setCommands(&scene);
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
