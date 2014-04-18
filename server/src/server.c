/*
** server.c for server.c in /home/chouag_m/rendu/irc
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Sat Apr 12 17:25:09 2014 Mehdi Chouag
** Last update Thu Apr 17 21:40:29 2014 Mehdi Chouag
*/

#include "server.h"

void		read_client(char *buff, t_fd *fd, t_fd *cur)
{
  t_fd		*tmp2;
  char		to_send[4096];
  
  tmp2 = fd;
  if (!strcmp(cur->channel, "none"))
    send(cur->fd, ERR_CHAN, strlen(ERR_CHAN), 0);
  else
    {
      memset(to_send, 0, sizeof(to_send));
      sprintf(to_send, "%s: %s", cur->nickname, buff);
      while (tmp2 != NULL)
	{
	  if (!strcmp(tmp2->channel, cur->channel))
	    send(tmp2->fd, to_send, strlen(to_send), 0);
	  tmp2 = tmp2->next;
	}
      tmp2 = fd;
    }
}

int		check_command(char *buff, t_fd *cur, t_fd *all)
{
  char		**cmd;
  int		i;

  i = 0;
  cmd = my_str_to_wordtab(buff, ' ');
  if (!cur_list(cmd[0]))
    {
      check_current(cmd[0], cmd[1], cur, all);
      my_free_wordtab(cmd);
      return (1);
    }
  else if (!all_list(cmd[0]))
    {
      check_list(cmd, all, cur);
      my_free_wordtab(cmd);
      return (1);
    }
  else if (buff[0] == '/')
    {
      send(cur->fd, ERR_CMD, strlen(ERR_CMD), 0);
      i = 1;
    }
  my_free_wordtab(cmd);
  return (i);
}

void			set_all_fd(t_fd *fd, t_server *s)
{
  t_fd			*tmp;

  tmp = fd;
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, &(s->readfd));
      tmp = tmp->next;
    }
}

int			main(int argc, char **argv)
{
  t_server		s;
  
  if (argc == 2)
    {
      signal(SIGINT, my_sighandler);
      signal(SIGQUIT, my_sighandler);
      if (loop(&s, argv[1]) == -1)
	{
	  printf("Error on select. Exiting...\n");
	  exit(EXIT_FAILURE);
	}
    }
  else
    printf("Usage: ./serveur [port]\n");
  return (0);
}
