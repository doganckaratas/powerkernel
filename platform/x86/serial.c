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

#if defined(SERIAL_1)
#define SP SER1
#elif defined(SERIAL_2)
#define SP SER2
#elif defined(SERIAL_3)
#define SP SER3
#elif defined(SERIAL_4)
#define SP SER4
#endif

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

#ifdef SERIAL_DEBUG
void serial_send_str(const char *str)
{
	int i = 0;
	for (i = 0; i < (int) strlen(str); i++) {
		serial_send_char(SP, *(str + i));
	}
}
#else
void serial_send_str(uint16_t sba, const char *str)
{
	int i = 0;
	for (i = 0; i < (int) strlen(str); i++) {
		serial_send_char(sba, *(str + i));
	}
}
#endif /* SERIAL_DEBUG */

