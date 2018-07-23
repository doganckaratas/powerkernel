/*
### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3
*/

#if 0

#ifndef __TTY_H__
#define __TTY_H__

enum vga_colors
{
	BLACK 		= 0,
	BLUE 		= 1,
	GREEN 		= 2,
	CYAN 		= 3,
	RED 		= 4,
	MAGENTA		= 5,
	BROWN 		= 6,
	GRAY 		= 8,
	LTGRAY 		= 7,
	LTBLUE 		= 9,
	LTGREEN		= 10,
	LTCYAN		= 11,
	LTRED 		= 12,
	LTMAGENTA 	= 13,
	LTBROWN 	= 14,
	WHITE 		= 15
};	


// [ AAAA BBBB CCCCC DDDD ]  -> framebuffer
// ( ==== ) -> video hardware memory
// first line selected
// [ {AAAA} BBBB CCCC DDDD ]
//     v
// ( AAAA ) -> to the video output
// second line selected
// [ A{AAA B}BBB CCCC DDDD ]
//      v
//  ( AAAB ) -> to the video output
// third line selected
// [ AA{AA BB}BB CCCC DDDD ]
//       v
// ( AABB ) -> to the video output
// ...

#define pair(c, color) (c | color << 8)
#define TAB 8

static const size_t WIDTH = 80; // default screen width
static const size_t HEIGHT = 25; // default screen height
char **buffer; // framebuffer with 4 page.
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* base_addr; // video hardware memory port

void tty_8025_init();
void tty_version();
void setcolor(uint8_t );
void printf(char*, ...);
void putchar(char );
void clear(void );

#endif /* __TTY_H__ */

#endif
