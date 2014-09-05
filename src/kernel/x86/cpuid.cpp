#include <kernel/cpuid.hpp>

bool 	CPUID::m_ext[cpuid::__MAX] ;
perfmon 		CPUID::m_perfmon;
uint32_t 	CPUID::m_max_basic_input, CPUID::m_max_ext_input;
uint8_t  	CPUID::m_cpu_signature[13];
uint8_t  	CPUID::m_stepping, CPUID::m_model, CPUID::m_family, CPUID::m_type, CPUID::m_ext_model, CPUID::m_ext_family;
uint16_t 	CPUID::m_cache_line_size;
uint32_t 	CPUID::m_features_ecx, CPUID::m_features_edx;
uint8_t  	CPUID::m_sse_max_major, CPUID::m_sse_max_minor;
uint8_t  	CPUID::m_cpu_brand[49];
cpuid_cache 	CPUID::m_cache_info[32];
uint8_t  	CPUID::m_cache_count;
uint8_t  	CPUID::m_l2_assoc;
uint16_t 	CPUID::m_l2_cache_size;
uint8_t  	CPUID::m_l2_cache_line_size;


const char * L2_associativity[0x10] = 
{
    "disabled", "direct mapped",
    "2-way", "reserved",
    "4-way", "reserved",
    "8-way", "reserved",
    "16-way", "reserved", "reserved",
    "reserved", "reserved", "reserved", "reserved",
    "fully associative"
};

