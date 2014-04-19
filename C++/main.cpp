//
// main.cpp for main.cpp in /home/chouag_m/perso/my_irc/C++
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Fri Apr 18 19:02:31 2014 Mehdi Chouag
// Last update Sun Apr 20 00:23:33 2014 Mehdi Chouag
//

#include "Server.hh"

Server	g_s;

void    sighandle(int i)
{
  std::cout << "\n\033[31;1mSIGNAL "<< i << " RECIEVED\nSERVER SHUTTING DOWN\033[0m\n";
  g_s.deleteAllFd();
  g_s.closeServerFd();
  exit (0);
}

int		main(void)
{
  try 
    {
      signal(SIGINT, sighandle);
      signal(SIGQUIT, sighandle);
      g_s.loop();
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (-1);
    }
  return (0);
}
