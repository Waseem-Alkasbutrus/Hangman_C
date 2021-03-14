#ifndef HANGMAN_H_
#define HANGMAN_H_

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//definitions
#define MSIS 51 //Maximum string input size
#define LIVES 7
#define GUESS_BANK 36//has space for alphanumeric characters (only lower case values)

//Typedefs
typedef struct {
	char master[MSIS];
	char encrypted[MSIS];
	char guesses[GUESS_BANK];
} puzzle;

//util function declarations
int menu(char optionCount, int menu);
void printMenuInterface(int menuID);
void printStickMan(int stage);
void clearNewline(char str[]);

//game logic declarations
void getPuzzle(puzzle *p);
int game(puzzle *p);
int checkGuess(puzzle *p, char guess);
void encryptPuzzle(puzzle *p);


#endif