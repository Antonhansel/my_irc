/*
** my_str_to_wordtab.c for str_to_wordtab in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Mon Apr  7 18:11:27 2014 Mehdi Chouag
** Last update Wed Apr 16 20:25:39 2014 Mehdi Chouag
*/

#include "server.h"

int		count_word(char *str, char c)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (str[i] != 0)
    {
      if (str[i] == c)
        j++;
      i++;
    }
  return (i + 1);
}

int		my_strnlen(char *str, char c)
{
  int		i;

  i = 0;
  while (str[i] && str[i] != c)
    i++;
  return (i);
}

char		**my_str_to_wordtab(char *str, char c)
{
  char		**result;
  int		i;
  int		j;
  int		count;

  i = -1;
  count = 0;
  if (str == NULL)
    return (NULL);
  result = xmalloc((count_word(str, c) + 1) * sizeof(*result));
  while (++i < count_word(str, c))
    {
      while (str[count] == c)
	count++;
      result[i] = malloc(my_strnlen(&str[count], c) + 1);
      j = -1;
      while (str[count] != c && str[count] != 0 && str[count] != '\n')
	{
          result[i][++j] = str[count];
          count++;
	}
      result[i][j + 1] = '\0';
    }
  result[i] = NULL;
  return (result);
}
