#include "UDP_client.h"

// Function to create a request
uint8_t* create_request(const char* expr, size_t expr_len, size_t* request_len) {
    *request_len = 2 + expr_len;
    uint8_t* request = (uint8_t*)malloc(*request_len);
    request[0] = 0; // Opcode: Request
    request[1] = expr_len; // Payload Length
    memcpy(request + 2, expr, expr_len); // Payload Data
    return request;
}

// Function to handle the response from the server
void handle_response(const uint8_t* response, size_t response_len) {
    if (response_len < 3) {
        fprintf(stderr, "Invalid response received\n");
        return;
    }

    if (response[1] == 0) { // Status: OK
        printf("OK:%.*s\n", (int)(response_len - 3), response + 3);
    } else { // Status: Error
        printf("ERR:%.*s\n", (int)(response_len - 3), response + 3);
    }
}

// Function to create a UDP client
UDPClient* create_UDPClient(const char* host, int port) {
    UDPClient* client = (UDPClient*)malloc(sizeof(UDPClient));
    client->host = strdup(host);
    client->port = port;
    client->sockfd = -1;
    return client;
}

// Function to destroy the UDP client
void destroy_UDPClient(UDPClient* client) {
    if (client->sockfd != -1) {
        close(client->sockfd);
    }
    free(client->host);
    free(client);
}

// Function to run the UDP client's main loop
void run_UDPClient(UDPClient* client) {
    // Get address info for the host
    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", client->port);
    int addr_status;
    if ((addr_status = getaddrinfo(client->host, port_str, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(addr_status));
        exit(EXIT_FAILURE);
    }

    // Create a socket
    for (p = servinfo; p != NULL; p = p->ai_next) {
        client->sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (client->sockfd != -1) {
            break;
        }
    }

    // Check if the socket is created
    if (client->sockfd == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Read input from stdin and send it to the server
    char input[512];
    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        // Send request
        size_t request_len;
        uint8_t* request = create_request(input, strlen(input), &request_len);
        sendto(client->sockfd, request, request_len, 0, p->ai_addr, p->ai_addrlen);
        free(request);

        // Receive response
        uint8_t buffer[512];
        ssize_t recv_len = recvfrom(client->sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (recv_len == -1) {
            perror("Error receiving data from server");
            exit(EXIT_FAILURE);
        }

        // Handle response
        handle_response(buffer, recv_len);
    }

    freeaddrinfo(servinfo); // Free the linked list
    close(client->sockfd);
}

