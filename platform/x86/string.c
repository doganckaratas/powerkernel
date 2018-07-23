/*
### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3
*/

#include <stddef.h>
#include <stdint.h>
#include "string.h"

size_t strlen(const char* str) 
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

void strcpy(char* dst, char* src)
{
	for(int i = 0; i < (int) strlen(dst); i++)
	{
		dst[i] = '\0';
	}
	
	for(int i = 0; i < (int)strlen(src); i++)
	{
		dst[i] = src[i];
	}
}

int strseek(char* str, char delimiter) // delimiter sayısı döndürür
{
	int count = 0;
	for(int i = 0; i < (int) strlen(str); i++)
	{
		if(str[i] == delimiter)
		{
			count++;
		}
		else
		{
			continue;
		}
	}
	return count;
}

/**

// STRTOKU DÜZELT, PRİNTF İÇİN FORMAT SPECİFİER TOKENİZE ET, VARİADİC FONK HALİNE GETİR.

void strtok(string str, string *dest, char delimiter) // delimiter karakter ile string ayırma
{
	int count = strseek(str,delimiter);	
	string buffer[count + 1];
	int current = 0;
	for(int i = 0; i < (int) strlen(str); i++)
	{
		if(str[i] == delimiter)
		{
			current += 1;
		}
		else
		{
			buffer[i][current] = str[i];
		}
	}
	for(int i = 0; i < count + 1; i++)
	{	
		dest[i] = buffer[i];
		
	}
}
*/


char* itoa(int val, int base) // val == 0 workaround'u acil degismeli.
{
	if (val == 0) // quick workaround FIXME
		return "0";
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return (char* ) &buf[i+1];
}
