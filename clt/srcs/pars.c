/*
** pars.c for pars in /home/apollo/rendu/PSU_2013_myirc/client
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Tue Apr 15 11:34:57 2014 ribeaud antonin
** Last update Thu Apr 17 16:59:38 2014 ribeaud antonin
*/

#include "Client.h"
#include <stdlib.h>
#include <stdio.h>

char	*get_infos(t_client *clt, char const *input)
{
  char	**tab;
  char	**tab2;
  
  tab = my_str_to_wordtab((char*)input, ' ');
  if (tab[1] == NULL || strlen(tab[1]) > 26)
    return ((char*)"-<strong>[Error]: </strong>must specify an address");
  tab2 = my_str_to_wordtab(tab[1], ':');
  clt->ip = realIp(tab2[0]);
  if (tab2[1] == NULL)
    clt->port = 6667;
  else
    clt->port = atoi(tab2[1]);
  return (NULL);
}

char	*parsCommand(t_local *local, t_client *c, char const *input)
{
  char	*command;

  if ((command = checkCommand(input, local)) == NULL)
    return (returnError(1));
  if (strcmp(command, "/server") == 0)
    {
      if (c->connected == 0)
	{
	  if ((command = get_infos(c, input)) != NULL)
	    return (command);
	  return (init_client(c));
	}
      return ((char*)"-<strong>[Error]: </strong>Already connected!");
    }
  else if (c->connected == 1)
    return (verifySyntax(input, command));
  return ((char*)"-<strong>[Error]: </strong>You need to be connected!");
}

char	*parsMessage(const char *input)
{
  if (check_char(input, (char*)"-/\\") == 0 || input[0] != '-')
    return ((char*)input);
  else
    return ((char*)"-<strong>[Error]: </strong>Wrong message format!");
}
