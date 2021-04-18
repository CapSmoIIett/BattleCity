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
            shoot(scene);             // если необходимо выстрелить - стреляем
            is_shoot = 0;
        }

        if (command != nullptr) {                                               // если есть команда на выполнение
            tank->set_dir(command->direction);                                  // Устанавоиваем направление
            Rect <int>future_rectangle = tank->get_future_rectangle(scene);
            bool is_intersect = tank->now_rectangle(scene).intersects(future_rectangle) && tank_id != tank->id;
            if (is_intersect) {                                                 // Если из-зи этого будет столкновение возвращаем все параметры - команда не выполнена
                tank->set_dir(direction);
            }
            else {
                direction = command->direction;                     // мы полностью изменяем направление
                if (command->is_shoot)  is_shoot = 1;
                command = nullptr;                              // убираем команду - она выполнена 
            };
        }

        scene->map_objects[tank_id]->set_speed(3);

        if (tank->did_collided()) {
            command = nullptr;              // Столкновение обнуляет команду
            direction = rand() % 4;
            tank->set_dir(direction);
        }
    }        //else { scene->map_objects[tank_id]->set_speed(0); }//оста
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
    for (auto i : scene->map_objects){
        if (i.second->data.type == "PlayerTank")
            player_tank = i.first;
    }

    for (int i = 0; i < tanks.size(); i++) { // Если танк был уничтожен -
        if (scene->map_objects.find(tanks[i]) ==
            scene->map_objects.end()) {
            map_ai_tanks.erase(tanks[i]);
            this->tanks.erase(tanks.begin() + i); // удаляем его из нашего списка
        }
    }

    if (clock.getElapsedTime() - last_spawn >= sf::seconds(time_to_spawn) &&
            tanks.size() < maxTanks) {
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

void AIScene::setCommands(ObjectScene *scene) {
    if (scene->map_objects.find(player_tank) != scene->map_objects.end()) {
        Point player_point = scene->map_objects[player_tank]->get_point();
        for (int i : tanks) {
            Object *object = scene->map_objects[i];
            Tank *tank = dynamic_cast<Tank *>(object);
            Point point = tank->get_point();
            if (player_point.x - point.x < 5 &&
                player_point.x - point.x > -5) {
                if (player_point.y > point.y) { // если игрок ниже
                    map_ai_tanks[object->id]->setCommand(Command(DOWN, 1));
                }
                else {
                    map_ai_tanks[object->id]->setCommand(Command(UP, 1));
                }
            }
            if (player_point.y - point.y < 5 &&
                player_point.y - point.y > -5) {
                if (player_point.x > point.x) { // если игрок правее
                    map_ai_tanks[object->id]->setCommand(Command(RIGHT, 1));
                }
                else
                {
                    map_ai_tanks[object->id]->setCommand(Command(LEFT, 1));
                }
            }
        }
    }
}

void AIScene::manageAllAITanks(ObjectScene *scene) {
    for (auto i : map_ai_tanks) {
        i.second->manageTank(scene);
    }
}