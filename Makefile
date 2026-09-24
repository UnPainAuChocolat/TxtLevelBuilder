#-----------------------------------[Variables]-----------------------------------

NAME=												game

CC=													g++

SRC=												main.cpp\
													menu.cpp\
													Player/player.cpp\
													Objects/ground.cpp\
													levelLoader.cpp

FLAG=												-Wall -Wextra -Werror

#---------------------------------------[Func]-------------------------------------

all:
	$(CC) $(FLAG) $(SRC) -lraylib -o $(NAME)

#---------------------------------------[PHONY]------------------------------------

.PHONY: all
