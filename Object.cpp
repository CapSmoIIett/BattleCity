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


Rect<int> Object::now_rectangle(AbstractScene *abstract_scene)                        
{
    Point point = abstract_scene->map_objects[id]->get_point();
    return Rect <int>(point.x, point.y, width, heigth);
}





Tank::Tank( const int id,
            Point init_point, 
            const int dir, 
            const int health, 
            const int heigth, 
            const int width, 
            int speed ): 
Object( id, 
        "Tank",
        init_point, 
        health, 
        heigth, 
        width, 
        speed), 
Directable(dir){ 
    std::cout << "конструктор танка\n"; 
}

bool Tank::did_collided(){
    return recently_collided;
}

void Tank::make_damage(AbstractScene *abstract_scene){
    Object* object = abstract_scene->map_objects[id];
    Tank* tank = dynamic_cast<Tank *>(object);
    tank->set_health(tank->get_health() - 1);                 // и это ссылка, экземпляр изменился в другой сцене
}

Rect<int> Tank::get_future_rectangle(AbstractScene *abstract_scene){ 
    Object* object = abstract_scene->map_objects[id];
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

void Tank::handle_tick(AbstractScene *abstract_scene){
    Rect <int>future_rectangle = get_future_rectangle(abstract_scene);
    
    for (auto i : abstract_scene->map_objects)
    {
        bool is_intersect = i.second->now_rectangle(abstract_scene).intersects(future_rectangle) && i.first != id;
        if (is_intersect){
            this->recently_collided = true; //Это для AITank.нет урона при наезде танка
           std::cout << "танк столкнулся c " << "\n";
            return;
        }
    }
    this->recently_collided = false; //Это для AITank.
    move(abstract_scene);
}

void Tank::move(AbstractScene *abstract_scene){
    Object* object = abstract_scene->map_objects[id];
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

