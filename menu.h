#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
 using namespace sf;
 
 void menu(RenderWindow & window) {
	Texture bcTexture, menuTexture1, menuTexture2, menuTexture3;
	bcTexture.loadFromFile("battle-city.png");  // battle city
	menuTexture1.loadFromFile("Player1.png");   // 1 игрок
	menuTexture2.loadFromFile("Player2.png");   // 2 игрока
	menuTexture3.loadFromFile("EXIT.png");      // выход
	Sprite bc(bcTexture), menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3);
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
 
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu && (!Keyboard::isKeyPressed(Keyboard::Escape))) // оставлять esc?
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
			if (menuNum == 1 || menuNum == 2) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 3)  { window.close(); isMenu = false; }
 
		}
		
		window.draw(bc);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		
		window.display();
	}
}
