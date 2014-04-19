//
// server.hh for server in /home/chouag_m/perso/my_irc/C++
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Fri Apr 18 18:22:06 2014 Mehdi Chouag
// Last update Sat Apr 19 02:05:25 2014 Mehdi Chouag
//

#ifndef SERVER_HH_
# define SERVER_HH_

# include <iostream>
# include <list>
# include <map>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <vector>
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
# include <string>
# include <sstream>

#define ERR_JOIN        "<strong>[admin] : specify the channel to join\n"
#define ERR_JOINSIZE    "<strong>[admin] : 9 character max for a channel\n"
#define ERR_NICK        "<strong>[admin] : /nick [nickname], 9 character max\n"
#define ERR_NICKUSED    "<strong>[admin] : This nickname is already used\n"
#define ERR_CHAN        "<strong>[admin] : /join [channel] to enter a channel\n"
#define ERR_PART        "<strong>[admin] : /part [channel]\n"
#define ERR_PARTCHAN    "<strong>[admin] : Can't leave this channel\n"
#define ERR_MSG         "<strong>[admin] : /msg [nickname] [message]\n"
#define ERR_MSGUSER     "<strong>[admin] : Unknown user</strong>\n"
#define ERR_USER        "<strong>[admin] : join a channel to see the users\n"
#define UP_CHAN         "<strong>[admin] : Channel update\n"
#define UP_PART         "<strong>[admin] : Leave the channel\n"
#define UP_NICK         "<strong>[admin] : nickname update\n"
#define ERR_CMD         "<strong>[admin] : Command Unknown\n"

enum Command
  {
    JOIN = 0,
    PART = 1,
    USERS = 2,
    LIST = 3,
    NICK = 4,
    MSG = 5
  };

typedef struct	s_server
{
  int		fd;
  std::string	channel;
  std::string	nickname;
  std::string	nick;
  bool		isClose;
}		t_server;

class Server
{
public:
  Server();
  ~Server();
  void			loop();

private:
  void			initServer();
  t_server		addClient();
  void			setAllFd();
  int			getMaxFd();
  void			readClient();
  void			deleteFd(bool);
  bool			checkCommand(std::string, t_server&);
  void			sendMessage(std::string, t_server&);
  void			join(std::string&, t_server&);
  void			part(std::string&, t_server&);
  void			users(std::string&, t_server&);
  void			list(std::string&, t_server&);
  void			nick(std::string&, t_server&);
  void			msg(std::string&, t_server&);

private:
  struct sockaddr_in    _sin;
  struct sockaddr_in    _client_sin;
  struct timeval	_tv;
  int                   _serverfd;
  socklen_t             _client_len;
  int                   _clientfd;
  fd_set                _readfd;
  std::vector<t_server>	_server;
  std::vector<std::string> _option;
  int			_count;
  std::map<int, void (Server::*)(std::string&, t_server&)> _ptr;
};

#endif /* !SERVER_HH_ */
