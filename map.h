#ifndef SIMPLE_RTS_DRAWSCENE_H
#define SIMPLE_RTS_DRAWSCENE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "AbstractScene.h"
#include "Object.h"

using namespace sf;

//рисуемый объект - знает, как нарисовать себя на передаваемом холсте
class DrawObject: public Object
{
    public:
        Sprite * sprite = nullptr; // основной рисуемый объект

        DrawObject(Sprite * sprite, int id, String name, Point point, int health, const int heigth = 0, const int width = 0, int speed = 0)
        :Object(id, name, point, health, heigth, width, speed), sprite(sprite){};
        ~DrawObject(){};
        
        virtual void draw(RenderWindow &window, AbstractScene *abstract_scene) = 0; //сам объект не имеет смысла, это интерфейс.   
};

//стенка
class DrawBlock: public DrawObject
{
    public:
        DrawBlock(Sprite * sprite, const int id, String name, Point point, int health, const int heigth = 0, const int width = 0, int speed = 0) : 
            DrawObject(sprite, id, name, point, health, heigth, width, speed){};
        ~DrawBlock(){};

        void draw(RenderWindow &window, AbstractScene *abstract_scene)
        {
            Point point = abstract_scene->getPoint(id);
            sprite->setPosition(point.x, point.y);
            window.draw(*sprite);
        }
};

//штаб
class DrawHeadquarters: public DrawObject
{
    private:
        Sprite *living_headquarters_sprite, *dead_headquarters_sprite;

    public:
        DrawHeadquarters(Sprite *living_headquarters_sprite, Sprite *dead_headquarters_sprite, const int id, String name, 
        Point point, int health, const int heigth = 0, const int width = 0, int speed = 0):
            DrawObject(living_headquarters_sprite, id, name, point, health, heigth, width, speed),
            living_headquarters_sprite(living_headquarters_sprite), dead_headquarters_sprite(dead_headquarters_sprite){};
       
        ~DrawHeadquarters(){};
        
        void draw(RenderWindow &window, AbstractScene *abstract_scene)
        {
            Point point = abstract_scene->getPoint(id);
            sprite->setPosition(point.x, point.y);
            Object * abstract_object = abstract_scene->map_objects[id];
            Headquarters *abstract_headquarters = dynamic_cast<Headquarters *>(abstract_object);
            
            bool is_alive = abstract_headquarters->is_alive; // Мы с самог начала думали об этом, когда разделили на сцены
            if(is_alive){ sprite = living_headquarters_sprite; } 
            else { sprite = dead_headquarters_sprite; }

            window.draw(*sprite);
        }    
};

class DrawBullet: public DrawObject
{
    private:
        Sprite *up_sprite, *down_sprite, *right_sprite, *left_sprite;

    public:
        DrawBullet( const int id, Sprite *up_sprite, Sprite *down_sprite, Sprite *right_sprite, Sprite *left_sprite, String name, 
        Point point, int health, const int heigth = 0, const int width = 0, int speed = 0): DrawObject(up_sprite, id, name, point, health, heigth, width, speed)
        {
            this->up_sprite    = up_sprite;
            this->down_sprite  = down_sprite;
            this->right_sprite = right_sprite;
            this->left_sprite  = left_sprite;
        };

        void draw(RenderWindow &window, AbstractScene *abstract_scene)
        {
            //получаем направление
            //обращаясь к отображению этого объекта в абстрактной сцене.

            Object * abstract_object = abstract_scene->map_objects[id];
            Bullet *abstr_bullet = dynamic_cast<Bullet *>(abstract_object);
            int direction = abstr_bullet->get_dir(); // Мы с самог начала думали об этом, когда разделили на сцены
            switch(direction) 
            {
                case DOWN:  sprite = down_sprite;  break;
                case RIGHT: sprite = right_sprite; break;
                case UP:    sprite = up_sprite;    break;
                case LEFT:  sprite = left_sprite;  break;
            }
            Point point = abstract_scene->getPoint(id);
            sprite->setPosition(point.x, point.y);
            window.draw(*sprite);
        };
};

//цель - реализовать отрисовку танка
class DrawTank: public DrawObject
{
    private:
        Sprite *up_sprite, *down_sprite, *right_sprite, *left_sprite;

    public:
        DrawTank( const int id, Sprite *up_sprite, Sprite *down_sprite, Sprite *right_sprite, Sprite *left_sprite, String name, 
            Point point, int health, const int heigth = 0, const int width = 0, int speed = 0): DrawObject(up_sprite, id, name, point, health, heigth, width, speed)
            {
                this->up_sprite    = up_sprite;
                this->down_sprite  = down_sprite;
                this->right_sprite = right_sprite;
                this->left_sprite  = left_sprite;
            };
        ~DrawTank(){};
        
