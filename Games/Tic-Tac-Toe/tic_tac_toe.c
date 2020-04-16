/*	
 * ############ TIC TAC TOE ###################
 *	
 * Implementation of Simple Tic Tac Toe Game
 * in C Language.
 * Auther - L Saimohan Rao
 * Email  - saimohanrao92@gmail.com
 * GitHub - https://github.com/saimohan1
 *
 * ############################################
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define ROW		3
#define COLUMN		3
#define BOARD_SIZE  ROW * COLUMN
#define MAX_NAME_SIZE	50
#define X_TYPE		"X"
#define O_TYPE		"O"
#define NUM2ASCII(num) ((48) +(num)) /* 48 is ASCII value of 0 */
#define ASCII_OF_X	88 /* ASCII value of X */
#define ASCII_OF_O	79 /* ASCII value of O */
#define MAX_RETRIES	3

/* Player object */
typedef struct player {
	char name[MAX_NAME_SIZE];
	char type;
	bool winner;
	void *board; /* To store the board */	
} __attribute__((packed)) player_t;

/* TIC TAC TOE */
struct tic_tac_toe {
	char *board;		/* ROW * COLUMN Board */
	struct player *player1; /* Player1 Object */
	struct player *player2; /* Player2 Object */
	int 	*used_numbers;  /* Stores the used inputes */
	uint8_t	size;		/* Size of the board */
	uint8_t input_index;	/* Current input index */
} __attribute__((packed)) tic_tac_toe_t;

enum players {
	PLAYER1 = 1,
	PLAYER2
};

enum board_postion {
	POSITION_0 = 0,
	POSITION_1,
	POSITION_2,
	POSITION_3,
	POSITION_4,
	POSITION_5,
	POSITION_6,
	POSITION_7,
	POSITION_8,
};

/* alloc_board:
 * Allocated the required amount of Memory for 
 * board, Players, used numbers.
 * Returns:
 * On Sucess  - Allocated struct tic_tac_toe object
 * on Failure - NULL
 */
static struct tic_tac_toe *
alloc_board(void)
{
	struct tic_tac_toe *board;
	/* First Allocate the memory for board object */
	board = malloc(sizeof(struct tic_tac_toe));
	if (!board)
		goto fail;
	memset(board, 0, sizeof(struct tic_tac_toe));
	/* Now allocate memory for the board */
	board->board = malloc(sizeof(char) * BOARD_SIZE);
	if (!board->board)
		goto board_fail;
	memset(board->board, 0, sizeof(char) * BOARD_SIZE);
	/* Now allocate memory for used number */
	board->used_numbers = malloc(sizeof(int) * BOARD_SIZE);
	if (!board->used_numbers)
		goto used_number_fail;

	/* Now allocate memory for player 1 */
	board->player1 = malloc(sizeof(struct player));
	if (!board->player1)
		goto player1_falied;

	/* Now allocate memory for player 2 */
	board->player2 = malloc(sizeof(struct player));
	if (!board->player2)
		goto player2_falied;

	/* Successfully Allocated Memory for all the objects */
	board->size = BOARD_SIZE;	
	assert(board != NULL);
	return board;

player2_falied:
	free(board->player1);
player1_falied:
	free(board->used_numbers);
used_number_fail:
	free(board->board);
board_fail:
	free(board);
fail:
	return NULL;
}

/* initialize_board:
 */
static void
initialize_board(struct tic_tac_toe *board)
{
	int i;
	
	board->size = ROW * COLUMN;
	/* Initialize board with Numbers */
	for (i = 0; i < board->size; i++) {
		board->board[i] = NUM2ASCII(i);		
	}
	
	board->player1->winner = false;
	board->player2->winner = false;
	board->player1->board = board->player2->board = board;
}

static void
display_header()
{
	printf("#################################\n");
	printf("\t TIC-TAC-TOE\n");
	printf("#################################\n");
	
}

/* display_board
 *
 *  0 | 1 | 2
 *  3 | 4 | 5
 *  6 | 7 | 7
 */
static void
display_board(struct tic_tac_toe *board)
{
	system("clear");
	display_header();
	printf("---------------------------------\n");
	printf("\t%c | %c | %c\n", board->board[0],
			board->board[1], board->board[2]);
	printf("\t%c | %c | %c\n", board->board[3],
			board->board[4], board->board[5]);
	printf("\t%c | %c | %c\n", board->board[6],
			board->board[7], board->board[8]);
	printf("---------------------------------\n");
}

/* get_user_details:
 * Function will take user input
 */
static void
get_user_details(struct tic_tac_toe *board)
{
	printf("Please Enter the first player name: ");
	fgets(board->player1->name, MAX_NAME_SIZE, stdin);
	strtok(board->player1->name, "\n");
	printf("First Player %s will play with 'X'\n", board->player1->name);
	board->player1->type = ASCII_OF_X;
	printf("Please Enter the Second player name: ");
	fgets(board->player2->name, MAX_NAME_SIZE, stdin);
	strtok(board->player2->name, "\n");
	printf("Second Player %s will play with 'O'\n", board->player2->name);
	board->player2->type = ASCII_OF_O;
}

/* Validate user input Number */
static inline bool
is_not_valid_number(int input)
{
	if (input < 0 || input > 9) 
		return true;
	else
		return false;
}

/* Function will validate if it is already entered */
static inline bool
is_used_number(int input, struct tic_tac_toe *board)
{
	int i;
	
	for (i = 0; i < board->size; i++) {
		if (board->used_numbers[i] == input && input != 0)
			return true;
	}
	return false;
}

