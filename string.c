#include "string.h"

void strcpy(char* dest, char* src, int length)
{
    for(int i = 0; i < length; i++)
    {
        dest[i] = src[i];
    }
}