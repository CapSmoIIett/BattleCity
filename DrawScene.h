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
        // Основной рисуемый объект
        Sprite*  sprite = nullptr; 

        // Конструктор Рисуемого объекта
        DrawObject(Sprite*  sprite, int id, String name, Point point, int health, const int heigth = 0, const int width = 0, int speed = 0);

        // Деструктор Рисуемого объекта
        ~DrawObject();

        // Функция, рисования
        virtual void draw(RenderWindow &window, AbstractScene* abstract_scene) = 0; //сам объект не имеет смысла, это интерфейс.   
};

//стенка
class DrawBlock: public DrawObject
{
    public:
        // Конструктор рисуемого блока
        DrawBlock(Sprite*  sprite, const int id, String name = " ", Point point = {0, 0}, int health = 1, const int heigth = 0, const int width = 0, int speed = 0);

        // Деструктор рисуемого блока
        ~DrawBlock();

        // Функция, рисования
        void draw(sf::RenderWindow &window, AbstractScene* abstract_scene);
};

//штаб
class DrawHeadquarters: public DrawObject
{
    private:
        // Спрайт живого штаба
        Sprite* living_headquarters_sprite;
        // Спрайт мертвого штаба
        Sprite* dead_headquarters_sprite;

    public:
        // Конструктор рисуемого штаба
        DrawHeadquarters(Sprite* living_headquarters_sprite, Sprite* dead_headquarters_sprite, const int id, String name, 
        Point point, int health, const int heigth = 0, const int width = 0, int speed = 0);
       
        // Деструктор рисуемого штаба
        ~DrawHeadquarters();
        
        // Функция, рисования
        void draw(RenderWindow &window, AbstractScene* abstract_scene); 
};

class DrawBullet: public DrawObject
{
    private:
        // Спрайт движения вверх 
        Sprite* up_sprite;
        // Спрайт движения вниз
        Sprite* down_sprite;
        // Спрайт движения вправо
        Sprite* right_sprite;
        // Спрайт движения влево
        Sprite* left_sprite;

    public:
        // Конструктор рисуемой пули
        DrawBullet( const int id, Sprite* up_sprite, Sprite* down_sprite, Sprite* right_sprite, Sprite* left_sprite, String name, 
        Point point, int health, const int heigth = 0, const int width = 0, int speed = 0);

        // Деструктор рисуемой пули
        ~DrawBullet();
        
        // Функция, рисования
        void draw(RenderWindow &window, AbstractScene* abstract_scene);
};

//цель - реализовать отрисовку танка
class DrawTank: public DrawObject
{
    private:
        // Спрайт движения вверх 
        Sprite* up_sprite;
        // Спрайт движения вниз
        Sprite* down_sprite;
        // Спрайт движения вправо
        Sprite* right_sprite;
        // Спрайт движения влево
        Sprite* left_sprite;

    public:
        // Конструктор рисуемого танка
        DrawTank( const int id, Sprite* up_sprite, Sprite* down_sprite, Sprite* right_sprite, Sprite* left_sprite, String name = " ", 
        Point point = {0, 0}, int health = 0, const int heigth = 0, const int width = 0, int speed = 0);

        // Деструктор рисуемого танка
        ~DrawTank();
        
        // Функция, рисования
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

        // Конструктор рисующей сцены
        DrawScene();
       
        // Деструктор рисующей сцены
        ~DrawScene();

        // Функиця, загружающая из изображения текстуры
        void setImage(Sprite &sprite, int a, int b, int c, int d);

        // Функция, добавляющая объект
        void add_obj(const int id, const std::string& type);

        // Функция, синхронизирующая сцены
        void synchronize(AbstractScene* abstract_scene);

        //глобальная функция рисования
        //проходится по object_list и вызывает для draw каждого
        void draw(sf::RenderWindow &window, AbstractScene* abstract_scene);

        // Функция определяющая расположение файла с текстурами
        std::string getCurrentLocationTextures();
};
