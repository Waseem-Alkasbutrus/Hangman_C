#include "hangman.h"

/*
	to do:
		erno error checking
		minimize risks and perform error handling
		check for repeat guesses 
		add pve 
		add settings to the main menu
		add a play again option straight from the game over menu
	done: 
		
*/

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: ./a.out MODE\n\nModes: \t1: Player vs Player\n\t2: Player vs Computer\n");
		return 1;
	} if (argv[1][0] != '1' && argv[1][0] != '2') {
		printf("Usage: ./a.out MODE\n\nModes: \t1: Player vs Player\n\t2: Player vs Computer\n");
		return 1;
	}

	while(1) {
		system("clear");
		int winner = 0, mainOption = menu('2', 0);

		switch (mainOption) {
			case 1: //play
				system("clear");
				winner = getPuzzle();
				system("clear");
				break;
			case 2: //exit
				system("clear");
				return 0;
		}

		int VictoryOption = menu('2', winner);
		
		if(VictoryOption == 2) {
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
		2 for host win
		3 for player win
*/

int getPuzzle() {
	int winner = 1, option = 2; //2 if host wins, 3 if player(s) win
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

		option = menu('2', 1);

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
		2 for host win
		3 for player win
*/
int Game(char puzzle[MSIS], char encryptedPuzzle[MSIS]) {
	int winner = 3, lives = LIVES; //2 if host wins, 3 if player(s) win

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
			winner = 2;
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

int menu(char optionCount, int menu) {//utility function
	int result = -1;

	while(1) {
		char input = 0;

		if (menu >= 0) {
			printMenu(menu);
		}

		printf("Option: ");
		scanf("%c", &input);

		while(getchar() != '\n');

		if(input >= 49 && input <= optionCount) {
			result = input - '0';
			break;
		} else {
			printf("\nInvalid Option. Please try again\n");
		}
	}

	return result;
}