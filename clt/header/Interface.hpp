//
// Client.hpp for client in /home/apollo/rendu/PSU_2013_myirc/client
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Sat Apr 12 18:46:09 2014 ribeaud antonin
// Last update Thu Apr 17 19:28:31 2014 ribeaud antonin
//

#ifndef INTERFACE_HPP_
# define INTERFACE_HPP_

# define WIDTH 600
# define HEIGHT 800

# include "Client.h"
# include <sstream>
# include <QtCore>
# include <QFont>
# include <QPainter>
# include <QDesktopServices>
# include <QtWidgets/QApplication>
# include <QtWidgets/QPushButton>
# include <QtWidgets/QLCDNumber>
# include <QtWidgets/QColorDialog>
# include <QtWidgets/QGridLayout>
# include <QtWidgets/QHBoxLayout>
# include <QtWidgets/QGroupBox>
# include <QtWidgets/QDialog>
# include <QtWidgets/QMenuBar>
# include <QtWidgets/QMenu>
# include <QtWidgets/QAction>
# include <QtWidgets/QLabel>
# include <QtWidgets/QMessageBox>
# include <QLineEdit>
# include <QTextEdit>
# include <QString>
# include <QTime>
# include <QTimer>

class	Worker : public QObject
{
  Q_OBJECT
public:
  Worker();
  ~Worker();
  QString getInput();
  void	stopWork();
public slots:
  void	process();
signals:
  void	finished();
  void	error();
private:
  QString _input;
};

class	Client : public	QWidget
{
  Q_OBJECT

public:
  Client();
public slots:
  void		countTime();
  void		getInput();
  void		testRec();
  void		selectBackground();
  void		showAbout() const;
  void		toggleStatus();
private:
  QString	setStatus(QString input);
  void		addHomeMsg();
  void		addInput(QString);
  void		initLayouts();
  void		userLayout();
  void		inputLayout();
  void		displayLayout();
  void		init_ui();
  void		applyLayouts();
  void		timeLayout();
  void		connectSlots();
  int		engageRec();
  void		getInput2(QString input);
  void		printInfos(QString input);
  void		menuBar();
  int		browser(QString input);
protected:
  int		_status;
  QAction	*_exitAction;
  QAction	*_toggleStatus;
  QAction	*_backgroundColor;
  QAction	*_about;
  QMenuBar	*_menuBar;
  QMenu		*_fileMenu;
  QGridLayout	*_mainLayout;
  QTextEdit	*_users;
  QTextEdit	*_chatbox;
  QLabel	*_input;
  QPushButton	*_send;
  QLCDNumber	*_time;
  QTimer	*_timer;
  QTimer	*_timerec;
  QLineEdit	*_lineedit;
  Worker	*_worker;
  char		*_usersInput;
};

#endif /* INTERFACE_HPP_ */
