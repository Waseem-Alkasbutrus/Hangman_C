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

//util function declarations
int menu(char optionCount, int menu);
void printMenuInterface(int menuID);
void printStickMan(int stage);
void clearNewline(char str[]);

//game logic declarations
int getPuzzle();
int game(char puzzle[MSIS], char encryptedPuzzle[MSIS]);
int checkGuess(char puzzle[MSIS], char encryptedPuzzle[MSIS], char guess);
void encryptPuzzle(char puzzle[MSIS], char encryption[MSIS]);

//Typedefs
typedef struct {
	char master[51];
	char encrypted[51];
	char guesses[36];//has space for alphanumeric characters (only lower case values)
} puzzle;


#endif