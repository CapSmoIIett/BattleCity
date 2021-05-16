#include "Posts.h"

void intToByte(int n, unsigned char* result) {

    result[0] = n % 256;
    n /= 256;
    result[1] = n % 256;
    n /= 256;
    result[2] = n % 256;
    n /= 256;
    result[3] = n % 256;
    n /= 256;
}

int byteToInt(unsigned char* byte) {

    int n = 0;

    n = n + (byte[0] & 0x000000ff);
    n = n + ((byte[1] & 0x000000ff) << 8);
    n = n + ((byte[2] & 0x000000ff) << 16);
    n = n + ((byte[3] & 0x000000ff) << 24);


    return n;
}