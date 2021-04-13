#include "ObjectScene.h"

ObjectScene::ObjectScene(){
    std::cout << "Конструктор абстрактной сцены." << "\n";
    map_objects[1] = new Object(1, "UnDistrBlock", Point{0, -16}, 1000, 12, 625); // Верхняя граница карты
    map_objects[2] = new Object(2, "UnDistrBlock", Point{0, 625}, 1000, 12, 625); // Нижняя граница карты
    map_objects[3] = new Object(3, "UnDistrBlock", Point{-16, 0}, 1000, 625, 12); // Левая граница карты
    map_objects[4] = new Object(4, "UnDistrBlock", Point{625, 0}, 1000, 625, 12); // Правая граница карты
    count_id = 5;
}
   
ObjectScene::~ObjectScene(){
    std::cout << "Деструктор абстрактной сцены." << "\n";
}

int ObjectScene::addObject(Object* object){
    map_objects[count_id] = object;
    count_id++;
    return count_id - 1;
}   

int ObjectScene::addObject(int x, int y, String name){
    //map_objects[count_id] = new Object(count_id, name, Point {x, y}, 1);
    if(name == "DistrBlock") {
            map_objects[count_id] = new DistrBlock(count_id, Point{x, y}, 1);
        } else if(name == "UnDistrBlock") {
            map_objects[count_id] = new Object(count_id, "UnDistrBlock", Point{x, y}, 100000);
        } else if(name == "Tank") {
            map_objects[count_id] = new Tank(count_id, Point{x, y});
        } else if(name == "PlayerTank") { //отличие только в том, что не создаётся AI_tank
            map_objects[count_id] = new Tank(count_id, Point{x, y}, 0, "PlayerTank");
       } else if(name == "WaterBlock") {
            map_objects[count_id] = new Object(count_id, "WaterBlock", Point{x, y});
        }/* else if(name == "HeadquartersBlock") {
            map_objects[count_id] = new Headquarters(count_id, Point{x, y});
        }*/ else if(name == "Spawner") {
            map_objects[count_id] = new Object(count_id, "Spawner", Point{x, y}, 1000, 0, 0);
        } else if(name == "Explosion") {
            map_objects[count_id] = new Object(count_id, "Explosion", Point{x, y}, 1000);
        }
    count_id++;
    return count_id - 1; 
}                                        

void ObjectScene::clearDead(){
    std::vector <int> to_remove;
    for(auto i: map_objects){
        if(i.second->health <= 0){
            to_remove.push_back(i.first);                                           // Добавляем в очередь на удаление

            /*if(i.second->serialise().type == "Tank" or i.second->serialise().type == "PlayerTank"){
                Point point = i.second->get_point();
                addObject(point.x, point.y, "Explosion");
            }*/
                //---циклические зависимости возникают, не получается убрать в объект---
        }
    }
    for(auto i: to_remove) {
       delete map_objects[i];
        map_objects.erase(i);
    }
}                                 

Point ObjectScene::getPoint(int id){
    return map_objects[id]->get_point();
}                       
    
void ObjectScene::createBullet(int id){
    //напоминание: танк 15*3 на 15*3
    //пуля 4*3 на 4*3
    Tank* object = dynamic_cast<Tank*>(map_objects[id]);
    Point point = object->get_point();
    int dir = object->get_dir();
    //map_objects[count_id] = new Bullet(count_id, point, dir);
    sf::Time now = clock.getElapsedTime();
    if(now - object->last_shoot > sf::seconds(0.5)){
        switch (dir) {
            case DOWN:  map_objects[count_id] = new Bullet(count_id, {point.x + 14, point.y + 45}, dir);
                break;
            case RIGHT: map_objects[count_id] = new Bullet(count_id, {point.x + 45, point.y + 16}, dir);
                break;
            case UP:    map_objects[count_id] = new Bullet(count_id, {point.x + 16, point.y - 12}, dir);
                break;
            case LEFT:  map_objects[count_id] = new Bullet(count_id, {point.x - 12, point.y + 16}, dir);
                break;
        }
        object->last_shoot = now;
    }
    count_id++;
}                 

void ObjectScene::loadMap(std::fstream& file)
{
    std::string str;
    int x = 0;
    int y = 0;
    while(std::getline(file, str))
    {
        for (auto& i : str){
            switch(i)
            {
                case '#': this->addObject(x, y, "DistrBlock");        break;
                case '@': this->addObject(x, y, "UnDistrBlock");      break;
                case '.': break;
                case '!': this->addObject(x, y, "HeadquartersBlock"); break;    // База                          
                case '~': this->addObject(x, y, "WaterBlock");        break;    // Вода                           
                case 's': this->addObject(x, y, "Spawner");           break;    // Создатель танков                           
            }
            x += 24; //3 * 8(px в блоке)
        }
        x = 0;
        y += 24;
            
    }
}



void ObjectScene::handleTickAll(){
        
        for (auto i : map_objects){
            i.second->handle_tick(this);
        }

}