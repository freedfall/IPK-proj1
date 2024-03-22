# Changelog

[v1.0.0] - 2023-03-20

### 2023-03-18

Implemented basic TCP client functionality in TCP_client.c:

Functions for creating, destroying, and running the TCP client.

Connecting to the server and sending/receiving messages.

Implemented basic UDP client functionality in UDP_client.c:

Functions for creating, destroying, and running the UDP client.

Sending requests to the server and receiving/handling responses.

### 2023-03-19

Added main_logic.c to handle command line arguments and run the appropriate client based on the mode specified (TCP or UDP).

Enhanced UDP client functionality in UDP_client.c:

Added create_request function to create requests with proper formatting.

Added handle_response function to handle responses from the server and print them with appropriate status messages (OK or ERR).

Added corresponding header files for TCP_client, UDP_client.

### 2023-03-20

Made a repository

Improved signal handling in TCP_client.c:

Added SIGINT (Ctrl+C) handling to gracefully close the TCP client.

Refactored code to improve modularity and maintainability:

Moved the main loop for TCP and UDP clients to run_TCPClient and run_UDPClient functions, respectively.

Separated functions into appropriate source files and header files.

Fixed memory management issues:

Handled possible memory leaks by adding proper memory deallocation in destroy_TCPClient, destroy_UDPClient, and destroy_IPKCPCClient functions.

Ensured that all dynamically allocated memory is properly freed before exiting the program.

Added License

### 2023-03-21

Implemented connection to domain names both for tcp and udp clients

Deleted ipkcpc.c, ipkcpc.h files for being useless

