#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#define close closesocket
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080
#define MAXLINE 1024

#ifdef _WIN32
void cleanup() { WSACleanup(); }
#endif

int main() {
  WSADATA wsData;
  if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
    perror("WSA Startup error: \n");
    return 0;
  }
  
  atexit(cleanup);
#endif

  int sockfd;
  char buffer[MAXLINE];
  char *hello = "hello from client";
  struct sockaddr_in servaddr;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation error");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  int n;
  unsigned int len;
  sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
  printf("hello message sent\n");
  
  n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
  
  buffer[n] = '\0';
  printf("server: %s\n", buffer);
  
  close(sockfd);
  return 0;
}

