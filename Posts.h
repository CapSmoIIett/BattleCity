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
    
    //
    PostSC(int id, int change, Object obj, int dir = 0);

    //
    PostSC(unsigned char* message);

    //
    unsigned char* encrypt();

    //
    PostSC static dencrypt(unsigned char* message);
};

struct PostC
{
    int command;
    int direction;

    //
    PostC(int command, int direction = 0);

    //
    PostC(unsigned char* message);

    //
    unsigned char* encrypt();

    //
    PostC static dencrypt(unsigned char* message);
};