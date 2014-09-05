#include <types.h>
#include <klibc/stdio.h>
#include <klibc/string.h>
#include <stdarg.h>
#include <types.h>
#include <malloc.h>


char** 			make_args(char *str, uint32_t* size)
{
	int i = 0;
	
	char* ptr;
	char** args = (char**)malloc(sizeof(char*) * 32);
	// initialisieren und ersten Abschnitt erstellen
	ptr = strtok(str, " ");
	
	while(ptr != NULL) 
	{
		args[i] = ptr;
		i++;
	 	ptr = strtok(NULL, " ");
	}
	*size = i;
	
	return args;
	
}
/** Convert an int into a char* */
char *_itoa(char* result, int base, int value)
{
    if (base < 2 || base > 36) { *result = '\0'; return result; }
	
	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}
char *itoa(int value)
{
	char result[260];

	return _itoa(result, 10, value);
}
char *itox(int value)
{
    char result[260];

	return _itoa(result, 16, value);    
}

/* print a char */
extern void putchar(const char ch);
/* print a string */
extern void puts(const char *str);





/* printf */
int printf(const char *format, ...)
{
	char str[260] = { 0 };
	
	va_list ap;
    va_start(ap, format);
    int n = vsprintf(str, format, ap);
    va_end(ap);
    
    puts(str);
        
    return n;
}
int scanf(const char *format, ...)
{
        int len = 0;
        char buffer[255];
        char *current = &buffer[0];
        int *num;
        va_list ap;

        va_start(ap, format);

        while(*format != '\0')
        {
                if(*format == '%')
                {
                        format++;

                        switch (*format)
                        {
                                /* read a string */
                                case 's':
                                        current = va_arg(ap, char *);
                                        gets(current);
                                        break;

                                /* read a character */
                                case 'c':
                                        current = va_arg(ap, char *);
                                        /* here? */
                                        break;

                                /* read a decimal */
                                case 'd':
                                        num = va_arg(ap, int *);
                                        gets(buffer);
                                        *num = atoi(buffer);
                                        break;
                                	
                        }
                }

                format++;
                len++;
        }
        return len;
}




/* getchar */
int getchar()
{
        char c; 
        
        while((c = getch()) == 0);
        
        return c;
}






/* get a string */
char *gets(char *string)
{
        int count = 0;
        while(1)
        {
                *string = (char) getchar(); 
        
                if(*string == '\n') break;
                else if(*string == '\b')
                {
                        if(count > 0)
                        {
                                string--;
                                count--;
                        }
                }
                else
                {
                        putchar(*string);
                        string++;
                        count++;
                }
        }
        putchar('\n');
        *string = '\0';
        return string;
}


int snprintf(char* str, size_t size, const char* format, ...) 
{
        va_list ap;
        va_start(ap, format);
        int n = vsnprintf(str, size, format, ap);
        va_end(ap);
        return n;
}

int sprintf(char* str, const char* format, ...) 
{
        va_list ap;
        va_start(ap, format);
        int n = vsprintf(str, format, ap);
        va_end(ap);
        return n;
}

int sscanf(const char* s, const char* format, ...) 
{
        va_list ap;
        va_start(ap, format);
        int n = vsscanf(s, format, ap);
        va_end(ap);
        return n;
}

