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
};

#define SER1 0x3F8
#define SER2 0x2F8
#define SER3 0x3E8
#define SER4 0x2E8

#if defined(SERIAL_1)
#define SP SER1
#elif defined(SERIAL_2)
#define SP SER2
#elif defined(SERIAL_3)
#define SP SER3
#elif defined(SERIAL_4)
#define SP SER4
#endif

#ifdef SERIAL_DEBUG
#define SERIAL_IO 1
/* switch output streams with respect to this flag */
void serial_setup(uint16_t);
int serial_send_available();
void serial_send_str(const char *);
void serial_send_char(const char);
void serial_send(const char *fmt, ...);
#else
#define SERIAL_IO 0
void serial_setup(uint16_t, uint16_t);
int serial_send_available(uint16_t);
void serial_send_str(uint16_t, const char *);
void serial_send_char(uint16_t, const char);
void serial_send(uint16_t, const char *, ...);
#endif /* SERIAL_DEBUG */

#endif /* __SERIAL_H__ */
