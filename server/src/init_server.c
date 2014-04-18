/*
** init_server.c for init_server.c in /home/chouag_m/rendu/irc
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Apr 16 13:45:55 2014 Mehdi Chouag
** Last update Thu Apr 17 19:04:30 2014 ribeaud antonin
*/

#include "server.h"

t_fd			*g_fd;

void			my_free_wordtab(char **cmd)
{
  int			i;

  i = -1;
  while (cmd[++i])
    xfree(cmd[i]);
}

void			my_sighandler(int num)
{
  t_fd			*save;

  printf("\n\033[31;1mSIGNAL %i RECIEVED\nSERVER SHUTTING DOWN\033[0m\n", num);
  while (g_fd != NULL)
    {
      save = g_fd;
      g_fd = g_fd->next;
      free(save);
    }
  exit(EXIT_SUCCESS);
}

void			init_server(t_server *s, char *port)
{
  int			opt;
  
  opt = 1;
  s->serverfd = xsocket(PF_INET, SOCK_STREAM, 0);
  setsockopt(s->serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  s->sin.sin_family = AF_INET;
  s->sin.sin_port = htons(atoi(port));
  s->sin.sin_addr.s_addr = INADDR_ANY;
  xbind(s->serverfd, &(s->sin), (socklen_t)sizeof(s->sin));
  xlisten(s->serverfd, 10);
  s->client_len = sizeof(s->client_sin);
}

int			loop(t_server *s, char *str)
{
  struct timeval	tv;
  int			ret;

  g_fd = NULL;
  init_server(s, str);
  add_in_list(&g_fd, s, xaccept(s->serverfd, &(s->client_sin), &(s->client_len)));
  tv.tv_usec = 100;
  ret = 0;
  while (ret != -1)
    {
      FD_ZERO(&(s->readfd));
      FD_SET(s->serverfd, &(s->readfd));
      set_all_fd(g_fd, s);
      if (g_fd != NULL)
	ret = select(get_max_fd(g_fd), &(s->readfd), NULL, NULL, &tv);
      if (FD_ISSET(s->serverfd, &(s->readfd)) && ret != -1)
	add_in_list(&g_fd, s,
		    xaccept(s->serverfd, &(s->client_sin), &(s->client_len)));
      else
	g_fd = linked_list(s, g_fd);
      usleep(1000);
    }
  return (ret);
}
