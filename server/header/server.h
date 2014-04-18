/*
** header.h for header.h in /home/chouag_m/rendu/irc
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Sat Apr 12 17:32:13 2014 Mehdi Chouag
** Last update Thu Apr 17 22:29:19 2014 Mehdi Chouag
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

void			init_server(t_server *s, char *port);
int			xbind(int sockfd, struct sockaddr_in *addr, socklen_t addrlen);
int			xsocket(int domain, int type, int protocol);
int			xaccept(int sockfd, struct sockaddr_in *addr ,socklen_t *len);
int			xlisten(int sockfd, int backlog);
void			*xmalloc(size_t size);
void			xfree(void *ptr);
ssize_t			xrecvserver(int sockclient, t_server *s);
int			xsendserver(int sockserver, char *buf, t_server *s);
char			**my_str_to_wordtab(char*, char);
void			my_free_wordtab(char **cmd);
void			add_in_list(t_fd **front_ptr, t_server *s, int newfd);
int			get_max_fd(t_fd *fd);
void			init_server(t_server *s, char *port);
int			loop(t_server *s, char *str);
int			all_list(char *buff);
int			cur_list(char *buff);
void			check_current(char *cmd, char *params,t_fd *fd, t_fd *all);
void			check_list(char **cmd, t_fd *fd, t_fd *cur);
int			check_command(char *buff, t_fd *cur, t_fd *all);
void			join(char *cmd, t_fd *fd, t_fd *all);
void			part(char *cmd, t_fd *fd, t_fd *all);
void			nick(char *cmd, t_fd *fd, t_fd *all);
void			list(char **cmd, t_fd *fd, t_fd *cur);
void			users(char **cmd, t_fd *fd, t_fd *cur);
t_fd			*linked_list(t_server *s, t_fd *fd);
void			set_all_fd(t_fd *fd, t_server *s);
void			my_sighandler(int num);
void			read_client(char *buff, t_fd *fd, t_fd *cur);
void			msg(char **cmd, t_fd *fd, t_fd *cur);
void			send_private(t_fd *fd, t_fd *cur, char **cmd);
void			my_sighandler(int num);
void			aff_chan(t_fd *fd, t_fd *cur);
int			get_list_size(t_fd *fd);
int			found_chan(char **cmd, char *channel);
char			**settab(t_fd *fd);
void			sort_chan(t_fd *fd, t_fd *cur, char *find);

#endif /* !SERVER_H_ */
