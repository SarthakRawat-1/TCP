/*
 * TCP Client Implementation in C
 * This client connects to a web server, sends an HTTP HEAD request,
 * and prints the response headers.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

// Target server IP (Yahoo web server)
#define IP "98.137.11.164"  /* www.yahoo.com */
// HTTP port (standard web port)
#define PORT 80 /* http */

int main() {
    int s;                  // Socket file descriptor
    char buf[512];          // Buffer to store server response
    char *data;             // Pointer to hold our HTTP request

    // Structure to store server address information
    struct sockaddr_in sock;

    // HTTP HEAD request - asks server for headers only (no body)
    data = "HEAD / HTTP/1.0\r\n\r\n";  // \r\n\r\n indicates end of headers

    // Create TCP socket:
    // AF_INET = IPv4 address family
    // SOCK_STREAM = Reliable, connection-oriented byte stream (TCP)
    // 0 = Default protocol (TCP for SOCK_STREAM)
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Check if socket creation succeeded
    if (s < 0) {
        printf("socket() error");
        return -1;  // Return error code
    }

    // Configure server address structure:
    sock.sin_addr.s_addr = inet_addr(IP);  // Convert IP string to binary form
    sock.sin_port = htons(PORT);           // Convert port to network byte order
    sock.sin_family = AF_INET;             // Use IPv4 address family

    // Connect to the server:
    // s = socket descriptor
    // (struct sockaddr *)&sock = cast to generic socket address type
    // sizeof(...) = size of the address structure
    if (connect(s, (struct sockaddr *)&sock, sizeof(struct sockaddr_in)) != 0) {
        printf("connect() error");
        close(s);   // Cleanup socket before exiting
        return -1;  // Return error code
    }

    // Send HTTP HEAD request to server:
    // write() sends data through the connected socket
    // data = our request string
    // strlen(data) = length of request (without null terminator)
    write(s, data, strlen(data));

    // Clear buffer using memset (fill with zeros) before receiving data
    memset(buf, 0, 512);

    // Read server response:
    // read() will block until data is available
    // buf = buffer to store received data
    // 511 = maximum bytes to read (leaves space for null terminator)
    read(s, buf, 511);

    // Close socket connection (cleanup resources)
    close(s);

    // Print server response (HTTP headers)
    printf("\n%s\n", buf);

    return 0;  
}

