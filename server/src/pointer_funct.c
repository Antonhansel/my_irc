/*
** pointer_funct.c for pointer_funct in /home/chouag_m/rendu/irc
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Apr 16 18:53:09 2014 Mehdi Chouag
** Last update Thu Apr 17 21:05:31 2014 Mehdi Chouag
*/

#include "server.h"

void		join(char *cmd, t_fd *fd, t_fd *all)
{
  (void)all;
  if (strcmp(cmd, "") && strlen(cmd) <= 9)
    {
      sprintf(fd->channel, "<strong>%s</strong>", cmd);
      send(fd->fd, UP_CHAN, strlen(UP_CHAN), 0);
    }
  else if (strlen(cmd) > 9)
    send(fd->fd, ERR_JOINSIZE, strlen(ERR_JOINSIZE), 0);
  else
    send(fd->fd, ERR_JOIN, strlen(ERR_JOIN), 0);
}

void		part(char *cmd, t_fd *fd, t_fd *all)
{
  char		temp[128];

  (void)all;
  if (strcmp(cmd, ""))
    {
      sprintf(temp, "<strong>%s</strong>", cmd);
      if (strcmp(temp, fd->channel) == 0)
	{
	  sprintf(fd->channel, "none");
	  send(fd->fd, UP_PART, strlen(UP_PART), 0);
	}
      else
	send(fd->fd, ERR_PARTCHAN, strlen(ERR_PARTCHAN), 0);
    }
  else
    send(fd->fd, ERR_PART, strlen(ERR_PART), 0);
}

void		nick(char *cmd, t_fd *fd, t_fd *all)
{
  t_fd		*tmp;
  int		is_taken;
  char		temp[128];

  sprintf(temp, "<em>%s</em>", cmd);
  tmp = all;
  is_taken = 0;
  while (tmp != NULL)
    {
      if (strcmp(temp, tmp->nickname) == 0)
	is_taken = 1;
      tmp = tmp->next;
    }
  if (strcmp(cmd, "") && strlen(cmd) <= 9 && !is_taken)
    {
      sprintf(fd->nickname, "<em>%s</em>", cmd);
      send(fd->fd, UP_NICK, strlen(UP_NICK), 0);
    }
  else if (is_taken == 1)
    send(fd->fd, ERR_NICKUSED, strlen(ERR_NICKUSED), 0);
  else
    send(fd->fd, ERR_NICK, strlen(ERR_NICK), 0);
}

void		list(char **cmd, t_fd *fd, t_fd *cur)
{
  char		buff[4096];

  memset(buff, 0, sizeof(buff));
  if (strcmp(cmd[1], "") == 0)
    aff_chan(fd, cur);
  else
    sort_chan(fd, cur, cmd[1]);
}

void		users(char **cmd, t_fd *fd, t_fd *cur)
{
  t_fd		*tmp;
  char		nick[4096];

  (void)cmd;
  tmp = fd;
  memset(nick, 0, sizeof(nick));
  if (strcmp("none", cur->channel) == 0)
      send(cur->fd, ERR_USER, strlen(ERR_USER), 0);
  else
    {
      while (tmp != NULL)
	{
	  if (strcmp(tmp->channel, cur->channel) == 0)
	    sprintf(nick, " %s %s", strdup(nick), tmp->nickname);
	  tmp = tmp->next;
	}
      send(cur->fd, nick, strlen(nick), 0);
    }
}
