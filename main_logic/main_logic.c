#include "main_logic.h"

void print_usage() {
    fprintf(stderr, "Usage: ipkcpc -h <host> -p <port> -m <mode> (tcp|udp)\n");
}

int main(int argc, char *argv[]) {
    char* host = NULL;
    char* mode = NULL;
    int port = -1;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) {
            host = argv[++i];
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            port = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            mode = argv[++i];
        } else {
            print_usage();
            return 1;
        }
    }

    // Check if all required arguments are present
    if (host == NULL || port == -1 || (strcmp(mode, "tcp") != 0 && strcmp(mode, "udp") != 0)) {
        print_usage();
        return 1;
    }

    // Create and run the client
    if (strcmp(mode, "tcp") == 0) {
        TCPClient* client = create_TCPClient(host, port);
        if (client == NULL) {
            fprintf(stderr, "Error: Failed to create TCP client\n");
            return 1;
        }
        run_TCPClient(client);
        destroy_TCPClient(client);
    } else {
        UDPClient* client = create_UDPClient(host, port);
        if (client == NULL) {
            fprintf(stderr, "Error: Failed to create UDP client\n");
            return 1;
        }
        run_UDPClient(client);
        destroy_UDPClient(client);
    }

    return 0;
}
