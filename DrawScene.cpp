#include "DrawScene.h"


DrawObject::DrawObject( Sprite*  sprite, int id, String name, Point point):
Object(id, name, point), sprite(sprite){
    std::cout << "Конструктор объекта." << "\n";
}

DrawObject::~DrawObject(){
    std::cout << "Деструктор объекта." << "\n";
}




DrawBlock::DrawBlock(   Sprite*  sprite, 
                        const int id,
                        String name, 
                        Point point) : 
DrawObject(sprite, id, name, point){
    std::cout << "Конструктор блока." << "\n";
}

DrawBlock::~DrawBlock(){
    std::cout << "Деструктор блока." << "\n";
}

void DrawBlock::draw(sf::RenderWindow &window, ObjectScene* scene){
    Point point = scene->getPoint(id);
    sprite->setPosition(point.x, point.y);
    window.draw(*sprite);
}




DrawHeadquarters::DrawHeadquarters( Sprite* living_headquarters_sprite, 
                                    Sprite* dead_headquarters_sprite, 
                                    const int id, String name, 
                                    Point point):
DrawObject(living_headquarters_sprite, id, name, point),
living_headquarters_sprite(living_headquarters_sprite), 
dead_headquarters_sprite(dead_headquarters_sprite){
    std::cout << "Конструктор штаба." << "\n";
}

DrawHeadquarters::~DrawHeadquarters(){
    std::cout << "Деструктор штаба." << "\n";
}
        
void DrawHeadquarters::draw(RenderWindow &window, ObjectScene* scene){
    Point point = scene->getPoint(id);
    sprite->setPosition(point.x, point.y);
    Object*  object = scene->map_objects[id];
    Headquarters* headquarters = dynamic_cast<Headquarters* >(object);
            
    bool is_alive = headquarters->is_alive; // Мы с самог начала думали об этом, когда разделили на сцены
    if(is_alive){ sprite = living_headquarters_sprite; } 
    else { sprite = dead_headquarters_sprite; }

    window.draw(*sprite);
}    




DrawBullet::DrawBullet( const int id, 
                        Sprite* up_sprite, 
                        Sprite* down_sprite, 
                        Sprite* right_sprite, 
                        Sprite* left_sprite, 
                        String name, 
                        Point point): 
DrawObject(up_sprite, id, name, point){
    std::cout << "Конструктор пули." << "\n";
    this->up_sprite = up_sprite;
    this->down_sprite = down_sprite;
    this->right_sprite = right_sprite;
    this->left_sprite = left_sprite;
}

DrawBullet::~DrawBullet(){
    std::cout << "Деструктор пули." << "\n";
}

void DrawBullet::draw(RenderWindow &window, ObjectScene* scene){

    Object*  object = scene->map_objects[id];
    Bullet* abstr_bullet = dynamic_cast<Bullet* >(object);
    int direction = abstr_bullet->get_dir();                            //получаем направление
    switch(direction)
    {
        case DOWN:  sprite = down_sprite;  break;
        case RIGHT: sprite = right_sprite; break;
        case UP:    sprite = up_sprite;    break;
        case LEFT:  sprite = left_sprite;  break;
    }
    Point point = scene->getPoint(id);
    sprite->setPosition(point.x, point.y);
    window.draw(*sprite);
}



DrawTank::DrawTank( const int id, 
                    Sprite* up_sprite, 
                    Sprite* down_sprite, 
                    Sprite* right_sprite, 
                    Sprite* left_sprite, 
                    String name, Point point): 
DrawObject(up_sprite, id, name, point){
    std::cout << "Конструктор танка." << "\n";
    this->up_sprite = up_sprite;
    this->down_sprite = down_sprite;
    this->right_sprite = right_sprite;
    this->left_sprite = left_sprite;
}
        
DrawTank::~DrawTank(){
    std::cout << "Деструктор танка." << "\n";
}
        
void DrawTank::draw(sf::RenderWindow &window, ObjectScene* scene){

    Object*  object = scene->map_objects[id];
    Tank* abstr_tank = dynamic_cast<Tank* >(object);

    int direction = abstr_tank->get_dir();                          //получаем направление
       
    switch(direction) 
    {
        case DOWN:  sprite = down_sprite;  break;
        case RIGHT: sprite = right_sprite; break;
        case UP:    sprite = up_sprite;    break;
        case LEFT:  sprite = left_sprite;  break;
    }
    Point point = scene->getPoint(id);
    sprite->setPosition(point.x, point.y);
    window.draw(*sprite);
}




