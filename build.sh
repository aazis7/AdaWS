#!/bin/bash

CC=gcc
FLAGS="-Wall -Wextra"
SERVER=server
CLIENT=client
MAIN=adaws

$CC $FLAGS $CLIENT.c $SERVER.c $MAIN.c -o $MAIN
