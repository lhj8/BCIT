#ifndef COMP8005_ASSIGNMENT1_COMMON_H
#define COMP8005_ASSIGNMENT1_COMMON_H

#include <assert.h>
#include <crypt.h>
#include <omp.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <pthread.h>
#include "linkedList.h"
#include "client.h"

#define BUF_SIZE 4096
#define PASS_LEN 15
#define PASS_ARR_LEN 95
#define DEFAULT_SINGLE_THREAD 1
#define DEFAULT_PORT_SERVER 53000
#define TRUE 1
#define FALSE 0
#define OPT_ONE "1"
#define OPT_TWO "2"
#define OPT_THREE "3"
#define OPT_FOUR "4"
#define OPT_FIVE "5"
#define OPT_SIX "6"
#define COMMAND_SEND "send"
#define COMMAND_USER "user"
#define COMMAND_START "start"
#define COMMAND_EXIT "exit"
#define COMMAND_FOUND "found"
#define COMMAND_DISPLAY "display"
#define COMMAND_FLUSH "flush"
#define EPOLL_SIZE 10


static const char *passwd_arr = "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "0123456789~!@#+$%^&*_`-=.,"
                                "(){|}:;<>?[\\]^ \"\'";

int read_from_shadow(char *file_directory, char *file_list);
void find_user(char *file_list, LinkedList *user_list);
void save_user(char *user_info, LinkedList *user_list, int i);
void save_userinfo(char *user_info, LinkedList *user_list, int i);
void salt_setting(LinkedList *user_list);
void free_heap_memory(LinkedList *user_list);
void password_generator(int *ptr1, int *ptr2, int temp_pwlen, LinkedList *user_list, int user_index, void* opts);

#endif // COMP8005_ASSIGNMENT1_COMMON_H
