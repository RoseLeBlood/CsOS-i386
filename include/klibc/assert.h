#ifndef	_ASSERT_H
#define	_ASSERT_H

#ifdef	__cplusplus
extern "C" {
#endif


#undef	assert

#ifdef	NDEBUG
	#define	assert(EX) ((void)0)
	#define pannic(msg) ((void)0)
#else
	void __assert(const char *, const char *, int);
	void __panic(const char *, const char *, int);
	
	#define assert(exp) ( (exp) ? (void) 0 : __assert(#exp, __FILE__, __LINE__))
	#define panic(msg) __panic(msg, __FILE__, __LINE__);
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* _ASSERT_H */

