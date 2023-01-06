#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
  const int CHOOSE_PROTOCOL_AUTOMATICALLY = 0;
	const int PORT = 8080;
  int socket_fd = socket(AF_INET, SOCK_STREAM, CHOOSE_PROTOCOL_AUTOMATICALLY);
  if (socket_fd == -1) {
    perror("webserver (socket)");
    return 1;
  }
  printf("socket created succesfully\n");
	/* bind(socket_fd, sockaddr *address, */
           /* address_len); */
  return 0;
}
