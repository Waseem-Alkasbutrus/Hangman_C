#include "hangman.h"

/*
	to do:
		check for repeats
		add pve and settings to the main menu
		add a play again option straight from the game over menu
		re-organize main function
*/

int main(void) {
	int reOption = 1;

	while(reOption == 1) {
		system("clear");
		bool exitStatus = false;
		int mainOption = -1, winner = 0;

		while(mainOption == -1){
			printMenu(0);
			mainOption = menu('2');

			switch (mainOption) {
				case 1: 
					system("clear");
					winner = getPuzzle();
					system("clear");
					break;
				case 2: 
					system("clear");
					return 0;
				default: printf("\nInvalid option. Try again.\n");
			}
		}

		while (true) {
			switch(winner) {
				case 1: 
					printStickMan(0);
					printMenu(2);
					break;
				case 2: 
					printMenu(3);
			}

			reOption = menu('2');

			if (reOption != -1) {
				break;
			}
		}
		
		if(reOption == 2) {
			break;
		}
	}

	system("clear");
	return 0;
}

/*
	getPuzzle: stores a user-input puzzle, continues the game and returns the winner.

	Parameters:
		NONE
	Returns: 
		1 for host win
		2 for player win
*/

int getPuzzle() {
	int winner = 1, option = 2; //1 if host wins, 2 if player(s) win
	char puzzle[MSIS] = {}, encryptedPuzzle[MSIS] = {};

	while(option != 1) {

		if(option == 2) {
			printf("Player(s), Look away. Host, enter your puzzle (maximum of %d characters).\n", MSIS-1);
			printf("Puzzle: ");
			fgets(puzzle, MSIS, stdin);
			for(int i = 0; i < MSIS; i++) {
				if (puzzle[i] == '\n') {
					puzzle[i] = '\0';
					break;
				}
			}
		}

		printf("\nYou Entered: ");
		puts(puzzle);

		printMenu(1);
		option = menu('2');

		switch(option) {
			case 1: 
				system("clear");
				encryptPuzzle(puzzle, encryptedPuzzle);
				winner = Game(puzzle, encryptedPuzzle);
				system("clear");
				break;
			case 2:
				system("clear");
				break;
			default:
				printf("\nInvalid option. Try again.\n");
		}
	}

	printf("The puzzle was: ");
	puts(puzzle);

	return winner;
}

/*
	Game: asks the players to enter single-character guesses and returns the winner.

	parameters: 
		char puzzle[MSIS]: the original puzzle entered by the host
		char encryptedPuzzle[MSIS]: the encrypted version of puzzle

	Returns:	
		1 for host win
		2 for player win
*/
int Game(char puzzle[MSIS], char encryptedPuzzle[MSIS]) {
	int winner = 2, lives = LIVES; 

	while(lives >= 0 && strcmp(puzzle, encryptedPuzzle) != 0) {
		if(lives > 0) {
			char guess = '0';

			printStickMan(lives);

			printf("Puzzle:\n");
			puts(encryptedPuzzle);

			printf("\nGuess: ");
			guess = getchar();
			while(getchar() != '\n');

			system("clear");

			int mathces = checkGuess(puzzle, encryptedPuzzle, guess);

			if (mathces == 0) {
				lives--;
				printf("\"%c\" is incorrect :(\n1 life lost, %d lives remain.", guess, lives);
			} else if (mathces > 0) {
				printf("\"%c\" is correct :D\nNo lives lost, %d lives remain", guess, lives);
			} else {
				printf("Invalid guess. Only alphanumeric characters allowed (A-Z, 0-9).\n");
				printf("No lives lost, %d lives remain", lives);
			}
		} else {
			winner = 1;
			lives--;
		}
	}

	system("clear");
	return winner;
}

/*
	checkGuess: checks if a single-character guess is used in the puzzle, if it is it decrypts 
				the character in that index in the encryptedPuzzle.

	Parameters:
		char puzzle[MSIS]: the original puzzle entered by the host
		char encryptedPuzzle[MSIS]:the encrypted version of puzzle
		char guess: the guess entered by the player

	Returns:
		-1 if no matches were found
		int instances of guess in puzzle
*/
int checkGuess(char puzzle[MSIS], char encryptedPuzzle[MSIS], char guess) {
	int matches = -1;

	if(isalnum(guess)){
		matches = 0;

		for (int i = 0; i < strlen(puzzle); i++) {
			if (puzzle[i] == guess) {
				encryptedPuzzle[i] = puzzle[i];
				matches++;
			} else if (guess >= 65 && (guess + 32 == puzzle[i] || guess -32 == puzzle[i])) {
				encryptedPuzzle[i] = puzzle[i];
				matches++;
			}
		} 
	}

	return matches;
}


