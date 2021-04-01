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

#include "AbstractScene.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


using namespace sf;

struct Point                                                                             //точка, возвращаемая абстрактным классом для отрисовки текстуры
{ 
    int x, y;
};

struct Data 
{
    std::string str, type;
};

class Directable
{
    protected:
        int direct;

    public:
        Directable(const int dir = 0):direct(dir){}
        virtual ~Directable(){};

        void set_dir(const int dir) { this->direct = dir;return; }
        int& get_dir() { return direct; }  
};
//////////////////////////////////////////////////////////////////////////////////////
class Object                                                                            // бывший AbstractObject
{
    protected:
        //
        Point point;
        //
        int speed;
        //
        const int width, heigth;

    public:
        //
        Data data;
        //
        const int id;
        //
        int health;

        //
        Object(const int id, sf::String name, Point point, int health = 1, int heigth = 39, int width = 39, int speed = 0);  // TODO разобраться с параметрами по умолчанию
        
        //
        ~Object(){};

        //
        void set_point(Point point);
        
        //
        Point get_point();
        
        //
        void set_health( int new_healse);
        
        //
        int get_health();

        //
        virtual Data serialise(){ return data;};

        //
        virtual void apply(Data d){ this->data = d;};

        //
        void set_speed(int speed);

        //
        int get_speed();
       
        // рамка, в которой сейчас находится объект
        Rect <int>now_rectangle(class AbstractScene *abstract_scene);

        //
        virtual void make_damage(class AbstractScene *abstract_scene) {};

        //
        virtual void handle_tick(class AbstractScene *abstract_scene) {};
};

/////////////////////////////// танк, блоки, пуля и штаб //////////////////////////////

//////////
class Tank: public Object, public Directable
{

    public:
        //
        Time last_shoot;

    protected:
        //
        bool recently_collided;

    public:
        //
        Tank(const int id, Point init_point = {50, 50}, const int dir = UP, const int health = 1, const int heigth = 39, const int width = 39, int speed = 1);  // TODO Разобраться с порядком параметров

        //
        ~Tank(){};
       
        //
        bool did_collided();
    
        //
        void make_damage(class AbstractScene *abstract_scene);

        // рамка, в которой будет находиться объект, если ему ничего не помешает
        Rect <int>get_future_rectangle(class AbstractScene *abstract_scene);

        //
        void handle_tick(class AbstractScene *abstract_scene);

    protected:
        //
        void move(class AbstractScene *abstract_scene);
};
////////


class DistrBlock: public Object
{
    public:
        DistrBlock(const int id, Point point = {0,0}, const int health = 1):Object(id, "DistrBlock", point, health)
            { std::cout << "конструктор разрушимого блока\n"; }
};

class Headquarters: public Object
{
    public:
        bool is_alive;

        Headquarters(const int id, Point point):Object(id, "Headquarters", point, 1), is_alive(true)
            { std::cout << "конструктор штаба\n"; }
};

class Bullet: public Object, public Directable
{
    public:
        Bullet(const int id, Point init_point = {0, 0}, const int dir = 0, const int health = 1): Object(id, "Bullet", init_point, health), Directable(dir)
            { std::cout << "конструктор пули\n"; };
        ~Bullet(){};
};
