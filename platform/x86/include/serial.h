/*
### PowerKernel
### (c) 2011 - 2017
### Doğan Can Karataş -- v0.3
*/

#ifndef __SERIAL_H__
#define __SERIAL_H__

#define	NORM	"\033[0m"
#define	BLACK	"\033[30m"
#define	RED	"\033[31m"
#define	GREEN	"\033[32m"
#define	ORANGE	"\033[33m"
#define	BLUE	"\033[34m"
#define	PURPLE	"\033[35m"
#define	CYAN	"\033[36m"
#define	LGRAY	"\033[37m"
#define	DGRAY	"\033[30;1m"
#define	LRED	"\033[31;1m"
#define	LGREEN	"\033[32;1m"
#define	YELLOW	"\033[33;1m"
#define	LBLUE	"\033[34;1m"
#define	LPURPLE	"\033[35;1m"
#define	LCYAN	"\033[36;1m"
#define	WHITE	"\033[37;1m"

enum serial_base_addr {
	ttyS0=0x3F8,
	ttyS1=0x2F8,
	ttyS2=0x3E8,
	ttyS3=0x2E8
};

struct serial_port {
	enum serial_base_addr addr;
	uint16_t baud;
} tty1; /* there is only 1 tty device atm */


inline char* serial_addr_to_name(enum serial_base_addr sba);
void serial_setup(enum serial_base_addr, uint16_t);
int serial_send_available();
void serial_send_str(const char *);
void serial_send_char(const char);
void serial_send(const char *fmt, ...);

#endif /* __SERIAL_H__ */
