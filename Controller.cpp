 #include "Controller.h"
 #include "GameOver.h"

Controller::Controller() : 
tank_id(-1), 
health(3),
direct(UP),
start_x(0),
start_y(0) { 
    ride = 0;
}

Controller::~Controller() {

}
void Controller::setStartXY(int x, int y) {
    start_x = x;
    start_y = y;
}
      
void Controller::setUp() {
    direct = UP;
    ride = 1;
}
void Controller::setDown() {
    direct = DOWN;
    ride = 1;
}
void Controller::setLeft() {
    direct = LEFT;
    ride = 1;
}
void Controller::setRight() {
    direct = RIGHT;
    ride = 1;
}

void Controller::stop(int direction) {
    if (direct == direction)        // Что бы при изменнении направления танк не останавливался
        ride = 0;
}

void Controller::shoot(ObjectScene *scene) {
    scene->createBullet(tank_id);
}

void Controller::manageTank(ObjectScene *scene, RenderWindow & window) {
    if (scene->map_objects.find(tank_id) != scene->map_objects.end()) {
        Tank *abstr_tank = dynamic_cast<Tank *>(scene->map_objects[tank_id]);
                    
        if (ride) {
            abstr_tank->set_dir(direct);// теперь устанавливаем направление, такое, как нашей переменной.
            scene->map_objects[tank_id]->set_speed(3);
        } 
        else { 
            scene->map_objects[tank_id]->set_speed(0); //останавливаем танк
        }
    } 

    else { //танк был убит!
        health--;
        if(health >= 0 ) 
        {
            std::cout << "Танк игрока был возрождён, осталось жизней: " << health << "\n";
            this->tank_id = scene->addObject(start_x, start_y, PLAYER_TANK);
            ride = 0; //пусть стоит на старте
        }       
        else
        {   Time t1 = seconds(1);
            sleep(t1);
            final(window);
        }
    }
}  
        