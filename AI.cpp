#include "AI.h"


AIController::AIController(int id, int x, int y) : tank_id(id),
direction(UP),
start_x(0),
start_y(0) {
    command = nullptr;
}

AIController::~AIController() {

};

void AIController::setStartXY(int x, int y) {
    start_x = x;
    start_y = y;
}

void AIController::setUp() {
    direction = UP;
}
void AIController::setDown() {
    direction = DOWN;
}
void AIController::setLeft() {
    direction = LEFT;

}
void AIController::setRight() {
    direction = RIGHT;
}

void AIController::shoot(ObjectScene *scene) {
        scene->createBullet(tank_id);
}

void AIController::manageTank(ObjectScene *scene) {

    static int is_shoot = 0;            // Для стрельбы в нужном направлении нам необходимо в первом кадре повернуть танк, а во втором выстрелить. Тут мы запоинаем - нужно нам стрелять в следующем кадре или нет         
    if (scene->map_objects.find(tank_id) != scene->map_objects.end()) {

        Tank *tank = dynamic_cast<Tank *>(scene->map_objects[tank_id]);
        
        if (is_shoot) {
            shoot(scene);               // если необходимо выстрелить - стреляем
            is_shoot = 0;
        }

        if (command != nullptr) {                               // если есть команда на выполнение
            tank->set_dir(command->direction);                  // Устанавоиваем направление
            Rect <int>future_rectangle = tank->get_future_rectangle(scene);
            bool is_intersect = tank->now_rectangle(scene).intersects(future_rectangle) && tank_id != tank->id;

            // Если из-зи этого будет столкновение возвращаем все параметры - команда не выполнена
            if (is_intersect) {         
                tank->set_dir(direction);
            }
            // Если поворот пройдет успешно
            else {
                direction = command->direction;                 // мы полностью изменяем направление
                if (command->is_shoot)  is_shoot = 1;
                command = nullptr;                              // и убираем команду, т.к. она выполнена 
            };
        }

        scene->map_objects[tank_id]->set_speed(3);

        if (tank->did_collided()) {
            command = nullptr;              // Столкновение обнуляет команду
            is_shoot = 0;
            direction = rand() % 4;
            tank->set_dir(direction);
        }
    }   
}




AIScene::AIScene(ObjectScene *scene, int max) : maxTanks(max) {
    for (auto i : scene->map_objects) { // Получаем точки спавнеров
        if (i.second->data.type == "Spawner")
            spawners.push_back(i.second->get_point());
    }
    last_spawn = clock.getElapsedTime();
    time_to_spawn = rand() % 5 + 3;
}

    // ОБновлять состояние сцены (синхронизировать ее с ObjectScene)
void AIScene::synchronize(ObjectScene *scene) {
    for (auto i : scene->map_objects){                  // ОБновляем список игроков
        if (i.second->data.type == "PlayerTank")
            player_tank.push_back(i.first);
    }

    for (auto i : map_ai_tanks) {                       // Если танк был уничтожен -
        if (scene->map_objects.find(i.first) == scene->map_objects.end()) {
            map_ai_tanks.erase(i.first);                // удаляем его из нашего списка
        }
    }

    if (clock.getElapsedTime() - last_spawn >= sf::seconds(time_to_spawn) &&
            map_ai_tanks.size() < maxTanks) {
        int spawn = rand() % (spawners.size()); // Выбираем случайный спавнер
        Point point = spawners[spawn];

        std::cout << "\n\n\n"
                  << spawn << " " << point.x << " " << point.y << "\n";
        std::cout << "Spawn tank" << map_ai_tanks.size() + 1 << "\n";

        int id = scene->addObject(point.x, point.y, "Tank");
        map_ai_tanks[id] = new AIController(id, point.x, point.y);

        // Устанавливаем новые значения для спавнов
        last_spawn = clock.getElapsedTime();
        time_to_spawn = rand() % 5 + 3;
    }
}

