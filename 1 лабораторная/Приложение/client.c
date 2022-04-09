#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 256

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("ENTER:./client ADDR PORT MESSAGE");
    exit(EXIT_FAILURE);
  }
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1) {
    perror("Socket failed.");
    exit(EXIT_FAILURE);
    return fd;
  }

  struct sockaddr_in servaddr = {0};
  socklen_t addrlen = sizeof servaddr;

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);
  servaddr.sin_port = htons(atoi(argv[2]));

  for (int i = 0; i < 10; i++) {
    ssize_t res = sendto(fd, (const char *)argv[3], strlen(argv[3]), 0,
           (const struct sockaddr *)&servaddr, addrlen);
    if (res == -1) {
    perror("Sendto failed.");
    exit(EXIT_FAILURE);
    return res;
    }

sleep(atoi(argv[3]));

    char buf[BUFSIZE];
    int nrecv = recvfrom(fd, (char *)buf, BUFSIZE, 0,
                         (struct sockaddr *)&servaddr, &addrlen);
    if (nrecv == -1) {
    perror("Recvfrom failed.");
    exit(EXIT_FAILURE);
    return nrecv;
    }
    buf[nrecv] = '\0';
    printf("Recv from server : %s\n\n", buf);
  }

  close(fd);
  return 0;
}
