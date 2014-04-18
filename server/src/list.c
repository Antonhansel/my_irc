/*
** list.c for list in /home/apollo/rendu/PSU_2013_myirc
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr 16 22:47:37 2014 ribeaud antonin
** Last update Fri Apr 18 17:31:38 2014 ribeaud antonin
*/

#include "server.h"

void		check_current(char *cmd, char *params, t_fd *fd, t_fd *all)
{
  char		*tab[3];
  void		(*ptr[3])(char*, t_fd*, t_fd*);
  int		i;

  i = 0;
  tab[0] = strdup("/join");
  tab[1] = strdup("/part");
  tab[2] = strdup("/nick");
  ptr[0] = &join;
  ptr[1] = &part;
  ptr[2] = &nick;
  while (i < 4)
    {
      if (strcmp(cmd, tab[i]) == 0)
	{
	  (*ptr[i])(params, fd, all);
	  i = 4;
	}
      i++;
    }
}

void		check_list(char **cmd, t_fd *fd, t_fd *cur)
{
  char		*tab[3];
  void		(*ptr[3])(char**, t_fd*, t_fd*);
  int		i;

  i = 0;
  tab[0] = strdup("/list");
  tab[1] = strdup("/users");
  tab[2] = strdup("/msg");
  ptr[0] = &list;
  ptr[1] = &users;
  ptr[2] = &msg;
  while (i < 4)
    {
      if (strcmp(cmd[0], tab[i]) == 0)
	{
	  (*ptr[i])(cmd, fd, cur);
	  i = 4;
	}
      i++;
    }
}

void		delete_elem(t_fd **fd, t_fd **tmp, t_fd **prev)
{
  if (*prev != NULL)
    {
      close((*tmp)->fd);
      (*prev)->next = (*tmp)->next;
    }
  else
    {
      close((*tmp)->fd);
       *fd = (*tmp)->next;
    }
}

void		get_next(t_fd *fd, t_fd **tmp, t_fd **prev)
{
  if (fd != NULL)
    {
      (*prev) = (*tmp);
      (*tmp) = (*tmp)->next;
    }
}

t_fd		*linked_list(t_server *s, t_fd *fd)
{
  t_fd		*tmp;
  t_fd		*prev;
  char		buff[4096];

  tmp = fd;
  prev = NULL;
  while (tmp != NULL && fd != NULL)
    {
      memset(buff, 0, sizeof(buff));
      if (FD_ISSET(tmp->fd, &(s->readfd)))
	{
	  if ((int)recv(tmp->fd, buff, 4096, 0) == 0)
	    {
	      if (tmp->next != NULL)
		delete_elem(&fd, &tmp, &prev);
	      if (prev == NULL)
		fd = NULL;
	    }
	  else if (!check_command(buff, tmp, fd))
	    read_client(buff, fd, tmp);
	}
      get_next(fd, &tmp, &prev);
    }
  return (fd);
}
