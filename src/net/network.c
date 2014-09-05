#include <net/network.h>

typedef struct
{
    IP_t src;
    IP_t dest;
    uint8_t res;
    uint8_t prot;
    uint16_t length;
} __attribute__((packed)) updtcpPseudoHeader_t;


// compute internet checksum for "count" bytes beginning at location "addr"
uint16_t internetChecksum(void* addr, size_t count, uint32_t pseudoHeaderChecksum)
{
    uint32_t sum  = pseudoHeaderChecksum;
    uint8_t* data = addr;

    while (count > 1) // inner loop
    {
        sum   += (data[0] << 8) | data[1]; // Big Endian
        data  += 2;
        count -= 2;
    }

    if (count > 0) // add left-over byte, if any
    {
        sum += data[0] << 8;
    }

    while (sum >> 16) // fold 32-bit sum to 16 bits
    {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    return ~sum & 0xFFFF;
}

uint16_t udptcpCalculateChecksum(void* p, uint16_t length, IP_t srcIP, IP_t destIP, uint16_t protocol)
{
    updtcpPseudoHeader_t pseudo;
    pseudo.src.iIP = srcIP.iIP;
    pseudo.dest.iIP = destIP.iIP;
    pseudo.length = htons(length);
    pseudo.prot = protocol;
    pseudo.res = 0;

    uint32_t pseudoHeaderChecksum = 0;
    uint8_t* data = (uint8_t*)&pseudo;

    for (uint8_t i = 0; i < sizeof(updtcpPseudoHeader_t); i+=2)
    {
        // pseudo header contains 6 WORD
        pseudoHeaderChecksum += (data[i] << 8u) | data[i+1]; // Big Endian
    }

    return internetChecksum(p, length, pseudoHeaderChecksum);
}

bool sameSubnet(IP_t IP1, IP_t IP2, IP_t subnet)
{
    return ((IP1.iIP & subnet.iIP) == (IP2.iIP & subnet.iIP));
}
