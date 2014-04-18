/*
** check_cmd.c for check_cmd in /home/chouag_m/rendu/irc
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Apr 16 13:55:07 2014 Mehdi Chouag
** Last update Fri Apr 18 17:34:27 2014 ribeaud antonin
*/

#include "server.h"

int		cur_list(char *buff)
{
  if (strcmp(buff, "/join") == 0 || strcmp(buff, "/part") == 0
      || strcmp(buff, "/nick") == 0)
    return (0);
  return (-1);
}

int		all_list(char *buff)
{
  if (strcmp(buff, "/list") == 0 || strcmp(buff, "/users") == 0
      || strcmp(buff, "/msg") == 0)
    return (0);
  return (-1);
}

void		msg(char **cmd, t_fd *fd, t_fd *cur)
{
  t_fd		*tmp;
  char		temp[4096];
  char		is_exist;

  tmp = fd;
  is_exist = 0;
  if (strcmp(cmd[1], "") == 0 || strcmp(cmd[2], "") == 0)
    send(cur->fd, ERR_MSG, strlen(ERR_MSG), 0);
  else
    {
      sprintf(temp, "<em>%s</em>", cmd[1]);
      while (tmp != NULL)
	{
	  if (strcmp(tmp->nickname, temp) == 0)
	    {
	      send_private(cur, tmp, cmd);
	      is_exist = 1;
	    }
	  tmp = tmp->next;
	}
      if (!is_exist)
	send(cur->fd, ERR_MSGUSER, strlen(ERR_MSGUSER), 0);
    }
}

void		send_private(t_fd *fd, t_fd *cur, char **cmd)
{
  char		msg[4096];
  char		nick[512];
  char		to_send[4096];
  int		i;

  i = 2;
  memset(nick, 0, sizeof(nick));
  memset(msg, 0, sizeof(msg));
  sprintf(nick, "<strong>[Private message]</strong>\n%s", fd->nickname);
  while (cmd[i])
    {
      if (strcmp(cmd[i], "") != 0)
	sprintf(msg, "%s %s", strdup(msg), strdup(cmd[i]));
      i++;
    }
  sprintf(to_send, "%s: %s\n", nick, msg);
  send(cur->fd, to_send, strlen(to_send), 0);
}

void		aff_chan(t_fd *fd, t_fd *cur)
{
  t_fd		*tmp;
  char		**tab;
  char		chan[4096];
  int		i;

  tmp = fd;
  i = -1;
  memset(chan, 0, sizeof(chan));
  tab = settab(fd);
  while (tmp != NULL)
    {
      if (tmp->channel != NULL &&
	  strcmp("none", tmp->channel) != 0
	  && !found_chan(tab, tmp->channel))
	tab[++i] = strdup(tmp->channel);
      tmp = tmp->next;
    }
  i = -1;
  while (tab[++i] != '\0')
    sprintf(chan, " %s %s", strdup(chan), tab[i]);
  send(cur->fd, chan, strlen(chan), 0);
}
