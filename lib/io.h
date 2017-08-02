/**
### io.h
### PowerKernel 0.2
### 2011 - 2017 -- Doğan Can Karataş
### Son Değişiklik - 02/2017
**/


//  typedef string yap

#ifndef __IO_H__
#define __IO_H__

inline void memcpy(void *, void *, int );
inline int memcmp(void *, void *, int );
inline unsigned char inportb(unsigned int );
inline void outportb(unsigned int ,unsigned char );

#endif
#include "io.c"
