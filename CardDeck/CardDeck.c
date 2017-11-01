/*==============================================================================
|
|   Source code: CardDeck.c
|        Author: Nicolas Queijo
|    Student ID: 5152398
|    Assignment: Program #3 Simulates and deals deck of cards
|        Course: COP 4338 - Programming III
|       Section: U03
|    Instructor: William Feild
|      Due Date: Oct 17, 2017, by the end of class
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______________________________________ [Signature]
|
|      Language: C
|   Compile/Run:
| 			gcc CardDeck.c –o CardDeck.out
|			./CardDeck.out n m
|
|			Where n and m are the cards per hands and players respectively;
|			they must be integer values between 1-13 and their product
|			cannot exceed 52.
|
|			Assure the header file required (CardDeckHeader.h) is located
|			in the same directory as CardDeck.c
|
|  +----------------------------------------------------------------------------
|
|   Description: This program simulates the process of generating a deck of 52
|				 cards, shuffling the deck, and dealing the shuffled deck to
|				 a set of players.
|         Input: Two integers in the range of 1-13. 
|				 Their product cannot exceed 52.
|        Output: The original deck of cards in order, the shuffled deck, and
|				 the hands of each player after the cards have been dealt.
|       Process: Construction of a deck using the appropriate data structures,
|				 shuffling of the deck using randomized algorithms, distribution
|				 of the cards to the players in the game aka dealing.
|    Required Features Not Included: N/A
|    Known Bugs: N\A
|
|*============================================================================*/

#include <stdio.h>
#include <stdlib.h> // needed to use atoi function
#include "CardDeckHeader.h" // contains all the constants and prototypes needed

enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES};
enum Rank {_A, _2, _3, _4, _5, _6, _7, _8, _9, _10, _J, _Q, _K};

//const char* SUIT_NAMES[] = {CLUBS_ICON, DIAMONDS_ICON, HEARTS_ICON, SPADES_ICON};
const char* SUIT_NAMES[] = {"C", "D", "H", "S"};
const char* RANK_NAMES[] = {"A", "2", "3", "4", "5", "6","7",
							 "8", "9", "T", "J", "Q", "K"};

/*------------------------------------------------------------------------------
|  function: main()
|
|  Purpose: Entry point of program execution
|  @param   argc - the number of command-line arguments
|  @param	argv - array of strings representing the command-line arguments
|  @return  0  -- flag indicating program executed successfully
------------------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	validateInput(argc, argv);
	int const CARDS_PER_HAND = atoi(argv[CARDS_PER_HAND_INDEX]);
	int const PLAYERS = atoi(argv[PLAYERS_INDEX]);
	int deck[SUIT_SIZE][RANK_SIZE][SUIT_RANK_PAIR_SIZE];
	createDeck(deck);
	printf(NEWLINE);
	printf(ORIGINAL_DECK_TITLE);
	displayDeck(deck);
	shuffleDeck(deck);
	printf(DIVIDER);
	printf(SHUFFLED_DECK_TITLE);
	displayDeck(deck);
	int hands[MAX_CARDS_PER_HAND][MAX_PLAYERS][SUIT_RANK_PAIR_SIZE];
	dealHands(deck, hands, CARDS_PER_HAND, PLAYERS);
	printf(DIVIDER);
	printf(HANDS_TITLE);
	displayHands(hands, CARDS_PER_HAND, PLAYERS);
	return EXIT_SUCCESS;
} // end main function


/*------------------------------------------------------------------------------
|  function: validateInput(argc, argv)
|
|  Purpose: Validates the input of the program by calling other functions that
|			validate each requirement of the input validation. If at any point
|			the input invalidation fails an appropriate error message is printed
|			and the program exits.
|  @param   argc - the number of command-line arguments
|  @param	argv - array of strings representing the command-line arguments
------------------------------------------------------------------------------*/
void validateInput(int argc, char* argv[]) {
	validateArgumentCount(argc);
	validateArgumentTypes(argv);
	validateArgumentRange(argv);
} // end validateInput function


/*------------------------------------------------------------------------------
|  function: validateArgumentCount(argc)
|
|  Purpose: Validates the user entered the correct number of command-line args
|  @param   argc - the number of command-line arguments
------------------------------------------------------------------------------*/
void validateArgumentCount(int argc) {
	if (argc != TOTAL_COMMAND_LINE_ARGS) {
		printf("Error. Two command-line arguments required.\n");
		exit(EXIT_FAILURE);
	} // end if
} // end validateArgumentCount function


