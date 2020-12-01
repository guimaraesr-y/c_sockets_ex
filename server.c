#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>

#define MAX_BUFFER 10
#define NUM_CONN 3
#define PORT 5000
#define SA struct sockaddr

int handleClient(int connfd);

int main()
{
  int sockfd, connfd, len;
  struct sockaddr_in servaddr,cli;
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);
  
  int bd = bind(sockfd, (SA*)&servaddr, sizeof(servaddr));
  if (bd < 0)
  {
    printf("[!] Erro ao iniciar servidor!");
    exit(1);
  }
  
  listen(sockfd, NUM_CONN);
  
  len = sizeof(cli);
  connfd = accept(sockfd, (SA*)&cli, &len);
  
  handleClient(connfd);
  
  return 0;
}

int handleClient(int connfd)
{
  char buf[MAX_BUFFER];
  int n;
  
  for (;;)
  {
    bzero(buf, sizeof(buf));
    recv(connfd, buf, sizeof(buf), 0);
    printf("%s", buf);
    
    bzero(buf, sizeof(buf));
    n = 0;
    while((buf[n++] = getchar()) != '\n');
    send(connfd, buf, sizeof(buf), 0);
  }
}