DrawScene::DrawScene(){
    std::cout << "Конструктор DrawScene." << "\n";

    all_image.loadFromFile(getCurrentLocationTextures());
    all_texture.loadFromImage(all_image);    

    // Блоки карты
    setImage(block_sprite, 256, 0, 8, 8);
    setImage(indestructible_block_sprite, 256, 16, 8, 8);
    setImage(water_sprite, 256, 48, 8, 8);

    // Штаб
    setImage(iliving_headquarters_sprite, 304, 32, 16, 16);
    setImage(dead_headquarters_sprite, 320, 32, 16, 16);

    // Танк игрока
    setImage(tank_up_sprite, 1, 2, 13, 13);
    setImage(tank_down_sprite, 65, 1, 13, 13);
    setImage(tank_right_sprite, 97, 1, 13, 13);
    setImage(tank_left_sprite, 34, 1, 13, 13);

    // Танки врагов       
    setImage(tank_up_sprite2, 1, 160, 13, 15);          
    setImage(tank_down_sprite2, 65, 161, 13, 15);
    setImage(tank_right_sprite2, 97, 161, 15, 13);
    setImage(tank_left_sprite2, 33, 161, 15, 13);

    // Пуля
    setImage(bullet_up_sprite, 323, 102, 3, 4);         
    setImage(bullet_down_sprite, 339, 102, 3, 4);
    setImage(bullet_right_sprite, 346, 102, 4, 3);
    setImage(bullet_left_sprite, 330, 102, 4, 3);

    // Взрыв
    setImage(explosion_1, 256, 128, 16, 16);       
    setImage(explosion_2, 272, 128, 16, 16);
    setImage(explosion_3, 288, 128, 16, 16);
}

DrawScene::~DrawScene(){
    std::cout << "Деструктор DrawScene." << "\n"; 
};

void DrawScene::setImage(Sprite &sprite, int a, int b, int c, int d){

    sprite.setTexture(all_texture);
    sprite.setTextureRect(IntRect(a, b, c, d));
    sprite.scale(3, 3); 
}
       
void DrawScene::add_obj(const int id, const std::string& type){
    // собираем объекты в зависимости от их типа
    std::cout << id << "\n";
    std::cout << type << "\n";
         if (type == "DistrBlock")        { object_list[id] = new DrawBlock(&block_sprite, id); } 
    else if (type == "UnDistrBlock")      { object_list[id] = new DrawBlock(&indestructible_block_sprite, id); } 
    else if (type == "WaterBlock")        { object_list[id] = new DrawBlock(&water_sprite, id);} 
    else if (type == "HeadquartersBlock") { object_list[id] = new DrawBlock(&iliving_headquarters_sprite, id);} 
    else if (type == "Tank")              { object_list[id] = new DrawTank (id, &tank_up_sprite2, &tank_down_sprite2, &tank_right_sprite2, &tank_left_sprite2); } 
    else if (type == "PleerTank")         { object_list[id] = new DrawTank (id, &tank_up_sprite, &tank_down_sprite, &tank_right_sprite, &tank_left_sprite); } 

}

void DrawScene::synchronize(ObjectScene *scene){

        for(auto i: scene->map_objects){                       //забирает измемения из абстрактной сцены и создаёт объекты
            if(object_list.find(i.first/*id*/) == object_list.end()){
                add_obj(i.first/*id*/, i.second->data.type);            //если нет объекта в рисующей схеме
                                                                        //значит его надо создать
            }
        }
        //сверяет изменения с абстрактной сценой и удаляет объекты
        std::vector<int> to_remove;
        for(auto i: this->object_list) {
            if (scene->map_objects.find(i.first) ==
                scene->map_objects.end()) {
                delete i.second;                        //если нет объекта в абстрактной сцене
                                                        //значит его надо удалить и из нашей сцены
                to_remove.push_back(i.first);
            }
        }
        for (auto i : to_remove) {
            object_list.erase(i);
        }
}

void DrawScene::draw(sf::RenderWindow &window, ObjectScene* scene) { 
    for (auto& i : object_list) { 
        i.second->draw(window, scene); 
    } 
}

std::string DrawScene::getCurrentLocationTextures(){
    char* way = new char[200];                          
    way = getcwd(way, 200);                               // Получаем текущую деректорию

    std::string str(way);
    str += "/txtrs.png";
    std::cout << str << "\n";
    delete[] way;
    return str;
}


