#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>  

enum type {
    IPV4 = 4,
    IPV6 = 6,
};

typedef struct {
    enum type IP_TYPE;
    union {
        struct in_addr ipv4;
        struct in6_addr ipv6;
    } ipaddr;
} ip_t;

int main(void)
{
    ip_t addr1, addr2;
    addr1.IP_TYPE = IPV4;
    addr2.IP_TYPE = IPV6;

    
}