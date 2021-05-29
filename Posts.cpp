#include "Posts.h"

void intToByte(int n, unsigned char* result) {

    int flag = 0;

    if (n < 0)                  // Если меньше нуля
    {
        flag = 1;
        n *= -1;
    }

    result[3] = n % 256;
    n /= 256;
    result[2] = n % 256;
    n /= 256;
    result[1] = n % 256;
    n /= 256;
    result[0] = n % 256;
    n /= 256;

     if (flag)                   // Если меньше нуля
        result[0] |= 1 << 7;    // Сохраняем в 8-ом биту знак
    else 
        result[0] &= ~(1 << 7);
}

int byteToInt(unsigned char* byte) {

    int n = 0;
    int flag = 0;

    if (byte[0] >> 7 & 1)       // Если число отрицательно
    {
        byte[0] &= ~(1 << 7);
        flag = 1;
    }

    n = n + (byte[3] & 0x000000ff);
    n = n + ((byte[2] & 0x000000ff) << 8);
    n = n + ((byte[1] & 0x000000ff) << 16);
    n = n + ((byte[0] & 0x000000ff) << 24);

    if (flag)
        n *= -1;

    return n;
}

PostSC::PostSC(int id, int change, Object obj, int dir) :
id(id),
change(change),
type(obj.type),
point(obj.get_point()),
direction(dir)
{
        
}

PostSC::PostSC(unsigned char* message) :
id(byteToInt(message)),
change(byteToInt(message + 16)),
type(byteToInt(message + 4)),
point({byteToInt(message + 8),
byteToInt(message + 12)}),
direction(byteToInt(message + 20))    
{
    
}

unsigned char* PostSC::encrypt()
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

PostSC PostSC::dencrypt(unsigned char* message)
{
        
    int id =  byteToInt(message); 
    int type =  byteToInt(message + 4);
    int x = byteToInt(message + 8);
    int y = byteToInt(message + 12);
    int change = byteToInt(message + 16); 
    int direction = byteToInt(message + 20); 

    return PostSC (id, change, Object(id, type, {x, y}), direction);
}




PostC::PostC(int command, int dir) :
command(command),
direction(dir)
{

}

PostC::PostC(unsigned char* message) :
command(byteToInt(message)),
direction(byteToInt(message + 4))
{

}

unsigned char* PostC::encrypt()
{
    unsigned char* answer = new unsigned char[POST_C_SIZE];
        
    intToByte(command, answer);
    intToByte(direction, answer + 4);

    return answer;
}

PostC PostC::dencrypt(unsigned char* message)
{
    return PostC(byteToInt(message), byteToInt(message + 4));
}