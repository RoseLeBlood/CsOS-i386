
#include <klibc/string.h>
#include <klibc/malloc.h>
#include <klibc/ctype.h>
#include <klibc/errno.h>
#include <klibc/limits.h>

#undef memcpy
void* memcpy(void* destination, const void* source, size_t num) 
{
        void* temporaryDestination = destination;
        asm volatile("rep movsl ; mov %3, %2 ; rep movsb" : "+S"(source), "+D"(temporaryDestination) : "c"(num / 4), "r"(num % 4) : "cc", "memory");

        return destination;
}
void*	memcpyn (uint8_t* s1, unsigned int pos1, const uint8_t* s2, unsigned int pos2, size_t n)
{
	for(unsigned int i = 0; i < n; i++)
	{
		s1[pos1+i] = s2[pos2+i];
	}
	return s1;
}
#undef memmove
void* memmove(void* destination, const void* source, size_t num) 
{
        if (destination < source)
                asm volatile("rep movsb" :: "S"(source), "D"(destination), "c"((long)num) : "cc", "memory");
        else
                asm volatile("std; rep movsb; cld" :: "S"((unsigned char*)source + num - 1), "D"((unsigned char*)destination + num - 1), "c"((long)num) : "cc", "memory");

        return destination;
}

#undef strcpy
char* strcpy(char* destination, const char* source) 
{
        return (char*)memcpy(destination, source, strlen(source) + 1);
}

#undef strncpy
char* strncpy(char* destination, const char* source, size_t n) 
{
        size_t len = strlen(source) + 1;
        if (len > n) len = n;
        memcpy(destination, source, len);
        if (len < n) memset(destination + len, '\0', n - len);
        return destination;
}

#undef strcat
char* strcat(char* s1, const char* s2) 
{
        strcpy(s1 + strlen(s1), s2);
        return s1;
}

#undef strncat
char* strncat(char* s1, const char* s2, size_t n) 
{
        size_t n2 = strlen(s2);
        if (n2 > n) n2 = n;
        strncpy(s1 + strlen(s1), s2, n2);
        s1[strlen(s1) + n2] = '\0';
        return s1;
}

#undef memcmp
int memcmp(const void* ptr1, const void* ptr2, size_t num) 
{
        const unsigned char* vptr1 = (const unsigned char*)ptr1;
        const unsigned char* vptr2 = (const unsigned char*)ptr2;
        while (num) {
                if (*vptr1 > *vptr2) return 1;
                else if (*vptr1 < *vptr2) return -1;
                vptr1++; vptr2++; num--;
        }
        return 0;
}

#undef strcmp
int strcmp(const char* str1, const char* str2) 
{
        size_t len1 = strlen(str1);
        size_t len2 = strlen(str2);
        
        int cmpResult = memcmp(str1, str2, (len1 < len2) ? len1 : len2);
        if (cmpResult != 0)
                return cmpResult;
        
        if (len1 > len2)
                return 1;
        else if (len1 < len2)
                return -1;
        
        return 0;
}

#undef strncmp
int strncmp(const char* s1, const char* s2, size_t n) 
{
        return memcmp(s1, s2, n);
}

#undef memchr
void* memchr(const void* ptr, int value, size_t num) 
{
        const unsigned char* vptr = (const unsigned char*)ptr;
        while (num) {
                if (*vptr == (unsigned char)value)
                        return ((void*)vptr);
                vptr++; num--;
        }
        return NULL;
}

#undef strchr
char* strchr(const char* s, int c) 
{
        return (char*)memchr(s, c, strlen(s) + 1);
}

#undef strcspn
size_t strcspn(const char* s1, const char* s2)
 {
        char* pbrk = strpbrk(s1, s2);
        if (pbrk == NULL)
                return strlen(s1);
        return (size_t)(pbrk - s1);
}

#undef strpbrk
char* strpbrk(const char* s1, const char* s2)
{
        int s2len = strlen(s2);
        for (; *s1 != '\0'; s1++) {
                int i;
                for (i = 0; i < s2len; i++)
                        if (*s1 == s2[i])
                                return (char*)s1;
        }
        return NULL;
}

#undef strrchr
char* strrchr(const char* str, int character)
{
        int i = strlen(str);
        for (; i >= 0; i--)
                if (str[i] == character)
                        return (char*)str + i;
        return NULL;
}

#undef strspn
size_t strspn(const char* s1, const char* s2) 
{
        int found = 0;
        size_t len = 0;
        do {
                size_t i;
                for (i = 0; i < strlen(s2); i++) 
                {
                        if (s1[len] == s2[i]) 
                        {
                                len++;
                                found = 1;
                                break;
                        }
                }
        } while(found);
        return len;
}

#undef strstr
char* strstr(const char* s1, const char* s2) 
{
        size_t s2len = strlen(s2);
        for (; *s1 != '\0'; s1++) 
        {
                size_t i;
                for (i = 0; i < s2len; i++) 
                {
                        if (s2[i] == '\0')
                                return (char*)s1;
                        if (s2[i] == *s1)
                                continue;
                        break;
                }
        }
        return NULL;
}

