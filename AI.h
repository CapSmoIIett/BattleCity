#pragma once


#include "ObjectScene.h"
#include "Object.h"
#include <random>

class AIController {
    private:
        std::unordered_map<int, Tank*> map_ai_tanks;
        Tank* player_tank;
        
    
};

class AITank : Tank{
    private:

};