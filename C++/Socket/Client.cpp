#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

using namespace std;

const int PORT = 8081;
const char *SERVER_IP = "127.0.0.1";

int main() {

  int fd = socket(AF_INET, SOCK_STREAM, 0);  
  struct sockaddr_in client_address, server_addr;
  char buffer[1024];

  // Specifying the address
  memset(&client_address, 0, sizeof(client_address));
  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(PORT);

  //  Ask a Connection 
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
  {
    perror("Invalid server address");
    close(fd);
    return -1;
  }
  
  if (connect(fd, (struct sockaddr *)&client_address, sizeof(client_address)) < 0)
  {
    perror("Connection failed : ");
    close(fd);
    return -1;
  }
  
  cout << "Connection successful established" << endl;

  // Send a message to the server
  send(fd, buffer, strlen(buffer), 0);

  // Receive a response from the server
  int bytes_received = recv(fd, buffer,sizeof(buffer)-1,0);
  if (bytes_received > 0)
  {
    buffer[bytes_received] =  '\0';
    cout << "Server reply: " << buffer << endl;
  } else {
    cout << "Server response failed" <<endl;
  }

  close(fd);


  return 0;
}