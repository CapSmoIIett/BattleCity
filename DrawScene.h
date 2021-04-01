#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

#include <unistd.h>

#include "AbstractScene.h"
#include "Object.h"

using namespace sf;

//рисуемый объект - знает, как нарисовать себя на передаваемом холсте
class DrawObject: public Object
{
    public:
        // основной рисуемый объект
        Sprite*  sprite = nullptr; 

        //
        DrawObject(Sprite*  sprite, int id, String name, Point point, int health, const int heigth = 0, const int width = 0, int speed = 0);

        //
        ~DrawObject();
        
        //
        virtual void draw(RenderWindow &window, AbstractScene* abstract_scene) = 0; //сам объект не имеет смысла, это интерфейс.   
};

//стенка
class DrawBlock: public DrawObject
{
    public:
        //
        DrawBlock(Sprite*  sprite, const int id, String name = " ", Point point = {0, 0}, int health = 1, const int heigth = 0, const int width = 0, int speed = 0);

        //
        ~DrawBlock();

        //
        void draw(sf::RenderWindow &window, AbstractScene* abstract_scene);
};

//штаб
class DrawHeadquarters: public DrawObject
{
    private:
        //
        Sprite* living_headquarters_sprite;
        //
        Sprite* dead_headquarters_sprite;

    public:
        //
        DrawHeadquarters(Sprite* living_headquarters_sprite, Sprite* dead_headquarters_sprite, const int id, String name, 
        Point point, int health, const int heigth = 0, const int width = 0, int speed = 0);
       
        //
        ~DrawHeadquarters();
        
        //
        void draw(RenderWindow &window, AbstractScene* abstract_scene); 
};

class DrawBullet: public DrawObject
{
    private:
        //
        Sprite* up_sprite;
        //
        Sprite* down_sprite;
        //
        Sprite* right_sprite;
        //
        Sprite* left_sprite;

    public:
        //
        DrawBullet( const int id, Sprite* up_sprite, Sprite* down_sprite, Sprite* right_sprite, Sprite* left_sprite, String name, 
        Point point, int health, const int heigth = 0, const int width = 0, int speed = 0);

        ~DrawBullet();
        //
        void draw(RenderWindow &window, AbstractScene* abstract_scene);
};

//цель - реализовать отрисовку танка
class DrawTank: public DrawObject
{
    private:
        //
        Sprite* up_sprite;
        //
        Sprite* down_sprite;
        //
        Sprite* right_sprite;
        //
        Sprite* left_sprite;

    public:
        //
        DrawTank( const int id, Sprite* up_sprite, Sprite* down_sprite, Sprite* right_sprite, Sprite* left_sprite, String name = " ", 
        Point point = {0, 0}, int health = 0, const int heigth = 0, const int width = 0, int speed = 0);

        //
        ~DrawTank();
        
        //
        void draw(sf::RenderWindow &window, AbstractScene* abstract_scene);
};


// напишем рисующую сцену
class DrawScene
{
    private:
    
        //вся картинка
        Image   all_image; //создаем объект Image (изображение)
        Texture all_texture;

        Sprite  block_sprite, indestructible_block_sprite, water_sprite;
        //штаб
        Sprite  iliving_headquarters_sprite, dead_headquarters_sprite;
        //танк
        Sprite  tank_up_sprite, tank_down_sprite, tank_right_sprite, tank_left_sprite;
        //вражеский танк
        Sprite  tank_up_sprite2, tank_down_sprite2, tank_right_sprite2, tank_left_sprite2;
        //пуля
        Sprite  bullet_up_sprite, bullet_down_sprite, bullet_right_sprite, bullet_left_sprite;
        //взрыв
        Sprite  explosion_1, explosion_2, explosion_3;
        
    public:

        std::unordered_map <int, DrawObject*> object_list;

        //
        DrawScene();
       
        //
        ~DrawScene();

        //
        void setImage(Sprite &sprite, int a, int b, int c, int d);

        //
        void add_obj(const int id, const std::string& type);

        //
        void synchronize(AbstractScene* abstract_scene);

        //глобальная функция рисования
        //проходится по object_list и вызывает для draw каждого
        void draw(sf::RenderWindow &window, AbstractScene* abstract_scene);

        std::string getCurrentLocationTextures();
};
