/*
** Client.h for Client in /home/apollo/rendu/PSU_2013_myirc/client
** 
** Made by ribeaud antonin
** Login   <ribeau_a@epitech.net>
** 
** Started on  Mon Apr 14 18:10:09 2014 ribeaud antonin
** Last update Sat Apr 19 19:44:06 2014 Mehdi Chouag
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

typedef struct		s_client
{
  struct protoent	*pr;
  struct sockaddr_in	sin;
  char			*ip;
  int			fd;
  int			socket;
  int			port;
  int			connected;
}			t_client;

typedef	struct		s_local
{
  char			*message;
  char			*commands[11];
}			t_local;

/** xfuncs **/
int	xbind(int, struct sockaddr_in *, socklen_t);
int	xsocket(int, int, int);
int	xaccept(int, struct sockaddr_in *, socklen_t *);
int	xlisten(int, int);
int	xconnect(int, struct sockaddr_in *, socklen_t);
/** Client.c **/
char	*parsInput(char const *);
void	initStruct();
int	xsend(const char *);
char	*xrecieve();
void	endConnection();
/** str_to_wordtab.c **/
int	word_count(char *, char);
char	**my_str_to_wordtab2(char *, char, char **);
char	**my_str_to_wordtab(char *, char);
/** init_funcs.c **/
char	*returnError(int);
char	*init_client(t_client *);
/** pars.c **/
char	*checkCommand(char const *, t_local *);
char	*verifySyntax(char const *, char *);
char	*realIp(char *);
int	check_char(char const *, char *);
/** pars.c **/
char	*parsCommand(t_local *, t_client *, char const *);
char	*parsMessage(char const *);
char	*get_infos(t_client *, char const *);

#endif /* CLIENT_H */
