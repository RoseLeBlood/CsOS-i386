#include <klibc/cxx/new.hpp>
#include <malloc.h>
#include <ctype.h>

new_handler handler = NULL;

extern void* operator new (unsigned int n)        							
{ 
	void *nn =  (malloc (n*4)); 

	if((nn == NULL  && handler != NULL))
	{
		handler();
	}
	return nn;
}
extern void* operator new[] (unsigned int n)         							
{ 
	void *nn =  (malloc (n*4)); 

	if((nn == NULL  && handler != NULL))
	{
		handler();
	}
	return nn;
}
extern void  operator delete (void* p)                                	
{ 
	free (p); 
}
extern void  operator delete[] (void* p)                        		
{ 
	free (p); 
}
extern void* operator new (unsigned int, void* p)         					
{ 
	return (p);
}
extern void* operator new[] (unsigned int, void* p)         					
{ 	
	return (p); 
}

extern void  operator delete  (void*, void*)         					
{ 
}
extern void  operator delete[](void*, void*) 	        				
{ 
}

new_handler set_new_handler (new_handler new_p)
{
	new_handler old = handler;
	handler = new_p;
	return old;
}
new_handler get_new_handler()
{
	return handler;
}