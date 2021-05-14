#pragma once 

#include "Object.h"

void intToByte(int n, unsigned char* result) {

     result[0] = n & 0x000000ff;
     result[1] = n & 0x0000ff00 >> 8;
     result[2] = n & 0x00ff0000 >> 16;
     result[3] = n & 0xff000000 >> 24; 
}

int byteToInt(unsigned char* byte) {

    int n = 0;

    n = n + (byte[0] & 0x000000ff);
    n = n + ((byte[1] & 0x000000ff) << 8);
    n = n + ((byte[2] & 0x000000ff) << 16);
    n = n + ((byte[3] & 0x000000ff) << 24);


    return n;
}
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
        intToByte(object.health, answer + 8);
        intToByte(change, answer + 8);  

        return answer;
    }

    Post static dencrypt(unsigned char* message)
    {
        
        int id =  byteToInt(message); 
        int type =  byteToInt(message + 4);
        int x = byteToInt(message + 8);
        int y = byteToInt(message + 12);
        int health = byteToInt(message + 8);
        int change = byteToInt(message + 8);  

        return Post (id, change, Object(id, type, {x, y}, health));
    }
};