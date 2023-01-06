#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 2048

int main() {
  // == create socket == //
  const int CHOOSE_PROTOCOL_AUTOMATICALLY = 0;
  int socket_fd = socket(AF_INET, SOCK_STREAM, CHOOSE_PROTOCOL_AUTOMATICALLY);
  if (socket_fd == -1) {
    perror("webserver (socket)");
    return 1;
  }
  printf("socket created succesfully\n");

  // == bind socket == //
  const int port = 8080;
  struct sockaddr_in host_addr;
  int host_addrlen = sizeof(host_addr);

  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(port);
  host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socket_fd, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
    perror("webserver (binds)");
    return 1;
  }
  printf("socket succesfully bound to address\n");

  // == start listening on socket == //
  if (listen(socket_fd, SOMAXCONN)) {
    perror("webserver (listen)");
    return 1;
  }
  printf("socket listening for connections\n");

  char buffer[BUFFER_SIZE];
  char resp[] = "HTTP/1.0 200 OK\r\n"
                "Server: webserver-c\r\n"
                "Content-type: text/html\r\n\r\n"
                "<html>hello, world</html>\r\n";
  while (1) {
    // == accept incoming connection on new socket == //
    int new_socket_fd = accept(socket_fd, (struct sockaddr *)&host_addr,
                               (socklen_t *)&host_addrlen);
    if (new_socket_fd < 0) {
      perror("webserver (accept)\n");
      continue;
    }
    printf("connection accepted \n");

    // == read from socket == //
    int read_ret = read(new_socket_fd, buffer, BUFFER_SIZE);
    if (read_ret < 0) {
      perror("webserver (read)\n");
      continue;
    }

    // == write to socket == //
    int write_ret = write(new_socket_fd, resp, strlen(resp));
    if (write_ret < 0) {
      perror("webserver (write)\n");
      continue;
    }

    close(new_socket_fd);
  }

  return 0;
}
