#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#define bzero(b, len) \
    (memset((b), '\0', (len)), (void)0)
#define read(a, b, c) recv(a, b, c, 0)
#define write(a, b, c) send(a, b, c, 0)
#define close closeocket
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#endif


#define MAX 80
#define PORT 8080
#define SA struct sockaddr


void func(int sockfd) {
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        print("enter string: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n') {
            ;
        }
    }
}