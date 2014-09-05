#ifndef __CPUID_H__
#define __CPUID_H__
#include <types.h>

namespace cpuid
{
	enum cpuid_t
	{
		FPU, 
		VME, 
		DE, 
		PSE,
        TSC, 
        MSR, 
        PAE, 
        MCE,
        CX8, 
        APIC, 
        SEP, 
        MTRR,
        PGE, 
        MCA, 
        CMOV, 
        PAT,
        PSE_36, 
        PSN, 
        CLFSH, 
        DS,
        ACPI, 
        MMX, 
        FXSR, 
        SSE, 
        SSE2, 
        SS, 
        HTT, 
        TM, 
        PBE,
        /* ECX */
        SSE3, 
        MONITOR, 
        DS_CPL, 
        VMX,
        SMX, 
        EST, 
        TM2, 
        SSSE3,
        CNXT_ID, 
        CMPXCHG16B,
        xTPR_Update_Control,
        PDCM, 
        DCA, 
        SSE4_1, 
        SSE4_2, 
        POPCNT, 
        __MAX
	};
}

struct cpuid_cache
{
    uint8_t  level;
    uint8_t  type;
    
    uint8_t  ways;
    uint8_t  partitions;
    uint16_t line_size;
    uint32_t sets;
    
    uint32_t cache_size;
};

struct perfmon
{
        uint8_t  version;
        uint8_t  ncounters;
        uint8_t  counter_width;
        uint8_t  ebx_width;
        uint32_t available_events;
        uint8_t  nC0, nC1, nC2, nC3, nC4;
};


class CPUID
{
public:
	static bool IsSupport(cpuid::cpuid_t ext) { return m_ext[ext]; }
	
	static void parse();
private:
	static void parse_cpuid_features(void);
	static void parse_cpuid_ext_2(void);
	static void parse_cpuid_ext_6(void);
	static void parse_cpuid_ext_0(void);
	static void parse_cpuid_basic_A(void) ;
	static void parse_cpuid_basic_4(void);
	static void parse_cpuid_basic_2(void);
	static void parse_cpuid_basic_1(void);
	static void parse_cpuid_basic_0(void);
private:
    static bool 		m_ext[cpuid::__MAX];
    
    static perfmon 		m_perfmon;
    static uint32_t 	m_max_basic_input, m_max_ext_input;
    static uint8_t  	m_cpu_signature[13];
    static uint8_t  	m_stepping, m_model, m_family, m_type, m_ext_model, m_ext_family;
    static uint16_t 	m_cache_line_size;
    static uint32_t 	m_features_ecx, m_features_edx;
    static uint8_t  	m_sse_max_major, m_sse_max_minor;
    static uint8_t  	m_cpu_brand[49];
    static cpuid_cache 	m_cache_info[32];
    static uint8_t  	m_cache_count;
    static uint8_t  	m_l2_assoc;
    static uint16_t 	m_l2_cache_size;
    static uint8_t  	m_l2_cache_line_size; 
};

#endif