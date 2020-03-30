#include "string.h"
#include "frame_buffer.h"
#include "mem_manager.h"

void strcpy(char* dest, char* src, int length)
{
    for(int i = 0; i < length; i++)
    {
        dest[i] = src[i];
    }
    dest[length] = '\0';
}

int strlen(char* src)
{
    int pos = 0;
    while(src[pos] != '\0')
    {
        pos++;
    }
    return pos;
}

void strcat(char* dest, char* appendString)
{
    // dest: "helloworld\0" 
    // appendString "world\0"
    // "hello world\0"
    int startNewStringAt = strlen(dest);
    for(int i = 0; i < strlen(appendString); i++)
    {
        dest[startNewStringAt] = appendString[i];
        startNewStringAt++;
    }
    dest[startNewStringAt] = '\0';
}

void strshorten(char* src, int shortenAmount)
{
    if(strlen(src) >= shortenAmount)
    {
        src[strlen(src)-shortenAmount] = '\0';
    }
}

void strtok(char** dest, char* src)
{
    //figure out how many tokens are in src?
    //assuming each token is separated by a single space
    // "hello world elephant"

    int numberOfTokens = count_chars(src, ' ') + 1;
    char* s = getMem(numberOfTokens + 1);
    strcpy(s, "\0", 1);
    for(int i = 0; i < numberOfTokens; i++)
    {
        strcat(s, "?\0");
    }
    fb_clear();
    fb_write_string(0, s, strlen(s));
    /*
        HW: now that we have the number of tokens, ask for memory to
        store that many strings in dest, then fill those strings up 
        with the individual tokens.  Note that each token will need
        its own memory that a bucket in dest points to.

        "a by cat"
        dest = ["a", "by", "cat"]
        dest gets enough memory to hold 3 char* (ie strings)
        dest[0] gets enough memory to hold 1 char
        dest[1] gets enough memory to hold 2 chars
        dest[2] gets enough memory to hold 3 chars
    */ 

}

int count_chars(char* src, char search_char)
{
    int count = 0;
    for(int i = 0; i < strlen(src); i++)
    {
        if(src[i] == search_char)
        {
            count++;
        }
    }
    return count;
}