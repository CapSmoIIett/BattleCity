#include "AbstractScene.h"

AbstractScene::AbstractScene(){
    
    map_objects[1] = new Object(1, "TopBorderline", Point{0, -16}, 1000); // Верхняя граница карты
    map_objects[2] = new Object(2, "BotBorderline", Point{0, 625}, 1000); // Нижняя граница карты
    map_objects[3] = new Object(3, "LeftBorderline", Point{-16, 0}, 1000); // Левая граница карты
    map_objects[4] = new Object(4, "RightBorderline", Point{625, 0}, 1000); // Правая граница карты
}
   
AbstractScene::~AbstractScene(){

}

int AbstractScene::addObject(Object* object){
    map_objects[count_id] = object;
    count_id++;
    return 0;
}   

int AbstractScene::addObject(int x, int y, String name){
    map_objects[count_id] = new Object(count_id, name, Point {x, y}, 1);
    count_id++;
    return 0;
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


