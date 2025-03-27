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
  struct sockaddr_in client_address;

  // Specifying the address
  memset(&client_address, 0, sizeof(client_address));
  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(8080);
  client_address.sin_addr.s_addr = INADDR_ANY;

  //  Ask a Connection 
  if (connect(fd, (struct sockaddr *)&client_address, sizeof(client_address)) < 0)
  {
    perror("Connection failed : ");
    close(fd);
    return 1;
  }
  
  cout << "Connection successful" << endl;

  close(fd);


  return 0;
}