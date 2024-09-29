#ifndef COMP8005_ASSIGNMENT1_COMMON_H
#define COMP8005_ASSIGNMENT1_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>
#include <time.h>
#include "linkedList.h"

#define BUF_SIZE 4096
#define PASS_LEN 6
#define PASS_ARR_LEN 95
#define DEFAULT_DIR "/etc/shadow"

static const char passwd_arr[] = {
        '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u','v', 'w', 'x', 'y', 'z', '{', '|', '}', '~',
        '0', '1', '2', '3','4', '5', '6', '7', '8', '9', ':', ';', '<', '=','>', '?',
        '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J','K', 'L', 'M','N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        };

void parse_command(int argc, char *argv[], char* file_directory, LinkedList* user_list);
void option_init(char* file_directory);
int read_from_shadow(char* file_directory, char* file_list);
void find_user(char* file_list, LinkedList* user_list);
void save_user(char* user_info, LinkedList* user_list, int i);
void save_userinfo(char* user_info, LinkedList* user_list, int i);
void compare_password_with_salt(LinkedList *user_list);
void recursive_init(LinkedList *user_list, int passwd_len, int user_index);
void brute_force_crack(LinkedList *user_list, char* str, int index, int ptr, int user_index, int* flag);
void free_heap_memory(LinkedList *user_list);



#endif //COMP8005_ASSIGNMENT1_COMMON_H
