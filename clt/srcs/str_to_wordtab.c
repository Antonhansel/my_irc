/*
** str_to_wordtab.c<2> for strtowordtab in /home/apollo/rendu/PSU_2013_myirc/client
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Mon Apr 14 21:32:52 2014 ribeaud antonin
** Last update Thu Apr 17 22:17:32 2014 ribeaud antonin
*/

#include "Client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	word_count(char *str, char delim)
{
  int	i;
  int	w;

  w = 0;
  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] != delim && str[i] != '\t')
        {
          w += 1;
          while (str[i] != delim && str[i] != '\t' && str[i] != '\0')
            i += 1;
        }
      else
        i += 1;
    }
  return (w);
}

char	**my_str_to_wordtab2(char *str, char delim, char **tab)
{
  int	word;
  int	i;
  int	c;

  word = 0;
  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] != delim && str[i] != '\t')
        {
          c = i;
          while (str[i] != delim && str[i] != '\t' && str[i] != '\0')
            i = i + 1;
          if ((tab[word] = (char *)malloc((i - c + 1) * sizeof(**tab))) == NULL)
            exit (1);
          strncpy(tab[word], &str[c], i - c);
          word = word + 1;
        }
      else
        i = i + 1;
    }
  tab[word] = '\0';
  return (tab);
}

char	**my_str_to_wordtab(char *str, char delim)
{
  char	**tab;

  if ((tab = (char **)malloc((word_count(str, delim) + 1) 
			     * sizeof(*tab))) == NULL)
    exit (1);
  return (my_str_to_wordtab2(str, delim, tab));
}
