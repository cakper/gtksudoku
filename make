#!/bin/bash
gcc -Wall -o sudoku interface.c list.c logic.c signals.c main.c `pkg-config --cflags --libs gtk+-2.0` -export-dynamic
