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
        //
        Controller();
        //
         ~Controller();
        //
        void setStartXY(int x, int y);
      
        //
        void setUp();
        //
        void setDown();
        //
        void setLeft();
        //
        void setRight();

        //
        void stop(int direction);
        //
        void shoot(ObjectScene *scene);

        // функция, следящая за танком
        virtual void manageTank(ObjectScene *scene, RenderWindow & window);
};