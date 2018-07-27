/**
 * @file   src/include/string.h
 * @brief  generic string definitions
 * @date   28/07/2018
 * @author Doğan Can Karataş
 */

#ifndef __STRING_H__
#define __STRING_H__

/**
 * @brief number base (radix) definitions for integer parsing
 */
enum radix{
	BASE_2 = 2,
	BASE_10 = 10,
	BASE_16 = 16
};

void memset(void*, int, size_t);
void memcpy(void *, void *, size_t );
int memcmp(void *, void *, size_t );
char* itoa(int, int);
size_t strlen(const char*);
void strcpy(char*, char*);
void strtok(char*, char*[], char);
int strseek(char*, char);

#endif /* __STRING_H__ */
