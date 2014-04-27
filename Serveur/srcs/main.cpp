//
// main.cpp for main.c in /home/chouag_m/Qt/Serveur
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Tue Apr 22 00:29:50 2014 Mehdi Chouag
// Last update Sat Apr 26 22:43:11 2014 Mehdi Chouag
//

#include "serveur.hh"
#include <QApplication>
#include <signal.h>

void    sighandle(int i)
{
  std::cout << "\n\033[31;1mSIGNAL "<< i << " RECIEVED\nSERVER SHUTTING DOWN\033[0m\n";
  exit (0);
}

int		main(int argc, char *argv[])
{
  QApplication	a(argc, argv);
  Serveur	w;

  signal(SIGINT, sighandle);
  signal(SIGQUIT, sighandle);
  w.launch();
  w.connectSql();
  
  return (a.exec());
}
