//
// Server.cpp for Server.cpp in /home/chouag_m/perso/my_irc/C++
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Fri Apr 18 18:14:36 2014 Mehdi Chouag
// Last update Sat Apr 19 23:59:54 2014 Mehdi Chouag
//

#include "Server.hh"

Server::Server()
{
  _option.push_back("/join");
  _option.push_back("/part");
  _option.push_back("/users");
  _option.push_back("/list");
  _option.push_back("/nick");
  _option.push_back("/msg");
  _option.push_back("/login");
  _option.push_back("/kick");
  _option.push_back("/logout");
  _ptr[JOIN] = &Server::join;
  _ptr[PART] = &Server::part;
  _ptr[USERS] = &Server::users;
  _ptr[LIST] = &Server::list;
  _ptr[NICK] = &Server::nick;
  _ptr[MSG] = &Server::msg;
  _ptr[LOGIN] = &Server::login;
  _ptr[KICK] = &Server::kick;
  _ptr[LOGOUT] = &Server::logout;
  _count = 0;
  initServer();
}

Server::~Server()
{
}

void		Server::initServer()
{
  int		opt;

  opt = 1;
  _serverfd = socket(PF_INET, SOCK_STREAM, 0);
  setsockopt(_serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  _sin.sin_family = AF_INET;
  _sin.sin_port = htons(6667);
  _sin.sin_addr.s_addr = INADDR_ANY;
  bind(_serverfd, (struct sockaddr *)&(_sin), (socklen_t)sizeof(_sin));
  listen(_serverfd, 10);
  _client_len = sizeof(_client_sin);
  _tv.tv_usec = 100;
}

t_server	Server::addClient()
{
  t_server		s;
  std::ostringstream    number;

  number << _count;
  s.channel = "none";
  s.nickname = "<em>Anonymous" + number.str() + "</em>";
  s.nick = "Anonymous" + number.str();
  s.isClose = false;
  s.isAdmin = false;
  s.fd = accept(_serverfd, (struct sockaddr *)&(_client_sin), &(_client_len));
  std::cout << "\033[32;1mNew Connection from : " 
	    << inet_ntoa(_client_sin.sin_addr);
  std::cout << " as " << s.nick << "\033[0m" << std::endl;
  _count++;
  return (s);
}

void		Server::setAllFd()
{
  std::vector<t_server>::iterator it;

  for (it = _server.begin(); it != _server.end(); ++it)
    FD_SET((*it).fd, &(_readfd));
}

int		Server::getMaxFd()
{
  std::vector<t_server>::iterator it;
  int		sock(0);

  for (it = _server.begin(); it != _server.end(); ++it)
    if ((*it).fd > sock)
      sock = (*it).fd;
  return (sock + 1);
}

void		Server::join(std::string &buff, t_server &s)
{
  std::string	tmp;

  tmp = buff.substr(6, buff.size());
  tmp = tmp.substr(0, tmp.find_first_of(" "));
  if (tmp.empty())
    send(s.fd, ERR_CHAN, strlen(ERR_CHAN), 0);
  else if (buff.size() > 6 + tmp.size())
    send(s.fd, "<strong>[admin] : Too many argument</strong>", 44, 0);
  else
    {
      tmp = tmp.substr(0, tmp.find_first_of("\n"));
      if (tmp.size() <= 9)
	{
	  std::cout << "\033[32;1m" << s.nick << " just change his channel to ";
	  std::cout << tmp << "\033[0m" << std::endl;
	  tmp = "<strong>" + tmp + "</strong>";
	  s.channel = tmp;
	  send(s.fd, UP_CHAN, strlen(UP_CHAN), 0);
	}
      else
	send(s.fd, ERR_JOINSIZE, strlen(ERR_JOINSIZE), 0);
    }
}

void		Server::part(std::string &buff, t_server &s)
{
  std::string	tmp;
  std::string   prev;

  tmp = buff.substr(6, buff.size());
  tmp = tmp.substr(0, tmp.find_first_of(" "));
  if (tmp.empty())
    send(s.fd, ERR_PART, strlen(ERR_PART), 0);
  else if (buff.size() > 6 + tmp.size())
    send(s.fd, "<strong>[admin] : Too many argument</strong>", 44, 0);
  else
    {
      tmp = tmp.substr(0, tmp.find_first_of("\n"));
      prev = tmp;
      if (s.channel == ("<strong>" + tmp + "</strong>"))
	{
	  std::cout << "\033[32;1m" << s.nick << " just leave ";
	  std::cout << prev << "\033[0m" << std::endl;
	  tmp = "none";
	  s.channel = tmp;
	  send(s.fd, UP_PART, strlen(UP_PART), 0);
	}
      else
	send(s.fd, ERR_PARTCHAN, strlen(ERR_PARTCHAN), 0);
    }
}

void		Server::users(std::string &buff, t_server &s)
{
  std::string   tmp;
  std::vector<t_server>::iterator it;

  (void)buff;
  if (!s.isAdmin)
    {
      for (it = _server.begin(); it != _server.end(); ++it)
	if (s.channel == (*it).channel && (*it).channel != "none")
	  tmp += " " + (*it).nickname;
    }
  else
    for (it = _server.begin(); it != _server.end(); ++it)
      tmp += " " + (*it).nickname;
  if (_server.size() > 0)
    send(s.fd, tmp.c_str(), tmp.size(), 0);
}

void		Server::list(std::string &buff, t_server &s)
{
  std::string	tmp;
  
  tmp = buff.substr(6, buff.size());
  tmp = tmp.substr(0, tmp.find_first_of(" "));
  if (tmp.empty() && buff.size() == 6)
    sendAllList(tmp, false, s);
  else if (buff.size() > 6 + tmp.size() || (tmp.empty() && buff.size() == 6))
    send(s.fd, "<strong>[admin] : Too many argument</strong>", 44, 0);
  else
    sendAllList(tmp, true, s);
}

void		Server::nick(std::string &buff, t_server &s)
{
  std::string   prev;
  std::string	tmp;
  bool		exist(false);
  std::vector<t_server>::const_iterator it;
  

  tmp = buff.substr(6, buff.size());
  tmp = tmp.substr(0, tmp.find_first_of(" "));
  if (tmp.empty() || buff.size() > 6 + tmp.size())
    send(s.fd, ERR_NICK, strlen(ERR_NICK), 0);
  else
    {
      tmp = tmp.substr(0, tmp.find_first_of("\n"));
      prev = s.nick;
      for (it = _server.begin(); it != _server.end(); ++it)
	if ((*it).nick == tmp || tmp == "chouag_m")
	  exist = true;      
      if (!exist && tmp.size() <= 9 && !s.isAdmin)
	{
	  std::cout << "\033[32;1m" << s.nick << " has setup his nickname to ";
	  std::cout << tmp << "\033[0m" << std::endl;
	  s.nick = tmp;
	  s.nickname = "<em>" + tmp + "</em>";;
	  send(s.fd, UP_NICK, strlen(UP_NICK), 0);
	}
      else if (s.nick.size() > 9)
	send(s.fd, ERR_NICK, strlen(ERR_NICK), 0);
      else if (s.isAdmin)
	send(s.fd, ERR_ADMINNICK, strlen(ERR_ADMINNICK), 0);
      else
	send(s.fd, ERR_NICKUSED, strlen(ERR_NICKUSED), 0);
    }
}

void		Server::msg(std::string &buff, t_server &s)
{
  std::string	nickname;
  std::string	message;
  std::vector<t_server>::const_iterator it;  
  bool		exist(false);

  nickname = buff.substr(5, buff.size());
  message = nickname.substr(nickname.find_first_of(" ") + 1, std::string::npos);
  nickname = nickname.substr(0, nickname.find_first_of(" "));
  nickname = "<em>" + nickname + "</em>";
  if (nickname.empty() || message.empty() ||
      nickname.size() == 1 || message.size() == 1 ||
      nickname == message)
    send(s.fd, ERR_MSG, strlen(ERR_MSG), 0);
  else
    {
      message = "<strong>[Private message]</strong> " + nickname + ": " + message;
      for (it = _server.begin(); it != _server.end(); ++it)
	if ((*it).nickname == nickname)
	  {
	    send((*it).fd, message.c_str(), message.size(), 0);
	    exist = true;
	  }
      if (!exist)
	send(s.fd, ERR_MSGUSER, strlen(ERR_MSGUSER), 0);
    }
}

bool		Server::checkCommand(std::string buff, t_server &s)
{
  bool		find(false);
  size_t	funct(0);

  for (size_t i(0); i != _option.size(); i++)
    if (buff.find(_option[i]) <= buff.size())
      if (buff.substr(0, _option[i].size()) == _option[i])
	{
	  if ((_option[i] == "/kick" || _option[i] == "/logout") && s.isAdmin)
	    {
	      find = true;
	      funct = i;
	    }
	  else if (_option[i] != "/kick" && _option[i] != "/logout")
	    {
	      find = true;
	      funct = i;
	    }
	  else
	    find = false;
	  break;
	}
  if (find)
    (this->*_ptr[funct])(buff, s);
  else if (buff[0] == '/')
    {
      send(s.fd, ERR_CMD, strlen(ERR_CMD), 0);
      return (true);
    }
  return (find);
}	

void		Server::deleteFd(bool del)
{
  std::vector<t_server>::iterator it;
  std::vector<t_server> tmp;
  t_server	s;

  if (del)
    {
      for (it = _server.begin(); it != _server.end(); ++it)
	{
	  if (!(*it).isClose)
	    tmp.push_back(*it);
	  else
	    s = (*it);
	}
      if (_server.size() != tmp.size())
	{
	  std::cout << "\033[31;1m" << s.nick << " has left the server\033[0m" << std::endl;
	  close(s.fd);
	}
      _server = tmp;
    }
}

void		Server::readClient()
{
  std::string	msg;
  char		buff[4096];
  bool		del(false);
  
  for (size_t i(0); i != _server.size(); i++)
    if (FD_ISSET(_server[i].fd, &(_readfd)))
      {
	memset(buff, 0, sizeof(buff));
	if ((int)recv(_server[i].fd, buff, 4096, 0) == 0)
	  {
	    _server[i].isClose = true;
	    del = true;
	  }
	else if(!checkCommand(std::string(buff), _server[i]))
	  sendMessage(std::string(buff), _server[i]);
      }
  deleteFd(del);
}

void		Server::sendMessage(std::string buff, t_server &s)
{
  std::vector<t_server>::iterator it;
  
  buff = s.nickname + ": " + buff;
  if (s.channel == "none")
    send(s.fd, ERR_CHAN, strlen(ERR_CHAN), 0);
  else
    for (it = _server.begin(); it != _server.end(); ++it)
      if ((*it).channel == s.channel)
	send((*it).fd, buff.c_str(), buff.size(), 0);
}

void		Server::loop()
{
  int		ret;

  _server.push_back(addClient());
  ret = 0;
  while (ret != -1)
    {
      FD_ZERO(&_readfd);
      FD_SET(_serverfd, &(_readfd));
      setAllFd();
      if (_server.size() > 0)
	ret = select(getMaxFd(), &(_readfd), NULL, NULL, &(_tv));
      if (FD_ISSET(_serverfd, &(_readfd)) && ret != -1)
	_server.push_back(addClient());
      else
	readClient();
      usleep(1000);
    }
  perror("Select ");
  std::cout << "Exiting the Loop" << std::endl;
}
