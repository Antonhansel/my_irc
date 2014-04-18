/*
** init_funcs.c for init in /home/apollo/rendu/PSU_2013_myirc/client
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Mon Apr 14 20:23:53 2014 ribeaud antonin
** Last update Fri Apr 18 17:54:41 2014 ribeaud antonin
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Client.h"

char			*returnError(int errnum)
{
  (void)errnum;
  return ((char *)"-<strong>[Error]: </strong>Command not found");
}

int		check_ip(char *ip)
{
  int		i;
  int		count;

  i = 0;
  count = 0;
  while (ip[i] != '\0')
    {
      if (ip[i] == '.')
	count++;
      i++;
    }
  return (count);
}

char	*init_client(t_client *c)
{
  int	opt;

  opt = 1;
  c->pr = getprotobyname("TCP");
  if (check_ip(c->ip) == 3)
    {
      if ((c->fd = xsocket(AF_INET, SOCK_STREAM, c->pr->p_proto)) == -1)
	return ((char*)"-<strong>[Error]: </strong>Opening socket failed.");
      setsockopt(c->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
      c->sin.sin_family = AF_INET;
      c->sin.sin_port = htons(c->port);
      c->sin.sin_addr.s_addr = inet_addr(c->ip);
      if (xconnect(c->fd, &(c->sin), (socklen_t)sizeof(c->sin)) != -1)
	{
	  c->connected = 1;
	  return ((char*)"-<strong>[Sucess]: </strong>Connected!");
	}
    }
  return ((char*)"-<strong>[Error]: </strong>Unable to connect to server");
}
