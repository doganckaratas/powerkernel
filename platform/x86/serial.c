/*
### PowerKernel
### (c) 2011 - 2017
### Doğan Can Karataş -- v0.3
*/

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "types.h"
#include "string.h"
#include "io.h"
#include "serial.h"

/* Serial Mini-Info Sheet
0x3F8 = First Serial Port
0x2F8 = Second Serial Port
0x3E8 = Third Serial Port (May be different)
0x2E8 = Fourth Serial Port (May be different)

SBA = Serial Base Address
D   = Data
IE  = Interrupt Enable
TE  = Transmit Queue Empty
BE  = Break/Error
SC  = Status Change
BL  = Baud Rate LSB Bits
BH  = Baud Rate MSB Bits
DL  = Divisor Latch Address Bit
DB  = Data Bits   [00  = 5bit, 01  = 6bit, 10  = 7bit, 11  = 8bit]
SB  = Stop Bit    [0   = 1bit, 1   = 1,5/2 bit ]
PB  = Parity Bits [--0 = N/A, 001 = ODD,  011 = EVEN, 101 = MARK, 111 = SPC]
X   = Unused

        7  6  5  4  3  2  1  0
SBA+0 = D  D  D  D  D  D  D  D   Data Buffer          (DLAB 0)
SBA+1 = X  X  X  X  SC BE TE IE  Interrupt Enable Reg (DLAB 0)
SBA+0 = BL BL BL BL BL BL BL BL  LSB of Baud          (DLAB 1)
SBA+1 = BH BH BH BH BH BH BH BH  MSB of Baud          (DLAB 1)
SBA+2 = .  .  .  .  .  .  .  .   FIFO Control Reg
SBA+3 = DL .  PB PB PB SB DB DB  Line Control Reg
SBA+4 = .  .  .  .  .  .  .  .   Modem Control Reg
SBA+5 = .  .  .  .  .  .  .  .   Line Status Reg
SBA+6 = .  .  .  .  .  .  .  .   Modem Status Reg
SBA+7 = .  .  .  .  .  .  .  .   Scratch Reg
*/

#ifdef SERIAL_DEBUG
void serial_setup(uint16_t baud)
{
	outportb(SP + 1, 0x00); /* clear all ints */
	outportb(SP + 3, 0x80); /* enable DLAB */
	outportb(SP + 0, baud & 0xFF); /* lsb of baud */
	outportb(SP + 1, (baud >> 8) & 0xFF); /* msb of baud */
	outportb(SP + 3, 0x03); /* 8N1 setup */
	outportb(SP + 2, 0xC7); /* enable FIFO */
	outportb(SP + 4, 0x0B); /* IRQ bits set, Rts & dts set. */

	serial_send("stdin: %s\r\nstdout:%s\r\nstderr:%s\r\n",
		SERIAL_IO ? "serial" : "display",
		SERIAL_IO ? "serial" : "display",
		SERIAL_IO ? "serial" : "display");
}

int serial_send_available()
{
	return inportb(SP + 5) & 0x20;
}

void serial_send_char(const char c)
{
	if (serial_send_available()) {
		outportb(SP, c);
	}
}

void serial_send_str(const char *str)
{
	int i = 0;
	for (i = 0; i < (int) strlen(str); i++) {
		serial_send_char(*(str + i));
	}
}

void serial_send(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int d = 0;
	int x = 0;
	char c = '\0';
	char *s;
	while (*fmt != '\0') {
		if(*fmt == '%') {
			switch (*(fmt + 1)) {
				case 'd':
					d = va_arg(args, int);
					serial_send_str(itoa(d, BASE_10));
					break;
				case 'c':
					c = va_arg(args, char);
					serial_send_char(c);
					break;
				case 's':
					s = va_arg(args, char *);
					serial_send_str(s);
					break;
				case 'x':
					x = va_arg(args, int);
					serial_send_str(itoa(x, BASE_16));
					break;
				default:
					++fmt;
					break;
			}
			++fmt;
		} else {
			serial_send_char(*fmt);
		}
		++fmt;
	}
	va_end(args);
}
#else
void serial_setup(uint16_t sba, uint16_t baud)
{
	outportb(sba + 1, 0x00); /* clear all ints */
	outportb(sba + 3, 0x80); /* enable DLAB */
	outportb(sba + 0, baud & 0xFF); /* lsb of baud */
	outportb(sba + 1, (baud >> 8) & 0xFF); /* msb of baud */
	outportb(sba + 3, 0x03); /* 8N1 setup */
	outportb(sba + 2, 0xC7); /* enable FIFO */
	outportb(sba + 4, 0x0B); /* IRQ bits set, Rts & dts set. */
}

int serial_send_available(uint16_t sba)
{
	return inportb(sba + 5) & 0x20;
}

void serial_send_char(uint16_t sba, const char c)
{
	if (serial_send_available(sba)) {
		outportb(sba, c);
	}
}

void serial_send_str(uint16_t sba, const char *str)
{
	int i = 0;
	for (i = 0; i < (int) strlen(str); i++) {
		serial_send_char(sba, *(str + i));
	}
}

void serial_send(uint16_t sba, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int d = 0;
	char c = '\0';
	char *s;
	while (*fmt != '\0') {
		if(*fmt == '%') {
			switch (*(fmt + 1)) {
				case 'd':
					d = va_arg(args, int);
					serial_send_str(sba, itoa(d, BASE_10));
					break;
				case 'c':
					c = va_arg(args, char);
					serial_send_char(sba, c);
					break;
				case 's':
					s = va_arg(args, char *);
					serial_send_str(sba, s);
					break;
				default:
					++fmt;
					break;
			}
			++fmt;
		} else {
			serial_send_char(sba, *fmt);
		}
		++fmt;
	}
	va_end(args);
}
#endif /* SERIAL_DEBUG */

