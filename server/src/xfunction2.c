/*
** xfunction2.c for xfunction2 in /home/chouag_m/rendu/TCP/function
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Thu Apr 10 00:34:32 2014 Mehdi Chouag
** Last update Fri Apr 18 17:33:55 2014 ribeaud antonin
*/

#include "server.h"

void	*xmalloc(size_t size)
{
  void	*ret;

  if ((ret = malloc(size)) != NULL)
    return (ret);
  fprintf(stderr, "Can't allocate the pointer");
  exit(EXIT_FAILURE);
}

void	xfree(void *ptr)
{
  if (ptr != NULL)
    free(ptr);
  else
    fprintf(stderr, "The pointer is already NULL\n");
}

int     get_list_size(t_fd *fd)
{
  t_fd	*tmp;
  int	i;

  i = 0;
  tmp = fd;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

int	found_chan(char **cmd, char *channel)
{
  int	i;

  i = 0;
  while (cmd[i] != NULL)
    {
      if (strcmp(channel, cmd[i]) == 0)
	return (1);
      i++;
    }
  return (0);
}
