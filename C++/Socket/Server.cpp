#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

using namespace std;

int main() {

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    if (fd < 0)
    {
        perror("Socket failed");
        return 1;
    }
    
    cout << "Socket created successfully" << endl;

    // Binding a socket 
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY; // Bind to any network interface

    if (bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(fd);
        return 1;
    }
    
    cout << "Socket successfully bound to 8080" << endl;


    // Listening for connections
    if (listen(fd, SOMAXCONN))
    {
        perror("Listen failed");
        close(fd);
        return 1;
    }
    
    close(fd);

    return 0;
}