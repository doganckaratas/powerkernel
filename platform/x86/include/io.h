/**
 * @file   x86/include/io.h
 * @brief  x86 platform IO definitions
 * @date   28/07/2018
 * @author Doğan Can Karataş
 */

#ifndef __IO_H__
#define __IO_H__

uint8_t in_byte(unsigned int);
uint16_t in_word(unsigned int);
void out_byte(unsigned int, uint8_t);
void out_word(unsigned int, uint16_t);
void dump_regs(void);

/**
 * @brief register structure for x86
 */
struct Register {
	int eax;
	int ebx;
	int ecx;
	int edx;
	int esi;
	int edi;
	int ebp;
	int esp;
	int eip;
	int efl;
};

#endif /* __IO_H__ */
