 #include "Controller.h"


Controller::Controller() : 
tank_id(-1), 
health(3),
direct(UP),
start_x(0),
start_y(0) { 
    ride = 0;
}

Controller::~Controller() {

}
void Controller::setStartXY(int x, int y) {
    start_x = x;
    start_y = y;
}
      
void Controller::setUp() {
    direct = UP;
    ride = 1;
}
void Controller::setDown() {
    direct = DOWN;
    ride = 1;
}
void Controller::setLeft() {
    direct = LEFT;
    ride = 1;
}
void Controller::setRight() {
    direct = RIGHT;
    ride = 1;
}

void Controller::stop(int direction) {
    if (direct == direction)        // Что бы при изменнении направления танк не останавливался
        ride = 0;
}

void Controller::shoot(ObjectScene *scene) {
    scene->createBullet(tank_id);
}

void final(RenderWindow & window)
{
    Texture bcTexture, menuTexture3, endTexture, tankTexture;
	bcTexture.loadFromFile("battle-city.png");  // battle city
	menuTexture3.loadFromFile("EXIT.png");      // выход
    endTexture.loadFromFile("end.png");         // 
    tankTexture.loadFromFile("tank.png");      	// танк
	Sprite bc(bcTexture), menu3(menuTexture3), end(endTexture), tank1(tankTexture), tank2(tankTexture);
	bool isMenu = 1;
	int menuNum = 0;
	bc.setPosition(100, 50);
	bc.scale(0.3, 0.3);
    menu3.setPosition(260, 440);
	menu3.scale(3, 3);
    end.setPosition(210, 250);
	end.scale(0.3, 0.3);
    tank1.setPosition(100, 250);
	tank1.scale(3, 3);
	tank2.setPosition(500, 500);
	tank2.scale(3, 3);
	tank2.rotate(180);
 
	/////////////////////////////////////////////////
	while (isMenu)
	{
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(0, 0, 0)); // 129, 181, 221
 
		if (IntRect(200, 440, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Red); menuNum = 3; }
 
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 3) { window.close(); isMenu = false; } 
		}
	
        window.draw(tank1);
		window.draw(tank2);
		window.draw(bc);
        window.draw(end);
		window.draw(menu3);
		
		window.display();
	}
}

void Controller::manageTank(ObjectScene *scene, RenderWindow & window) {
    if (scene->map_objects.find(tank_id) != scene->map_objects.end()) {
        Tank *abstr_tank = dynamic_cast<Tank *>(scene->map_objects[tank_id]);
                    
        if (ride) {
            abstr_tank->set_dir(direct);// теперь устанавливаем направление, такое, как нашей переменной.
            scene->map_objects[tank_id]->set_speed(3);
        } 
        else { 
            scene->map_objects[tank_id]->set_speed(0); //останавливаем танк
        }
    } 

    else { //танк был убит!
        health--;
        if(health >= 0 ) 
        {
            std::cout << "Танк игрока был возрождён, осталось жизней: " << health << "\n";
            this->tank_id = scene->addObject(start_x, start_y, PLAYER_TANK);
            ride = 0; //пусть стоит на старте
        }       
        else
        {   Time t1 = seconds(1);
            sleep(t1);
            final(window);
        }
    }
}  
        