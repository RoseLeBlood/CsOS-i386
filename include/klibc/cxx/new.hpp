#ifndef __NEW_CXX_H__
#define __NEW_CXX_H__


void* operator new (unsigned int n);
void* operator new[] (unsigned int n);
void  operator delete (void* p);
void  operator delete[] (void* p);

void* operator new (unsigned int, void* p);
void* operator new[] (unsigned int, void* p);

void  operator delete  (void*, void*);
void  operator delete[](void*, void*);


typedef void (*new_handler)();

new_handler set_new_handler (new_handler new_p);
new_handler get_new_handler();
#endif
