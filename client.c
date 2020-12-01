#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>

#define PORT      5000
#define DATA_SIZE 300
#define SI struct in_addr
#define SA struct sockaddr

int main(void)
{
  int sockfd, len;
  char buf[DATA_SIZE];
  //struct hostent *he;
  struct sockaddr_in theiraddr;
  
  //he = gethostbyname("localhost");
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  theiraddr.sin_family = AF_INET;
  theiraddr.sin_port = htons(PORT);
  //theiraddr.sin_addr = *((SI*) he->h_addr);
  theiraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  bzero(&(theiraddr.sin_zero), 8);
  
  printf("[!] Iniciando conexão...\n");
  
  int cntg = connect(sockfd, (SA*)&theiraddr, sizeof(SA));
  
  if (cntg == -1)
  {
    printf("[!] Erro ao conectar!\n");
    exit(0);
  }
  printf("[!] Conectado!\n");
  
  while (1)
  {
    bzero(buf, sizeof(buf));
    int n = 0;
    while((buf[n++] = getchar()) != '\n');
    send(sockfd, buf, sizeof(buf), 0);
    
    bzero(buf, sizeof(buf));
    recv(sockfd, buf, DATA_SIZE, 0);
    printf("%s", buf);
  }
}