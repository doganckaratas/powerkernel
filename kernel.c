/**
### kernel.c 
### PowerKernel 0.2
### 2011 - 2017 -- Doğan Can Karataş
### Son Değişiklik - 02/2017
**/

#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "./lib/types.h"
#include "./lib/string.h"
#include "./lib/io.h"
#include "./lib/tty.h"

#if defined(__linux__)
#error "gnu capraz derleyici algilanmadi. sikinti olusabilir."
#endif
 
#if !defined(__i386__)
#error "i386-elf/i686-elf derleyici gereklidir."
#endif
 
#if defined(__cplusplus)
extern "C"
#endif


// FS KURDUKTAN SONRA FAT32 YADA BAŞKA BİR FS HEADER'INI EZMEDEN BOOTLOADER KAS.
// memory allocator şart

void kernel_main() 
{
	tty_init();
	setcolor(color_pair(LTRED,BLACK));
	printf("PowerKernel 0.2 Baslatiliyor.\n\n");
	setcolor(color_pair(LTGREEN,BLACK));
	putchar('>');
	setcolor(color_pair(LTGRAY,BLACK));
	printf("substring test\n");
	string u;
	printf(substring("substring test",4,5));
	printf(u);
}

// kernel tüm işlemleri yaptıktan somra frontend e handoff yapmalı
