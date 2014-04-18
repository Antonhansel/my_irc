/*
** Client.c for client in /home/apollo/rendu/PSU_2013_myirc/client/srcs
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Mon Apr 14 18:25:45 2014 ribeaud antonin
** Last update Fri Apr 18 17:57:03 2014 ribeaud antonin
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Client.h"

t_local		g_local;
t_client	g_client;

void		endConnection()
{
  g_client.connected = 0;
}

int		xsend(const char *buf)
{
  int		ret;

  ret = -1;
  if (g_client.connected == 1)
    {
      ret = sendto(g_client.fd, buf, strlen(buf), 0,
		   (struct sockaddr *)&(g_client.sin),
		   (socklen_t)sizeof(g_client.sin));
      if (ret == -1)
	{
	  perror("Send ");
	  return (0);
	}
    }
  return (ret);
}

char			*xrecieve()
{
  fd_set		fdset;
  int			ret;
  socklen_t		len;
  char			buff[4096];
  struct timeval	tv;

  if (g_client.connected == 1)
    {
      len = (socklen_t)sizeof(g_client.sin);
      memset(buff, 0, 4096);
      FD_ZERO(&fdset);
      FD_SET(g_client.fd, &fdset);
      tv.tv_usec = 1;
      ret = select(g_client.fd + 1, &fdset, NULL, NULL, &tv);
      if (ret >= 0)
	{
	  if (FD_ISSET(g_client.fd, &fdset))
	    {
	      ret = recvfrom(g_client.fd, buff, sizeof(buff), 0,
			     (struct sockaddr *)&(g_client.sin), &len);
	      if (ret == -1)
		{
		  perror("Receive ");
		  return ((char*)"");
		}
	      return (strdup(buff));
	    }
	}
    }
  return ((char*)"");
}

void		initStruct()
{
  g_client.ip = NULL;
  g_local.message = NULL;
  g_local.commands[0] = strdup("/server");
  g_local.commands[1] = strdup("/nick");
  g_local.commands[2] = strdup("/list");
  g_local.commands[3] = strdup("/join");
  g_local.commands[4] = strdup("/part");
  g_local.commands[5] = strdup("/users");
  g_local.commands[6] = strdup("/send_file");
  g_local.commands[7] = strdup("/accept_file");
  g_local.commands[8] = strdup("/msg");
  g_local.commands[9] = '\0';
  g_client.connected = 0;
}

char		*parsInput(char	const *input)
{
  g_local.message = NULL;
  if (strlen(input) > 140)
    return ((char*)"-<strong>[Error]: </strong>message too long!");
  if (strlen(input) > 1)
    {
      if (input[0] == '/')
	return (parsCommand(&g_local, &g_client, input));
      else if (g_client.connected == 1)
	return (parsMessage(input));
      else
	return ((char*)"-<strong>[Error]: </strong>You need to be connected!");
    }
  return (returnError(2));
}
