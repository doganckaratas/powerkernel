/*
### PowerKernel
### (c) 2011 - 2017
### Doğan Can Karataş -- v0.3
*/
#if 0 /* we do not need video teletype for now */

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "types.h"
#include "string.h"
#include "tty.h"

#ifdef SERIAL_DEBUG
#define SERIAL_IO 1
#else
#define SERIAL_IO 0
#endif /* SERIAL_DEBUG */

#if 0
static void write_framebuffer(char** );
static void clear_page(char** );
static void putchar_color_coord(char , size_t , size_t );
static char** select_page(char** , int );
#endif

// soft buffer kullan ve base address e flush et, böyle çok unstable

void tty_8025_init() // text mode 80x25 init
{
	char newbuf[WIDTH][HEIGHT*4];
	buffer = (char**) newbuf;
#if 0
	char** page;
#endif
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = pair(WHITE, BLACK);
	base_addr = (uint16_t*) 0xB8000;	// video ram base addr
#if 0
	buffer[16][16] = pair('A', terminal_color);
	page = select_page(buffer, 0);
	write_framebuffer(page);
	clear_page(page);
#endif
}

void tty_version()
{
	setcolor(pair(LTRED,BLACK));
	printf("PowerKernel 0.3\n");
	setcolor(pair(LTGRAY,BLACK));
	printf("(c) 2011 - 2018 Dogan Can Karatas.\n");
	printf("stdin: %s\nstdout:%s\nstderr:%s",
		SERIAL_IO ? "serial" : "display",
		SERIAL_IO ? "serial" : "display",
		SERIAL_IO ? "serial" : "display");
}

#if 0
static void write_framebuffer(char** page)
{
	uint16_t* pg;
	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			pg[i*WIDTH + j] = page[i][j];
		}
	}
	base_addr = pg;
}

static char** select_page(char** buf, int start)
{
	char **page;
	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			page[j][i] = buf[j + start][i];
		}
	}
	return page;
}

static void clear_page(char** page) // page'i null yapip ekrana basar
{
/*
	terminal_row = 0;
	terminal_column = 0;

	for(uint16_t i = 0; i < WIDTH * HEIGHT * 2 ; i++)
	{
		putchar('\0');
	}
*/

	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			page[j][i] = '\0';
		}
	}
	terminal_row = 0;
	terminal_column = 0;
	write_framebuffer(page);
}
#endif
void setcolor(uint8_t color) //farklı renkler seçer putchar ve printf için
{
	terminal_color = color;
}

static void putchar_color_coord(char c, size_t x, size_t y) // explicit çağırma
{
	const size_t i = y * WIDTH + x;
	base_addr[i] = pair(c, terminal_color);
}

static void scroll_framebuffer() // old
{
	for (size_t i = 1; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			base_addr[(i - 1)*WIDTH + j] = base_addr[i*WIDTH + j];
		}
	}
	for (size_t i = 0; i < WIDTH; i++) {
		base_addr[(HEIGHT - 1)*WIDTH + i] = '\0';
	}
	terminal_row = HEIGHT;
	terminal_column = 0;
}

void putchar(char c) // add screen buffer scroll feature for more than 25 lines.
{
	if (c == '\n') {
		if (terminal_row < HEIGHT) {
			terminal_row += 1;
			terminal_column = 0;
		} else {
			scroll_framebuffer();
		}
		//base_addr[(HEIGHT -1)*WIDTH + terminal_column] = pair(c,terminal_color);

	} else if (c == '\t') {
		if (WIDTH - terminal_column < TAB) {
			terminal_column = TAB - WIDTH + terminal_column;
			terminal_row += 1;
		} else {
			terminal_column += TAB;
		}
	} else {
		putchar_color_coord(c, terminal_column, terminal_row);
		if ( ++terminal_column == WIDTH) {
			terminal_column = 0;
			terminal_row += 1;
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
	//float f; //bunları ilerde implement edicem, ayrıca /t, /a gibi escapeleri de eklicem
	//double d;
	char ch;
	char* s;
	char* i;
	va_list args;
	va_start(args,str);

	for (size_t id = 0; id < strlen(str); id++) {
		if (str[id] != '%') {
			putchar(str[id]);
		} else {
			switch (str[id+1]) {
				case 'd':
					i = itoa(va_arg(args, int),BASE_10);
					for (size_t j = 0; j < strlen(i); j++)
						putchar(i[j]);
					id++;
					break;
				case 'c':
					ch = (char) va_arg(args,int);
					putchar(ch);
					id++;
					break;
				case 's':
					s = va_arg(args,char*);
					for (size_t j = 0; j < strlen(s); j++)
						putchar(s[j]);
					id++;
					break;
				case 'x':
					i  = itoa(va_arg(args, int), BASE_16);
					for (size_t j = 0; j < strlen(i); j++)
						putchar(i[j]);
					id++;
					break;
				default:
					id++;
					break;
			}
		}
	}
	va_end(args);
}

#if 0
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

#endif

#endif
