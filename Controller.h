#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "ObjectScene.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

using namespace sf;

class Controller {
    private:
        
        int tank_id;   
        int health;        // здоровье игрока - количество попыток
        int direct;
        int start_x, start_y;
        bool ride;          
    public:
        Controller():tank_id(-1), 
                        health(10),
                        direct(UP),
                        start_x(0),
                        start_y(0){ 
            ride = 0;
        };
         ~Controller(){};

        void setStartXY(int x, int y){
            start_x = x;
            start_y = y;
        }
      
        void setUp(){
            direct = UP;
            ride = 1;
        };
        void setDown(){
            direct = DOWN;
            ride = 1;
        };
        void setLeft(){
            direct = LEFT;
            ride = 1;
        };
        void setRight(){
            direct = RIGHT;
            ride = 1;
        };

        void stop(){
            ride = 0;
        }

       void shoot(ObjectScene *scene){
            scene->createBullet(tank_id);
        };

        // функция, следящая за танком
        virtual void manageTank(ObjectScene *scene)
        {
            if (scene->map_objects.find(tank_id) != scene->map_objects.end()){
                    Tank *abstr_tank = dynamic_cast<Tank *>(scene->map_objects[tank_id]);
                    
                    if (ride) {
                        abstr_tank->set_dir(direct);// теперь устанавливаем направление, такое, как нашей переменной.
                        scene->map_objects[tank_id]->set_speed(3);
                    } 
                    else { scene->map_objects[tank_id]->set_speed(0); }//останавливаем танк
            } 

            else { //танк был убит!
                health--;
                
                std::cout << "Танк игрока был возрождён, осталось жизней: " << health << "\n";
                this->tank_id = scene->addObject(start_x, start_y, "Tank");
                ride = 0; //пусть стоит на старте
            }
        }  
        
};