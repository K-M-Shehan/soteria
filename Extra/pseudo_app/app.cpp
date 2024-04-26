#include <iostream>
#include <cstring>
#include <cstdio>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "your-esp8266-ip-address"
#define SERVER_PORT 80
#define MESSAGE "Hi"

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    // Set server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    // Send message to server
    if (send(sock, MESSAGE, strlen(MESSAGE), 0) < 0) {
        std::cerr << "Send failed" << std::endl;
        return -1;
    }
    std::cout << "Message sent" << std::endl;

    // Close socket
    close(sock);
    return 0;
}
