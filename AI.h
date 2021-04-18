#pragma once

#include "ObjectScene.h"
#include "Object.h"
#include "Controller.h"
#include <random>

/*
controller - управляет танком, контроллирует его движение (по умолчанию ездит рандомно и стреляет в игрока когда его видит)
scene - регулирует поведения всех танков, согласовывает их действия, дпет им приказы. Спавнит их
*/

struct Command {
    int direction;
    int is_shoot;
 
    Command(int dir, int shoot = 0) : direction(dir), is_shoot(shoot) { };
};

class AIController
{

private:
    int tank_id;
    int direction;
    int start_x, start_y;
    Command* command;

public:
    AIController(int id, int x, int y);

    ~AIController();

    void setStartXY(int x, int y);

    void setUp();
    void setDown();
    void setLeft();
    void setRight();
    
    void setCommand(Command com){
        command = new Command(com);
    };

    void shoot(ObjectScene*);

    // функция, следящая за танком
    virtual void manageTank(ObjectScene *scene);
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
    AIScene(ObjectScene *scene, int max);

    // ОБновлять состояние сцены (синхронизировать ее с ObjectScene)
    void synchronize(ObjectScene *scene);

    //
    void setCommands(ObjectScene *scene);

    //
    void manageAllAITanks(ObjectScene *scene);
};
