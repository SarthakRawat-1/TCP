/*
 * TCP Server Implementation in C
 * Listens for incoming connections, reads client data,
 * and sends a simple response.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8181  // Server listening port

int main() {
    int s;          // Server socket file descriptor
    int c;          // Client connection file descriptor
    socklen_t addrlen; // Client address structure length
    char buf[512];  // Data buffer for client communication
    char *data;     // Response message pointer

    // Address structures for server and client
    struct sockaddr_in srv, cli;

    // Initialize server/client address structures to zero
    memset(&srv, 0, sizeof(srv));
    memset(&cli, 0, sizeof(cli));

    // Create TCP socket:
    // AF_INET = IPv4
    // SOCK_STREAM = TCP
    // 0 = Default protocol
    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s < 0) {
        printf("socket() error\n");
        return -1;
    }

    // Configure server address structure:
    srv.sin_family = AF_INET;              // IPv4 address family
    srv.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on all interfaces (0.0.0.0)
    srv.sin_port = htons(PORT);            // Port in network byte order

    // Bind socket to server address:
    // Associates socket with server IP:PORT combination
    if (bind(s, (struct sockaddr *)&srv, sizeof(srv))) {
        printf("bind() error\n");
        close(s);
        return -1;
    }

    // Put socket in listening state:
    // 5 = backlog queue size (max pending connections)
    if (listen(s, 5)) {
        printf("listen() error\n");
        close(s);
        return -1;
    }

    printf("Listening on 0.0.0.0:%d\n", PORT);

    // Accept incoming connection:
    // Blocks until client connects
    c = accept(s, (struct sockaddr *)&srv, &addrlen);

    if (c < 0) {
        printf("accept() error\n");
        close(s);
        return -1;
    }

    printf("Client connected\n");

    // Read client data (up to 511 bytes + null terminator)
    read(c, buf, 511);
    
    // Prepare response message
    data = "httpd v1.0\n";
    
    // Send response to client
    write(c, data, strlen(data));

    // Cleanup connections
    close(c);  // Close client socket
    close(s);  // Close server socket

    return 0;
}

// Start the server. Open another terminal window and write :- env - telnet localhost 8181 and then we can send a mock request to our server.
