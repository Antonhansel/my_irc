//
// serveur.cpp for serveur in /home/chouag_m/Qt/LALALA
// 
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
// 
// Started on  Mon Apr 21 22:49:00 2014 Mehdi Chouag
// Last update Sun Apr 27 16:13:24 2014 Mehdi Chouag
//

#include "serveur.hh"
#include "ui_qtcestnul.hh"

Serveur::Serveur(QWidget *parent) : QMainWindow(parent)
{
  setWindowTitle("my_irc server");
  setFixedSize(this->width(),this->height());
  _option.push_back("/join");
  _option.push_back("/part");
  _option.push_back("/users");
  _option.push_back("/list");
  _option.push_back("/nick");
  _option.push_back("/msg");
  _option.push_back("/login");
  _option.push_back("/kick");
  _option.push_back("/logout");
  _ptr["/join"] = &Serveur::join;
  _ptr["/part"] = &Serveur::part;
  _ptr["/users"] = &Serveur::users;
  _ptr["/list"] = &Serveur::list;
  _ptr["/nick"] = &Serveur::nick;
  _ptr["/msg"] = &Serveur::msg;
  _ptr["/login"] = &Serveur::login;
  _ptr["/kick"] = &Serveur::kick;
  _ptr["/logout"] = &Serveur::logout;
  _count = 0;
}

Serveur::~Serveur()
{}

std::ostream&		operator<<(std::ostream& flux, const QString& data)
{
  flux << data.toStdString();
  return (flux);
}

void		Serveur::join(QStringList &list, t_client &c)
{
  if (list.size() != 2)
    c.socket->write(ERR_CHAN); 
  else if (list.at(1).size() > 9)
    c.socket->write(ERR_JOINSIZE);
  else
    {
      std::cout << "\033[32;1m" <<  c.nick.toStdString();
      std::cout << " has setup his channel to " << list.at(1).toStdString();
      std::cout << "\033[0m" << std::endl;
      c.channel = "<strong>" + list.at(1) + "</strong>";
      c.socket->write(UP_CHAN);
    }
}

void		Serveur::part(QStringList &list, t_client &c)
{
  if (list.size() != 2)
    c.socket->write(ERR_PART); 
  else if ("<strong>" + list.at(1) + "</strong>" != c.channel)
    c.socket->write(ERR_PARTCHAN);
  else
    {
      std::cout << "\033[31;1m" <<  c.nick.toStdString();
      std::cout << " has leave the channel " << list.at(1).toStdString();
      std::cout << "\033[0m" << std::endl;
      c.channel = "none";
      c.socket->write(UP_PART);
    }
}

void		Serveur::users(QStringList &list, t_client &c)
{
  (void)c;
  (void)list;
  std::cout << "USERS\n" << std::endl;
}

void		Serveur::list(QStringList &list, t_client &c)
{
  (void)c;
  (void)list;
  std::cout << "LIST\n" << std::endl;
}

void		Serveur::msg(QStringList &list, t_client &c)
{
  (void)c;
  (void)list;
  std::cout << "MSG\n" << std::endl;
}

void		Serveur::login(QStringList &list, t_client &c)
{
  (void)c;
  (void)list;
  std::cout << "LOGIN\n" << std::endl;
}

void		Serveur::kick(QStringList &list, t_client &c)
{
  (void)c;
  (void)list;
  std::cout << "KICK\n" << std::endl;
}

void		Serveur::logout(QStringList &list, t_client &c)
{
  (void)c;
  (void)list;
  std::cout << "LOGOUT\n" << std::endl;
}

void		Serveur::nick(QStringList &list, t_client &c)
{
  bool		isExist(false);

  if (list.size() != 2 || list.at(1).size() > 9)
    c.socket->write(ERR_NICK); 
  else
    {
      for (int i(0); i != _clients.size(); i++)
	{
	  if (_clients[i].nick == list.at(1))
	    isExist = true;
	}
      if (!isExist)
	{
	  std::cout << "\033[32;1m" <<  c.nick.toStdString();
	  std::cout << " has setup his nickname to " << list.at(1).toStdString();
	  std::cout << "\033[0m" << std::endl;
	  c.nick = list.at(1);
	  c.nickname = "<em>" + list.at(1) + "</em>";
	  c.socket->write(UP_NICK);
	}
      else
	c.socket->write(ERR_NICKUSED);
    }
}

