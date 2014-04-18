//
// Client.cpp for Client in /home/apollo/rendu/PSU_2013_myirc/client/srcClient
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Sat Apr 12 17:29:26 2014 ribeaud antonin
// Last update Thu Apr 17 23:12:07 2014 ribeaud antonin
//

#include "Interface.hpp"
#include "Client.h"

void	Client::addInput(QString input)
{
  _chatbox->append(input);
}

QString	Client::setStatus(QString input)
{
  QString	status;

  status = "<strong>[AFK]</strong>";
  input += '\n';
  if (_status == 1)
    {
      status += input;
      input = status;
    }
  return (input);
}

void	Client::getInput2(QString input)
{
  char	*str;
  
  input = setStatus(input);
  str = parsInput(input.toUtf8().constData());
  if (str[0] != '-')
    {
      if ((int)strlen(str) > 0)
	{
	  if (xsend(str) == 0)
	    {
	      addInput("<strong>-[Error]: </strong>Connection Crashed!");
	      endConnection();
	    }
	}
      else
	addInput("<strong>-[Error]: </strong>Message too long!");
    }
  else
    {
      input = QString::fromUtf8(str);
      addInput(input);
    }
}

int		Client::browser(QString input)
{
  QStringList	list;
  QString	test;

  
  test = "https://intra.epitech.eu/user/";
  list = input.split(" ");
  if (list[0] == "/intra")
    {
      if (list.size() > 1)
	{
	  test += list[1];
	  QDesktopServices::openUrl(QUrl(test));
	  return (1);
	}
    }
  return (0);
}

void	Client::getInput()
{
  QString      input;

  input = _lineedit->text();
  _lineedit->setText("");
  if (input.size() > 0)
    {
      if (browser(input) == 0)
	{
	  if (input == "/help")
	    addHomeMsg();
	  else if (input == "/quit")
	    QCoreApplication::quit();
	  else
	    getInput2(input);
	}
    }
}

void	Client::inputLayout()
{
  QString	input;

  _send = new QPushButton("send");
  _lineedit = new QLineEdit(this);
  _lineedit->setGeometry(QRect((WIDTH/5), (HEIGHT) -
  (HEIGHT/3.2), (WIDTH - 20), (HEIGHT/20))); 
  input = _lineedit->text();
  _input = new QLabel(input, this);
  _input->setAlignment(Qt::AlignCenter);
}

void	Client::timeLayout()
{
  _time = new QLCDNumber;
  _timer = new QTimer;

  _time->setDigitCount(12);
  _time->display(QTime::currentTime().toString(QString("hh:mm:ss")));
  _time->setPalette(Qt::red);
  _timer->start(100);
  _time->setFixedSize((WIDTH/6), (HEIGHT/20));
}

void	Client::countTime()
{
  _time->display(QTime::currentTime().toString(QString("hh:mm:ss")));
}

void	Client::displayLayout()
{
  _chatbox = new QTextEdit(this);
  _chatbox->setFrameStyle(QFrame::Box | QFrame::Raised);
  _chatbox->setFocus();
  _chatbox->setStyleSheet
    ("background : url(.images/logo.jpg) no-repeat center white;");
  _chatbox->setReadOnly(true);
  addHomeMsg();
}

void		Client::userLayout()
{
   QString	str;
  
  _users = new QTextEdit(this);
  _users->setFixedWidth((WIDTH/6));
  _users->setFrameStyle(QFrame::Box | QFrame::Sunken);
  _users->setReadOnly(true);
  _users->setStyleSheet
    ("background : url(.images/users.png) center; color : white;");
}

void	Client::applyLayouts()
{
  _mainLayout->setMenuBar(_menuBar);
  _mainLayout->addWidget(_users, 0, 0);
  _mainLayout->addWidget(_chatbox, 0, 1);
  _mainLayout->addWidget(_time, 1, 0);
  _mainLayout->addWidget(_input, 1, 1, Qt::AlignLeft);
  _mainLayout->addWidget(_send, 1, 1, Qt::AlignRight);
}

