#ifndef _STD_UTILITY_H_
#define _STD_UTILITY_H_

#include <cxx/common.hpp>
#include <cxx/new.hpp>
#include <cxx/inttokey.hpp>

/// Shorthand for container iteration.
#define foreach(type,i,ctr)	for (type i = (ctr).begin(); i != (ctr).end(); ++ i)
/// Shorthand for container reverse iteration.
#define eachfor(type,i,ctr)	for (type i = (ctr).rbegin(); i != (ctr).rend(); ++ i)

#define TEMPLATE_FULL_DECL1(d1,t1)		template <d1 t1>
#define TEMPLATE_FULL_DECL2(d1,t1,d2,t2)	template <d1 t1, d2 t2>
#define TEMPLATE_FULL_DECL3(d1,t1,d2,t2,d3,t3)	template <d1 t1, d2 t2, d3 t3>
#define TEMPLATE_DECL1(t1)		TEMPLATE_FULL_DECL1(typename,t1)
#define TEMPLATE_DECL2(t1,t2)		TEMPLATE_FULL_DECL2(typename,t1,typename,t2)
#define TEMPLATE_DECL3(t1,t2,t3)	TEMPLATE_FULL_DECL3(typename,t1,typename,t2,typename,t3)
#define TEMPLATE_TYPE1(type,a1)		type<a1>
#define TEMPLATE_TYPE2(type,a1,a2)	type<a1,a2>
#define TEMPLATE_TYPE3(type,a1,a2,a3)	type<a1,a2,a3>


namespace std
{
	namespace internal
	{
        template<typename T> void copy_n(const T* first, size_t n, T* result, int_to_type<false>)
        {
                const T* last = first + n;
                switch (n & 0x3)
                {
                case 0:
                        while (first != last)
                        {
                                *result++ = *first++;
                case 3: *result++ = *first++;
                case 2: *result++ = *first++;
                case 1: *result++ = *first++;
                        }
                }
        }
        template<typename T> void copy_n(const T* first, size_t n, T* result, int_to_type<true>)
        {
                assert(result >= first + n || result < first);
                Sys::MemCpy(result, first, n * sizeof(T));
        }

        template<typename T> void copy(const T* first, const T* last, T* result, int_to_type<false>)
        {
                T* localResult = result;
                while (first != last)
                        *localResult++ = *first++;
        }
        template<typename T> void copy(const T* first, const T* last, T* result, int_to_type<true>)
        {
                const size_t n = reinterpret_cast<const char*>(last) - reinterpret_cast<const char*>(first);
                Sys::MemCpy(result, first, n);
        }

        template<typename T> inline void move_n(const T* from, size_t n, T* result, int_to_type<false>)
        {
                for (int i = int(n) - 1; i >= 0; --i)
                        result[i] = from[i];
        }
        template<typename T> inline void move_n(const T* first, size_t n, T* result, int_to_type<true>)
        {
                Sys::MemMove(result, first, n * sizeof(T));
        }

        template<typename T> inline void move(const T* first, const T* last, T* result, int_to_type<false>)
        {
                result += (last - first);
                while (--last >= first)
                        *(--result) = *last;
        }
        template<typename T> inline  void move(const T* first, const T* last, T* result, int_to_type<true>)
        {

                const size_t n = reinterpret_cast<uintptr_t>(last) - reinterpret_cast<uintptr_t>(first);
                Sys::MemMove(result, first, n);
        }
		

        template<typename T> void copy_construct_n(const T* first, size_t n, T* result, int_to_type<false>)
        {
                for (size_t i = 0; i < n; ++i)
                        new (result + i) T(first[i]);
        }
        template<typename T> void copy_construct_n(const T* first, size_t n, T* result, int_to_type<true>)
        {
                assert(result >= first + n || result < first);
                Sys::MemCpy(result, first, n * sizeof(T));
        }

        template<typename T> void destruct_n(T* first, size_t n, int_to_type<false>)
        {
                sizeof(first);
                for (size_t i = 0; i < n; ++i)
                        (first + i)->~T();
        }
        template<typename T> inline void destruct_n(T*, size_t, int_to_type<true>)
        {
                // Nothing to do, no destructor needed.
        }

        template<typename T> void destruct(T* mem, int_to_type<false>)
        {
                sizeof(mem);
                mem->~T();
        }
        template<typename T> inline void destruct(T*, int_to_type<true>)
        {
                // Nothing to do, no destructor needed.
        }

        template<typename T> void construct(T* mem, int_to_type<false>)
        {
                new (mem) T();
        }
        template<typename T> inline void construct(T*, int_to_type<true>)
        {
                // Nothing to do
        }

        template<typename T> inline void copy_construct(T* mem, const T& orig, int_to_type<false>)
        {
                new (mem) T(orig);
        }
        template<typename T> inline void copy_construct(T* mem, const T& orig, int_to_type<true>)
        {
                mem[0] = orig;
        }

        template<typename T> void construct_n(T* to, size_t count, int_to_type<false>)
        {
                sizeof(to);
                for (size_t i = 0; i < count; ++i)
                        new (to + i) T();
        }
        template<typename T> inline void construct_n(T*, int, int_to_type<true>)
        {
                // trivial ctor, nothing to do.
        }


        template<class TIter, class TPred> void test_ordering(TIter first, TIter last, const TPred& pred)
        {
        	sizeof(first); sizeof(last); sizeof(pred);
        }

        template<typename T1, typename T2, class TPred> inline bool debug_pred(const TPred& pred, const T1& a, const T2& b) 
        {
         	return pred(a, b);
        }
       
        
        namespace simd 
        {
		    #define ALL_MMX_REGS_CHANGELIST "mm0","mm1","mm2","mm3","mm4","mm5","mm6","mm7","st","st(1)","st(2)","st(3)","st(4)","st(5)","st(6)","st(7)"
			#if CPU_HAS_3DNOW
			    inline void reset_mmx (void) { asm ("femms":::ALL_MMX_REGS_CHANGELIST); }
			#elif CPU_HAS_MMX
			    inline void reset_mmx (void) { asm ("emms":::ALL_MMX_REGS_CHANGELIST); }
			#else
			    inline void reset_mmx (void) {}
			#endif
		} 
	} 
}
#endif