void AIScene::setCommands(ObjectScene *scene) {
    std::vector<Point> player_points;
    for (int player : player_tank){
        if (scene->map_objects.find(player) != scene->map_objects.end()) 
            player_points.push_back(scene->map_objects[player]->get_point());
    }

    for (auto i : map_ai_tanks) {                   // Проверяем каждый ИИ
        Object *object = scene->map_objects[i.first];
        Tank *tank = dynamic_cast<Tank *>(object);
        Point point = tank->get_point();
        for (auto player_point : player_points) {
            if (player_point.x - point.x < 5 &&         
                player_point.x - point.x > -5) {        // Если игрок и ИИ на одной вертикали 
                if (player_point.y > point.y) {         // если игрок ниже
                    if (checkVisibility(scene, point, DOWN))
                        map_ai_tanks[object->id]->setCommand(Command(DOWN, 1));
                        break;
                }
                else {
                    if (checkVisibility(scene, point, UP))
                        map_ai_tanks[object->id]->setCommand(Command(UP, 1));
                        break;
                }
            }
            if (player_point.y - point.y < 5 &&
                player_point.y - point.y > -5) {        // Если игрок и ИИ на одной горизонтали
                if (player_point.x > point.x) {         // если игрок правее
                    if (checkVisibility(scene, point, RIGHT))
                        map_ai_tanks[object->id]->setCommand(Command(RIGHT, 1));
                        break;
                }
                else
                {
                    if (checkVisibility(scene, point, LEFT))
                        map_ai_tanks[object->id]->setCommand(Command(LEFT, 1));
                        break;
                }
            }
        }
    }
    /*for (int player : player_tank) {                        // Для каждого игрока
        if (scene->map_objects.find(player) != scene->map_objects.end()) {
            Point player_point = scene->map_objects[player]->get_point();
            for (auto i : map_ai_tanks) {                   // Проверяем каждый ИИ
                Object *object = scene->map_objects[i.first];
                Tank *tank = dynamic_cast<Tank *>(object);
                Point point = tank->get_point();
                if (player_point.x - point.x < 5 &&         
                    player_point.x - point.x > -5) {        // Если игрок и ИИ на одной вертикали 
                    if (player_point.y > point.y) {         // если игрок ниже
                        if (checkVisibility(scene, point, DOWN))
                            map_ai_tanks[object->id]->setCommand(Command(DOWN, 1));
                    }
                    else {
                        if (checkVisibility(scene, point, UP))
                            map_ai_tanks[object->id]->setCommand(Command(UP, 1));
                    }
                }
                if (player_point.y - point.y < 5 &&
                    player_point.y - point.y > -5) {        // Если игрок и ИИ на одной горизонтали
                    if (player_point.x > point.x) {         // если игрок правее
                        if (checkVisibility(scene, point, RIGHT))
                            map_ai_tanks[object->id]->setCommand(Command(RIGHT, 1));
                    }
                    else
                    {
                        if (checkVisibility(scene, point, LEFT))
                            map_ai_tanks[object->id]->setCommand(Command(LEFT, 1));
                    }
                }
            }
        }
    }*/
}

void AIScene::manageAllAITanks(ObjectScene *scene) {
    for (auto i : map_ai_tanks) {
        i.second->manageTank(scene);
    }
}

bool AIScene::checkVisibility (ObjectScene *scene, Point point, int dir) {
    // Данный вариант не работает и слишком замедляет игру
    sf::String name_closer;
    //Point point_closer = {-1, -1};
    int difference = 625; 

    // Ищем ближайший объект к танку(ИИ)
    // если это игорок - то возвращаем true
    switch (dir)            // Квадрат видимости должен быть идентичен траектории пули
    {
        case UP: {
            for (auto i : scene->map_objects){
                Point p = i.second->get_point();
                if (i.second->data.type == "Tank") continue;
                if (p.x - point.x < 13 &&         
                    p.x - point.x > -13)
                    if (difference > point.y - p.y){        // Если растояние (разница в точках) меньше 
                        name_closer = i.second->data.type;  
                        difference = point.y - p.y;         
                    }
            }
            break;
        }
        case DOWN:  {
            for (auto i : scene->map_objects){
                Point p = i.second->get_point();
                if (i.second->data.type == "Tank") continue;
                if (p.x - point.x < 13 &&         
                    p.x - point.x > -13)
                    if (difference > p.y - point.y){        // Если растояние (разница в точках) меньше 
                        name_closer = i.second->data.type;  
                        difference = p.y - point.y;         
                    }
            }
            break;
        }
        case LEFT:  {
            for (auto i : scene->map_objects){
                Point p = i.second->get_point();
                if (i.second->data.type == "Tank") continue;
                if (p.y - point.y < 13 &&
                    p.y - point.y > -13)
                    if (difference > point.y - p.y){        // Если растояние (разница в точках) меньше 
                        name_closer = i.second->data.type;  
                        difference = point.y - p.y;         
                    }
            }
            break;
        }
        case RIGHT: {
            for (auto i : scene->map_objects){
                Point p = i.second->get_point();
                if (i.second->data.type == "Tank") continue;
                if (p.y - point.y < 13 &&
                    p.y - point.y > -13)
                    if (difference > p.y - point.y){        // Если растояние (разница в точках) меньше 
                        name_closer = i.second->data.type;  
                        difference = p.y - point.y;         
                    }
            }
            break;
        }
    }

    return name_closer == "PlayerTank";
}