#include "mem_manager.h"

char* dataMarkStart = (char*) 0x00200000;
char* dataMarkEnd = (char*) 0x010FF7FE;
char* dataRealStart = (char*) 0x010FF7FF;
char* dataRealEnd = (char*) 0x01FFEFFE;

int isMemAvailable(char* baseAddress, int size)
{
    for(char* c = baseAddress; c < (baseAddress+size); c++)
    {
        if(*c == 1)
        {
            return 0; //this base address won't work out
        }
    }
    return 1; //this base address will work
}

void markMemory(char* baseAddress, int size)
{
    for(char* c = baseAddress; c < baseAddress + size; c++)
    {
        *c = 1;
    }
}

char* getMem(int numBytes)
{
    //How much do I have to add to my found memory in first half to get 
    //corresponding memory in second half.
   int dataMapOffset = (int)dataRealStart - (int)dataMarkStart;
   for(char* c = dataMarkStart; c <= dataMarkEnd; c++)
   {
       if(*c == 0)
       {
           if(isMemAvailable(c, numBytes))
           {
               markMemory(c, numBytes); //mark the memory as not available
               return c + dataMapOffset;
           }
       }
   }
   return 0x0; //didn't find available memory
}

void freeMem(char* baseAddress, int numBytes)
{
    for(int i = 0; i < numBytes; i++)
    {
        *(baseAddress + i) = 0;
    }
}

void unmarkAllMemory()
{
    for(char* c = dataMarkStart; c <= dataMarkEnd; c++)
    {
        *c = 0;
    }
}
