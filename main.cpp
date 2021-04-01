#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "AbstractScene.h"
#include "Object.h"
#include "DrawScene.h"


using namespace std;

int main() {

    // все подготовительные действия
    // минимальная длительность игрового цикла
    Time cycle_time = seconds(0.02);//0.02f);
    RenderWindow window(VideoMode(624, 624), "simple rts");
    AbstractScene abstract_scene;
    DrawScene draw_scene;

    Clock clock;
    Event event;
    while (window.isOpen()) 
    {
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
                window.close();
        }
        //пришлось дать знать рисующей сцене о абстрактной сцене. Это нужно, что бы получать х, y отображения этого объекта.

        draw_scene.synchronize(&abstract_scene); 
        window.clear();
        draw_scene.draw(window, &abstract_scene);
    
        window.display();
        //Time elapsed_time = clock.getElapsedTime() % cycle_time;
        //std::cout << "отрисовано за " << elapsed_time.asMilliseconds() << " миллисекунд\n";
        //sleep(cycle_time - elapsed_time);
    }

    

    return 0;
} 
