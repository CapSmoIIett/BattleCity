#pragma once

#include "ObjectScene.h"
#include "Object.h"
#include "Controller.h"
#include <random>

/*
controller - управляет танком, контроллирует его движение (по умолчанию ездит рандомно и стреляет в игрока когда его видит)
scene - регулирует поведения всех танков, согласовывает их действия, дпет им приказы. Спавнит их
*/
struct AIPoint
{
    //
    AIPoint *p_up;
    AIPoint *p_down;
    AIPoint *p_left;
    AIPoint *p_right;

    AIPoint()
    {
        p_up = nullptr;
        p_down = nullptr;
        p_left = nullptr;
        p_right = nullptr;
    };
};

class AIController
{

private:
    int tank_id;
    int direct;
    int start_x, start_y;
    bool ride;

public:
    AIController(int id, int x, int y) : tank_id(id),
                                         direct(UP),
                                         start_x(0),
                                         start_y(0)
    {
        ride = 1;
    };
    ~AIController(){};

    void setStartXY(int x, int y)
    {
        start_x = x;
        start_y = y;
    }

    void setUp()
    {
        direct = UP;
        ride = 1;
    };
    void setDown()
    {
        direct = DOWN;
        ride = 1;
    };
    void setLeft()
    {
        direct = LEFT;
        ride = 1;
    };
    void setRight()
    {
        direct = RIGHT;
        ride = 1;
    };

    void stop(int direction)
    {
        if (direct == direction) // Что бы при изменнении направления танк не останавливался
            ride = 0;
    }

    void shoot(ObjectScene *scene)
    {
        scene->createBullet(tank_id);
    };

    // функция, следящая за танком
    virtual void manageTank(ObjectScene *scene)
    {
        if (scene->map_objects.find(tank_id) != scene->map_objects.end())
        {
            Tank *abstr_tank = dynamic_cast<Tank *>(scene->map_objects[tank_id]);

            if (ride)
            {
                abstr_tank->set_dir(direct); // теперь устанавливаем направление, такое, как нашей переменной.
                scene->map_objects[tank_id]->set_speed(3);
            }
            if (abstr_tank->did_collided())
            {

                direct = rand() % 4;
                abstr_tank->set_dir(direct);
            }
            //else { scene->map_objects[tank_id]->set_speed(0); }//оста
        }
    }
};

class AIScene
{
private:
    std::unordered_map<int, AIController *> map_ai_tanks;
    std::vector<int> tanks;
    //std::unordered_map<int, Controller*> map_ai_control;
    //std::unordered_map<Point, AIPoint*> map_points;
    std::vector<Point> spawners;
    int player_tank;
    sf::Clock clock;
    sf::Time last_spawn;
    int time_to_spawn;
    int maxTanks;

public:
    AIScene(ObjectScene *scene, int max) : maxTanks(max)
    {
        for (auto i : scene->map_objects)
        { // Получаем точки спавнеров
            if (i.second->data.type == "Spawner")
                spawners.push_back(i.second->get_point());
        }
        last_spawn = clock.getElapsedTime();
        time_to_spawn = rand() % 5 + 3;
    };

    // ОБновлять состояние сцены (синхронизировать ее с ObjectScene)
    void synchronize(ObjectScene *scene)
    {
        for (auto i : scene->map_objects){
            if (i.second->data.type == "PlayerTank")
                player_tank = i.first;
        }

        for (int i = 0; i < tanks.size(); i++)
        { // Если танк был уничтожен -
            if (scene->map_objects.find(tanks[i]) ==
                scene->map_objects.end())
            {
                map_ai_tanks.erase(tanks[i]);
                this->tanks.erase(tanks.begin() + i); // удаляем его из нашего списка
            }
        }

        if (clock.getElapsedTime() - last_spawn >= sf::seconds(time_to_spawn) &&
            tanks.size() < maxTanks)
        {
            int spawn = rand() % (spawners.size()); // Выбираем случайный спавнер
            Point point = spawners[spawn];

            std::cout << "\n\n\n"
                      << spawn << " " << point.x << " " << point.y << "\n";
            std::cout << "Spawn tank" << tanks.size() + 1 << "\n";

            int id = scene->addObject(point.x, point.y, "Tank");
            tanks.push_back(id);
            map_ai_tanks[id] = new AIController(id, point.x, point.y);

            // Устанавливаем новые значения для спавнов
            last_spawn = clock.getElapsedTime();
            time_to_spawn = rand() % 5 + 3;
        }
    }

    //
    void setComands(ObjectScene *scene)
    {
        if (scene->map_objects.find(player_tank) != scene->map_objects.end())
        {
            Point player_point = scene->map_objects[player_tank]->get_point();
            for (int i : tanks)
            {
                Object *object = scene->map_objects[i];
                Tank *tank = dynamic_cast<Tank *>(object);
                Point point = tank->get_point();
                if (player_point.x - point.x < 20 &&
                    player_point.x - point.x > -20)
                {
                    if (player_point.y > point.y)
                    { // если игрок ниже
                        map_ai_tanks[object->id]->setDown();
                        map_ai_tanks[object->id]->shoot(scene);
                    }
                    else
                    {
                        map_ai_tanks[object->id]->setUp();
                        map_ai_tanks[object->id]->shoot(scene);
                    }
                }
                if (player_point.y - point.y < 20 &&
                    player_point.y - point.y > -20)
                {
                    if (player_point.x > point.x)
                    { // если игрок правее
                        map_ai_tanks[object->id]->setRight();
                        map_ai_tanks[object->id]->shoot(scene);
                    }
                    else
                    {
                        map_ai_tanks[object->id]->setLeft();
                        map_ai_tanks[object->id]->shoot(scene);
                    }
                }
            }
        }
    }

    //
    void manageAllAITanks(ObjectScene *scene)
    {
        for (auto i : map_ai_tanks)
        {
            i.second->manageTank(scene);
        }
    }
};

class AITank : Tank
{
private:
};