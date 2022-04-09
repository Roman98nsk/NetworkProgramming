#include "erproc.h"
#define BUFSIZE 81

int childWork(int sockCli);

int main() {
  int sockMain = Socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in servaddr = {0};
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = 0;

  socklen_t addrlen = sizeof servaddr;

  Bind(sockMain, (struct sockaddr *)&servaddr, addrlen);

  Getsockname(sockMain, (struct sockaddr *)&servaddr, &addrlen);
  printf("Server: port - %d\n", ntohs(servaddr.sin_port));
  printf("./client 127.0.0.1 %d 3\n", ntohs(servaddr.sin_port));

  Listen(sockMain, 5);

  int sockCli = 0;
  pid_t child;

 signal(SIGCHLD, SIG_IGN);

  while (1) {
    sockCli = Accept(sockMain, 0, 0);

    child = fork();
    if (child == 0) {
      close(sockMain);
      childWork(sockCli);
      close(sockCli);
      exit(EXIT_SUCCESS);
    } else if (child > 0) {
      close(sockCli);
    } else {
      perror("Fork failed.");
      exit(EXIT_FAILURE);
    }
  }
  close(sockMain);
  return 0;
}

int childWork(int sockCli) {
  while (1) {
    char buf[3] = {0};
    ssize_t msglen = Recv(sockCli, buf, BUFSIZE, 0);
    // buf[msglen] = '\0';
    if (msglen <= 0) {
      printf("Client disconnected...\n\n");
      return 1;
    }
    char format_msg[BUFSIZE] = {0};
    sprintf(format_msg, "Message: %s\nLenght: %ld\n\n", buf, msglen);
    printf("%s", format_msg);

    Send(sockCli, format_msg, strlen(format_msg), 0);
  }
  return 0;
}

void reaper() {
  int status;
  while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0)
    ;
}
