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
#include "serial.h"
#include "string.h"
#include "io.h"

#if defined(__linux__)
#error "You are using non-cross targeting GCC compiler. There may be some issues."
#endif

#if !defined(__i386__)
#error "GCC is not targeting i386. Please use ix86-elf toolchain."
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
	serial_setup(ttyS0, 38400);
	serial_send(LRED"PowerKernel 0.3.240718"NORM"\r\n"
			"(c) 2011 - 2018 Dogan C. Karatas."
			" All Rights Reserved.\r\n");
	asm ("mov eax, 48" : : );
	asm ("mov ebx, 23" : : );
	dump_regs();
}

// kernel tüm işlemleri yaptıktan somra frontend e handoff yapmalı
