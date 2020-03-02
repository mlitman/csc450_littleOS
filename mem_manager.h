int isMemAvailable(char* baseAddress, int size);

void markMemory(char* baseAddress, int size);

char* getMem(int numBytes);

void freeMem(char* baseAddress, int numBytes);

void unmarkAllMemory();
