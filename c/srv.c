#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

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
  return 0;
}
