#include "DrawScene.h"


DrawObject::DrawObject( Sprite*  sprite, 
                        int id, 
                        String name, 
                        Point point, 
                        int health, 
                        const int heigth, 
                        const int width, 
                        int speed ):
Object(id, name, point, health, heigth, width, speed), sprite(sprite){
    std::cout << "Конструктор объекта." << "\n";
}

DrawObject::~DrawObject(){
    std::cout << "Деструктор объекта." << "\n";
}




DrawBlock::DrawBlock(   Sprite*  sprite, 
                        const int id, 
                        String name, 
                        Point point, 
                        int health, 
                        const int heigth, 
                        const int width, 
                        int speed ) : 
DrawObject(sprite, id, name, point, health, heigth, width, speed){
    std::cout << "Конструктор блока." << "\n";
}

DrawBlock::~DrawBlock(){
    std::cout << "Деструктор блока." << "\n";
}

void DrawBlock::draw(sf::RenderWindow &window, AbstractScene* abstract_scene){
    Point point = abstract_scene->getPoint(id);
    sprite->setPosition(point.x, point.y);
    window.draw(*sprite);
}




DrawHeadquarters::DrawHeadquarters( Sprite* living_headquarters_sprite, 
                                    Sprite* dead_headquarters_sprite, 
                                    const int id, String name, 
                                    Point point, 
                                    int health, 
                                    const int heigth, 
                                    const int width, 
                                    int speed ):
DrawObject(living_headquarters_sprite, id, name, point, health, heigth, width, speed),
living_headquarters_sprite(living_headquarters_sprite), 
dead_headquarters_sprite(dead_headquarters_sprite){
    std::cout << "Конструктор штаба." << "\n";
}

DrawHeadquarters::~DrawHeadquarters(){
    std::cout << "Деструктор штаба." << "\n";
}
        
void DrawHeadquarters::draw(RenderWindow &window, AbstractScene* abstract_scene){
    Point point = abstract_scene->getPoint(id);
    sprite->setPosition(point.x, point.y);
    Object*  abstract_object = abstract_scene->map_objects[id];
    Headquarters* abstract_headquarters = dynamic_cast<Headquarters* >(abstract_object);
            
    bool is_alive = abstract_headquarters->is_alive; // Мы с самог начала думали об этом, когда разделили на сцены
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
                        Point point, 
                        int health, 
                        const int heigth, 
                        const int width, 
                        int speed ): 
DrawObject(up_sprite, id, name, point, health, heigth, width, speed){
    std::cout << "Конструктор пули." << "\n";
    this->up_sprite = up_sprite;
    this->down_sprite = down_sprite;
    this->right_sprite = right_sprite;
    this->left_sprite = left_sprite;
}

DrawBullet::~DrawBullet(){
    std::cout << "Деструктор пули." << "\n";
}

void DrawBullet::draw(RenderWindow &window, AbstractScene* abstract_scene){
    //получаем направление
    //обращаясь к отображению этого объекта в абстрактной сцене.

    Object*  abstract_object = abstract_scene->map_objects[id];
    Bullet* abstr_bullet = dynamic_cast<Bullet* >(abstract_object);
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
}



DrawTank::DrawTank( const int id, 
                    Sprite* up_sprite, 
                    Sprite* down_sprite, 
                    Sprite* right_sprite, 
                    Sprite* left_sprite, 
                    String name, 
                    Point point, 
                    int health, 
                    const int heigth, 
                    const int width, 
                    int speed): 
DrawObject(up_sprite, id, name, point, health, heigth, width, speed){
    std::cout << "Конструктор танка." << "\n";
    this->up_sprite = up_sprite;
    this->down_sprite = down_sprite;
    this->right_sprite = right_sprite;
    this->left_sprite = left_sprite;
}
        
DrawTank::~DrawTank(){
    std::cout << "Деструктор танка." << "\n";
}
        
void DrawTank::draw(sf::RenderWindow &window, AbstractScene* abstract_scene){
    //получаем направление
    //обращаясь к отображению этого объекта в абстрактной сцене.
    
    Object*  abstract_object = abstract_scene->map_objects[id];
    Tank* abstr_tank = dynamic_cast<Tank* >(abstract_object);
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
}




DrawScene::DrawScene(){
    std::cout << "Конструктор DrawScene." << "\n";

    
    //
    //"/home/matthew/Projects/BattleCity/txtrs.png"
    //all_image.loadFromFile(getCurrentLocationTextures());
   // all_texture.loadFromImage(all_image);
    all_image.loadFromFile(getCurrentLocationTextures());
    all_texture.loadFromImage(all_image);

    

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
}

DrawScene::~DrawScene(){
    std::cout << "Деструктор DrawScene." << "\n"; 
};

void DrawScene::setImage(Sprite &sprite, int a, int b, int c, int d){

    sprite.setTexture(all_texture);
    sprite.setTextureRect(IntRect(a, b, c, d));
    sprite.scale(3, 3); //да
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

/*void DrawScene::synchronize(AbstractScene* abstract_scene){
    //забирает измемения из абстрактной сцены и создаёт объекты
    for(auto i: abstract_scene->map_objects){
        if(object_list.find(i.first) == object_list.end()){ add_obj(i.first, abstract_scene->map_objects[i.first]->data.type); }
    }
    //сверяет изменения с абстрактной сценой и удаляет объекты
    std::vector<int> to_remove;
    for(auto i: this->object_list) 
    {
        if (abstract_scene->map_objects.find(i.first) == abstract_scene->map_objects.end()) 
        { delete i.second; to_remove.push_back(i.first); }
    }

    for (auto i : to_remove) { object_list.erase(i); }
}*/

void DrawScene::draw(sf::RenderWindow &window, AbstractScene* abstract_scene) { 
    for (auto& i : object_list) { 
        i.second->draw(window, abstract_scene); 
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

void DrawScene::synchronize(AbstractScene *abstract_scene){

        for(auto i: abstract_scene->map_objects){                           //забирает измемения из абстрактной сцены и создаёт объекты
            if(object_list.find(i.first/*id*/) == object_list.end()){
                //если нет объекта в рисующей схеме
                //значит его надо создать
                add_obj(i.first/*id*/, i.second->data.type);
            }
        }
        //сверяет изменения с абстрактной сценой и удаляет объекты
        /*std::vector<int> to_remove;
        for(auto i: this->object_list) {
            if (abstract_scene->map_objects.find(i.first) ==
                abstract_scene->map_objects.end()) {
                //если нет объекта в абстрактной сцене
                //значит его надо удалить и из нашей сцены
                delete i.second;
                to_remove.push_back(i.first);
            }
        }
        for (auto i : to_remove) {
            object_list.erase(i);
        }*/
    };
