#include "erproc.h"

#define BUFSIZE 81

int Socket(int domain, int type, int protocol) {
  int res = socket(domain, type, protocol);
  if (res == -1) {
    perror("Socket failed.");
    exit(EXIT_FAILURE);
  }
  return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  int res = bind(sockfd, addr, addrlen);
  if (res == -1) {
    perror("Bind failed.");
    exit(EXIT_FAILURE);
  }
}

ssize_t Recv(int sockfd, void *buf, size_t len, int flags) {
  ssize_t res = recv(sockfd, buf, len, flags);
  if (res == -1) {
    perror("Recv failed.");
    exit(EXIT_FAILURE);
  }
  return res;
}

ssize_t Send(int fd, const void *buf, size_t n, int flags) {
  ssize_t res = send(fd, buf, n, flags);
  if (res == -1) {
    perror("Send failed.");
    exit(EXIT_FAILURE);
  }
  return res;
}

struct hostent *Gethostbyaddr(const char *addr, int len, int type) {
  struct hostent *res = gethostbyaddr(addr, len, type);
  if (res == NULL) {
    perror("Gethostbyaddr failed");
    exit(EXIT_FAILURE);
  }
  return res;
}

char *Inet_ntoa(struct in_addr in) {
  char *res = inet_ntoa(in);
  if (res == NULL) {
    perror("Inet_ntoa failed");
    exit(EXIT_FAILURE);
  }
  return res;
}

int Inet_pton(int af, const char *src, void *dst) {
  int res = inet_pton(af, src, dst);
  if (res == 0) {
    printf(
        "src does not contain a character string "
        "representing a valid network "
        "address in the specified address family.\n");
    exit(EXIT_FAILURE);
  }
  if (res == -1) {
    perror("Inet_pton failed.");
    exit(EXIT_FAILURE);
  }
  return res;
}

int Getsockname(int serv, struct sockaddr *servaddr, socklen_t *addrlen) {
  int res = getsockname(serv, servaddr, addrlen);
  if (res == -1) {
    perror("Getsockname failed");
    exit(EXIT_FAILURE);
  }
  return res;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  int res = accept(sockfd, addr, addrlen);
  if (res == -1) {
    perror("Accept failed.");
    exit(EXIT_FAILURE);
  }
  return res;
}

pid_t Fork() {
  pid_t res = fork();
  if (res == -1) {
    perror("Fork failed.");
    exit(EXIT_FAILURE);
  }
  return res;
}

int Listen(int sockfd, int backlog) {
  int res = listen(sockfd, backlog);
  if (res == -1) {
    perror("Listen failed.");
    exit(EXIT_FAILURE);
  }
  return res;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  int res = connect(sockfd, addr, addrlen);
  if (res == -1) {
    perror("Connect failed.");
    exit(EXIT_FAILURE);
  }
  return res;
}
