/*
### PowerKernel 
### 2011 - 2017 -- Doğan Can Karataş
### Son Değişiklik - 08/2017 - v0rev3
*/

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

static const size_t WIDTH = 80;
static const size_t HEIGHT = 25;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* base_addr;

uint8_t color_pair(enum vga_colors, enum vga_colors );
uint16_t colored_char(char , uint8_t );
void tty_8025_init();
void setcolor(uint8_t );
void putchar_at(char, uint8_t , size_t , size_t );
void printf(char*, ...);
void putchar(char );
void clear(void );

#endif
