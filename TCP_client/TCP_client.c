#include "TCP_client.h"

// Global variable to keep track of whether the client should keep running
static volatile bool keep_running = true;

// Function to create a TCP client
TCPClient* create_TCPClient(const char* host, int port) {
    TCPClient* client = (TCPClient*)malloc(sizeof(TCPClient));
    client->host = strdup(host);
    client->port = port;
    client->sockfd = -1;
    return client;
}

// Function to handle SIGINT
void handle_sigint(int sig) {
    (void)sig;
    keep_running = false;
}

// Function to destroy the TCP client
void destroy_TCPClient(TCPClient* client) {
    if (client->sockfd != -1) {
        close(client->sockfd);
    }
    free(client->host);
    free(client);
}

// Function to run the TCP client's main loop
void run_TCPClient(TCPClient* client) {
    // Get address info for the host
    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int addr_status;
    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", client->port);
    if ((addr_status = getaddrinfo(client->host, port_str, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(addr_status));
        exit(EXIT_FAILURE);
    }

    // Create and connect the socket
    bool connected = false;
    for (p = servinfo; p != NULL; p = p->ai_next) {
        client->sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (client->sockfd == -1) {
            continue;
        }

        if (connect(client->sockfd, p->ai_addr, p->ai_addrlen) == 0) {
            connected = true;
            break;
        }

        close(client->sockfd);
    }

    if (!connected) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo); // Free the linked list

    // Read input from stdin and send it to the server
    char input[512];
    fgets(input, sizeof(input), stdin); // HELLO
    send(client->sockfd, input, strlen(input), 0);

    // Receive the response from the server
    char buffer[512];
    ssize_t recv_len = recv(client->sockfd, buffer, sizeof(buffer) - 1, 0);
    if (recv_len == -1) {
        perror("Error receiving data from server");
        close(client->sockfd);
        exit(EXIT_FAILURE);
    }

    if (recv_len == 0) {
        perror("Server closed connection\n");
        close(client->sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[recv_len] = '\0'; // Add null terminator to the end of the string
    printf("%s", buffer); // HELLO

    if (strncmp(buffer, "BYE", 3) == 0) {
        close(client->sockfd);
        exit(EXIT_FAILURE);
    }

    // Set up signal handler for SIGINT (handling Ctrl+C)
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = handle_sigint;
    sigaction(SIGINT, &act, NULL);

    while (1) {
        fgets(input, sizeof(input), stdin);

        // Handle Ctrl+C
        if (!keep_running) {
            strncpy(input, "BYE\n", sizeof(input) - 1);
            input[sizeof(input) - 1] = '\0';
            printf("\n%s", input);
        }
        
        // Send the input to the server
        send(client->sockfd, input, strlen(input), 0);

        // Receive the response from the server
        recv_len = recv(client->sockfd, buffer, sizeof(buffer) - 1, 0);
        if (recv_len == -1) {
            perror("Error receiving data from server");
            close(client->sockfd);
            exit(EXIT_FAILURE);
        }

        if (recv_len == 0) {
            perror("Server closed connection\n");
            close(client->sockfd);
            exit(EXIT_FAILURE);
        }

        buffer[recv_len] = '\0';
        printf("%s", buffer); // RESULT or BYE


        // Check if the server sent BYE
        if (strncmp(input, "BYE", 3) == 0 || strncmp(buffer, "BYE", 3) == 0 || !keep_running) {
            printf("hui\n");
            break;
        }
    }

    close(client->sockfd);
}