void		Serveur::launch()
{
  
  _serveur = new QTcpServer(this);
  if (_serveur->listen(QHostAddress::Any, 6667))
    {
      std::cout << "\033[32;1mThe server is running up \033[0m" << std::endl;
      connect(_serveur, SIGNAL(newConnection()),this, SLOT(newClient()));
    }
  else
    std::cout << "\033[31;1mFail on launching the serveur \033[0m" << std::endl;
}

void		Serveur::newClient()
{
  t_client	c;
  QString	addr;
  
  c.socket = _serveur->nextPendingConnection();
  addr = c.socket->peerAddress().toString();
  std::cout << "\033[32;1mNew connection from : " << addr; 
  std::cout << "\033[0m" << std::endl;
  c.nickname = "<em>Anonymous" + QString::number(_count) + "</em>";
  c.nick = "Anonymous" + QString::number(_count);
  c.channel = "none";
  c.socket->write("Welcome on my_irc\n");
  _clients << c;
  connect(c.socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
  connect(c.socket, SIGNAL(disconnected()), this, SLOT(disconnectClient()));
  _count++;
}

bool		Serveur::checkCommand(QStringList &list, t_client &c)
{
  bool		find(false);
  std::vector<QString>::const_iterator it;

  for (it = _option.begin(); it != _option.end(); ++it)
      {
        if ((*it) == list.at(0))
	  {
	    find = true;
	    (this->*_ptr[(*it)])(list, c);
	    break;
	  }
      }
  return (find);
}

void		Serveur::deleteSpace(QString &msg)
{
  QString	line;
  std::string	parsing = msg.toStdString();

  if (parsing.find("") <= parsing.size())
    {
      for (size_t i(0); i != parsing.size(); i++)
	{
	  if (parsing[i] != ' ')
	    line += parsing[i];
	  else if (parsing[i - 1] != ' ' && parsing[i] == ' ' && parsing[i + 1] != '\0')
	    line += parsing[i];
	}
      if (line[line.size() - 1] == ' ')
	line.resize(line.size() - 1);
      msg = line;
    }
}

void		Serveur::receiveData(void)
{
  QTcpSocket	*socket;
  QStringList	list;
  QString	msg;
  char		test[4096];
  size_t        i;

  socket = qobject_cast<QTcpSocket *>(sender());
  memset(test, 0, 4096);
  socket->read(test, sizeof(test));
  msg = test;
  msg.resize(msg.size() - 1);
  deleteSpace(msg);
  for (i = 0; _clients[i].socket != socket; i++);
  list = msg.split(' ');
  msg = _clients[i].nickname + " " + msg + "\n";
  if (!checkCommand(list, _clients[i]))
    sendAll(msg, _clients[i].channel);
}

void		Serveur::disconnectClient()
{
   QTcpSocket	*socket;
   size_t	i;

   socket = qobject_cast<QTcpSocket *>(sender());
   for (i = 0; _clients[i].socket != socket; i++);
   std::cout << "\033[31;1m" << _clients[i].nick.toStdString() << " has left the server";
   std::cout << "\033[0m" << std::endl;
   _clients[i].socket->close();
   _clients.removeAt(i);
}

void    Serveur::sendAll(QString &msg, QString &channel)
{
  for (int i(0); i != _clients.size(); i++)
    {
      if (_clients[i].channel == channel && channel != "none")
	_clients[i].socket->write(msg.toStdString().c_str());
      else if (channel == "none")
	_clients[i].socket->write(ERR_CHAN);
    }
}

void	Serveur::connectSql()
{
  QSqlDatabase db = QSqlDatabase::addDatabase("lostsoul");
  db.setHostName("localhost");
  db.setDatabaseName("lostsoul");
  db.setUserName("root");
  db.setPassword("root");
  bool ok = db.open();
  std::cout << ok << std::endl;
}