/*
	encryptPuzzle: it copies the contents of puzzle into the adress of encryption with all the alphanumeric
					characters changed into '*'

	Parameters:
		char puzzle[MSIS]: the original puzzle entered by the host
		char encryption[MSIS]: an address where the encrypted puzzle will be saved
	Returns: 
		NONE
*/
void encryptPuzzle(char puzzle[MSIS], char encryption[MSIS]) {
	int i = 0;

	while(puzzle[i] != '\0' && puzzle[i] != '\n') {
		if (isalnum(puzzle[i])) {
			encryption[i] = '*';
		} else {
			encryption[i] = puzzle[i];
		}
		i++;
	}
}

/*
	printStickMan: prints the current stage of the stickman

	Parameters:
		int stage: the number of lives available for the players (0-7)

	Returns: 
		NONE
*/
void printStickMan(int stage) {
	switch(stage) {
		case 7: printf("\n ╔═══╗\n ║\n ║\n ║\n ║\n ║\n═╩\n\n");
			break;
		case 6: printf("\n ╔═══╗\n ║   │\n ║\n ║\n ║\n ║\n═╩\n\n");
			break;
		case 5: printf("\n ╔═══╗\n ║   │\n ║   O\n ║\n ║\n ║\n═╩\n\n");
			break;
		case 4: printf("\n ╔═══╗\n ║   │\n ║   O\n ║   ┼\n ║   ┴\n ║\n═╩\n\n");
			break;
		case 3: printf("\n ╔═══╗\n ║   │\n ║   O\n ║  └┼\n ║   ┴\n ║\n═╩\n\n");
			break;
		case 2: printf("\n ╔═══╗\n ║   │\n ║   O\n ║  └┼┘\n ║   ┴\n ║\n═╩\n\n");
			break;
		case 1: printf("\n ╔═══╗\n ║   │\n ║   O\n ║  └┼┘\n ║  ┌┴\n ║\n═╩\n\n");
			break;
		case 0: printf("\n ╔═══╗\n ║   │\n ║   O\n ║  └┼┘\n ║  ┌┴┐\n ║\n═╩\n\n");
			break;
	}
}

void printMenu(int menuID){
	switch(menuID) {
		case 0:
			printf("╔════════════════════════════════╗\n");
			printf("╔  ╔ ╔══╗ ╔═╗╔ ╔══╗ ╔╗╔╗ ╔══╗ ╔═╗║\n");
			printf("╠══╣ ╠══╣ ║ ║║ ║ ═╗ ║║║║ ╠══╣ ║ ║║\n");
			printf("║  ╝═╝  ╝═╝ ╚╝═╝══╝═╝╚╝╝═╝  ╝═╝ ╚╝\n");
			printf("╠════════════════════════════════╣\n");
			printf("║            [1] PLAY            ║\n");
			printf("╠════════════════════════════════╣\n");
			printf("║            [2] EXIT            ║\n");
			printf("╚════════════════════════════════╝\n");
			break;
		case 1: 
			printf("╔════════════════════════════════╗\n");
			printf("║          [1] CONFIRM           ║\n");
			printf("╠════════════════════════════════╣\n");
			printf("║           [2] RETRY            ║\n");
			printf("╚════════════════════════════════╝\n");
			break;
		case 2:			
			printf("╔════════════════════════════════╗\n");
			printf("║           GAME OVER!           ║\n");
			printf("║    VICTORY FOR THE HOST(S)!    ║\n");
			printf("╠════════════════════════════════╣\n");
			printf("║         [1] Main Menu          ║\n");
			printf("╠════════════════════════════════╣\n");
			printf("║            [2] Exit            ║\n");
			printf("╚════════════════════════════════╝\n");
			break;
		case 3: 
			printf("╔════════════════════════════════╗\n");
			printf("║        CONGRATULATIONS!        ║\n");
			printf("║   VICTORY FOR THE PLAYER(S)!   ║\n");
			printf("╠════════════════════════════════╣\n");
			printf("║         [1] Main Menu          ║\n");
			printf("╠════════════════════════════════╣\n");
			printf("║            [2] Exit            ║\n");
			printf("╚════════════════════════════════╝\n");
			break;
	}
}

int menu(char optionCount) {//utility function
	int result = -1;

	if (optionCount >= 49 && optionCount <= 57) {
		char input;

		printf("Option: ");
		scanf("%c", &input);

		while(getchar() != '\n');

		if(input >= 49 && input <= optionCount) {
			result = input - '0';
		}
	}

	return result;
}