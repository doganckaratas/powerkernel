/*
### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3
*/

//  typedef string yap

#ifndef __IO_H__
#define __IO_H__

void memset(void*, int, size_t);
void memcpy(void *, void *, size_t );
int memcmp(void *, void *, size_t );
unsigned char inportb(unsigned int );
void outportb(unsigned int ,unsigned char );

struct Register {
	int eax;
	int ebx;
	int ecx;
	int edx;
	int esi;
	int edi;
	int ebp;
	int esp;
	int eip;
	int efl;
};

void dump_regs(void);
#endif
