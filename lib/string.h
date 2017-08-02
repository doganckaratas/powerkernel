/**
### string.h
### PowerKernel 0.2
### 2011 - 2017 -- Doğan Can Karataş
### Son Değişiklik - 02/2017
**/


#ifndef __STRING_H__
#define __STRING_H__

char* itoa(int, int);
size_t strlen(const string );
inline void strcpy(string, string );
void strtok(string, string[], char);
int strseek(string, char);
string substring(string, int, int);

#endif
#include "string.c"
