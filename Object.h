#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <string>

#include "ObjectScene.h"
#include "Constants.h"

using namespace sf;

struct Point                                                                             //точка, возвращаемая абстрактным классом для отрисовки текстуры
{ 
    int x, y;
};

// Класс объектов с напралением
class Directable
{
    protected:
        // Направление 
        int direct;

    public:

        // Конструктор  объектов с напралением
        Directable(const int dir = 0):direct(dir){};

        // Деструктор  объектов с напралением
        virtual ~Directable(){};

        // Функция, устанавливающая напраление
        void set_dir(const int dir) { this->direct = dir;return; }

        // Функция, получения напраления 
        int& get_dir() { return direct; }  
};

// Класс объекта
class Object                                                                            // бывший Object
{
    protected:
        // Расположение объекта
        Point point;
        // Скорость объекта
        int speed;
        // Ширина и высота объекта
        const int width, heigth;

    public:
        // Тип объекта
        int type;
        // Айди объекта
        const int id;
        // Здоровье объекта
        int health;

        // Конструктор объекта          TODO сделать у всех одинковые размеры
        Object(const int id, int type, Point point, int health = 1, int heigth = SIZEBLOCK * PROPORTION, int width = SIZEBLOCK * PROPORTION, int speed = 0);  // TODO разобраться с параметрами по умолчанию
        
        // Деструктор объекту
        ~Object(){
            //std::cout <<"Деструктор   " << type << "\n";
        };

        // Сеттер расположения объекта
        void set_point(Point point);
        
        // Геттер расположения объекта
        Point get_point();
        
        // Сеттер здоровья
        void set_health( int new_healse);
        
        // Геттер здоровья
        int get_health();

        // Сеттер скорости
        void set_speed(int speed);

        // Геттер скорости
        int get_speed();
       
        // Рамка, в которой сейчас находится объект
        Rect <int>now_rectangle(class ObjectScene *scene);

        // Функция, обрабатывающая получения урона
        virtual void make_damage(class ObjectScene *scene) {};

        // Функция обновления состояния
        virtual void handle_tick(class ObjectScene *scene) {};

        //
        virtual sf::Rect<int> get_future_rectangle(class ObjectScene *scene) {return sf::Rect <int>(point.x, point.y, width, heigth);}; 
};

// Объект танка
class Tank: public Object, public Directable
{

    public:
        // Время последнего выстрела
        Time last_shoot;

    protected:
        // 
        bool recently_collided;

    public:
        // Конструктор танка
        Tank(const int id, Point init_point = {50, 50}, const int dir = 0, int type = TANK, const int health = 1, const int heigth = SIZETANK * PROPORTION, const int width = SIZETANK * PROPORTION, int speed = 0);  // TODO Разобраться с порядком параметров

        // Деструктор танка
        ~Tank(){};
       
        // 
        bool did_collided();
    
        // Функция, обрабатывающая получения урона
        virtual void make_damage(class ObjectScene *scene);

        // Рамка, в которой будет находиться объект, если ему ничего не помешает
        virtual Rect<int> get_future_rectangle(class ObjectScene *scene);

        // Функция обновления состояния
        virtual void handle_tick(class ObjectScene *scene);

        //
        //sf::Rect<int> get_future_rectangle(ObjectScene *scene); 

    protected:
        // Функция перемещения танка
        void move(class ObjectScene *scene);

        //friend void AIController::manageTank();
};


// Разрушаемый блок
class DistrBlock: public Object
{
    public:
        DistrBlock(const int id, Point point = {0,0}, const int health = 1):Object(id, DISTR_BLOCK, point, health)
            { std::cout << "конструктор разрушимого блока\n"; }

        ~DistrBlock(){
            std::cout <<"Деструктор разрушимого блока\n";
        };

        virtual void make_damage(class ObjectScene* scene) {
            //Object* object = scene->
            health--;
        }
};

// Штаб
class Headquarters: public Object
{
    public:
        // Состояние - жив или нет

        // Конструктор штаба
        Headquarters(const int id, Point point):Object(id, HEADQUARTERS, point, 3, SIZEBLOCK * PROPORTION * 2, SIZEBLOCK * PROPORTION * 2)
            { std::cout << "конструктор штаба\n"; }

        virtual void make_damage(class ObjectScene *scene) { 
            health--; 
        };
};

// Пуля
class Bullet: public Object, public Directable
{
    public:
        // Конструктор пули
        Bullet(const int id, Point init_point, const int dir);

        // Деструктор пули
        ~Bullet(){ std::cout << "Деструктор пули\n"; };
        
        //
        virtual void make_damage(ObjectScene* scene);
        
        //
        void move(class ObjectScene *scene);

        //
        void handle_tick(class ObjectScene *scene);
};

