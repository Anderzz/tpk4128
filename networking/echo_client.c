#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(){

    int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor < 0){
        perror("Error creating socket");
        exit(1);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(65432);
    int len = sizeof(server_address);

    if (connect(socket_file_descriptor, (struct sockaddr *)&server_address, len) < 0){
        perror("Error connecting to server");
        exit(2);
    }

    char* buffer = "Hello from client!";
    if (write(socket_file_descriptor, buffer, strlen(buffer)) < 0){
        perror("Error writing to socket");
        exit(3);
    }

    char data[1024];
    memset(data, 0, 1024);
    if (read(socket_file_descriptor, data, sizeof(data)) < 0){
        perror("Error reading from socket");
        exit(4);
    }
    printf("%s\n", data);

    close(socket_file_descriptor);
    
    return 0;

}