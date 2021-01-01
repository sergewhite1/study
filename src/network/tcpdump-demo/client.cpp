#include <cstring>
#include <iostream>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
  int fd = 0;
  int ret = 0;

  do {

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd != -1) {
      std::cout << "Socket created success. fd=" << fd << std::endl;
    } else {
      std::cout << "Socket creation failed!" << std::endl;
      ret =1;
      break;
    }

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(4040);

    int connect_res = connect(fd, (const sockaddr*)(&server_addr), sizeof(server_addr));
    if (connect_res == 0) {
      std::cout << "Connect successfull." << std::endl;
    } else {
      std::cout << "Connect failed! " << gai_strerror(connect_res) << std::endl;
      std::cout << "Errno=" << errno << " : " << strerror(errno) << std::endl;
      ret = 1;
      break;
    }

    const char buff[]="Hello_ABC";
    std::cout << "buff=" << buff << std::endl;
    int write_res = write(fd, buff, sizeof(buff));
    std::cout << "write_res=" << write_res;
    if (write_res != -1) {
      std::cout << " success" << std::endl;
    } else {
      std::cout << " failed! " << gai_strerror(write_res) << std::endl;
      std::cout << "Errno=" << errno << " : " << strerror(errno) << std::endl;
      ret = 1;
      break;
    }

  } while(0);

  if (fd) {
    close(fd);
  }

  return ret;
}
