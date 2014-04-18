/*
** list2.c for list2 in /home/apollo/rendu/PSU_2013_myirc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr 16 22:48:35 2014 ribeaud antonin
** Last update Thu Apr 17 22:51:11 2014 Mehdi Chouag
*/

#include "server.h"

void		add_in_list(t_fd **front_ptr, t_server *s, int newfd)
{
  static int	count;
  t_fd		*newElement;
  t_fd		*tmp;

  printf("\033[32;1mNew Connection from : %s\033[0m\n",
	 inet_ntoa(s->client_sin.sin_addr));
  tmp = *front_ptr;
  newElement = xmalloc(sizeof(t_fd));
  newElement->fd = newfd;
  newElement->next = NULL;
  memset(newElement->nickname, 0, sizeof(newElement->nickname));
  sprintf(newElement->nickname, "<em>Anonymous%d</em>", count);
  memset(newElement->channel, 0, sizeof(newElement->channel));
  sprintf(newElement->channel, "none");
  if (*front_ptr == NULL)
    *front_ptr = newElement;
  else
    {
      while (tmp->next != NULL)
        tmp = tmp->next;
      tmp->next = newElement;
    }
  fflush(stdout);
  count++;
}

int		get_max_fd(t_fd *fd)
{
  t_fd		*tmp;
  int		sock;

  tmp = fd;
  sock = 0;
  while (tmp != NULL)
    {
      if (tmp->fd > sock)
	sock = tmp->fd;
      tmp = tmp->next;
    }
  if (sock == 0)
    return (0);
  return (sock + 1);
}

char		**settab(t_fd *fd)
{
  char		**tab;
  int		i;

  i = 0;
  tab = xmalloc(sizeof(char *) * (get_list_size(fd) + 1));
  while (i != get_list_size(fd))
    {
      tab[i] = "\0";
      i++;
    }
  return (tab);
}

void		sort_chan(t_fd *fd, t_fd *cur, char *find)
{
  t_fd		*tmp;
  char		**tab;
  char		chan[4096];
  int		i;
  char		buff[512];

  tmp = fd;
  i = -1;
  memset(chan, 0, sizeof(chan));
  memset(buff, 0, sizeof(buff));
  tab = settab(fd);
  sprintf(buff, "<strong>%s", find);
  while (tmp != NULL)
    {
      if (strcmp("none", tmp->channel) != 0 
	  && !found_chan(tab, tmp->channel)
	  && strncmp(buff, tmp->channel, strlen(buff)) == 0)
	tab[++i] = strdup(tmp->channel);
      tmp = tmp->next;
    }
  i = -1;
  while (tab[++i] != '\0')
    sprintf(chan, " %s %s", strdup(chan), tab[i]);
  send(cur->fd, chan, strlen(chan), 0);
}