/*------------------------------------------------------------------------------
|  function: validateArgumentTypes(argv)
|
|  Purpose: Validates the two command-line to be are integers
|  @param	argv - array of strings representing the command-line arguments
------------------------------------------------------------------------------*/
void validateArgumentTypes(char* argv[]) {
	validateStringAsInteger(argv[CARDS_PER_HAND_INDEX]);
	validateStringAsInteger(argv[PLAYERS_INDEX]);
} // end validateArgumentTypes function


/*------------------------------------------------------------------------------
|  function: validateStringAsInteger(string)
|
|  Purpose: Takes a string and validates that every char in it is of a value 0-9
|  @param   string - the string to validate
------------------------------------------------------------------------------*/
void validateStringAsInteger(char* string) {
	const char NULL_CHAR = '\0';
	int index;
	for (index = 0; string[index] != NULL_CHAR; index++) {
		if (isdigit(string[index]) == FALSE) {
			printf("Error. Arguments must be positive integers.\n");
			exit(EXIT_FAILURE);
		} // end if
	} // end for
} // end validateStringAsInteger function


/*------------------------------------------------------------------------------
|  function: validateArgumentRange(argv)
|
|  Purpose: Validates that each of the command-line arguments is in the range of
|			1-13. Validates that the multiplication of the two command-line 
|			arguments does not exceed the amount of cards available. Does this
|			by first converting each string to its integer representation.
|  @param	argv - array of strings representing the command-line arguments
------------------------------------------------------------------------------*/
void validateArgumentRange(char* argv[]) {
	int cardsPerHand = atoi(argv[CARDS_PER_HAND_INDEX]);
	int players = atoi(argv[PLAYERS_INDEX]);
	if (cardsPerHand < MIN_CARDS_PER_HAND || cardsPerHand > MAX_CARDS_PER_HAND) {
		printf("Error. Cards per hand must be between %d-%d.\n", 
			MIN_CARDS_PER_HAND, MAX_CARDS_PER_HAND);
		exit(EXIT_FAILURE);
	} // end if
	if (players < MIN_PLAYERS || players > MAX_PLAYERS) {
		printf("Error. There must be between %d-%d players.\n", MIN_PLAYERS,
			MAX_PLAYERS);
		exit(EXIT_FAILURE);
	} // end if
	int cardsRequired = cardsPerHand * players;
	if (cardsRequired > TOTAL_CARDS) {
		printf("Error. Not enough cards for this game.\n");
		exit(EXIT_FAILURE);
	} // end if
} // end validateArgumentRange function


/*------------------------------------------------------------------------------
|  function: createDeck(deck)
|
|  Purpose: Initializes the deck to the default values. The first two dimensions
|			of the deck array represent the indices of the 52 cards. The third
|			dimension represents the suit and rank value of that card.
|  @param   deck - 3D array used to represent the deck of cards
------------------------------------------------------------------------------*/
void createDeck(int deck[SUIT_SIZE][RANK_SIZE][SUIT_RANK_PAIR_SIZE]) {
	int row;
	int col;
	for (row = 0; row < SUIT_SIZE; row++) {
		for (col = 0; col < RANK_SIZE; col++) {
			deck[row][col][SUIT_INDEX] = row;
			deck[row][col][RANK_INDEX] = col;
		} // end for
	} // end for
} // end createDeck function


/*------------------------------------------------------------------------------
|  function: displayDeck(deck)
|
|  Purpose: Displays the deck to the console. Does this by iterating through
|			each card and mapping the values in the third dimension of the array
|			to the constant strings arrays representing the suits and ranks.
|  @param   deck - 3D array used to represent the deck of cards
------------------------------------------------------------------------------*/
void displayDeck(int deck[SUIT_SIZE][RANK_SIZE][SUIT_RANK_PAIR_SIZE]) {
	int row;
	int col;
	for (row = 0; row < SUIT_SIZE; row++) {
		for (col = 0; col < RANK_SIZE; col++) {
			printf("%s%s  ", SUIT_NAMES[deck[row][col][SUIT_INDEX]],
				RANK_NAMES[deck[row][col][RANK_INDEX]]);
		} // end for
		printf(NEWLINE);
	} // end for
} // end displayDeck function


