#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "Object.h"
#include "ObjectScene.h"
#include "DrawScene.h"
#include "Controller.h"
#include "AI.h"
#include "menu.h"

using namespace std;

int main() {

    ObjectScene scene;
    fstream file("levels/1.txt");
    scene.loadMap(file);
    file.close();
    
    AIScene ai_scene(&scene, 10);

    Time cycle_time = seconds(0.02);//0.02f);
    RenderWindow window(VideoMode(624, 624), "BattleCity");
    DrawScene draw_scene;


    Controller controller;
    Controller controller2;
    controller.setStartXY(16 * 3 * 8, 24 * 3 * 8);
    controller2.setStartXY(8 * 3 * 8, 24 * 3 * 8);
    draw_scene.synchronize(&scene);/**/

    Clock clock;
    Event event;

    
    switch (menu(window))
    {
        case 1: player1(window, event, clock, controller, scene, ai_scene, draw_scene, cycle_time);
        break;

        case 2: player2(window, event, clock, controller, controller2, scene, ai_scene, draw_scene, cycle_time);
        break;

        default: break;
    }

    return 0;
} 