int vsnprintf(char* str, size_t size, const char* format, va_list ap) 
{
        // TODO: 'size' is not handled
        // TODO: 'e', 'f', 'g', 'n' specifiers to do
        // TODO: function doesn't return the number of printed characters
        
        if (size == 0)
                return 0;
        
        // we loop through each character of the format
        while (*format != '\0' && size > 1) 
        {
                // first we handle the most common case: a normal character
                if (*format != '%') {
                        *str++ = *format++;
                        continue;
                }
                
                // then we check if format is "%%"
                format++;
                if (*format == '%') 
                {
                        *str++ = '%';
                        format++;
                        continue;
                }
                
                // now we are sure we are in a special case
                // what we do is that we store flags, width, precision, length in variables
                bool sharpFlag = false;
                bool alignLeft = false;
                bool alwaysSign = false;
                bool noSign = false;
                bool padding = ' ';
                size_t minimumWidth = 0;
                size_t precision = 1;
                bool numberMustBeShort = false;
                bool numberMustBeLong = false;
                bool unsignedNumber = false;
                bool capitalLetters = false;
                bool octal = false;
                bool hexadecimal = false;
                bool pointer = false;
                bool tagFinished = false;
                
                // then we loop (and we modify variables) until we find a specifier
                do 
                {
                        
                        switch (*format) 
                        {
                                // flags
                                case '-': alignLeft = true;             format++; break;
                                case '+': alwaysSign = true;            format++; break;
                                case ' ': noSign = true;                format++; break;
                                case '0': padding = '0';                        format++; break;
                                case '#': sharpFlag = true;             format++; break;
                                
                                // width
                                case '1':
                                case '2':
                                case '3':
                                case '4':
                                case '5':               // width cannot start with 0 or it would be a flag
                                case '6':
                                case '7':
                                case '8':
                                case '9':
                                        minimumWidth = atoi(format);
                                        while (*format >= '0' && *format <= '9') format++;
                                        break;
                                case '*':
                                        minimumWidth = va_arg(ap, int);
                                        format++;
                                        break;
                                        
                                // precision
                                case '.':
                                        format++;
                                        if (*format == '*') 
                                        {
                                                precision = va_arg(ap, int);
                                                format++;
                                        } 
                                        else if (*format >= '0' && *format <= '9') 
                                        {
                                                precision = atoi(format);
                                                while (*format >= '0' && *format <= '9') format++;
                                        } 
                                        else 
                                        {
                                                precision = 0;          // this behavior is standardized
                                        }
                                        break;
                                        
                                // length
                                case 'h': numberMustBeShort = true;     format++; break;
                                case 'l':
                                case 'L': numberMustBeLong = true;      format++; break;
                                
                                // specifiers
                                
                                
                                //      strings
                                case 's': 
                                {
                                        char* nStr = va_arg(ap, char*);
                                        size_t len = strlen(nStr);
                                        
                                        if (!alignLeft && len < minimumWidth) 
                                        {
                                                while (len++ < minimumWidth)
                                                        *str++ = padding;
                                        }
                                        
                                        while (*nStr)
                                                *str++ = *nStr++;
                                        
                                        if (alignLeft && len < minimumWidth) 
                                        {
                                                while (len++ < minimumWidth)
                                                        *str++ = padding;
                                        }
                                        
                                        format++;
                                        tagFinished = true;
                                        break;
                                }
                                case 'b':
                                {
                                	bool bo = va_arg(ap, int);
                                	char* nStr = bo != 0 ? "true" : "false";
                                	size_t len = strlen(nStr);
                                	
                                	if (!alignLeft && len < minimumWidth) 
                                    {
                                            while (len++ < minimumWidth)
                                                    *str++ = padding;
                                    }
                                    
                                    while (*nStr)
                                            *str++ = *nStr++;
                                    
                                    if (alignLeft && len < minimumWidth) 
                                    {
                                            while (len++ < minimumWidth)
                                                    *str++ = padding;
                                    }
                                    
                                    format++;
                                    tagFinished = true;
                                    break;
                                }
                                
                                
                                //      characters
                                case 'c': 
                                {
                                        char toWrite;
                                        /*if (numberMustBeLong)         toWrite = (char)va_arg(ap, wchar_t);
                                        else                                    */toWrite = (char)va_arg(ap, int);
                                        
                                        if (!alignLeft) 
                                        {
                                                for (; minimumWidth > 1; minimumWidth--)
                                                        *str++ = padding;
                                        }
                                        
                                        *str++ = toWrite;
                                        
                                        if (alignLeft) 
                                        {
                                                for (; minimumWidth > 1; minimumWidth--)
                                                        *str++ = padding;
                                        }
                                        
                                        format++;
                                        tagFinished = true;
                                        break;
                                }
                                
                                
                                //      numbers
                                case 'o':       octal = true;
                                case 'p':       pointer = true;
                                case 'X':       capitalLetters = true;
                                case 'x':       hexadecimal = true;
                                case 'u':       unsignedNumber = true;
                                case 'd':
                                case 'i': 
                                {
                                        // first we handle problems with our switch-case
                                        if (octal) { pointer = false; hexadecimal = false; unsignedNumber = false; }
                                        
                                        // then we retreive the value to write
                                        unsigned long int toWrite;
                                        if (numberMustBeLong)                   toWrite = va_arg(ap, long int);
                                        else if (numberMustBeShort)             toWrite = (short int)va_arg(ap, int);
                                        else if (pointer)                               toWrite = (unsigned long int)va_arg(ap, void*);
                                        else                                            toWrite = va_arg(ap, int);
                                        
                                        // handling sign
                                        if (!noSign) {
                                                bool positive = (unsignedNumber || (((signed)toWrite) > 0));
                                                if (alwaysSign || !positive)
                                                        *str++ = (positive ? '+' : '-');
                                                if (!unsignedNumber && (((signed)toWrite) < 0))
                                                        toWrite = -((signed)toWrite);
                                        }
                                        
                                        if (sharpFlag && toWrite != 0) {
                                                if (octal || hexadecimal)
                                                        *str++ = '0';
                                                if (hexadecimal) {
                                                        if (capitalLetters)     *str++ = 'X';
                                                        else                            *str++ = 'x';
                                                }
                                        }
                                        
                                        // writing number
                                        int digitSwitch = 10;
                                        if (hexadecimal)        digitSwitch = 16;
                                        else if (octal) digitSwitch = 8;
                                        
                                        // this variable will be usefull
                                        char* baseStr = str;
                                        
                                        size_t numDigits = 0;
                                        do {
                                                if (numDigits)
                                                        memmove(baseStr + 1, baseStr, numDigits * sizeof(char));
                                                int modResult = toWrite % digitSwitch;
                                                if (modResult < 10)     {       *baseStr = '0' + modResult;                     str++;  }
                                                else if (capitalLetters)        {       *baseStr = 'A' + (modResult - 10);              str++;  }
                                                else                            {       *baseStr = 'a' + (modResult - 10);              str++;  }
                                                toWrite /= digitSwitch;
                                                numDigits++;
                                        } while (toWrite != 0);
                                        
                                        if (numDigits < minimumWidth) {
                                                minimumWidth -= numDigits;
                                                if (alignLeft) {
                                                        for (; minimumWidth > 0; minimumWidth--)
                                                                *str++ = padding;
                                                } else {
                                                        memmove(baseStr + minimumWidth * sizeof(char), baseStr, numDigits * sizeof(char));
                                                        memset(baseStr, padding, minimumWidth * sizeof(char));
                                                        str += minimumWidth;
                                                }
                                        }
                                        
                                        // finished
                                        format++;
                                        tagFinished = true;
                                        break;
                                }
                                
                                default:
                                        format++;
                                        tagFinished = true;
                                        break;
                                
                        }
                } while (!tagFinished);
        }
        
        *str = '\0';
        
        return 1;
}

int vsprintf(char* str, const char* format, va_list ap)
{
        return vsnprintf(str, (size_t)-1, format, ap);
}

int vsscanf(const char* s, const char* format, va_list ap)
{
        return 1;
}
