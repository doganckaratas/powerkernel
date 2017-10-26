/*
### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3
*/

#include <stddef.h>
#include <stdint.h>
#include <io.h>

void memset(void *dest, int data, size_t size) 
{
	char* dst=(char*) dest;
	for(;size;size--,dst++)
		*dst=data;
}

void memcpy(void *dest, void *src, size_t size)
{
   char *dst=dest;
   for (;size;size--,dest++,src++)
        *dst=*((char*)src);
}

int memcmp(void *dest, void *source, size_t size)
{
	char *dst = dest, *src = source;
	for(size_t i = 0; i < size; i++)
	{
		if(dst[i] == src[i])
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

unsigned char inportb(unsigned int port)
{
   unsigned char ret;
   asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
   return ret;
}

void outportb(unsigned int port,unsigned char value)
{
   asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
}

