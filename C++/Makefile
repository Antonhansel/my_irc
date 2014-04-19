##
## Makefile for  in /home/aube_a/Documents/projet/thread
## 
## Made by Mehdi Chouag
## Login   <aube_a@epitech.net>
## 
## Started on  Tue Mar 18 23:25:23 2014 Mehdi Chouag
## Last update Sat Apr 19 16:51:10 2014 Mehdi Chouag
##

SRCS		= main.cpp \
		  Server.cpp \
		  function.cpp \

OBJ2		= $(SRCS:.cpp=.o)

CPPFLAGS	= -W -Wall -Wextra -Werror

NAMES		= serveur

all: $(NAMES)

$(NAMES): $(OBJ2)
	g++ -o $(NAMES) $(OBJ2) -g
clean:
	rm -f $(OBJ2)

fclean: clean
	rm -f $(NAMES)

re: fclean all
