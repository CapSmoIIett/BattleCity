#pragma once 

#include "Object.h"


void intToByte(int n, unsigned char* result);
int byteToInt(unsigned char* byte);

struct Post
{
    int id;
    int change;

    // Нас интересует только:
    // id, Имя, Местоположение, Здоровь, change
    // size = sizeof(int) + sizeof(object.type) +
    //     sizeof(Point) + sizeof(int) + sizeof(int);
    static const int size = 24;

    Object object;
    
    Post(int id, int change, Object obj) :
    id(id),
    change(change),
    object(obj)
    {
        
    }

    Post(unsigned char* message) :
    id(byteToInt(message)),
    change(byteToInt(message + 20)),
    object(byteToInt(message), byteToInt(message + 4), 
    {byteToInt(message + 8), byteToInt(message + 12)}, byteToInt(message + 16))
    {
    
    }

    unsigned char* encrypt()
    {
        unsigned char* answer = new unsigned char[size];
        
        intToByte(object.id, answer);
        intToByte(object.type, answer + 4);
        intToByte(object.get_point().x, answer + 8);
        intToByte(object.get_point().y, answer + 12);
        intToByte(object.health, answer + 16);
        intToByte(change, answer + 20);  

        return answer;
    }

    Post static dencrypt(unsigned char* message)
    {
        
        int id =  byteToInt(message); 
        int type =  byteToInt(message + 4);
        int x = byteToInt(message + 8);
        int y = byteToInt(message + 12);
        int health = byteToInt(message + 16);
        int change = byteToInt(message + 20);  

        return Post (id, change, Object(id, type, {x, y}, health));
    }
};

