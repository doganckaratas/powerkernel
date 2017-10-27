/*
### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3
*/

#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "./include/x86/types.h"
#include "./include/x86/string.h"
#include "./include/x86/io.h"
#include "./include/x86/tty.h"

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

// ilerde her bir fonksiyona özel c dosyası olmalı, klasörler hiyerarşik olmalı..
// bundled c dosyaları gereksiz.

void kernel_main() 
{
	tty_8025_init();
	setcolor(pair(LTRED,BLACK));
	printf("PowerKernel 0.3 Baslatiliyor.\n");
	setcolor(pair(LTGRAY,BLACK));
	printf("(c) 2017 Dogan Can Karatas.\n\n");
	setcolor(pair(LTGREEN,BLACK));
	printf("%c",'>');
	setcolor(pair(LTGRAY,BLACK));
    printf("integer 0 to string  : \"%s\"\n",itoa(0,BASE_10));
    int k;
    for(k = 0;k<5;k++)
    {
        printf(" k = %d\n",k);
    }
    printf("Merhaba\t\t\t\t\t\t\t\t\tsafa \n");
}

// kernel tüm işlemleri yaptıktan somra frontend e handoff yapmalı
