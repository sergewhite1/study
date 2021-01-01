#include <cstring>
#include <iostream>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
  int listener_fd = 0;
  int fd = 0;
  int ret = 0;

  do {
    listener_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listener_fd != -1) {
      std::cout << "Socket created success. listener_fd=" << listener_fd << std::endl;
    } else {
      std::cout << "Socket creation failed!" << std::endl;
      ret = 1;
      break;
    }

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(4040);

    int bind_res = bind(listener_fd, (const sockaddr*)(&server_addr), sizeof(server_addr));
    if (bind_res == 0) {
      std::cout << "Bind success." << std::endl;
    } else {
      std::cout << "Bind failed!" << gai_strerror(bind_res) << std::endl;
      std::cout << "Errno=" << errno << " : " << strerror(errno) << std::endl;
    }

    int listen_res = listen(listener_fd, 1);
    if (listen_res == 0) {
      std::cout << "Listen success." << std::endl;
    } else {
      std::cout << "Listen failed!" << gai_strerror(listen_res) << std::endl;
      std::cout << "Errno=" << errno << " : " << strerror(errno) << std::endl;
    }

    int fd = accept(listener_fd, NULL, NULL);
    if (fd <= 0) {
      std::cout << "Accept failed!" << gai_strerror(fd) << std::endl;
      std::cout << "Errno=" << errno << " : " << strerror(errno) << std::endl;
      ret = 1;
      break;
    }

    std::cout << "Accept success. fd=" << fd << std::endl;

    char buff[1024];
    int read_res = read(fd, buff, sizeof(buff));
    std::cout << "read_res=" << read_res;
    if (read_res != -1) {
      std::cout << " sucess" << std::endl;
      std::cout << "buff=" << buff << std::endl;
    } else {
      std::cout << " failed!" << gai_strerror(read_res) << std::endl;
      std::cout << "Errno=" << errno << " : " << strerror(errno) << std::endl;
      ret = 1;
      break;
    }
  } while (0);

  if (fd) {
    close(fd);
  }

  if(listener_fd) {
    close(listener_fd);
  }

  return ret;
}