        void draw(sf::RenderWindow &window, AbstractScene *abstract_scene)
        {
            //получаем направление
            //обращаясь к отображению этого объекта в абстрактной сцене.
            Object * abstract_object = abstract_scene->map_objects[id];
            Tank *abstr_tank = dynamic_cast<Tank *>(abstract_object);
            int direction = abstr_tank->get_dir(); // Мы с самог начала думали об этом, когда разделили на сцены

            switch(direction) 
            {
                case DOWN:  sprite = down_sprite;  break;
                case RIGHT: sprite = right_sprite; break;
                case UP:    sprite = up_sprite;    break;
                case LEFT:  sprite = left_sprite;  break;
            }
            Point point = abstract_scene->getPoint(id);
            sprite->setPosition(point.x, point.y);
            window.draw(*sprite);
        };
};


// напишем рисующую сцену
class DrawScene: public AbstractScene
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

        void setImage(Sprite sprite, int a, int b, int c, int d)
        {
            all_image.loadFromFile("/home/asya/Projects/BattleCity/txtrs.png");
            all_texture.loadFromImage(all_image);

            sprite.setTexture(all_texture);
            sprite.setTextureRect(IntRect(a, b, c, d));
            sprite.scale(3, 3); //да
        };

        DrawScene()
        {
            setImage(block_sprite, 256, 0, 8, 8);
            setImage(indestructible_block_sprite, 256, 16, 8, 8);
            setImage(water_sprite, 256, 48, 8, 8);

            setImage(iliving_headquarters_sprite, 304, 32, 16, 16);
            setImage(dead_headquarters_sprite, 320, 32, 16, 16);

            setImage(tank_up_sprite, 1, 2, 13, 13);
            setImage(tank_down_sprite, 65, 1, 13, 13);
            setImage(tank_right_sprite, 97, 1, 13, 13);
            setImage(tank_left_sprite, 34, 1, 13, 13);
            
            setImage(tank_up_sprite2, 1, 160, 13, 15);          // танки врагов
            setImage(tank_down_sprite2, 65, 161, 13, 15);
            setImage(tank_right_sprite2, 97, 161, 15, 13);
            setImage(tank_left_sprite2, 33, 161, 15, 13);

            setImage(bullet_up_sprite, 323, 102, 3, 4);         // пуля
            setImage(bullet_down_sprite, 339, 102, 3, 4);
            setImage(bullet_right_sprite, 346, 102, 4, 3);
            setImage(bullet_left_sprite, 330, 102, 4, 3);

            setImage(explosion_1, 256, 128, 16, 16);       // взрыв
            setImage(explosion_2, 272, 128, 16, 16);
            setImage(explosion_3, 288, 128, 16, 16);
        };
       
            void add_obj(const int id, const std::string& type)
            {
                // собираем объекты в зависимости от их типа
                     if (type == "DistrBlock")        { map_objects[id] = new DrawBlock(id, &block_sprite); } 
                else if (type == "UnDistrBlock")      { map_objects[id] = new DrawBlock(id, &indestructible_block_sprite); } 
                else if (type == "WaterBlock")        { map_objects[id] = new DrawBlock(id, &water_sprite);} 
                else if (type == "HeadquartersBlock") { map_objects[id] = new DrawBlock(id, &iliving_headquarters_sprite);} 
                else if (type == "Tank")              { map_objects[id] = new DrawTank (id, &tank_up_sprite2, &tank_down_sprite2, &tank_right_sprite2, &tank_left_sprite2); } 
                else if (type == "PleerTank")         { map_objects[id] = new DrawTank (id, &tank_up_sprite, &tank_down_sprite, &tank_right_sprite, &tank_left_sprite); } 

            }

        void synchronize(AbstractScene *abstract_scene){
            //забирает измемения из абстрактной сцены и создаёт объекты
            for(auto i: abstract_scene->map_objects){
                if(map_objects.find(i.first/*id*/) == map_objects.end()){ add_obj(i.first/*id*/, abstract_scene->map_objects[i.first/*id*/]); }
            }
            //сверяет изменения с абстрактной сценой и удаляет объекты
            std::vector<int> to_remove;
            for(auto i: this->map_objects) 
            {
                if (abstract_scene->map_objects.find(i.first/*id*/) == abstract_scene->map_objects.end()) 
                    { delete i.second; to_remove.push_back(i.first); }
            }

            for (auto i : to_remove) { map_objects.erase(i); }
        };
        //глобальная функция рисования
        //проходится по object_list и вызывает для draw каждого
        void draw(sf::RenderWindow &window, AbstractScene *abstract_scene) { for (auto& i : map_objects) { i.second->draw(window, abstract_scene); } }

        ~DrawScene(){ };
};

#endif //SIMPLE_RTS_DRAWSCENE_H 