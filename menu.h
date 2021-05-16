#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include "DrawScene.h"
#include "Controller.h"
#include "AI.h"
 using namespace sf;
 
 int menu(RenderWindow & window) {
	int end = 0;
	Texture bcTexture, menuTexture1, menuTexture2, menuTexture3, tankTexture;
	bcTexture.loadFromFile("battle-city.png");  // battle city
	menuTexture1.loadFromFile("Player1.png");   // 1 игрок
	menuTexture2.loadFromFile("Player2.png");   // 2 игрока
	menuTexture3.loadFromFile("EXIT.png");      // выход
	tankTexture.loadFromFile("tank.png");      	// танк
	Sprite bc(bcTexture), menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), tank1(tankTexture), tank2(tankTexture);
	bool isMenu = 1;
	int menuNum = 0;
	bc.setPosition(100, 50);
	bc.scale(0.3, 0.3);
	menu1.setPosition(200, 330);
	menu1.scale(3, 3);
	menu2.setPosition(200, 380);
	menu2.scale(3, 3);
	menu3.setPosition(200, 440);
	menu3.scale(3, 3);
	tank1.setPosition(100, 250);
	tank1.scale(3, 3);
	tank2.setPosition(500, 500);
	tank2.scale(3, 3);
	tank2.rotate(180);
 
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(0, 0, 0)); // 129, 181, 221
 
		if (IntRect(200, 330, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(200, 380, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
		if (IntRect(200, 440, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Red); menuNum = 3; }
 
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { isMenu = false; end = 1;/**/}//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { isMenu = false; end = 2;/**/}//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 3) { window.close(); isMenu = false; }
 
		}
		
		window.draw(tank1);
		window.draw(tank2);
		window.draw(bc);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		
		window.display();
	}
	return end;
}

void player1(RenderWindow & window, Event event, Clock clock, Controller controller, ObjectScene scene, AIScene ai_scene, DrawScene draw_scene, Time cycle_time)
{
	while (window.isOpen()) 
        {
            while (window.pollEvent(event)) 
            {
                if (event.type == sf::Event::KeyPressed){
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up: {
                        controller.setUp();
                        break;
                    }
                    case sf::Keyboard::Down: {
                        controller.setDown();
                        break;
                    }
                    case sf::Keyboard::Left: {
                        controller.setLeft();
                        break;
                    }
                    case sf::Keyboard::Right: {
                        controller.setRight();
                        break;
                    }
                    }
                }

                else if (event.type == sf::Event::KeyReleased){
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:  {
                        controller.stop(UP);
                        break;
                    }
                    case sf::Keyboard::Down: {
                        controller.stop(DOWN);
                        break;
                    }
                    case sf::Keyboard::Left: {
                        controller.stop(LEFT);
                        break;
                    }
                    case sf::Keyboard::Right: {
                        controller.stop(RIGHT);
                        break;
                    }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Space)){ controller.shoot(&scene);    }
                
                if (Keyboard::isKeyPressed(Keyboard::Q))    { window.close();       };
                if (event.type == Event::Closed)
                    window.close();
            }
            

            controller.manageTank(&scene);

            ai_scene.synchronize(&scene);
            ai_scene.setCommands(&scene);
            ai_scene.manageAllAITanks(&scene);
            scene.handleTickAll();
            scene.clearDead();
            draw_scene.synchronize(&scene); 
            window.clear();    
            draw_scene.draw(window, &scene);
        
            window.display();
            Time elapsed_time = clock.getElapsedTime() % cycle_time;
            sleep(cycle_time - elapsed_time);
        }
}

void player2(RenderWindow & window, Event event, Clock clock, Controller controller, Controller controller2, ObjectScene scene, AIScene ai_scene, DrawScene draw_scene, Time cycle_time)
{
	while (window.isOpen()) 
        {
            while (window.pollEvent(event)) 
            {
                /**/
                if (event.type == sf::Event::KeyPressed){
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up: {
                        controller.setUp();
                        break;
                    }
                    case sf::Keyboard::Down: {
                        controller.setDown();
                        break;
                    }
                    case sf::Keyboard::Left: {
                        controller.setLeft();
                        break;
                    }
                    case sf::Keyboard::Right: {
                        controller.setRight();
                        break;
                    }
                    case sf::Keyboard::W: {
                        controller2.setUp();
                        break;
                    }
                    case sf::Keyboard::A: {
                        controller2.setLeft();
                        break;
                    }
                    case sf::Keyboard::S: {
                        controller2.setDown();
                        break;
                    }
                    case sf::Keyboard::D: {
                        controller2.setRight();
                        break;
                    }
                    }
                }


                else if (event.type == sf::Event::KeyReleased){
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:  {
                        controller.stop(UP);
                        break;
                    }
                    case sf::Keyboard::Down: {
                        controller.stop(DOWN);
                        break;
                    }
                    case sf::Keyboard::Left: {
                        controller.stop(LEFT);
                        break;
                    }
                    case sf::Keyboard::Right: {
                        controller.stop(RIGHT);
                        break;
                    }
                    case sf::Keyboard::W: {
                        controller2.stop(UP);
                        break;
                    }
                    case sf::Keyboard::A: {
                        controller2.stop(RIGHT);
                        break;
                    }
                    case sf::Keyboard::S: {
                        controller2.stop(DOWN);
                        break;
                    }
                    case sf::Keyboard::D: {
                        controller2.stop(RIGHT);
                        break;
                    }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Space)){ controller.shoot(&scene);    }
                
                if (Keyboard::isKeyPressed(Keyboard::Tab))  { controller2.shoot(&scene);    }

                if (Keyboard::isKeyPressed(Keyboard::Q))    { window.close();       };
                if (event.type == Event::Closed)
                    window.close();
            }
            

            controller.manageTank(&scene);/* */
            controller2.manageTank(&scene);

            ai_scene.synchronize(&scene);
            ai_scene.setCommands(&scene);
            ai_scene.manageAllAITanks(&scene);
            scene.handleTickAll();
            scene.clearDead();
            draw_scene.synchronize(&scene); 
            window.clear();     // window.clear(sf::Color(34,15,6));
            draw_scene.draw(window, &scene);
        
            window.display();
            Time elapsed_time = clock.getElapsedTime() % cycle_time;
            //std::cout << "отрисовано за " << elapsed_time.asMilliseconds() << " миллисекунд\n";
            sleep(cycle_time - elapsed_time);
        }
}