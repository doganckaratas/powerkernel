/*
### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3
*/

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <types.h>
#include <string.h>
#include <tty.h>

// soft buffer kullan ve base address e flush et, böyle çok unstable

uint8_t color_pair(enum vga_colors fg, enum vga_colors bg) // fore ve back renklerinden tek parça pair yarat
{
	return fg | bg << 4;
}
 
uint16_t colored_char(char c, uint8_t color) // 2 byte vga renkli text karakter çifti yarat
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

void clear() // ekranı null basar
{
	for(uint16_t i = 0; i < WIDTH * HEIGHT * 2 ; i++)
	{
		putchar('\0');
	}
}

void tty_8025_init() // text mode 80x25 init
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = color_pair(WHITE, BLACK);
	base_addr = (uint16_t*) 0xB8000;	// video ram base addr
	for (size_t y = 0; y < HEIGHT; y++) 
	{
		for (size_t x = 0; x < WIDTH; x++) 
		{
			const size_t i = y * WIDTH + x;
			base_addr[i] = colored_char(' ', terminal_color);
		}
	}
}
 
void setcolor(uint8_t color) //farklı renkler seçer putchar ve printf için
{
	terminal_color = color;
}
 
void putchar_color_coord(char c, uint8_t color, size_t x, size_t y) // explicit çağırma
{
	const size_t i = y * WIDTH + x;
	base_addr[i] = colored_char(c, color);
}

void putchar(char c) 
{
	putchar_color_coord(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == WIDTH) 
	{
		terminal_column = 0;
		if (++terminal_row == HEIGHT)
		{
			terminal_row = 0;
		}
	}
}

void printf(char* str, ...) // variadic printf template | dogan can karatas 08/2017
{
	//va_list args; // variadic fonksiyon
	// str'yi parse et, if else anahtarlarıyla kaç argüman olduğunu çıkar = count
	// va_start(args,count) 
	// sonra her bir argüman için if else'ler ile tiplere göre char print yap
	// va_end(args) ile bitir.
	int i;
	//float f; //bunları ilerde implement edicem, ayrıca /t, /a gibi escapeleri de eklicem
	//double d;
	char ch;
	char* s;
	char* buffer;
	va_list args;
	va_start(args,str);
	
	for (size_t id = 0; id < strlen(str); id++)
	{
		if(str[id] != '%') {
			switch(str[id]) {
				case '\n':
					terminal_row +=1;
					terminal_column = 0;
					break;
				default:
					putchar(str[id]);
					break;
			}
		} else {
			switch(str[id+1]) {
				case 'd':
					i = va_arg(args, int);
					buffer = itoa(i,10);
					for(size_t j = 0; j < strlen(buffer); j++)
						putchar(buffer[j]);
					id++;
					break;
				case 'c':
					ch = (char) va_arg(args,int);
					putchar(ch);
					id++;
					break;
				case 's':
					s = va_arg(args,char*);
					for(size_t j = 0; j < strlen(s); j++) 
						putchar(s[j]);
					id++;
					break;		
			}
		}
	}
	va_end(args);
}

/**
void printf (const char *format, ...)
{
	char **arg = (char **) &format;
    int c;
    char* buf;
    arg++;
    
    while ((c = *format++) != 0)
    {
		if (c != '%')
		{
			switch(c) // escape sequence ları yakala
			{
				case '\n': //newline
					terminal_row += 1;
					terminal_column = 0;
					break;
				default:
					putchar(c);
					break;
			}				
		}
        else
        {
			char *p;
            c = *format++;
            switch (c)
            {
				case 'd':
					buf = itoa (*((int *) arg++), 10);
					p = buf;
					goto string;
					break;
                case 'u':
                case 'x':
					
                case 's':
					p = *arg++;
						if (! p)
							p = "(null)";
					string:
					while (*p)
						putchar (*p++);
					break;
				default:
					putchar (*((int *) arg++));
					break;
            }
        }
    }
}

**/
