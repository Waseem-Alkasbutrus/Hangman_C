#ifndef HANGMAN_H_
#define HANGMAN_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//macros
#define MSIS 51 //Maximum string input size
#define LIVES 7

//util function declarations
int menu(char optionCount, int menu);
void printMenu(int menuID);
void printStickMan(int stage);

//hangman function declarations
int getPuzzle();
int Game(char puzzle[MSIS], char encryptedPuzzle[MSIS]);
int checkGuess(char puzzle[MSIS], char encryptedPuzzle[MSIS], char guess);
void encryptPuzzle(char puzzle[MSIS], char encryption[MSIS]);


#endif