void CPUID::parse_cpuid_features(void)
{
	m_sse_max_major = 0; m_sse_max_minor = 0;

    m_ext[cpuid::FPU] =    (m_features_edx & (1 << 0)) == 0 ? false : true;
    m_ext[cpuid::VME] =    (m_features_edx & (1 << 1)) == 0 ? false : true;
    m_ext[cpuid::DE] =     (m_features_edx & (1 << 2)) == 0 ? false : true;
    m_ext[cpuid::PSE] =    (m_features_edx & (1 << 3)) == 0 ? false : true;
    m_ext[cpuid::TSC] =    (m_features_edx & (1 << 4)) == 0 ? false : true;
    m_ext[cpuid::MSR] =    (m_features_edx & (1 << 5)) == 0 ? false : true;
    m_ext[cpuid::PAE] =    (m_features_edx & (1 << 6)) == 0 ? false : true;
    m_ext[cpuid::MCE] =    (m_features_edx & (1 << 7)) == 0 ? false : true;
    m_ext[cpuid::CX8] =    (m_features_edx & (1 << 8)) == 0 ? false : true;
    m_ext[cpuid::APIC] =   (m_features_edx & (1 << 9)) == 0 ? false : true;
    m_ext[cpuid::SEP] =    (m_features_edx & (1 << 11)) == 0 ? false : true;
    m_ext[cpuid::MTRR] =   (m_features_edx & (1 << 12)) == 0 ? false : true;
    m_ext[cpuid::PGE] =    (m_features_edx & (1 << 13)) == 0 ? false : true;
    m_ext[cpuid::MCA] =    (m_features_edx & (1 << 14)) == 0 ? false : true;
    m_ext[cpuid::CMOV] =   (m_features_edx & (1 << 15)) == 0 ? false : true;
    m_ext[cpuid::PAT] =    (m_features_edx & (1 << 16)) == 0 ? false : true;
    m_ext[cpuid::PSE_36] = (m_features_edx & (1 << 17)) == 0 ? false : true;
    m_ext[cpuid::PSN] =    (m_features_edx & (1 << 18)) == 0 ? false : true;
    m_ext[cpuid::CLFSH] =  (m_features_edx & (1 << 19)) == 0 ? false : true;
    m_ext[cpuid::DS] =             (m_features_edx & (1 << 21)) == 0 ? false : true;
    m_ext[cpuid::ACPI] =   (m_features_edx & (1 << 22)) == 0 ? false : true;
    m_ext[cpuid::MMX] =    (m_features_edx & (1 << 23)) == 0 ? false : true;
    m_ext[cpuid::FXSR] =   (m_features_edx & (1 << 24)) == 0 ? false : true;
    if((m_ext[cpuid::SSE] = (m_features_edx & (1 << 25)) == 0 ? false : true) == true)
    { 
    	m_sse_max_major = 1; 
    	m_sse_max_minor = 0; 
    } 
    if((m_ext[cpuid::SSE2] = (m_features_edx & (1 << 26)) == 0 ? false : true) == true)
    { 
    	m_sse_max_major = 2; 
    	m_sse_max_minor = 0; 
    } 
    m_ext[cpuid::SS] =             (m_features_edx & (1 << 27)) == 0 ? false : true;
    m_ext[cpuid::HTT] =    (m_features_edx & (1 << 28)) == 0 ? false : true;
    m_ext[cpuid::TM] =             (m_features_edx & (1 << 29)) == 0 ? false : true;
    m_ext[cpuid::PBE] =    (m_features_edx & (1 << 31)) == 0 ? false : true;

    if((m_ext[cpuid::SSE3] =  (m_features_ecx & (1 << 0)) == 0 ? false : true) == true)
    { 
    	m_sse_max_major = 3; 
    	m_sse_max_minor = 0; 
    } 
    m_ext[cpuid::MONITOR] =        (m_features_ecx & (1 << 3)) == 0 ? false : true;
    m_ext[cpuid::DS_CPL] =         (m_features_ecx & (1 << 4)) == 0 ? false : true;
    m_ext[cpuid::VMX] =            (m_features_ecx & (1 << 5)) == 0 ? false : true;
    m_ext[cpuid::SMX] =            (m_features_ecx & (1 << 6)) == 0 ? false : true;
    m_ext[cpuid::EST] =            (m_features_ecx & (1 << 7)) == 0 ? false : true;
    m_ext[cpuid::TM2] =            (m_features_ecx & (1 << 8)) == 0 ? false : true;
    m_ext[cpuid::SSSE3] =          (m_features_ecx & (1 << 9)) == 0 ? false : true;
    m_ext[cpuid::CNXT_ID] =        (m_features_ecx & (1 << 10)) == 0 ? false : true;
    m_ext[cpuid::CMPXCHG16B] =     (m_features_ecx & (1 << 13)) == 0 ? false : true;
    m_ext[cpuid::xTPR_Update_Control] = (m_features_ecx & (1 << 14)) == 0 ? false : true;
    m_ext[cpuid::PDCM] =           (m_features_ecx & (1 << 15)) == 0 ? false : true;
    m_ext[cpuid::DCA] =            (m_features_ecx & (1 << 18)) == 0 ? false : true;
    if((m_ext[cpuid::SSE4_1] =             (m_features_ecx & (1 << 19)) == 0 ? false : true) == true)
    { 
    	m_sse_max_major = 4; 
    	m_sse_max_minor = 1; 
    } 
    if((m_ext[cpuid::SSE4_2] =             (m_features_ecx & (1 << 20)) == 0 ? false : true) == true)
    { 
    	m_sse_max_major = 4; 
    	m_sse_max_minor = 2; 
    } 
    m_ext[cpuid::POPCNT] =         (m_features_ecx & (1 << 23)) == 0 ? false : true;
}
void CPUID::parse_cpuid_ext_2(void)
{
    size_t eax, ebx, ecx, edx;
    
    eax = 0x80000002;
    asm volatile("cpuid;":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(eax));
    
    *(uint32_t*)(m_cpu_brand + 0) = (uint32_t)eax;
    *(uint32_t*)(m_cpu_brand + 4) = (uint32_t)ebx;
    *(uint32_t*)(m_cpu_brand + 8) = (uint32_t)ecx;
    *(uint32_t*)(m_cpu_brand + 12) = (uint32_t)edx;
    m_cpu_brand[16] = 0;
    
    if(m_max_ext_input >= 0x80000003)
    {
        eax = 0x80000003;
        asm volatile("cpuid;":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(eax));    

        *(uint32_t*)(m_cpu_brand + 16) = (uint32_t)eax;
        *(uint32_t*)(m_cpu_brand + 20) = (uint32_t)ebx;
        *(uint32_t*)(m_cpu_brand + 24) = (uint32_t)ecx;
        *(uint32_t*)(m_cpu_brand + 28) = (uint32_t)edx;
        m_cpu_brand[32] = 0;
    }   
    
    if(m_max_ext_input >= 0x80000004)
    {
        eax = 0x80000004;
        asm volatile("cpuid;":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(eax));    

        *(uint32_t*)(m_cpu_brand + 32) = (uint32_t)eax;
        *(uint32_t*)(m_cpu_brand + 36) = (uint32_t)ebx;
        *(uint32_t*)(m_cpu_brand + 40) = (uint32_t)ecx;
        *(uint32_t*)(m_cpu_brand + 44) = (uint32_t)edx;
        m_cpu_brand[48] = 0;
    } 
}

void CPUID::parse_cpuid_ext_6(void)
{
    size_t eax, ebx, ecx, edx;
    
    eax = 0x80000006;
    asm volatile("cpuid;":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(eax));
    
    m_l2_assoc = (uint8_t)((ecx >> 12) & 0xF);
    m_l2_cache_size = (uint16_t)((ecx >> 16) & 0xFFFF);
    m_l2_cache_line_size = (uint8_t)(ecx & 0xFF);
}

void CPUID::parse_cpuid_ext_0(void)
{
    size_t eax;
    
    eax = 0x80000000;
    asm volatile("cpuid;":"=a"(eax):"a"(eax));
    
    m_max_ext_input = (uint32_t)eax;
}

