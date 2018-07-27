/**
 * @file   x86/io.c
 * @brief  x86 platform IO functions
 * @date   28/07/2018
 * @author Doğan Can Karataş
 */

#include <stddef.h>
#include <stdint.h>
#include "io.h"
#include "serial.h"

/**
 * @fn         unsigned char in_byte(unsigned int port)
 * @brief      receives 1 byte from specified port.
 * @param[in]  port address for receiving data
 * @return     data that received from port
 */
unsigned char in_byte(unsigned int port)
{
   unsigned char ret;
   asm volatile ("inb al, dx":"=a" (ret):"d" (port));
   return ret;
}

/**
 * @fn         unsigned char out_byte(unsigned int port, unsigned char value)
 * @brief      sends 1 byte to specified port.
 * @param[in]  port address for sending data
 * @param[in]  value data that will be sent through port
 * @return     void
 */
void out_byte(unsigned int port,unsigned char value)
{
   asm volatile ("outb dx, al": :"d" (port), "a" (value));
}

/**
 * @fn         void dump_regs(void)
 * @brief      dumps register information
 * @return     void
 */
void dump_regs(void)
{
	struct Register regs;
	asm volatile ("mov %0, eax\nmov %1, ebx\nmov %2, ecx\nmov %3, edx\nmov %4, esi\nmov %5, edi\n"
			"mov %6, ebp\nmov %7, esp\ncall _ip\n_ip: pop %8\npushf\n pop %9\n" :
			"=m" (regs.eax), "=m" (regs.ebx), "=m" (regs.ecx), "=m" (regs.edx), "=m" (regs.esi),
			"=m" (regs.edi), "=m" (regs.ebp), "=m" (regs.esp), "=m" (regs.eip), "=m" (regs.efl)
			);

	serial_send("\r\n========================= Register Dump =========================\r\n"
			"EAX: 0x%x\tEBX: 0x%x\tECX: 0x%x\tEDX: 0x%x\r\n"
			"ESI: 0x%x\tEDI: 0x%x\tEBP: 0x%x\tESP: 0x%x\r\n"
			"EIP: 0x%x\tEFL: 0x%x",
			regs.eax, regs.ebx, regs.ecx, regs.edx,
			regs.esi, regs.edi, regs.ebp, regs.esp,
			regs.eip, regs.efl);
	serial_send("\r\n=================================================================\r\n");
}
