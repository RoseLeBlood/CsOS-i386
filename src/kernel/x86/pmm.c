#include <kernel/pmm.h>


pmm_page_t 					pmm_allocated[PHYS_MAX_BLOCKS];   
unsigned 					pmm_bitmap[PHYS_MAX_PAGE];                   
unsigned 					pmm_page_number;                                            
uint32_t 					pmm_total; 


void pmm_free(void *addr)
{
	unsigned x;
	unsigned y;
        
	for(uint32_t i = 0; i < PHYS_MAX_BLOCKS; i++)
	{
		if(pmm_allocated[i].address == addr)
		{
			x = ((unsigned) addr / 4096) / 32;
			y = ((unsigned) addr / 4096) % 32;

			pmm_bitmap[x] = pmm_bitmap[x] - (1 << y);

			for(uint32_t j = 1; j < pmm_allocated[i].dim; j++)
			{
				if(y == 31)
				{
					y = 0;
					x++;
				}
				else
					y++;

				pmm_bitmap[x] = pmm_bitmap[x] - (1 << y);
			}

			pmm_allocated[i].dim = 0;

			break;
		}  
	}     
}
uint8_t pmm_if_free_page(int *x, int *y)
{
        if(*y == 31)
        {
                *y = 0;
                *x = *x + 1;
        }
        else
                *y = *y + 1;
        
        return ((pmm_bitmap[(int) *x] & (1 << (int) *y)) == 1) ? 0 : 1;  
}
intptr_t *pmm_alloc(size_t size)
{
	unsigned adr;
	unsigned x;
	unsigned y;
	unsigned j;
	int a,b;
	int ff;

	x = 0;
	while(x < (pmm_page_number / 32))
	{
		y = 0;
		while(y < 32)
		{               
			if((pmm_bitmap[x] & (1 << y)) == 0)
			{       
				a = x;
				b = y;
				for(j = 0; j <= size; j++)
				{
					if(j == size)
					{
						pmm_bitmap[x] = pmm_bitmap[x] + (1 << y);

						for(j = 1; j < size; j++)
						{
							if(y == 31)
							{
							y = 0;
							x++;
							}
							else
							y++;

							pmm_bitmap[x] = pmm_bitmap[x] + (1 << y);
						}


						adr = (x) * (1024 * 32 * PHYS_PAGE_SIZE) + (y * 1024 * PHYS_PAGE_SIZE);

						ff = pmm_first_free_alloc();
						pmm_allocated[ff].address = (void *) adr;
						pmm_allocated[ff].dim = size;
						return (intptr_t *) adr;
					}
					if(!pmm_if_free_page(&a, &b))
					{
						x = a;
						y = b;
						break;
					}
				}
			}
			y++;
		}
		x++;
	}
	return (intptr_t *) 0;
}
uint32_t pmm_get_free_pages()
{
    unsigned np = 0;
    unsigned x;
    unsigned y;
    
    for(x = 0; x < pmm_page_number / 32; x++)
    {
        for(y = 0; y < 32; y++)
        {
                if((pmm_bitmap[x] & (1 << y)) == 0)
                        np++;
        }
    }
    return np;      
}
void pmm_reserve(uint32_t start, uint32_t end)
{
    unsigned x1, x2;
    unsigned y1, y2;
    
    x1 = ((unsigned) start / 4096) / 32;
    y1 = ((unsigned) start / 4096) % 32;
    x2 = ((unsigned) end / 4096) / 32;
    y2 = ((unsigned) end / 4096) % 32;

    pmm_bitmap[x1] = pmm_bitmap[x1] - (1 << y1);
    
    while(x1 >= x2 && y1 >= y2)
    {
        if(y1 == 31)
        {
            y1 = 0;
            x1++;
        }
        else
            y1++;

    	pmm_bitmap[x1] = pmm_bitmap[x1] - (1 << y1);
    }
}
uint32_t pmm_first_free_alloc()
{
    for(uint32_t x = 0; x < PHYS_MAX_BLOCKS; x++)
    {
        if(pmm_allocated[x].dim == 0)
        { 
       		return x;
        }
	}
    return -1;
}
void pmm_init(uint32_t mem)
{
        unsigned x;
        
        pmm_total = mem;
        pmm_page_number = ((((unsigned) pmm_total / PHYS_PAGE_SIZE) / 32) * 32);

        for(x = 0; x < (pmm_page_number / 32); x++)
        {
        	pmm_bitmap[x] = 0;
        }                

        for(x = 0; x < PHYS_MAX_BLOCKS; x++)
        {
                pmm_allocated[x].dim = 0;
        }
        pmm_reserve(0x00000000, 0x000FFFFF);	// bios, rom etc
        pmm_reserve(0x00100000, 0x003FFFFF); 	// module
        pmm_reserve(0x00F00000, 0x00FFFFFF);	// hardware
        pmm_reserve(0x0C000000, 0x0FFFFFFF);  	// pci , hardware ...
}


