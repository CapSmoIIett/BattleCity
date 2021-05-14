#include "Posts.h"

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