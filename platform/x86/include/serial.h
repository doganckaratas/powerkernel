/*
### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3
*/

#ifndef __SERIAL_H__
#define __SERIAL_H__

#define SER1 0x3F8
#define SER2 0x2F8
#define SER3 0x3E8
#define SER4 0x2E8

void serial_setup(uint16_t, uint16_t);
void serial_send_str(uint16_t, const char *);
void serial_send_char(uint16_t, const char);
inline int serial_send_available(uint16_t);

#endif /* __SERIAL_H__ */
