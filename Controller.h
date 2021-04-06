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
        int since_last_click;//счётчик "когда последнее обновление", если > 10 то скорость устанавливается в 0.       
        int start_x, start_y;

    public:
        Controller():tank_id(-1), 
                        health(10),
                        direct(UP),
                        since_last_click(30),
                        start_x(0),
                        start_y(0){ 

        };
         ~Controller(){};

        void setStartXY(int x, int y){
            start_x = x;
            start_y = y;
        }
      
        void setUp(){
            direct = UP;
            since_last_click = 0;
        };
        void setDown(){
            direct = DOWN;
            since_last_click = 0;
        };
        void setLeft(){
            direct = LEFT;
            since_last_click = 0;
        };
        void setRight(){
            direct = RIGHT;
            since_last_click = 0;
        };

       void shoot(ObjectScene *scene){
            scene->createAbctractBullet(tank_id);
        };

        // функция, следящая за танком
        void manageTank(ObjectScene *scene)
        {
            if (scene->map_objects.find(tank_id) != scene->map_objects.end()){
                    Tank *abstr_tank = dynamic_cast<Tank *>(scene->map_objects[tank_id]);
                    
                    if (since_last_click < 30) {// если в течении последних 10 кадров небыло нажатий, то танк останавливается.
                        abstr_tank->set_dir(direct);// теперь устанавливаем направление, такое, как нашей переменной.
                        scene->map_objects[tank_id]->set_speed(3);
                    } 
                    else { scene->map_objects[tank_id]->set_speed(0); }//останавливаем танк
            } 

            else { //танк был убит!
                health--;
                
                std::cout << "Танк игрока был возрождён, осталось жизней: " << health << "\n";
                this->tank_id = scene->addObject(start_x, start_y, "Tank");
                since_last_click = 30; //пусть стоит на старте
            }
            since_last_click ++;
        }  
        
};