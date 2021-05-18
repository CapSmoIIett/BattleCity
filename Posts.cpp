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