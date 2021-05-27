 #include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
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
