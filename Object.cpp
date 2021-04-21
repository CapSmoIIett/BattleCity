#include "Object.h"


Object::Object( const int id, 
                sf::String type,
                Point point,   
                int health, 
                const int heigth, 
                const int width, 
                int speed ):
id(id),
data({type,type}),
point(point), 
health(health),
heigth(heigth), 
width(width), 
speed(speed) { 
    std::cout << "конструктор базового класса\n";
}

void Object::set_point(Point point){ 
    this->point = point; 
};

Point Object::get_point(){ 
    return point;
}

void Object::set_health(int new_healse){ 
    health = new_healse; 
}
        
int Object::get_health(){ 
    return health; 
} 

void Object::set_speed(int speed){ 
    this->speed = speed; 
}

int Object::get_speed(){
    return speed;
}

Rect<int> Object::now_rectangle(ObjectScene *scene)                        
{
    Point point = scene->map_objects[id]->get_point();
    return Rect <int>(point.x, point.y, width, heigth);
}






Tank::Tank( const int id,
            Point init_point, 
            const int dir,
            sf::String name, 
            const int health, 
            const int heigth, 
            const int width, 
            int speed ): 
Object( id, 
        name,
        init_point, 
        health, 
        heigth, 
        width, 
        speed), 
Directable(dir),
recently_collided(false){ 
    std::cout << "конструктор танка\n"; 
}

bool Tank::did_collided(){
    return recently_collided;
}

void Tank::make_damage(ObjectScene *scene){
    Object* object = scene->map_objects[id];
    Tank* tank = dynamic_cast<Tank *>(object);
    tank->set_health(tank->get_health() - 1);                 // и это ссылка, экземпляр изменился в другой сцене
}

Rect<int> Tank::get_future_rectangle(ObjectScene *scene){ 
    Object* object = scene->map_objects[id];
    Tank* tank = dynamic_cast<Tank *>(object);
    Point point = tank->get_point();
    int direct = tank->get_dir();
    switch (direct){
        case UP:    point.y -= speed; break;
        case DOWN:  point.y += speed; break;
        case LEFT:  point.x -= speed; break;
        case RIGHT: point.x += speed; break;
    }
    return sf::Rect <int>(point.x, point.y, width, heigth);
}

void Tank::handle_tick(ObjectScene *scene){
    Rect <int>future_rectangle = get_future_rectangle(scene);
    
    for (auto i : scene->map_objects)
    {
        bool is_intersect = i.second->now_rectangle(scene).intersects(future_rectangle) && i.first != id;
        if (is_intersect){
            this->recently_collided = true; //Это для AITank.нет урона при наезде танка
            //std::cout << "танк столкнулся c " << i.second->data.type << "\n";
            return;
        }
    }
    this->recently_collided = false; //Это для AITank.
    move(scene);
}

void Tank::move(ObjectScene *scene){
    Object* object = scene->map_objects[id];
    Tank* tank = dynamic_cast<Tank *>(object);
    Point point = tank->get_point();
    int direct = tank->get_dir();
    switch (direct)
    {
        case UP:    point.y -= speed; break;
        case DOWN:  point.y += speed; break;
        case LEFT:  point.x -= speed; break;
        case RIGHT: point.x += speed; break;
    }
    tank->set_point(point);
}
/////////////////////////////////////////////////////////////////////////////////

Bullet::Bullet(const int id, Point init_point, const int dir): 
Object(id, "Bullet", init_point, 1, 4 *3, 4*3, 10), Directable(dir) { 
    std::cout << "конструктор пули\n"; 
};



void Bullet::move(ObjectScene *scene){
        Object * object = scene->map_objects[id];
        Bullet *bullet = dynamic_cast<Bullet *>(object);
        Point point = bullet->get_point();
        //std::cout << "Координаты PhisicalBullet " << point.x << ", " << point.y << "\n";
        int direct = bullet->get_dir();
        switch (direct){
            case UP:
                point.y -= speed;
                break;
            case DOWN:
                point.y += speed;
                break;
            case LEFT:
                point.x -= speed;
                break;
            case RIGHT:
                point.x += speed;
                break;
        }
        bullet->set_point(point);
        //std::cout << "новые координаты PhisicalBullet " << point.x << ", " << point.y << "\n";
}

void Bullet::handle_tick(ObjectScene *scene){
        sf::Rect <int>future_rectangle = get_future_rectangle(scene);
        for (auto i : scene->map_objects){
            bool is_intersect = i.second->now_rectangle(scene).intersects(future_rectangle) && i.first != id;
            if (is_intersect){
                // пуля нанесла урон в двух
                i.second->make_damage(scene);
                make_damage(scene);
                std::cout << "Пуля " << i.first << "столкнулась с " << i.second->data.type << "\n";
                //       ", здоровье = " << scene->map_objects[i.first]->get_health() << "\n";
                return;
            }
        }
        move(scene);
}

void Bullet::make_damage(ObjectScene * scene){
        Object* object =  scene->map_objects[id];
        object->set_health(( object->get_health())-1);
}


