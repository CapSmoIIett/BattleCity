#pragma once

#include <AbstractScene.h>

AbstractScene::AbstractScene(){

}
   
AbstractScene::~AbstractScene(){

}

int AbstractScene::addObject(Object* object){
    map_objects[count_id] = object;
    count_id++;
}                                           

void AbstractScene::clearDead(){
    std::vector <int> to_remove;
    for(auto i: map_objects){
        if(i.second->health <= 0){
            to_remove.push_back(i.first);                                           // Добавляем в очередь на удаление

            if(i.second->name == "Tank" or i.second->name == "PlayerTank"){
                Point point = i.second->get_point();
                add_obj(point.x, point.y, "Explosion");
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


