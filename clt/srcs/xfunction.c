/*
** xfunction.c for xfunction in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Mar 26 18:15:05 2014 Mehdi Chouag
** Last update Fri Apr 18 17:51:21 2014 ribeaud antonin
*/

#include <stdlib.h>
#include "Client.h"

int	xbind(int sockfd, struct sockaddr_in *addr, socklen_t addrlen)
{
  int	rbind;

  rbind = bind(sockfd, (const struct sockaddr *)addr, addrlen);
  if (rbind == -1)
    close(sockfd);
  return (rbind);
}

int	xsocket(int domain, int type, int protocol)
{
  int	fd;

  fd = socket(domain, type, protocol);
  return (fd);
}

int	xaccept(int sockfd, struct sockaddr_in *addr, socklen_t *len)
{
  int	ret;

  ret = accept(sockfd, (struct sockaddr *)addr, len);
  return (ret);
}

int	xlisten(int sockfd, int backlog)
{
  int	ret;

  ret = listen(sockfd, backlog);
  return (ret);
}

int	xconnect(int sockfd, struct sockaddr_in *addr, socklen_t addrlen)
{
  int	ret;

  ret = connect(sockfd, (const struct sockaddr *)addr, addrlen);
  return (ret);
}
