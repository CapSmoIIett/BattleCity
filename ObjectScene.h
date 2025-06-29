#pragma once

#include <SFML/System/Clock.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>

#include "Object.h"

class Point;

class ObjectScene{
private:
    sf::Clock clock;

protected:
    int count_id;                                           // Количество объектов на карте
   
public: 
    std::unordered_map <int, class Object*> map_objects;          // Массив объектов на карте

    // Конструктор Абстрактной сцены
    ObjectScene();

    // Деструктор Абстрактной сцены
    ~ObjectScene();

    // Функция, добавляющая объект в массив объектов
    int addObject(class Object*);        


    
    // Функция, добавляющая объект в массив объектов
    int addObject(int x, int y, int type);   
    int addObject(int id, Object obj);                  // Необходим для работы клиента                                

    // Функция, очищающая список объектов от убитых, с health <= 0
    void clearDead();                                     

    // Функция, создающая пулю около этого танка с учётом направления дула танка
    void createBullet(int id);                     
    
    // Функция, выгружающая из памяти карту.
    void loadMap(std::fstream& file);

    // Функция, возвращающая point объекта по id
    class Point getPoint(int id);                                
    
    //
    void handleTickAll();
};

