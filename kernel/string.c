/**
 * @file   src/string.c
 * @brief  generic string functions
 * @date   28/07/2018
 * @author Doğan Can Karataş
 */

#include <stddef.h>
#include <stdint.h>
#include "string.h"

/**
 * @fn         void memset(void *dest, int data, size_t size)
 * @brief      fills memory area with data, from dest with length of size
 * @param[out] dest destination buffer
 * @param[in]  data data to be filled
 * @param[in]  size fill length
 * @return     void
 */
void memset(void *dest, int data, size_t size)
{
	char* dst = (char*) dest;
	for ( ; size ; size--, dst++)
		*dst = data;
}

/**
 * @fn         void memcpy(void *dest, void *src, size_t size)
 * @brief      copies memory area to dest from src with length of size
 * @param[out] dest destination buffer
 * @param[in]  src target buffer
 * @param[in]  size copy length
 * @return     void
 */
void memcpy(void *dst, void *src, size_t size)
{
// 	for ( ; size ; size--, ((uint8_t *) dst)++, ((uint8_t *) src)++) {
// 		*((uint8_t *) dst) = *((uint8_t *) src);
// 	}

	for (; size; size--) {
		*((uint8_t *) dst) = *((uint8_t *) src);
		dst = (uint8_t *) dst + 1;
		src = (uint8_t *) src + 1;
	}
}

/**
 * @fn         void memcmp(void *dest, void *src, size_t size)
 * @brief      copies memory area to dest from src with length of size
 * @param[out] dest destination buffer
 * @param[in]  src target buffer
 * @param[in]  size copy length
 * @return     void
 */
int memcmp(void *dst, void *src, size_t size)
{
	char *buf1 = dst, *buf2 = src;
	for(size_t i = 0; i < size; i++)
	{
		if(buf1[i] == buf2[i])
		{
			continue;
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

/**
 * @fn         size_t strlen(const char *str)
 * @brief      returns the size of zero terminated buffer
 * @param[in]  str buffer
 * @return     size of buffer
 */
size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

/**
 * @fn         void strcpy(char *dst, char *src)
 * @brief      copies from src to dst until NULL
 * @param[out] dst destination string
 * @param[in]  src source string
 * @return     void
 */
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

/**
 * @fn         int strseek(char *str, char *delimiter)
 * @brief      returns the number of occurences of delimiter in string
 * @param[in]  str input string
 * @param[in]  delimiter char to be counted
 * @return     number of occurences of delimiter
 */
int strseek(char* str, char delimiter)
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

/**
 * @fn         char* itoa(int val, int base)
 * @brief      converts integer value to string with respect of number base
 * @param[in]  val value to be converted to string
 * @param[in]  base number base of val
 * @return     string representation of val
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
