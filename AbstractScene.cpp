#include "AbstractScene.h"

AbstractScene::AbstractScene(){
    std::cout << "Конструктор абстрактной сцены." << "\n";
    map_objects[1] = new Object(1, "UnDistrBlock", Point{0, -16}, 1000); // Верхняя граница карты
    map_objects[2] = new Object(2, "UnDistrBlock", Point{0, 625}, 1000); // Нижняя граница карты
    map_objects[3] = new Object(3, "UnDistrBlock", Point{-16, 0}, 1000); // Левая граница карты
    map_objects[4] = new Object(4, "UnDistrBlock", Point{625, 0}, 1000); // Правая граница карты
}
   
AbstractScene::~AbstractScene(){
    std::cout << "Деструктор абстрактной сцены." << "\n";
}

int AbstractScene::addObject(Object* object){
    map_objects[count_id] = object;
    count_id++;
    return 0;
}   

int AbstractScene::addObject(int x, int y, String name){
    map_objects[count_id] = new Object(count_id, name, Point {x, y}, 1);
    count_id++;
    return 0; // может быть return count_id; ?
}                                        

void AbstractScene::clearDead(){
    std::vector <int> to_remove;
    for(auto i: map_objects){
        if(i.second->health <= 0){
            to_remove.push_back(i.first);                                           // Добавляем в очередь на удаление

            if(i.second->serialise().type == "Tank" or i.second->serialise().type == "PlayerTank"){
                Point point = i.second->get_point();
                addObject(point.x, point.y, "Explosion");
            }
                //---циклические зависимости возникают, не получается убрать в объект---
        }
    }
    for(auto i: to_remove) {
       delete map_objects[i];
        map_objects.erase(i);
    }
}                                 

Point AbstractScene::getPoint(int id){
    return map_objects[id]->get_point();
}                       
    
void AbstractScene::createAbctractBullet(int id){

}                 

void AbstractScene::loadMap(std::fstream& file)
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