#undef strtok
char* strtok(char* str, const char* delimiters) 
{
	static char* last = 0;
	
    if(!str)
        str = last;
        
    if(!str || *str == 0)
        return 0;
        
    while(*str != 0 && strchr(delimiters, *str) != 0)
        str++;
    char* end = str + strcspn(str, delimiters);
    last = end+1;
    *end = 0;
    
    return(str);
}

#undef memset
void* memset(void* ptr, int value, size_t num)
 {
        // 'stosl' will use the value in eax but we only want the value in al
        // so we make eax = al << 24 | al << 16 | al << 8 | al
        if ((value & 0xff) == 0)
                // this is a little optimization because memset is most often called with value = 0
                value = 0;
        else {
                value = (value & 0xff) | ((value & 0xff) << 8);
                value = (value & 0xffff) | ((value & 0xffff) << 16);
        }
        
        void* temporaryPtr = ptr;
        asm volatile("rep stosl ; mov %3, %2 ; rep stosb" : "+D"(temporaryPtr) : "a"(value), "c"(num / 4), "r"(num % 4) : "cc", "memory");

        return ptr;
}

#undef strlen
extern bool CPUID_IsSupport(uint32_t ext);

size_t strlen_sse4_2(const char *str)
{
   size_t index;

   asm(" mov $-16, %0;                      "
       " pxor %%xmm0, %%xmm0;               "
       ".strlen_4_2_start:                  "
       " add $16, %0;                       "
       " pcmpistri $0x08, (%0,%1), %%xmm0;  "
       " jnz .strlen_4_2_start;             "
       " add %2, %0;                        "
       :"=a"(index):"d"((size_t)str),"c"((size_t)str));
 
    return index;
}

size_t strlen_std(const char *  str)
{
	size_t len = 0;

    const char* endPtr = str;
    asm("repne scasb" : "+D"(endPtr) : "a"(0), "c"(~0) : "cc");
    len = (endPtr - str) - 1;

    return len;
}

size_t strlen(const char* str) 
{
    // check for SSE 4.2
    if(CPUID_IsSupport(44))
    {
        return strlen_sse4_2(str);
    }

    return strlen_std(str);   
}
#undef strdup
char *strdup (const char *s)
{
	char *d = ""; (char*)malloc (strlen (s) + 1);   // Allocate memory
    if (d != NULL) strcpy (d,s);         // Copy string if okay
    return d;      
}
#undef strtol
long strtol(const char *str, char **endptr, int base)
{
	long retval = 0;
    int overflow = 0;
    char sign = 0;
    int digit;

    while (isspace(*str)) {
        str++;
    }

    // Moegliches Vorzeichen auswerten
    if (*str == '+' || *str == '-') {
        sign = *str;
        str++;
    }

    // Moegliches 0, 0x und 0X auswerten
    if (*str == '0')
    {
        if (str[1] == 'x' || str[1] == 'X') {
            if (base == 0) {
                base = 16;
            }

            if (base == 16 && isxdigit(str[2])) {
                str += 2;
            }
        } else if (base == 0) {
            base = 8;
        }
    }

    while (*str)
    {
        if (isdigit(*str) && *str - '0' < base) {
            digit = *str - '0';
        } else if(isalpha(*str) && tolower(*str) - 'a' + 10 < base) {
            digit = tolower(*str) - 'a' + 10;
        } else {
            break;
        }

        if (retval > (LONG_MAX - digit) / base) {
            overflow = 1;
        }
        retval = retval * base + digit;

        str++;
    }

    if (endptr != NULL) {
        *(const char**)endptr = str;
    }

    if (overflow) {
        errno = ERANGE;
        return (sign == '-') ? LONG_MIN : LONG_MAX;
    }

    return (sign == '-') ? -retval : retval;
}
//
int bcmp(const void *b1, const void *b2, size_t length)
{
	char *p1, *p2;

	if (length == 0)
		return (0);
	p1 = (char *)b1;
	p2 = (char *)b2;
	do
		if (*p1++ != *p2++)
			break;
	while (--length);
	return (length);
}
void *memmem(const void *l, size_t l_len, const void *s, size_t s_len)
{
	register char *cur, *last;
	const char *cl = (const char *)l;
	const char *cs = (const char *)s;

	/* we need something to compare */
	if (l_len == 0 || s_len == 0)
		return NULL;

	/* "s" must be smaller or equal to "l" */
	if (l_len < s_len)
		return NULL;

	/* special case where s_len == 1 */
	if (s_len == 1)
		return memchr(l, (int)*cs, l_len);

	/* the last position where its possible to find "s" in "l" */
	last = (char *)cl + l_len - s_len;

	for (cur = (char *)cl; cur <= last; cur++)
		if (cur[0] == cs[0] && memcmp(cur, cs, s_len) == 0)
			return cur;

	return NULL;
}


