/*
** check_funcs.c for check_funcs in /home/apollo/rendu/PSU_2013_myirc/client/srcs
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Wed Apr 16 18:55:18 2014 ribeaud antonin
** Last update Thu Apr 17 22:20:23 2014 ribeaud antonin
*/

#include "Client.h"

char	*checkCommand(char const *input, t_local *local)
{
  int	i;

  i = 0;
  while (local->commands[i] != '\0')
    {
      if (strncmp(local->commands[i], input, strlen(local->commands[i])) == 0)
	return (local->commands[i]);
      i++;
    }
  return (NULL);
}

char	*verifySyntax(char const *input, char *command)
{
  char	**tab;

  tab = my_str_to_wordtab((char*)input, ' ');
  if (strlen(command) > 7)
    return ((char*)"-<strong>[Error]: </strong>Command not implemented yet");
  if (strcmp(command, "/nick") == 0 || strcmp(command, "/part") == 0 
      || strcmp(command, "/join") == 0 || strcmp(command, "/msg") == 0)
    {
      if (tab[1] == NULL)
	return ((char*)"-<strong>[Error]:</strong>Command needs argument");
      if (strcmp(command, "/nick") == 0 && (strlen(tab[1]) > 9 
			 || check_char(tab[1], (char*)"-<>/\\") != 0))
	return ((char*)"-<strong>[Error]:</strong>Wrong nickname syntax!");
      if (strcmp(command, "/msg") == 0 && (strlen(tab[1]) > 9 
					   || tab[2] == NULL))
	return ((char*)"-<strong>[Error]:</strong>No msg specified!");
    }
  return ((char*)input);
}

char	*realIp(char *input)
{
  int	i;
  int	j;
  char	test[20];
  
  i = 0;
  j = 0;
  memset(test, 0, sizeof(test));
  while (input[i] != '\0')
    {
      if ((input[i] >= 48 && input[i] <= 57) || input[i] == '.')
	{
	  test[j] = input[i];
	  j++;
	}
      i++;
    }
  return (strdup(test));
}

int	check_char(char const *input, char *str)
{
  int	i;
  int	j;
  
  i = 0;
  while (input[i] != '\0')
    {
      j = 0;
      while (str[j] != '\0')
	{
	  if (input[i] == str[j])
	    return (1);
	  j++;
	}
      i++;
    }
  return (0);
}
