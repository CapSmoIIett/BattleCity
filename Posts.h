#pragma once 

#include "Object.h"


void intToByte(int n, unsigned char* result);
int byteToInt(unsigned char* byte);

struct PostSC
{
    int id;
    int change;
    Point point;
    int type;
    int direction;

    /*
        для Create - id, point, type
        для Delete - id
        для Move   - id, point
        для Turn   - id, type, diretory
    */

    // Нас интересует только:
    // id, Имя, Местоположение, Здоровь, change
    // size = sizeof(int) + sizeof(object.type) +
    
    void set_dir(int dir)
    {
        direction = dir;
    }
    
    PostSC(int id, int change, Object obj, int dir = 0) :
    id(id),
    change(change),
    type(obj.type),
    point(obj.get_point()),
    direction(dir)
    {
        
    }

    PostSC(unsigned char* message) :
    id(byteToInt(message)),
    change(byteToInt(message + 16)),
    type(byteToInt(message + 4)),
    point({byteToInt(message + 8),
    byteToInt(message + 12)}),
    direction(byteToInt(message + 20))    
    {
    
    }

    unsigned char* encrypt()
    {
        unsigned char* answer = new unsigned char[POST_SC_SIZE];
        
        intToByte(id, answer);
        intToByte(type, answer + 4);
        intToByte(point.x, answer + 8);
        intToByte(point.y, answer + 12);
        intToByte(change, answer + 16); 
        intToByte(direction, answer + 20); 

        return answer;
    }

    PostSC static dencrypt(unsigned char* message)
    {
        
        int id =  byteToInt(message); 
        int type =  byteToInt(message + 4);
        int x = byteToInt(message + 8);
        int y = byteToInt(message + 12);
        int change = byteToInt(message + 16); 
        int direction = byteToInt(message + 20); 

        return PostSC (id, change, Object(id, type, {x, y}), direction);
    }
};

