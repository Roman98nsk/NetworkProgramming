#include <arpa/inet.h>
#include <memory.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "erproc.h"

#define BUFSIZE 81

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("ENTER:./client ADDR PORT MESSAGE");
    exit(EXIT_FAILURE);
  }
  int fd = Socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in servaddr = {0};
  socklen_t addrlen = sizeof servaddr;

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);
  servaddr.sin_port = htons(atoi(argv[2]));

  Connect(fd, (const struct sockaddr *)&servaddr, addrlen);

  for (int i = 0; i < 10; i++) {
    Send(fd, (const char *)argv[3], strlen(argv[3]), 0);

    char buf[BUFSIZE];
    int nrecv = Recv(fd, (char *)buf, BUFSIZE, 0);
    buf[nrecv] = '\0';
    printf("Recv from server : %s\n\n", buf);
    sleep(atoi(argv[3]));
  }
  close(fd);
  return 0;
}
