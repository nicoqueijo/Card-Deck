/*==============================================================================
|
|   Source code: CardDeckHeader.h
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
|*============================================================================*/

/* constants */
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define TOTAL_COMMAND_LINE_ARGS 3
#define CARDS_PER_HAND_INDEX 1
#define PLAYERS_INDEX 2
#define TRUE 1
#define FALSE 0
#define MIN_CARDS_PER_HAND 1
#define MAX_CARDS_PER_HAND 13
#define MIN_PLAYERS 1
#define MAX_PLAYERS 13
#define SUIT_SIZE 4
#define RANK_SIZE 13
#define TOTAL_CARDS 52
#define SUIT_RANK_PAIR_SIZE 2
#define SUIT_INDEX 0
#define RANK_INDEX 1
#define CLUBS_ICON "\xe2\x99\xa3"
#define DIAMONDS_ICON "\xe2\x99\xa6"
#define HEARTS_ICON "\xe2\x99\xa5"
#define SPADES_ICON "\xe2\x99\xa0"
#define NEWLINE "\n"
#define DIVIDER "\n--------------------------------------------------\n\n"
#define ORIGINAL_DECK_TITLE "Original deck:\n\n"
#define SHUFFLED_DECK_TITLE "Shuffled deck:\n\n"
#define HANDS_TITLE "Hands:\n\n"

/* function prototypes */
void validateInput(int, char*[]);
void validateArgumentCount(int);
void validateArgumentTypes(char*[]);
void validateStringAsInteger(char*);
void validateArgumentRange(char*[]);
void createDeck(int[SUIT_SIZE][RANK_SIZE][SUIT_RANK_PAIR_SIZE]);
void displayDeck(int[SUIT_SIZE][RANK_SIZE][SUIT_RANK_PAIR_SIZE]);
void shuffleDeck(int[SUIT_SIZE][RANK_SIZE][SUIT_RANK_PAIR_SIZE]);
void dealHands(int[SUIT_SIZE][RANK_SIZE][SUIT_RANK_PAIR_SIZE],
	int[MAX_CARDS_PER_HAND][MAX_PLAYERS][SUIT_RANK_PAIR_SIZE], int, int);
void displayHands(int[MAX_CARDS_PER_HAND][MAX_PLAYERS][SUIT_RANK_PAIR_SIZE],
	int, int);