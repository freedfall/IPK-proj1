#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdint.h>

typedef struct UDPClient {
    char* host;
    int port;
    int sockfd;
} UDPClient;

UDPClient* create_UDPClient(const char* host, int port);
void run_UDPClient(UDPClient* client);
void destroy_UDPClient(UDPClient* client);

#endif
