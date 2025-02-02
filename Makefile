CC=gcc
FLAGS=-Wall -Wextra
SERVER=server
CLIENT=client
MAIN=adaws

all:
	$(CC) $(FLAGS) $(CLIENT).c $(SERVER).c $(MAIN).c -o $(MAIN)

.PHONY: all
