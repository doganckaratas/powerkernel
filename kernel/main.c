/**
 * @file   src/entry.c
 * @brief  entry point of kernel
 * @date   28/07/2018
 * @author Doğan Can Karataş
 */

#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "serial.h"
#include "string.h"

#if defined(__linux__)
#error "Error: Non-cross compiler used. Compiler target: linux"
#endif

#if !defined(__i386__)
#error "Error: your system target is not i386 (x86-32)"
#endif

#if defined(__cplusplus)
extern "C"
#endif

char *test_serial();

/**
 * @fn         void kernel_main()
 * @brief      main function of kernel
 * @return     halts cpu on return
 */
void kernel_main()
{
	serial_setup(ttyS0, 38400);
	serial_send(LRED"PowerKernel 0.3.240718"NORM"\r\n"
			"(c) 2011 - 2018 Dogan C. Karatas."
			" All Rights Reserved.\r\n");
	char *c;
	while (1) {
		c = test_serial();
		if (strncmp(c, "exit", 4) == 0) {
			serial_send("halt!\r\n");
			break;
		}
	}
}

char *test_serial()
{
	/* test for serial recv */
	serial_send(">> ");
	char k = 0;
	int i = 0;
	char *str;
	/* due to not having memory allocator, fixed addr used for str. */
	str = (char* ) 0x00010;
	memset(str, 0, 32);
	while (1) {
		serial_recv_char(&k);
		if (k == 8) {
			serial_send_char(8);
			continue;
		}

		if (k == 13) {
			break;
		}
		if (k < 32 || k > 122) {
			continue;
		}
		*(str + i) = k;
		/* echo back*/
		serial_send_char(k);
		i++;
		k = 0;
	}
	serial_send("\r\nReceived: %s\r\n", str);
	return str;
}
