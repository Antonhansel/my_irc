/*
** serveur.h for Serveur in /home/chouag_m/Qt/LALALA
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Mon Apr 21 22:44:09 2014 Mehdi Chouag
// Last update Sat Apr 26 22:42:26 2014 Mehdi Chouag
*/

#ifndef SERVEUR_HH
#define SERVEUR_HH

#include <iostream>
#include <vector>
#include <map>
#include <QMainWindow>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSqlDatabase>

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
#define ERR_LOGIN       "<strong>[admin] : /login [username] [password]\n"
#define ERR_LOGINOPEN   "<strong>[admin] : Can't open the login file\n"
#define UP_LOGIN        "<strong>[admin] : You're now logged in\n"
#define UP_LOGOUT       "<strong>[admin] : You're now logged out\n"
#define ERR_LOGINFAIL   "<strong>[admin] : Username or password invalid\n"
#define ERR_ADMINNICK   "<strong>[admin] : You're already logged as admin\n"
#define ERR_ADMINKICK   "<strong>[admin] : /kick [nickname] [reason]\n"
#define ERR_ADMINKICK2  "<strong>[admin] : You can't kick yourself\n"
#define ERR_ADMINUSER   "<strong>[admin] : The user doesn't exist\n"
#define ERR_LOGINCON    "<strong>[admin] : You're account is already used in an other Client\n"
#define UP_ADMINKICK    "<strong>[admin] : The user has been kicked\n"

typedef struct	s_client
{
  QString	channel;
  QString	nickname;
  QString	nick;
  QTcpSocket	*socket;
}		t_client;

class Serveur : public QMainWindow
{
  Q_OBJECT
    
public:
  explicit Serveur(QWidget *parent = 0);
  ~Serveur();
  void launch();
  void connectSql();
public slots:
  void			newClient();
  void			receiveData(void);
  void			disconnectClient(void);

private:
  void			sendAll(QString&, QString&);
  bool			checkCommand(QStringList&, t_client&);
  void			join(QStringList&, t_client&);
  void			nick(QStringList&, t_client&);
  void			part(QStringList&, t_client&);
  void			users(QStringList&, t_client&);
  void			list(QStringList&, t_client&);
  void			msg(QStringList&, t_client&);
  void			login(QStringList&, t_client&);
  void			kick(QStringList&, t_client&);
  void			logout(QStringList&, t_client&);
  void			deleteSpace(QString&);

private:
  QTcpServer		*_serveur;
  QList<t_client>	_clients;
  quint16		_tailleMessage;
  size_t		 _count;
  std::vector<QString>	_option;
  std::map<QString, void(Serveur::*)(QStringList &, t_client&)> _ptr; 
};

std::ostream&		operator<<(std::ostream&, const QString&);

#endif /* !SERVEUR_HH */
