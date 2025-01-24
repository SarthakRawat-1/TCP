# TCP Client-Server Implementation

A simple TCP client and server demonstrating basic socket communication.

## Files
- `sockets.c` - Connects to a web server, sends HTTP HEAD request
- `srv.c` - Listens for connections, responds with version message

## Requirements
- GCC compiler
- Linux/macOS environment
- Basic network connectivity

## Client Usage
```bash
# Compile
gcc sockets.c -o client

# Run (connects to Yahoo web server)
./client

## Server Usage
# Compile
gcc srv.c -o server

# Run
./server

# In another terminal:
telnet localhost 8181
