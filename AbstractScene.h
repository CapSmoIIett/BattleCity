#pragma once

#include <SFML/System/Clock.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "InterfaseScene.h"
#include <iterator>


class AbstractScene{
private:
    sf::Clock clock;

protected:
    std::unordered_map <int, Object*> map_objects;          // Массив объектов на карте
    int count_id;                                           // Количество объектов на карте
   
public: 

    AbstractScene();

    ~AbstractScene(){};

    // Функция добавляющая объект в массив объектов
    int addObject(Object*);                                           

    // Функция, очищающая список объектов от убитых, с health <= 0
    void clearDead();                                     

    // Функция, создающая пулю около этого танка с учётом направления дула танка
    void createAbctractBullet(int id);                     
    
    // Функция, выгружающая из памяти карту.
    void loadMap();

    // Функция, возвращающая point объекта по id
    Point getPoint(int id);                                
    
};

