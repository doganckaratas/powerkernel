/*
### PowerKernel 
### 2011 - 2017 -- Doğan Can Karataş
### Son Değişiklik - 08/2017 - v0rev3
*/

//  typedef string yap

#ifndef __IO_H__
#define __IO_H__

void memset(void*, int, size_t);
void memcpy(void *, void *, size_t );
int memcmp(void *, void *, size_t );
unsigned char inportb(unsigned int );
void outportb(unsigned int ,unsigned char );

#endif
