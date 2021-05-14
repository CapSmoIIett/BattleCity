#include "Object.h"

struct Post
{
    int id;
    int change;

    Object object;
    

    Post(int id, int change, Object obj) :
    id(id),
    change(change),
    object(obj)
    {
        
    }

    void* encrypt(int& size)
    {
        unsigned char* answer = 0;

        // Нас интересует только:
        // id, Имя, Местоположение, Здоровье
        size = sizeof(int) + sizeof(object.data.type) +
            sizeof(Point) + sizeof(int);

        answer = new unsigned char[size];
        
        
        
    

        return (void*) answer;
    }
};