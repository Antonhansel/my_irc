//
// main.cpp for main in /home/apollo/rendu/PSU_2013_myirc/client/srcClient
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Sat Apr 12 17:22:57 2014 ribeaud antonin
// Last update Mon Apr 14 18:23:05 2014 ribeaud antonin
//

#include "Interface.hpp"

int		main(int argc, char **argv)
{
  QApplication	app(argc, argv);
  Client	Client;
  
  Client.show();
  return (app.exec());
}
