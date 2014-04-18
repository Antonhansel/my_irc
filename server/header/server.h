/*
** header.h for header.h in /home/chouag_m/rendu/irc
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Sat Apr 12 17:32:13 2014 Mehdi Chouag
** Last update Fri Apr 18 17:39:41 2014 ribeaud antonin
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/time.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

#define ERR_JOIN	"<strong>[admin] : specify the channel to join\n"
#define ERR_JOINSIZE	"<strong>[admin] : 9 character max for a channel\n"
#define ERR_NICK	"<strong>[admin] : /nick [nickname], 9 character max\n"
#define ERR_NICKUSED	"<strong>[admin] : This nickname is already used\n"
#define ERR_CHAN	"<strong>[admin] : /join to enter a channel\n"
#define ERR_PART	"<strong>[admin] : /part [channel]\n"
#define ERR_PARTCHAN	"<strong>[admin] : Can't leave this channel\n"
#define ERR_MSG		"<strong>[admin] : /msg [nickname] [message]\n"
#define ERR_MSGUSER	"<strong>[admin] : Unknown user</strong>\n"
#define ERR_USER	"<strong>[admin] : join a channel to see the users\n"
#define UP_CHAN		"<strong>[admin] : Channel update\n"
#define UP_PART		"<strong>[admin] : Leave the channel\n"
#define UP_NICK		"<strong>[admin] : nickname update\n"
#define ERR_CMD		"<strong>[admin] : Command Unknown\n"

typedef struct		s_server
{
  struct sockaddr_in	sin;
  struct sockaddr_in	client_sin;
  int			serverfd;
  socklen_t		client_len;
  fd_set		readf;
  int			clientfd;
  fd_set		readfd;
}			t_server;

typedef struct		s_fd
{
  int			fd;
  char			channel[128];
  char			nickname[128];
  struct s_fd		*next;
}			t_fd;

void	init_server(t_server *, char *);
int	xbind(int, struct sockaddr_in *, socklen_t);
int	xsocket(int, int, int);
int	xaccept(int, struct sockaddr_in *, socklen_t *);
int	xlisten(int, int);
void	*xmalloc(size_t);
void	xfree(void *);
ssize_t	xrecvserver(int, t_server *);
int	xsendserver(int, char *, t_server *);
char	**my_str_to_wordtab(char*, char);
void	my_free_wordtab(char **);
void	add_in_list(t_fd **, t_server *, int);
int	get_max_fd(t_fd *);
void	init_server(t_server *, char *);
int	loop(t_server *, char *);
int	all_list(char *);
int	cur_list(char *);
void	check_current(char *, char *, t_fd *, t_fd *);
void	check_list(char **, t_fd *, t_fd *);
int	check_command(char *, t_fd *, t_fd *);
void	join(char *, t_fd *, t_fd *);
void	part(char *, t_fd *, t_fd *);
void	nick(char *, t_fd *, t_fd *);
void	list(char **, t_fd *, t_fd *);
void	users(char **, t_fd *, t_fd *);
t_fd	*linked_list(t_server *, t_fd *);
void	set_all_fd(t_fd *, t_server *);
void	my_sighandler(int);
void	read_client(char *, t_fd *, t_fd *);
void	msg(char **, t_fd *, t_fd *);
void	send_private(t_fd *, t_fd *, char **);
void	my_sighandler(int);
void	aff_chan(t_fd *, t_fd *);
int	get_list_size(t_fd *);
int	found_chan(char **, char *);
char	**settab(t_fd *);
void	sort_chan(t_fd *, t_fd *, char *);

#endif /* !SERVER_H_ */
