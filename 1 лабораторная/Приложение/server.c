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

int main() {
  int serv = socket(AF_INET, SOCK_DGRAM, 0);
  if (serv == -1) {
    perror("Socket failed.");
    exit(EXIT_FAILURE);
    return serv;
  }

  struct sockaddr_in servaddr = {0}, cliaddr = {0};
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = 0;

  socklen_t addrlen = sizeof servaddr;

  int res = bind(serv, (struct sockaddr *)&servaddr, addrlen);
  if (res == -1) {
    perror("Bind failed.");
    exit(EXIT_FAILURE);
  }

  getsockname(serv, (struct sockaddr *)&servaddr, &addrlen);
  printf("Server: port - %d\n", ntohs(servaddr.sin_port));

  int hostportp;
  char *hostaddrp;
  socklen_t clilen = sizeof cliaddr;

  while (1) {
    char buf[3];

    ssize_t msglen = recvfrom(serv, buf, BUFSIZE, MSG_WAITALL,
                              (struct sockaddr *)&cliaddr, &clilen);
    if (msglen == -1) {
    perror("Recvfrom failed.");
    exit(EXIT_FAILURE);
    return msglen;
    }
    buf[msglen] = '\0';


    hostaddrp = inet_ntoa(cliaddr.sin_addr);
    hostportp = ntohs(cliaddr.sin_port);

    char format_msg[BUFSIZE];

    printf("Message: %s\nClient IP: %s\nClient port: %d\n\n", buf,
            hostaddrp, hostportp);

    int check = atoi(buf);
    check = check * 2;
    char test[msglen];
    sprintf(test,"%d", check);

    sprintf(format_msg, "Message: %s\nClient IP: %s\nClient port: %d\n\n", test,
            hostaddrp, hostportp);

    msglen = sendto(serv, format_msg, strlen(format_msg), 0,
                    (struct sockaddr *)&cliaddr, clilen);
    if (msglen == -1) {
    perror("Sendto failed.");
    exit(EXIT_FAILURE);
    return msglen;
    }

    struct timeval timeout;
    timeout.tv_sec = 20;

    if (setsockopt(serv, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) ==
        -1) {
      printf("Recv timeout\n");
      break;
    }
  }

  close(serv);
  return 0;
}
