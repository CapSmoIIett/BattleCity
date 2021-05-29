#include "ObjectScene.h"
#include "Constants.h"

ObjectScene::ObjectScene(){
    std::cout << "Конструктор абстрактной сцены." << "\n";
    map_objects[1] = new Object(1, UNDISTR_BLOCK, Point{0, -16}, 1000, 12, 625); // Верхняя граница карты
    map_objects[2] = new Object(2, UNDISTR_BLOCK, Point{0, 625}, 1000, 12, 625); // Нижняя граница карты
    map_objects[3] = new Object(3, UNDISTR_BLOCK, Point{-16, 0}, 1000, 625, 12); // Левая граница карты
    map_objects[4] = new Object(4, UNDISTR_BLOCK, Point{625, 0}, 1000, 625, 12); // Правая граница карты
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

int ObjectScene::addObject(int x, int y, int type){
    //map_objects[count_id] = new Object(count_id, type, Point {x, y}, 1);
    //TODO заменить на switch
    if(type == DISTR_BLOCK) {
            map_objects[count_id] = new DistrBlock(count_id, Point{x, y}, 1);
        } else if(type == UNDISTR_BLOCK) {
            map_objects[count_id] = new Object(count_id, UNDISTR_BLOCK, Point{x, y}, 100000);
        } else if(type == TANK) {
            map_objects[count_id] = new Tank(count_id, Point{x, y});
        } else if(type == PLAYER_TANK) { //отличие только в том, что не создаётся AI_tank
            map_objects[count_id] = new Tank(count_id, Point{x, y}, 0, PLAYER_TANK);
        } else if(type == WATER_BLOCK){
            map_objects[count_id] = new Object(count_id, WATER_BLOCK, Point{x, y});
        } else if(type == HEADQUARTERS) {
            map_objects[count_id] = new Headquarters(count_id, Point{x, y});
        } else if(type == SPAWNER) {
            map_objects[count_id] = new Object(count_id, SPAWNER, Point{x, y}, 1000, 0, 0);
        } else if(type == EXPLOSION) {
            map_objects[count_id] = new Object(count_id, EXPLOSION, Point{x, y}, 1000);
        }
    count_id++;
    return count_id - 1; 
}

int ObjectScene::addObject(int id, Object obj)
{
    if (map_objects.find(id) != map_objects.end())
        return id; 
    //TODO заменить на switch
    if(obj.type == DISTR_BLOCK) {
            map_objects[id] = new DistrBlock(id, obj.get_point(), 1);
        } 
        else if(obj.type == UNDISTR_BLOCK) {
            map_objects[id] = new Object(id, UNDISTR_BLOCK, obj.get_point(), 100000);
        } 
        else if(obj.type == TANK) {
            map_objects[id] = new Tank(id, obj.get_point());
        } 
        else if(obj.type == PLAYER_TANK) { //отличие только в том, что не создаётся AI_tank
            map_objects[id] = new Tank(id, obj.get_point(), 0, PLAYER_TANK);
        } 
        else if(obj.type == BULLET)
        {
            // Костыль для клиента
            int dir = obj.get_direction();
            map_objects[id] = new Bullet(id, obj.get_point(), dir);
            //map_objects[id] = new Object(id, BULLET, obj.get_point(), dir);
        } 
        else if(obj.type == WATER_BLOCK){
            map_objects[id] = new Object(id, WATER_BLOCK, obj.get_point());
        } 
        else if(obj.type == HEADQUARTERS) {
            map_objects[id] = new Headquarters(id, obj.get_point());
        } 
        else if(obj.type == SPAWNER) {
            map_objects[id] = new Object(id, SPAWNER, obj.get_point(), 1000, 0, 0);
        } 
        else if(obj.type == EXPLOSION) {
            map_objects[id] = new Object(id, EXPLOSION, obj.get_point(), 1000);
        }
    return id; 
}

void ObjectScene::clearDead(){
    std::vector <int> to_remove;
    for(auto i: map_objects){
        if(i.second->health <= 0){
            if(i.second->type == HEADQUARTERS) continue;
            to_remove.push_back(i.first);                                           // Добавляем в очередь на удаление
            /*
            AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
            */
            /*if(i.second->serialise().type == TANK or i.second->serialise().type == PLAYER_TANK){
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
    Tank* object;
    try {
        object = dynamic_cast<Tank*>(map_objects.at(id));     // .at - вызывает out_of_range если данный ключ не занят
    }
    catch (...) {
        return;
    }
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
                case '#': this->addObject(x, y, DISTR_BLOCK);        break;
                case '@': this->addObject(x, y, UNDISTR_BLOCK);      break;
                case '.': break;
                case '!': this->addObject(x, y, HEADQUARTERS); break;    // База                          
                case '~': this->addObject(x, y, WATER_BLOCK);        break;    // Вода                           
                case 's': this->addObject(x, y, SPAWNER);           break;    // Создатель танков                           
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