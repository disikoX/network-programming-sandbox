#include <sys/types.h>
#include <sys/socket.h>

int fd; // file descriptor

fd = socket(AF_INET, SOCK_STREAM, 0);

if (fd == -1) {
  
  switch (errno) {

    case EPROTONOTSUPPORT :
     std::cout << "Protocol not supported";

    case EACESS : 
     std::cout << "Permission denied";

    default:
      std::cout << "Check the Unix Manual";
      break;
  }

}