/*------------------------------------------------------------------------------
|  function: shuffleDeck(deck)
|
|  Purpose: Shuffles the deck using an algorithm that imitates Java's 
|			Collections.shuffle() method. Does this by traversing the deck and
|			for each cell it generates a random row and a random column, swaps
|			the contents of the current cell with the contents of the cell in 
|			that random row/column combination.
|			Time complexity: O(n * m) where n and m are the number of rows and 
|							 columns of the array respectively.
|			Source of algorithm:
|			https://docs.oracle.com/javase/6/docs/api/java/util/
|			Collections.html#shuffle(java.util.List)
|  @param   deck - 3D array used to represent the deck of cards
------------------------------------------------------------------------------*/
void shuffleDeck(int deck[SUIT_SIZE][RANK_SIZE][SUIT_RANK_PAIR_SIZE]) {
	srand(time(NULL));
	int row;
	int col;
	int randomRow;
	int randomCol;
	int suit;
	int rank;
	for (row = 0; row < SUIT_SIZE; row++) {
		for (col = 0; col < RANK_SIZE; col++) {
			randomRow = rand() % SUIT_SIZE;
			randomCol = rand() % RANK_SIZE;
			suit = deck[randomRow][randomCol][SUIT_INDEX];
			rank = deck[randomRow][randomCol][RANK_INDEX];
			deck[randomRow][randomCol][SUIT_INDEX] = deck[row][col][SUIT_INDEX];
			deck[randomRow][randomCol][RANK_INDEX] = deck[row][col][RANK_INDEX];
			deck[row][col][SUIT_INDEX] = suit;
			deck[row][col][RANK_INDEX] = rank;
		} // end for
	} // end for
} // end shuffleDeck function


/*------------------------------------------------------------------------------
|  function: dealHands(deck, hands, cardsPerHand, players)
|
|  Purpose: Takes the deck 3D array copies it to a 2D array and then uses that
|			2D array to distribute the cards into another 3D array used to 
|			represent the hands. Deals the cards one by one to each player until
|			each player has the cardsPerHand amount specified by the user.
|  @param   deck - 3D array used to represent the deck of cards
|  @param	hands - 3D array used to represent the hands that will be dealt
|  @param   cardsPerHand - the number of card each player receives
|  @param	players - the number of players participating in the game
------------------------------------------------------------------------------*/
void dealHands(int deck[SUIT_SIZE][RANK_SIZE][SUIT_RANK_PAIR_SIZE], 
	int hands[MAX_CARDS_PER_HAND][MAX_PLAYERS][SUIT_RANK_PAIR_SIZE],
	int cardsPerHand, int players) {
	int index = 0;
	int linearDeck[TOTAL_CARDS][SUIT_RANK_PAIR_SIZE];
	int row;
	int col;
	for (row = 0; row < SUIT_SIZE; row++) {
		for (col = 0; col < RANK_SIZE; col++, index++) {
			linearDeck[index][SUIT_INDEX] = deck[row][col][SUIT_INDEX];
			linearDeck[index][RANK_INDEX] = deck[row][col][RANK_INDEX];
		} // end for
	} // end for
	int cardsPerHandIndex;
	int playersIndex;
	index = 0;
	for (cardsPerHandIndex = 0; cardsPerHandIndex < cardsPerHand; 
		cardsPerHandIndex++) {
		for (playersIndex = 0; playersIndex < players; 
			playersIndex++, index++) {
			hands[cardsPerHandIndex][playersIndex][SUIT_INDEX] = 
				linearDeck[index][SUIT_INDEX];
			hands[cardsPerHandIndex][playersIndex][RANK_INDEX] = 
				linearDeck[index][RANK_INDEX];
		} // end for
	} // end for
} // end dealHands function


/*------------------------------------------------------------------------------
|  function: displayHands(hands, cardsPerHand, players)
|
|  Purpose: Displays the hands to the console. Does this by iterating through
|			each card and mapping the values in the third dimension of the array
|			to the constant strings arrays representing the suits and ranks.
|  @param   hands - 3D array used to represent the hands
|  @param	cardsPerHand - the number of card each player receives
|  @param	players - the number of players participating in the game
------------------------------------------------------------------------------*/
void displayHands(int hands[MAX_CARDS_PER_HAND][MAX_PLAYERS]
	[SUIT_RANK_PAIR_SIZE], int cardsPerHand, int players) {
	const int OFF_BY_ONE = 1;
	int playersIndex;
	int cardsPerHandIndex;
	for (playersIndex = 0; playersIndex < players; playersIndex++) {
		printf("%s %d:  ", "Player", playersIndex + OFF_BY_ONE);
		for (cardsPerHandIndex = 0; cardsPerHandIndex < cardsPerHand;
			cardsPerHandIndex++) {
			printf("%s%s  ", SUIT_NAMES[hands[cardsPerHandIndex][playersIndex][SUIT_INDEX]],
				RANK_NAMES[hands[cardsPerHandIndex][playersIndex][RANK_INDEX]]);
		} // end for
		printf(NEWLINE);
	} // end for
	printf(NEWLINE);
} // end displayHands function
