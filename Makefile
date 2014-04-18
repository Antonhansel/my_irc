##
## Makefile for  in /home/aube_a/Documents/projet/thread
## 
## Made by Mehdi Chouag
## Login   <aube_a@epitech.net>
## 
## Started on  Tue Mar 18 23:25:23 2014 Mehdi Chouag
## Last update Wed Apr 16 23:09:43 2014 ribeaud antonin
##

SRCS		= server/src/server.c \
		  server/src/list.c \
		  server/src/list2.c \
		  server/src/init_server.c \
		  server/src/check_cmd.c \
		  server/src/pointer_funct.c \
		  server/src/xfunction.c \
		  server/src/xfunction2.c \
		  server/src/my_str_to_wordtab.c

OBJ2		= $(SRCS:.c=.o)

CFLAGS		= -W -Wall -Wextra -Werror -I ./server/header
NAMES		= serveur

all: $(NAMES)

$(NAMES): $(OBJ2)
	gcc -o $(NAMES) $(OBJ2) -g
	cd clt && make

clean:
	rm -f $(OBJ2)
	cd clt && make clean
fclean: clean
	rm -f $(NAMES)
	cd clt && cd .. && rm -f ./client

re: fclean all
