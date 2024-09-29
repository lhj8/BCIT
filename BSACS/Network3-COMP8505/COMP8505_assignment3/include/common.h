#ifndef COMP_8505_ASSIGNMENT3__COMMON_H
#define COMP_8505_ASSIGNMENT3__COMMON_H


#include <stdio.h>
#include <sys/prctl.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stddef.h>
#include <limits.h>
#include <sys/types.h>
#include <getopt.h>
#include <regex.h>
#include <inttypes.h>
#include <pcap/bpf.h>
#include <pcap/pcap.h>
#include <pcap.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <setjmp.h>



#define DEFAULT_PORT 53000
#define TRUE 1
#define FALSE 0
#define MASK "bash_ass3"

void check_root_user(void);
char encrypt_decrypt(char input);


#endif COMP_8505_ASSIGNMENT3_COMMON_H
