#ifndef ERPROC_H
#define ERPROC_H

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

ssize_t Recv(int sockfd, void *buf, size_t len, int flags);

ssize_t Send(int fd, const void *buf, size_t n, int flags);

struct hostent *Gethostbyaddr(const char *addr, int len, int type);

char *Inet_ntoa(struct in_addr in);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Inet_pton(int af, const char *src, void *dst);

int Getsockname(int serv, struct sockaddr *servaddr, socklen_t *addrlen);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

pid_t Fork();

int Listen(int sockfd, int backlog);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

#endif