void CPUID::parse_cpuid_basic_A(void)  
{
    size_t eax, ebx, ecx, edx;
        
    eax = 0x0A;
    asm volatile("cpuid;":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(eax));

        m_perfmon.version = (uint8_t)(eax & 0xFF);
        
        /* if version == 0, performance monitoring is not supported, and lets set all the other values to 0 */
        if(!m_perfmon.version)
        {
                eax = ebx = 0;
                ecx = edx = 0;
        }

        m_perfmon.available_events = ebx;

        m_perfmon.ncounters = (uint8_t)((eax >> 8) & 0xFF);
        m_perfmon.counter_width = (uint8_t)((eax >> 16) & 0xFF);
        m_perfmon.ebx_width = (uint8_t)((eax >> 24) & 0xFF);

        m_perfmon.nC0 = (uint8_t)(edx & 0x0F);
        m_perfmon.nC1 = (uint8_t)((edx >> 4) & 0x0F);
        m_perfmon.nC2 = (uint8_t)((edx >> 8) & 0x0F);
        m_perfmon.nC3 = (uint8_t)((edx >> 12) & 0x0F);
        m_perfmon.nC4 = (uint8_t)((edx >> 16) & 0x0F);
}

void CPUID::parse_cpuid_basic_4(void)
{
    size_t eax, ebx, ecx, edx;
    size_t i;
   
    m_cache_count = 0;
   
    for(i = 0; i < 32; i++)
    {
        eax = 4;
        ecx = i;
        asm volatile("cpuid;":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(eax));
        
        if(!(eax & 0x0F)){break;}
        
        m_cache_info->type = (uint8_t)((eax >> 0) & 0x0F);
        m_cache_info->level = (uint8_t)((eax >> 5) & 0x03);
        
        m_cache_info->ways = (uint8_t)((ebx >> 22) & 0xFF);
        m_cache_info->partitions = (uint8_t)((ebx >> 12) & 0xFF);
        m_cache_info->line_size = (uint16_t)((ebx >> 0) & 0x3FF);
        m_cache_info->sets = ecx;
        
        m_cache_info->cache_size = (uint32_t)((uint32_t)(m_cache_info->ways + 1) * 
                                                  (uint32_t)(m_cache_info->partitions + 1) * 
                                                  (uint32_t)(m_cache_info->line_size + 1) * 
                                                  (uint32_t)(m_cache_info->sets + 1));
        m_cache_count++;                                      
    }
}

void CPUID::parse_cpuid_basic_2(void)
{
    size_t eax, ebx, ecx, edx;
        
    eax = 2;
    asm volatile("cpuid;":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(eax));

}

void CPUID::parse_cpuid_basic_1(void)
{
    size_t eax, ebx, ecx, edx;
    
    eax = 1;
    asm volatile("cpuid;":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(eax));
    
    m_features_ecx = ecx;
    m_features_edx = edx;
    
    m_stepping = (uint8_t)(eax & 0xF);
    m_model = (uint8_t)((eax >> 4) & 0xF);
    m_family = (uint8_t)((eax >> 8) & 0xF);
    m_type = (uint8_t)((eax >> 12) & 0x3);
    m_ext_model = (uint8_t)((eax >> 16) & 0xF);
    m_ext_family = (uint8_t)((eax >> 20) & 0xFF);
    
    m_cache_line_size = (uint16_t)(((ebx >> 8) & 0xFF) * 8);
}

void CPUID::parse_cpuid_basic_0(void)
{
    size_t eax, ebx, ecx, edx;
    
    eax = 0;
    asm volatile("cpuid;":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(eax));

    m_max_basic_input = (uint32_t)eax;
    *(uint32_t*)(m_cpu_signature + 0) = (uint32_t)ebx;
    *(uint32_t*)(m_cpu_signature + 4) = (uint32_t)edx;
    *(uint32_t*)(m_cpu_signature + 8) = (uint32_t)ecx;
    m_cpu_signature[12] = 0;
}
void CPUID::parse()
{
	m_cpu_brand[0] = 0;
    
    parse_cpuid_basic_0();
    if(m_max_basic_input >= 0x01)
    {
    	parse_cpuid_basic_1(); 
    	parse_cpuid_features();
    }
    if(m_max_basic_input >= 0x02)
    {
    	parse_cpuid_basic_2();
    }
    if(m_max_basic_input >= 0x04)
    {
    	parse_cpuid_basic_4();
    }
    parse_cpuid_basic_A();

    parse_cpuid_ext_0();
    if(m_max_ext_input >= 0x80000002)
    {
    	parse_cpuid_ext_2();
    }
    if(m_max_ext_input >= 0x80000006)
    {	
    	parse_cpuid_ext_6();
    }
}