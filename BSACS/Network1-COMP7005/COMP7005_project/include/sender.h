#ifndef PROJECT_SENDER_H
#define PROJECT_SENDER_H

#include "common.h"
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/select.h>


struct options
{
    char *file_name;
    char *ip_out;
    in_port_t port_out;
    int fd_in;
    int fd_out;
    int proxy_socket;
    char* file_arr[200];
    int file_count;
};



/**
 * Initialize default option for client
 * STDIN, STDOUT and port number saved
 *
 * @param opts client struct settings
 */
static void options_init(struct options *opts);


/**
 * Parse input from user server IP, server port, client text files are included.
 * Set the client option struct after parsing.
 * If there is no input, it will use DEFAULT value.
 *
 * @param argc number of argument
 * @param argv client's input
 * @param opts client option struct settings
 */
static void parse_arguments(int argc, char *argv[], struct options *opts);


/**
 * Initialize connection with server.
 * After successful connection, client will get message from server to confirm it is connected.
 *
 * @param opts client option struct settings
 */
static int options_process(struct options *opts);


/**
 * Free variables that were used for client option struct setting.
 *
 * @param opts client option struct settings
 */
static void cleanup(const struct options *opts);


/**
 * If client's input was *.txt, will loop client's current directory, get all text files, and store in array.
 *
 * @param opts client option struct settings
 */
void get_file_list(struct options *opts);


void send_file(struct options *opts, fd_set* read_fds);


#endif //PROJECT_SENDER_H
