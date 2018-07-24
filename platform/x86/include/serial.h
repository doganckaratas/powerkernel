/*
### PowerKernel
### (c) 2011 - 2017
### Doğan Can Karataş -- v0.3
*/

#ifndef __SERIAL_H__
#define __SERIAL_H__

enum serial_base_addr {
	ttyS0=0x3F8,
	ttyS1=0x2F8,
	ttyS2=0x3E8,
	ttyS3=0x2E8
};

struct serial_port {
	enum serial_base_addr addr;
	uint16_t baud;
} tty1;

void serial_setup(enum serial_base_addr, uint16_t);
int serial_send_available();
void serial_send_str(const char *);
void serial_send_char(const char);
void serial_send(const char *fmt, ...);

#endif /* __SERIAL_H__ */
