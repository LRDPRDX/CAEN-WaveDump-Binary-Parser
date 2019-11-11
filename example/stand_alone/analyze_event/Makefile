#compiler
CC = g++

#cpp flags
FLAGS 		= -std=c++11
CPPFLAGS 	= -Wall -Wextra

#libs
LIB     	= -lcaenparse

#directories
MAIN_DIR 	= ../../..
INC_DIR     = $(MAIN_DIR)/inc

#choose the executable name
EXE      	= analyze_event 

SRC     	= $(shell echo *.cpp)


$(EXE) : $(SRC)
	$(CC) $(SRC)  $(FLAGS) -I$(INC_DIR) $(LIB) -o $(EXE) 


.PHONY: clean
clean :
	rm $(EXE)
