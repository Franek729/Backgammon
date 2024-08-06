#pragma once

#define BOARD_SIZE 24
#define DICE 80
#define DICEY 16
#define MAX_HEIGHT 8
#define DICE_NUMBER 2
#define TEXT_SIZE 32

// board information
#define BOARD_PLACES 24
#define BOARD_SIZEY 17
#define BOARD_SIZEX 29

// printing info
#define BOARD_STARTLOCATION_X 40
#define BOARD_STARTLOCATION_Y 10
#define BOARD_MIDDLEX 55

// keycaps
#define MOVE_PAWN 'm'
#define ROLL_DICE 'r'
#define DEFAULTTEXTSIZE 32
#define ENTER 0x0d
#define NULLCHAR 0x00
#define SAVE_GAME 's'
#define LOAD_GAME 'l'
#define NEW_GAME 'n'

struct dice
{
    int x = DICE;
    int y = DICEY;
    int value = 0;
};

struct board_info
{
    int StartX = BOARD_STARTLOCATION_X;
    int StartY = BOARD_STARTLOCATION_Y;
    int EndX = BOARD_STARTLOCATION_X + BOARD_SIZEX;
    int EndY = BOARD_STARTLOCATION_Y + BOARD_SIZEY;
    int scrollx = 0;
    int scrolly = 0;
    int middleX = BOARD_MIDDLEX;
    int middleY = BOARD_STARTLOCATION_Y + BOARD_SIZEY / 2;
    int places = BOARD_PLACES;
};

struct field
{
    char player;
    int height;
};

struct board
{
    struct field fields[24];
    int white_bar;
    int red_bar;
    int white_home;
    int red_home;
};

enum player
{
    white, // 0
    red    // 1
};

struct game
{
    enum player players[2];
    enum player turn;
};

bool ingame = false;
bool dublet = false;

void UserInterface(struct game *game);

void BarAndHome(struct board *board);

void init_bars(struct board *board);

void print_fields_numbers(struct board_info *gboard);

void print_board(struct board_info *gboard);

void roll(struct dice dices[]);

void print_dices(struct dice dices[], int n);

void init_pawns(struct board *board);

enum player who_starts();

enum player tura(struct game *game);

void print_pawns(struct board *board, int j, int n, int x, int y);

void put_pawns(struct board *board, struct board_info *gboard);

char *text(int x, int y);

void move_pawn(board *board, int from, int howFar);

bool check_home(struct board *board, struct game *game);

void move_home(struct board *board, int from, struct game *game);

bool checkDublet(struct dice dices[]);

bool check_move(struct board *board, int n, int moveFrom, struct game *game);

void RemoveWhiteBar(board *board, game *game, int d);

void RemoveRedBar(board *board, game *game, int d);

void ChooseDiceForBar(dice dices[], board *board, board_info *gboard, game *game);

bool CheckingBar(board *board, game *game);

void make_move(dice d[], board *b, board_info *gb, game *g, int howFar, int i, int m, bool dublet);

void make_2_moves_r(dice d[], board *b, board_info *gb, game *g, bool dublet);

void make_2_moves_w(dice d[], board *b, board_info *gb, game *g, bool dublet);

void make_turn2(dice d[], board *b, board_info *gb, game *g, bool dub, char c);

void make_turn1(dice d[], board *b, board_info *gb, game *g, bool dub, char c);

void choose_quantity(dice dices[], board *board, board_info *gboard, game *game, bool dublet);

void init_game(board_info *gboard, dice dices[], game *game);

void save_game(board *board, game *game, dice dices[]);

void new_game(board *board, dice dices[], game *game);

void load_game(board *board, game *game, dice dices[]);

void in_game(board *board, board_info *gboard, game *game, dice dices[]);

void play_game(char zn, dice dices[], board *board, board_info *gboard, game *game, bool dublet, bool ingame);

void CheckForWinner(board* board);

#pragma once