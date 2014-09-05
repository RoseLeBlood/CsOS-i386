#include <stdlib.h>
#include <errno.h>


#define _ERRNO_ENTRIES_COUNT    16

struct ee 
{
        void*   stack;
        int             value;
} _errno_entries[_ERRNO_ENTRIES_COUNT];

int _errno_entries_oldest = 0;



int* _get_errno() 
{
        void* currentStack = 0;

        asm("mov %%esp, %0" : "=r"(currentStack));
        
        // now we search the table for a similar stack
        int i;
        for (i = 0; i < _ERRNO_ENTRIES_COUNT; i++) 
        {
                // two stacks are similar <=> diff less than 0x500
                if (abs(currentStack - _errno_entries[i].stack) < 0x500)
                        return &_errno_entries[i].value;
        }
        
        // there was no table entry, so we create one
        int* returnValue = &_errno_entries[_errno_entries_oldest].value;
        _errno_entries[_errno_entries_oldest].stack = currentStack;
        _errno_entries[_errno_entries_oldest].value = 0;
        _errno_entries_oldest++;
        _errno_entries_oldest %= _ERRNO_ENTRIES_COUNT;
        return returnValue;
}
