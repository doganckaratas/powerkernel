/**
### io.c 
### PowerKernel 0.2
### 2011 - 2017 -- Doğan Can Karataş
### Son Değişiklik - 02/2017
**/


inline void memcpy(void *dest, void *src, int n)
{
   char *dst=dest;
   for (;n;n--,dest++,src++)
        *dst=*((char*)src);
}

inline int memcmp(void *dest, void *source, int size)
{
	char *dst = dest, *src = source;
	for(int i = 0; i < size; i++)
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

inline unsigned char inportb(unsigned int port)
{
   unsigned char ret;
   asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
   return ret;
}

inline void outportb(unsigned int port,unsigned char value)
{
   asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
}

