######################################################################
# Automatically generated by qmake (3.0) Wed Apr 16 19:25:06 2014
######################################################################

TEMPLATE = app
TARGET = client
INCLUDEPATH += . header
QT += widgets
unix:OBJECTS_DIR = objs/

# Input
HEADERS += header/Client.h header/Interface.hpp
SOURCES += srcs/check_funcs.c \
           srcs/Client.c \
           srcs/init_funcs.c \
           srcs/Interface.cpp \
           srcs/main.cpp \
           srcs/pars.c \
           srcs/str_to_wordtab.c \
           srcs/xfunction.c \
           srcs/xfunction2.c