static uint8_t
get_user_input(struct player *player)
{
	int input, count = 0;
	struct tic_tac_toe *board = (struct tic_tac_toe *) player->board;
	assert(board != NULL);

//	printf("Board [%p]\n", board);
input:
	if (count < MAX_RETRIES) {
		printf("%s please enter your input: ", player->name);
		scanf("%d", &input);
		if (is_not_valid_number(input)) {
			printf("Please enter a valid input.!!! Retry\n");
			count++;
			goto input;
		}
		if (is_used_number(input, board)) {
			printf("Please enter a valid input.!!! Retry\n");
			count++;
			goto input;	
		}
		/* Valid input is entered So storing it */
		board->used_numbers[board->input_index++] = input;
		return input;
	} 
	printf("Maximum Retry reached. Quiting Game. Thank you.\n");
	return EINVAL;	
}

/* Stores value in the Board */
static void
add_input_to_board(struct tic_tac_toe *board, uint8_t input,
			enum players player)
{
	if (player == PLAYER1)
		board->board[input] = ASCII_OF_X; 
	else
		board->board[input] = ASCII_OF_O;
}

static struct player *
get_player(struct tic_tac_toe *board, enum players player)
{
	return player == PLAYER1 ? board->player1 : board->player2; 
}

/* Checks if the any of the rows has valid win combination */
static bool
is_row_completed(struct tic_tac_toe *board, struct player *player)
{
	if ( board->board[POSITION_0] == player->type &&
		board->board[POSITION_1] == player->type &&
		board->board[POSITION_2] == player->type) {
		return true;
	} else if ( board->board[POSITION_3] == player->type &&
			 board->board[POSITION_4] == player->type &&
			 board->board[POSITION_5] == player->type) {
		return true;
	} else if ( board->board[POSITION_6] == player->type &&
			 board->board[POSITION_7] == player->type &&
			 board->board[POSITION_8] == player->type) {
		return true;
	} else {
		return false;
	}
}

/* Checks if the any of the Colomn has valid win combination */
static bool
is_column_completed(struct tic_tac_toe *board, struct player *player)
{
	if ( board->board[POSITION_0] == player->type &&
		board->board[POSITION_3] == player->type &&
		board->board[POSITION_6] == player->type) {
		return true;
	} else if ( board->board[POSITION_1] == player->type &&
			 board->board[POSITION_4] == player->type &&
			 board->board[POSITION_7] == player->type) {
		return true;
	} else if ( board->board[POSITION_2] == player->type &&
			 board->board[POSITION_5] == player->type &&
			 board->board[POSITION_8] == player->type) {
		return true;
	} else {
		return false;
	}
}

/* Checks if the any of the Diagonal has valid win combination */
static bool
is_diagonal_completed(struct tic_tac_toe *board, struct player *player)
{
	if ( board->board[POSITION_0] == player->type &&
		board->board[POSITION_4] == player->type &&
		board->board[POSITION_8] == player->type) {
		return true;
	} else if ( board->board[POSITION_2] == player->type &&
			 board->board[POSITION_4] == player->type &&
			 board->board[POSITION_6] == player->type) {
		return true;
	} else {
		return false;
	}
}

/* Checks if the Match has a Draw/Tie */
static inline bool
is_tie(struct tic_tac_toe *board)
{
	return board->input_index > 8 ? true : false;
}

/* Validate the Winner of the Match */
static bool
match_finish(struct tic_tac_toe *board, enum players enum_player)
{	
	bool	finish = false;
	struct player *player = get_player(board, enum_player);
	finish = is_row_completed(board, player);
	if (finish) {
		player->winner = true;
		printf("Congratualtion %s !!! you won.\n", player->name);
		goto out;
	}
	finish = is_column_completed(board, player);
	if (finish) {
		player->winner = true;
		printf("\nCongratualtion %s !!! you won.\n", player->name);
		goto out;
	}	
	finish = is_diagonal_completed(board, player);
	if (finish) {
		player->winner = true;
		printf("\nCongratualtion %s !!! you won.\n", player->name);
		goto out;
	}
	finish = is_tie(board);
	if (finish)
		printf("\nMatch Finished with Draw.\n");
out:
	return finish;
}

/* Main Game */
static void
play_tic_tac_tie(struct tic_tac_toe *board)
{
	uint8_t player1_input, player2_input;
	while(1) {
		player1_input = get_user_input(board->player1);
		if (player1_input == EINVAL)
			return;
		add_input_to_board(board, player1_input, PLAYER1);
		display_board(board);
		/* validating match results */
		if (match_finish(board, PLAYER1))
			break;
		
		player2_input = get_user_input(board->player2);
		if (player1_input == EINVAL)
			return;
		add_input_to_board(board, player2_input, PLAYER2);
		display_board(board);
		/* validating match results */
		if (match_finish(board, PLAYER2))
			break;
	
	}

}

/* Resource Clean up Function */
static void
cleanup(struct tic_tac_toe *board)
{
	/* Clean up  memory */
	free(board->player2);
	free(board->player1);
	free(board->used_numbers);
	free(board->board);
	free(board);
}

int main()
{
	struct tic_tac_toe *board = alloc_board();
	display_header();
	initialize_board(board);
	get_user_details(board);
	display_board(board);
	play_tic_tac_tie(board);	
	cleanup(board);
	printf("Game Over. Thank you ^_^\n");
	return 0;
}
