//
// function.cpp for function.cpp in /home/chouag_m/perso/my_irc/C++
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sat Apr 19 16:43:54 2014 Mehdi Chouag
// Last update Sun Apr 20 00:43:08 2014 Mehdi Chouag
//

#include "Server.hh"

void	Server::sendAllList(std::string &buff, bool find, t_server &s)
{
  std::string   to_send;
  std::vector<std::string> chan;
  std::vector<t_server>::const_iterator it;
  bool		exist(false);

  buff = buff.substr(0, buff.find_first_of("\n"));
  buff = "<strong>" + buff;
  for (it = _server.begin(); it != _server.end(); ++it)
    {
      for (size_t i(0); i != chan.size(); i++)
	if (chan[i] == (*it).channel)
	  exist = true;
      if (!find && !exist && (*it).channel != "none")
	chan.push_back((*it).channel);
      else if (!exist && (*it).channel != "none" 
	       && (*it).channel.find(buff) < (*it).channel.size())
	chan.push_back((*it).channel);
      exist = false;
    }
  for (size_t i(0); i != chan.size(); i++)
    to_send += " " + chan[i];
  send(s.fd, to_send.c_str(), to_send.size(), 0);
}

void	Server::login(std::string &buff, t_server &s)
{
  std::string username;
  std::string password;

  username = buff.substr(7, buff.size());
  username = buff.substr(7, username.find_first_of(" "));
  if (!username.empty() && buff.size() > 8 + username.size())
    {
      password = buff.substr(8 + username.size(), username.size());
      password = password.substr(0, password.find_first_of(" "));
      password[password.size() - 1] = '\0';
    }
  if (username.empty() || password.empty() || buff.size() > 10 + username.size() + password.size())
    send(s.fd, ERR_LOGIN, strlen(ERR_LOGIN), 0);
  else
    findUser(username, password, s);
}

void	Server::findUser(std::string &username, std::string &password, t_server &s)
{
  std::ifstream file(".admin");
  std::vector<std::string> user;
  std::vector<std::string> pass;
  std::string tmp;
  bool		isConnect;

  password = sha512(password); 
  if (!file)
    send(s.fd, ERR_LOGINOPEN, strlen(ERR_LOGINOPEN), 0);
  else if (s.isAdmin)
    send(s.fd, ERR_ADMINNICK, strlen(ERR_ADMINNICK), 0);
  else
    {
      while (std::getline(file, tmp))
	{
	  user.push_back(tmp.substr(0, tmp.find_first_of(":")));
	  pass.push_back(tmp.substr(tmp.find_first_of(":") + 2, std::string::npos));
	}
      for (size_t z(0); z != _server.size(); z++)
        if (_server[z].nick == username)
	  isConnect = true;
      for (size_t i(0); i != user.size(); i++)
	  if (username == user[i] && pass[i] == password && !isConnect)
	    s.isAdmin = true;
      if (s.isAdmin)
	{
	  send(s.fd, UP_LOGIN, strlen(UP_LOGIN), 0);
	  s.nickname = "<strong>" + username + "</strong>";
	  s.nick = username;
	  std::cout << "\033[32;1mThe admin " << s.nick << " just logged in";
	  std::cout << "\033[0m" << std::endl;
	}
      else if (isConnect)
	send(s.fd, ERR_LOGINCON, strlen(ERR_LOGINCON), 0);
      else
	send(s.fd, ERR_LOGINFAIL, strlen(ERR_LOGINFAIL), 0);
    }
}

void	Server::kick(std::string &buff, t_server &s)
{
  std::string   username;
  std::string	message;
  bool		isKicked(false);

  username = buff.substr(6, buff.size());
  message = username.substr(username.find_first_of(" ") + 1, std::string::npos);
  username = username.substr(0, username.find_first_of(" "));
  if (username.empty() || username.size() == 1 ||
      message.size() == 1 || message.empty() ||
      username == message)
    send(s.fd, ERR_ADMINKICK, strlen(ERR_ADMINKICK), 0);
  else
    {
      for (size_t i(0); i != _server.size(); i++)
	if (_server[i].nick == username && username != s.nick)
	  {
	    std::cout << "\033[31;1m" << _server[i].nick << " has been kicked by ";
	    std::cout << s.nick << "\033[0m" << std::endl;
	    message = s.nickname + "<strong>has kicked you because : " 
	      + message + "<strong>"; 
	    send(_server[i].fd, message.c_str(), message.size(), 0);
	    _server[i].isClose = true;
	    isKicked = true;
	  }
      if (isKicked)
	send(s.fd, UP_ADMINKICK, strlen(UP_ADMINKICK), 0);
      else if (username == s.nick)
	send(s.fd, ERR_ADMINKICK2, strlen(ERR_ADMINKICK2), 0);
      else
	send(s.fd, ERR_ADMINUSER, strlen(ERR_ADMINUSER), 0);
      deleteFd(isKicked);
    }
}

void	Server::logout(std::string &buff, t_server &s)
{
  (void)buff;
  std::ostringstream    number;

  number << _count;
  std::cout << "\033[31;1mThe admin " << s.nick << " just logged out";
  std::cout << "\033[0m" << std::endl;
  s.nickname = "<em>Anonymous" + number.str() + "</em>";
  s.nick = "Anonymous" + number.str();
  s.isAdmin = false;
  send(s.fd, UP_LOGOUT, strlen(UP_LOGOUT), 0);
}

void		Server::deleteAllFd()
{
  std::vector<t_server>::iterator it;
  
  for (it = _server.begin(); it != _server.end(); ++it)
    close((*it).fd);
}


void	Server::closeServerFd(void)
{
  close(_serverfd);
}
