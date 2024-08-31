/**
 * Author: OscarPortillo37
 * Description: Notes on data structures used for sockets (courtesy of Beej's 
 * Network Programming Guide)
 * Date: 8/28/2024
 */

#include <stdint.h>

// Socket file descriptors use ints, everything else tends to use structs
int sockdescr;


/**
 * addrinfo struct (more recent invention used to prep socket address structs
 * for later use)
 * 
 * struct is also used in host name & service name lookups
 * 
 * typically organized as a LinkedList data structure w/ each node as a diff
 * socket address
 */
struct addrinfo {
    int                 ai_flags;       //AI_PASSIVE, AI_CANONNAME, etc.
    int                 ai_family;      //AF_INET, AF_INET6, AF_UNSPEC
    int                 ai_socktype;    //SOCK_STREAM, SOCK_DGRAM
    int                 ai_addrlen;     // size of ai_addr in bytes (IPv4 v IPv6)
    struct sockaddr*    ai_addr;        //struct sockaddr_in or sockaddr_in6
    char*               ai_canonname;   // full canonical hostname              
    struct addrinfo*    ai_next;        //LinkedList - next node
};


// General format & is used when connect() -> typically not packed manually,
// as it's tedious. Will be cast into this from sockaddr_in strct.
struct sockaddr {
    short int   sa_fam;         // address family, AF_XXXX (see addrinfo)
    char        sa_data[14];    // 14 bytes of protocol addresss
};


// --------------------------------------- IPv4 ------------------------------------
// (IPv4 only --> see sockaddr_in6 for IPv6)
struct sockaddr_in{
    short int           sin_family;     // Address family, AF_INET
    unsigned short int  sin_port;       // Port no., Network Byte Order
    struct in_addr      sin_addr;       // Internet address, Network Byte Order
    unsigned char       sin_zero[8];    // Filler for same size as struct sockaddr
};

// Struct for IPv4 IP addr (made a struct for historical reasons - used to be union?)
struct in_addr{
    uint32_t    s_addr;     // 4 bytes (recall IPv4 has four bytes separated by ".")
};


// --------------------------------------- IPv6 ------------------------------------
// (IPv6 only --> see sockaddr_in for IPv4)
struct sockaddr_in6 {
    uint16_t            sin6_family;    // Address family, AF_INET6
    uint16_t            sin6_port;      // Port no., Network Byte Order
    uint32_t            sin6_flowinfo;  // IPv6 flow info (sequencing, QoS for flow, etc)
    struct in_addr6     sin6_addr6;     // IPv6 address, Network Byte Order
    uint32_t            sin6_scopeID;   // Scope ID (local-link addr)
};

struct in_addr6 {
    unsigned char       s6_addr[16];    // IPv6 address
};


// ---------------------------- IP agnostic (works for both) ------------------------
struct sockaddr_storage {
    unsigned short  ss_family;    // address family

    // all this is padding, implementation specific - ignore:
    char            __ss_pad1[_SS_PADSIZE1];
    int64_t         __ss_align;       
    char            __ss_pad2[_SS_PADSIZE2];
};

