#pragma once


#include "ObjectScene.h"
#include "Object.h"
#include "Controller.h"
#include <random>

/*
controller - управляет танком, контроллирует его движение (по умолчанию ездит рандомно и стреляет в игрока когда его видит)
scene - регулирует поведения всех танков, согласовывает их действия, дпет им приказы. Спавнит их
*/
struct AIPoint{
    //
    AIPoint* p_up;
    AIPoint* p_down;
    AIPoint* p_left;
    AIPoint* p_right;
    
    AIPoint(){
        p_up    = nullptr;
        p_down  = nullptr;
        p_left  = nullptr;
        p_right = nullptr;
    };
};

class AIController : Controller{
    
    public:
        virtual void manageTank();

};

class AIScene {
    private:
        std::unordered_map<int, AIController*> map_ai_tanks;
        std::vector<int>tanks;
        //std::unordered_map<int, Controller*> map_ai_control;
        //std::unordered_map<Point, AIPoint*> map_points;
        std::vector<Point> spawners;
        Tank* player_tank;
        sf::Clock clock;
        sf::Time last_spawn;
        int time_to_spawn;
        int maxTanks;

    public:
        AIScene(ObjectScene* scene, int max) :
        maxTanks(max){
            for (auto i : scene->map_objects){                      // Получаем точки спавнеров
                if (i.second->data.type == "Spawner")
                    spawners.push_back(i.second->get_point());
            }
            last_spawn = clock.getElapsedTime();
            time_to_spawn = rand() % 10 + 100; 
        };
        
        // ОБновлять состояние сцены (синхронизировать ее с ObjectScene)
        void synchronize(ObjectScene* scene){
            if (clock.getElapsedTime() - last_spawn <= sf::seconds(time_to_spawn) &&
                tanks.size() < maxTanks){
                int spawn = rand() % spawners.size() - 1;       // Выбираем случайный спавнер
                Point point = spawners[spawn];
                std::cout << "Spawn tank" << tanks.size() + 1 << "\n";
                tanks.push_back(scene->addObject(point.x, point.y, "Tank"));
                last_spawn = clock.getElapsedTime();
            }
        }

        //
        void setComands(ObjectScene* scene){
        }

        //
        void manageAllAITanks (){                              
            for (auto i : map_ai_tanks){
                i.second->manageTank();
            }
        }
    
};

class AITank : Tank{
    private:

};