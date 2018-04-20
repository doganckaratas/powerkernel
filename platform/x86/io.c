/*
### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3
*/

#include <stddef.h>
#include <stdint.h>
#include "io.h"
#include "tty.h"

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
   asm volatile ("inb al, dx":"=a" (ret):"d" (port));
   return ret;
}

void outportb(unsigned int port,unsigned char value)
{
   asm volatile ("outb dx, al": :"d" (port), "a" (value));
}

void dump_regs(void)
{
	struct Register regs;
	asm volatile ("mov %0, eax\nmov %1, ebx\nmov %2, ecx\nmov %3, edx\nmov %4, esi\nmov %5, edi\n"
			"mov %6, ebp\nmov %7, esp\ncall _ip\n_ip: pop %8\npushf\n pop %9\n" :
			"=m" (regs.eax), "=m" (regs.ebx), "=m" (regs.ecx), "=m" (regs.edx), "=m" (regs.esi),
			"=m" (regs.edi), "=m" (regs.ebp), "=m" (regs.esp), "=m" (regs.eip), "=m" (regs.efl)
			);

	printf("\n===== Register Dump =====\n"
			"EAX: 0x%x\nEBX: 0x%x\nECX: 0x%x\nEDX: 0x%x\n"
			"ESI: 0x%x\nEDI: 0x%x\nEBP: 0x%x\nESP: 0x%x\n"
			"EIP: 0x%x\nEFL: 0x%x",
			regs.eax, regs.ebx, regs.ecx, regs.edx,
			regs.esi, regs.edi, regs.ebp, regs.esp,
			regs.eip, regs.efl);
	printf("\n=========================\n");
}
