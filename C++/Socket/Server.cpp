#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

using namespace std;

const int PORT = 8080;

int main() {

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    if (fd < 0)
    {
        perror("Socket failed");
        return -1;
    }
    
    cout << "Socket created successfully" << endl;

    // Binding a socket 
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; // Bind to any network interface

    if (bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(fd);
        return 1;
    }
    
    cout << "Socket successfully bound to "<< PORT << endl;


    // Listening for connections
    if (listen(fd, SOMAXCONN))
    {
        perror("Listen failed");
        close(fd);
        return -1;
    }
    

    // Accepting connection
    while (true)
    {
        int client_fd = accept(fd, (struct sockaddr * )&client_addr, &client_len);
        if (client_fd < 0)
        {
            perror("Accept failed");
            continue;
        }

        cout << "Accepted connection from client" << endl;

        //Handling client
        char buffer[1024];
        int bytes_received;

        bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);

        if (bytes_received < 0)
        {
            perror("Error in receiving data");
        }else {
            
            buffer[bytes_received] =  '\0';
            cout << "Client message: " << buffer <<endl;

            const char *response = "Message received";
            send(client_fd, response, strlen(response), 0);

        }
    
        close(client_fd);
        cout << "Client disconnected" << endl;
        
    }
    
    
    close(fd);

    return 0;
}