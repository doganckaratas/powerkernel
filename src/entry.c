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

// ilerde her bir fonksiyona özel c dosyasi olmali, klasorler hiyerarsik olmali..
// bundled c dosyalari gereksiz.

void test_serial();

void kernel_main()
{
	serial_setup(ttyS0, 38400);
	serial_send(LRED"PowerKernel 0.3.240718"NORM"\r\n"
			"(c) 2011 - 2018 Dogan C. Karatas."
			" All Rights Reserved.\r\n");
	test_serial();
}

void test_serial()
{
	/* test for serial recv */
	char k = 0;
	int i = 0;
	char *str;
	/* due to not having memory allocator, fixed addr used for str. */
	str = (char* ) 0x00010;
	memset(str, 0, 32);
	while (1) {
		serial_recv_char(&k);
		if (k == 13) {
			break;
		}
		if (k < 32 || k > 122) {
			continue;
		}
		*(str + i) = k;
		i++;
		k = 0;
	}
	serial_send("Received: %s\r\n", str);
}


// kernel tum islemleri yaptiktan somra frontend e handoff yapmali
