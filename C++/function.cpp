//
// function.cpp for function.cpp in /home/chouag_m/perso/my_irc/C++
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sat Apr 19 16:43:54 2014 Mehdi Chouag
// Last update Sat Apr 19 22:14:10 2014 Mehdi Chouag
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

  password = sha512(password); 
  if (!file)
    send(s.fd, ERR_LOGINOPEN, strlen(ERR_LOGINOPEN), 0);
  else
    {
      while (std::getline(file, tmp))
	{
	  user.push_back(tmp.substr(0, tmp.find_first_of(":")));
	  pass.push_back(tmp.substr(tmp.find_first_of(":") + 2, std::string::npos));
	}
      for (size_t i(0); i != user.size(); i++)
	  if (username == user[i] && pass[i] == password)
	    s.isAdmin = true;
      if (s.isAdmin)
	{
	  send(s.fd, UP_LOGIN, strlen(UP_LOGIN), 0);
	  s.nickname = "<strong>" + username + "</strong>";
	  s.nick = username;
	  std::cout << "\033[32;1mThe admin " << s.nick << " just logging";
	  std::cout << "\033[0m" << std::endl;
	}
      else
	send(s.fd, ERR_LOGINFAIL, strlen(ERR_LOGINFAIL), 0);
    }
}
