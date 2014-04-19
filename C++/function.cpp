//
// function.cpp for function.cpp in /home/chouag_m/perso/my_irc/C++
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Sat Apr 19 16:43:54 2014 Mehdi Chouag
// Last update Sat Apr 19 17:34:06 2014 Mehdi Chouag
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