void	Client::addHomeMsg()
{
  _chatbox->append(tr("<strong><em>Welcome on my_irc BETA</em></strong>"));
  _chatbox->append(tr("--Available commands are:"));
  _chatbox->append(tr("--/server _host_[:_port_]"));
  _chatbox->append(tr("--/nick _nickname_"));
  _chatbox->append(tr("--/join _channel_"));
  _chatbox->append(tr("--/part _channel_"));
  _chatbox->append(tr("--/users"));
  _chatbox->append(tr("--/list [_channel_]"));
  _chatbox->append(tr("--/msg _nickname_ _mesage_"));
  _chatbox->append(tr("--/send_file _nickname_ _file_"));
  _chatbox->append(tr("--/accept_file _nickname_"));
  _chatbox->append(tr("--/quit"));
}

void	Client::initLayouts()
{
  userLayout();
  menuBar();
  inputLayout();
  displayLayout();
  timeLayout();
}

void	Client::init_ui()
{
  _status = -1;
  initStruct();
  _usersInput = NULL;
  _mainLayout = new QGridLayout;
  setFixedSize(HEIGHT, WIDTH);
  setWindowTitle(tr("My_IRC"));
}

Client::Client() : QWidget()
{
  init_ui();  
  initLayouts();
  applyLayouts();
  connectSlots();
  setLayout(_mainLayout);
}

void		Client::printInfos(QString input)
{
  QStringList list = QString(input).split(" ");
  QString str1;

  _users->setText(" ");
  while (list.size() != 0)
    {
      str1 = list.at(0);
      _users->append(str1);
      list.removeFirst();
    }
}

int		Client::engageRec()
{
  QThread	*th = new QThread;

  _worker = new Worker();
  _worker->moveToThread(th);
  QObject::connect(th, SIGNAL(started()), _worker, SLOT(process()));
  QObject::connect(_worker, SIGNAL(finished()), th, SLOT(quit()));
  th->start();
  return (-1);
}

void		Client::toggleStatus()
{
  _status *= -1;
}

void		Client::menuBar()
{
  _menuBar = new QMenuBar;
  _fileMenu = new QMenu(tr("&Menu"), this);
  _toggleStatus = _fileMenu->addAction(tr("Change status"));
  _backgroundColor = _fileMenu->addAction(tr("Change background color"));
  _about = _fileMenu->addAction(tr("About"));
  _exitAction = _fileMenu->addAction(tr("E&xit"));
  _menuBar->addMenu(_fileMenu);

  connect(_exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(_toggleStatus, SIGNAL(triggered()), this, SLOT(toggleStatus()));
  connect(_backgroundColor, SIGNAL(triggered()), 
	  this, SLOT(selectBackground()));
  connect(_about, SIGNAL(triggered()), this, SLOT(showAbout()));
}

void		Client::testRec()
{
  QString	input;
  static	int  i = 0;

  if (i == 0)
    i = engageRec();
  else
    {
      input = _worker->getInput();
      if (input != "")
	{
	  if (input.at(0) != ' ')
	    addInput(input);
	  else
	    printInfos(input);
	}
      _worker->stopWork();
      i = 0;
    }
}

void	Client::selectBackground()
{
  QColor couleur = QColorDialog::getColor(Qt::white, this);
  QPalette palette;

  palette.setColor(QPalette::Background, couleur);
  this->setAutoFillBackground(true);
  this->setPalette(palette);
  this->show();
}

void		Client::showAbout() const
{
  QMessageBox msgBox;

  msgBox.setText("Coders:");
  msgBox.setInformativeText("ribeau_a\nchouag_m\n");
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.exec();
}

void	Client::connectSlots()
{
  _timerec = new QTimer;

  _timerec->start(10);
  QObject::connect(_lineedit, SIGNAL(returnPressed()), 
		   this,SLOT(getInput(void)));
  QObject::connect(_send, SIGNAL(clicked()), this,SLOT(getInput(void)));
  QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(countTime(void)));
  QObject::connect(_timerec, SIGNAL(timeout()), this, SLOT(testRec(void)));
}

Worker::Worker()
{
  
}

Worker::~Worker()
{
 
}

QString		Worker::getInput()
{
  return (_input);
}

void		Worker::process()
{
  char		*rec;

  rec = xrecieve();
  if (strlen(rec) > 1 && rec[strlen(rec) - 1] == '\n')
    rec[strlen(rec) - 1] = '\0';
  _input = QString::fromUtf8(rec);
}

void		Worker::stopWork()
{
  emit finished();
}
