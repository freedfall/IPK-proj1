#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>

typedef struct TCPClient {
    char* host;
    int port;
    int sockfd;
} TCPClient;

TCPClient* create_TCPClient(const char* host, int port);
void run_TCPClient(TCPClient* client);
void destroy_TCPClient(TCPClient* client);

#endif
