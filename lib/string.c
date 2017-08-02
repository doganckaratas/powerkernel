/**
### string.c
### PowerKernel 0.2
### 2011 - 2017 -- Doğan Can Karataş
### Son Değişiklik - 02/2017
**/


size_t strlen(const string str) 
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

inline void strcpy(string src, string dst)
{
	for(int i = 0; i < (int) strlen(dst); i++)
	{
		dst[i] = '\0';
	}
	
	for(int i = 0; i < (int)strlen(src); i++)
	{
		dst[i] = src[i];
	}
}

int strseek(string str, char delimiter) // delimiter sayısı döndürür
{
	int count = 0;
	for(int i = 0; i < (int) strlen(str); i++)
	{
		if(str[i] == delimiter)
		{
			count++;
		}
		else
		{
			continue;
		}
	}
	return count;
}

/**
void substring(string str, string result, int start, int count)
{
	for(int i = 0; i <= count; i++)
	{
		result[i] = '\0';
	}
	string buffer;
	int startcounter = 0;
	for(int i = 0; i < (int) strlen(str); i++)
	{
		if( i  < start )
		{
			continue;
		}
		else
		{
			if(startcounter < count)
			{
				buffer[startcounter] = str[i];
				startcounter++;
			}
			else
			{
				continue;
			}
		}
	}
	*result = *buffer;
}
**/

string substring(string str, int start, int count)
{
	string result;
	for(int i = 0; i <= count; i++)
	{
		result[i] = '\0';
	}
	string buffer;
	int startcounter = 0;
	for(int i = 0; i < (int) strlen(str); i++)
	{
		if( i  < start )
		{
			continue;
		}
		else
		{
			if(startcounter < count)
			{
				buffer[startcounter] = str[i];
				startcounter++;
			}
			else
			{
				continue;
			}
		}
	}
	*result = *buffer;
	return result;
}

// STRTOKU DÜZELT, PRİNTF İÇİN FORMAT SPECİFİER TOKENİZE ET, VARİADİC FONK HALİNE GETİR.

void strtok(string str, string *dest, char delimiter) // delimiter karakter ile string ayırma
{
	int count = strseek(str,delimiter);	
	string buffer[count + 1];
	int current = 0;
	for(int i = 0; i < (int) strlen(str); i++)
	{
		if(str[i] == delimiter)
		{
			current += 1;
		}
		else
		{
			buffer[i][current] = str[i];
		}
	}
	for(int i = 0; i < count + 1; i++)
	{	
		dest[i] = buffer[i];
		
	}
}

/**
char* itoa( int value, char* str, int base )
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
    	*str = '\0';
	    return str;
    }
    rc = ptr;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr = str;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}
**/

char* itoa(int val, int base)
{
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}