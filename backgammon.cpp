#define _CRT_SECURE_NO_WARNINGS
#include "backgammon.h"
#include "conio2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void start() // starting screen
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(6, 2);
    cputs("Welcome to Backgammon!");
    gotoxy(6, 3);
    cputs("Press N 2 times to start");
    char c = getch();
    if (c == 'n')
    {
        clrscr();
    }
    else
    {
        return;
    }
}

void UserInterface(game *game) // printing user interface on the screen
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(76, 1);
    cputs("q       = exit");
    gotoxy(76, 2);
    cputs("m       = move pawn");
    gotoxy(76, 3);
    cputs("s       = save game");
    gotoxy(76, 4);
    cputs("l       = load game");
    gotoxy(76, 5);
    cputs("n       = new game");
    gotoxy(76, 6);
    cputs("Turn:");
    gotoxy(76, 7);
    textcolor(WHITE);
    cputs(game->turn != white ? "white" : "red");
}

void BarAndHome(board *board) // printing bar and home info - number of pawns on each
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(88, 14);
    cputs("White Pawns on Bar:");
    gotoxy(88, 15);
    printf("%d", board->white_bar);
    gotoxy(88, 16);
    cputs("Red Pawns on Bar:");
    gotoxy(88, 17);
    printf("%d", board->red_bar);
    gotoxy(88, 18);
    cputs("White Pawns in Home:");
    gotoxy(88, 19);
    printf("%d", board->white_home);
    gotoxy(88, 20);
    cputs("Red Pawns in Home:");
    gotoxy(88, 21);
    printf("%d", board->red_home);
}

void init_bars(board *board) // initializing bar and home info to 0
{
    board->white_bar = 0;
    board->red_bar = 0;
    board->white_home = 0;
    board->red_home = 0;
}

void print_fields_numbers(board_info *gboard) // printing numbers of fields on the board
{
    textbackground(BLACK);
    textcolor(WHITE);
    for (int i = 1; i <= 6; i++)
    {
        gotoxy(gboard->EndX - 2 * i + 1, gboard->EndY);
        printf("%d", i);
    }
    for (int i = 7; i <= 9; i++)
    {
        gotoxy(gboard->middleX - 2 * i + 12, gboard->EndY);
        printf("%d", i);
    }
    for (int i = 10; i <= 12; i++)
    {
        gotoxy(gboard->middleX - 2 * i + 11, gboard->EndY);
        printf("%d", i);
    }
    for (int i = 13; i <= 18; i++)
    {
        gotoxy(gboard->StartX + 2 * i - 24, gboard->StartY - 1);
        printf("%d", i);
    }
    for (int i = 19; i <= 24; i++)
    {
        gotoxy(gboard->middleX + 2 * i - 36, gboard->StartY - 1);
        printf("%d", i);
    }
}

void print_board(board_info *gboard) // printing board on the screen
{
    textbackground(BLACK);
    textcolor(WHITE);
    for (int i = 0; i < (gboard->EndX - gboard->StartX); i++)
    {
        gotoxy(gboard->StartX + i + 2, gboard->StartY);
        cputs("=");
        gotoxy(gboard->StartX + i + 2, gboard->EndY - 1);
        cputs("=");
    }
    for (int i = 0; i < (gboard->EndY - gboard->StartY); i++)
    {
        gotoxy(gboard->StartX, gboard->StartY + i);
        cputs("::");
        gotoxy(gboard->EndX, gboard->StartY + i);
        cputs("::");
        gotoxy(gboard->middleX - 1, gboard->StartY + i);
        cputs(":::");
    }
    gotoxy(gboard->middleX - 1, gboard->middleY);
    cputs("BAR");
    gotoxy(gboard->EndX + 4, gboard->middleY);
    cputs("HOME");
}

void roll(dice dices[]) // rolling dices
{
    int res1 = 0;
    int res2 = 0;
    res1 += (rand() % 6) + 1;
    res2 += (rand() % 6) + 1;
    dices[0].value = res1;
    dices[1].value = res2;
}

void print_dices(dice dices[], int n) // printing dices on the screen
{
    char txt[TEXT_SIZE] = "DICE";
    for (int i = 0; i < n; i++)
    {
        char c = 49 + i;
        textbackground(BLACK);
        textcolor(WHITE);
        gotoxy(dices[i].x, dices[i].y - 1 + 3 * i);
        printf("%s %c\n", txt, c);
        textbackground(LIGHTGRAY);
        textcolor(BLACK);
        gotoxy(dices[i].x, dices[i].y + 3 * i);
        printf("%d", dices[i].value);
    }
}

void init_pawns(board &board) // initializing starting positions of pawns
{
    for (int i = 0; i < 24; i++)
    {
        board.fields[i].player = 0;
        board.fields[i].height = 0;
    }
    board.fields[0].player = white;
    board.fields[0].height = 2;
    board.fields[5].player = red;
    board.fields[5].height = 5;
    board.fields[7].player = red;
    board.fields[7].height = 3;
    board.fields[11].player = white;
    board.fields[11].height = 5;
    board.fields[12].player = red;
    board.fields[12].height = 5;
    board.fields[16].player = white;
    board.fields[16].height = 3;
    board.fields[18].player = white;
    board.fields[18].height = 5;
    board.fields[23].player = red;
    board.fields[23].height = 2;
}

enum player who_starts() // randomly choosing who starts
{
    srand(time(NULL));
    int res1 = 0;
    int res2 = 0;
    res1 += (rand() % 6) + 1;
    res2 += (rand() % 6) + 1;
    if (res1 > res2)
    {
        return white;
    }
    else
    {
        return red;
    }
}

enum player tura(game *game) // changing turn after each move
{
    if (game->turn == white)
    {
        return red;
    }
    else
    {
        return white;
    }
}

void print_pawns(board *board, int j, int n, int x, int y) // printing pawns on the screen
{
    textbackground(BLACK);

    struct field boardField = board->fields[j];

    if (boardField.player == white)
    {
        textcolor(WHITE);
    }
    else if (boardField.player == red)
    {
        textcolor(RED);
    }

    if (j >= 0 && j <= 11)
    {
        for (int i = 0; i < boardField.height; i++)
        {
            gotoxy(x - 2 * j - n, y - 2 - i);
            cputs("O");
        }
    }
    if (j >= 12 && j <= 23)
    {
        for (int i = 0; i < boardField.height; i++)
        {
            gotoxy(x + 2 * j - n, y + 1 + i);
            cputs("O");
        }
    }
}

void put_pawns(board *board, board_info *gboard) // putting pawns on the board
{
    textbackground(BLACK);

    for (int i = 0; i < 24; i++)
    {
        if (i >= 0 && i <= 5)
        {
            print_pawns(board, i, 1, gboard->EndX, gboard->EndY);
        }
        else if (i > 5 && i <= 11)
        {
            print_pawns(board, i, 4, gboard->EndX, gboard->EndY);
        }
        else if (i > 11 && i <= 17)
        {
            print_pawns(board, i, 21, gboard->StartX, gboard->StartY);
        }
        else if (i > 17 && i < 24)
        {
            print_pawns(board, i, 33, gboard->middleX, gboard->StartY);
        }
    }
}

char *text(int x, int y) // getting input from user to acknowledge which pawn to move
{
    static char textHolder[DEFAULTTEXTSIZE];
    int currChar = 0;
    char Char;
    do
    {
        Char = getch();
        if (Char > 47 && Char < 58)
        {
            textHolder[currChar] = Char;
            textHolder[currChar + 1] = ' ';
            textHolder[currChar + 2] = NULLCHAR;
            currChar++;
        }
        gotoxy(x, y);
        cputs(textHolder);
    } while (Char != ENTER);
    textHolder[currChar] = NULLCHAR;

    return textHolder;
}

bool check_home(board *board, game *game) // checking if all of the same color pawns are on their home board
{                                         // if yes, then they can move out of home board
    int Pawns = 0;
    if (game->turn == red)
    {
        for (int i = 0; i < 6; i++)
        {
            if (board->fields[i].player == red)
            {
                Pawns += board->fields[i].height;
            }
        }
        if (Pawns == 15)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (game->turn == white)
    {
        for (int i = 0; i < 6; i++)
        {
            if (board->fields[23 - i].player == white)
            {
                Pawns += board->fields[23 - i].height;
            }
        }
        if (Pawns == 15)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void move_home(board *b, int from, game *game) // moving pawns from home board
{
    if (check_home(b, game) == true)
    {
        if (b->fields[from - 1].player == white)
        {
            b->fields[from - 1].height -= 1;
            b->white_home += 1;
        }
        else if (b->fields[from - 1].player == red)
        {
            b->fields[from - 1].height -= 1;
            b->red_home += 1;
        }
    }
    else
    {
        return;
    }
}

void move_pawn(board *b, int from, int howfar, game *game) // moving pawns on the board
{
    if (from + howfar > 24 || from + howfar < 1)
    {
        move_home(b, from, game);
    }
    else
    {
        b->fields[from - 1].height -= 1;
        b->fields[from + howfar - 1].height += 1;
        if (b->fields[from - 1].player == white)
        {
            b->fields[from + howfar - 1].player = white;
        }
        else if (b->fields[from - 1].player == red)
        {
            b->fields[from + howfar - 1].player = red;
        }
    }
}

bool checkDublet(dice *dices) // checking if dices values are the same, if so returns true to dublet
{
    if (dices[0].value == dices[1].value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool check_move(board *b, int n, int moveFrom, game *g) // checking move possibility under all circumstances
{
    if (b->fields[moveFrom - 1].height == 0)
    {
        return false;
    }
    if (b->fields[moveFrom - 1].player != g->turn)
    {
        return false;
    }
    if (b->fields[moveFrom - 1].player == red)
    {
        n = -n;
    }
    int boardIndex = moveFrom + n - 1;
    if (b->fields[boardIndex].height == 0)
    {
        return true;
    }
    if (b->fields[boardIndex].player != b->fields[moveFrom - 1].player)
    {
        if (b->fields[boardIndex].height > 1)
        {
            return false;
        }

        b->fields[boardIndex].height = 0;

        if (b->fields[boardIndex].player == white)
        {
            b->white_bar += 1;
        }
        else if (b->fields[boardIndex].player == red)
        {
            b->red_bar += 1;
        }
        return true;
    }
    return true;
}

void RemoveWhiteBar(board *board, game *game, int d) //Removing white pawn from bar
{
    if (board->fields[d - 1].player != white)
    {
        if (board->fields[d - 1].height == 1)
        {
            board->fields[d - 1].player = white;
            board->red_bar += 1;
            board->white_bar -= 1;
        }
        else if (board->fields[d - 1].height > 1)
        {
            return;
        }
        else
        {
            board->fields[d - 1].player = white;
            board->white_bar -= 1;
            board->fields[d - 1].height += 1;
        }
    }
    else
    {
        board->fields[d - 1].height += 1;
        board->white_bar -= 1;
    }
}

void RemoveRedBar(board *board, game *game, int d)//Doing the same as above but for red pawns
{
    if (board->fields[24 - d].player != red)
    {
        if (board->fields[24 - d].height == 1)
        {
            board->fields[24 - d].player = red;
            board->white_bar += 1;
            board->red_bar -= 1;
        }
        else if (board->fields[24 - d].height > 1)
        {
            return;
        }
        else
        {
            board->fields[24 - d].player = red;
            board->red_bar -= 1;
            board->fields[24 - d].height += 1;
        }
    }
    else
    {
        board->fields[24 - d].height += 1;
        board->red_bar -= 1;
    }
}

void ChooseDiceForBar(dice dices[], board *board, board_info *gboard, game *game) // removing pawns from bar
{
    gotoxy(6, 2);
    cputs("Choose the dice to move the pawn from bar with:");

    int quantity;
    quantity = getch();
    if (quantity == 0x31)
    {
        if (game->turn == white && board->white_bar != 0)
        {
            RemoveWhiteBar(board, game, dices[0].value);
        }
        else if (game->turn == red && board->red_bar != 0)
        {
            RemoveRedBar(board, game, dices[0].value);
            ;
        }
    }
    else if (quantity == 0x32)
    {
        if (game->turn == white && board->white_bar != 0)
        {
            RemoveWhiteBar(board, game, dices[1].value);
        }
        else if (game->turn == red && board->red_bar != 0)
        {
            RemoveRedBar(board, game, dices[1].value);
        }
    }
    else
    {
        return;
    }
}

bool CheckingBar(board *board, game *game) // checking bar for the possibility of moving
{
    if (game->turn == white)
    {
        if (board->white_bar != 0)
        {
            return false;
        }
        else if (board->white_bar == 0)
        {
            return true;
        }
    }
    else
    {
        if (board->red_bar != 0)
        {
            return false;
        }
        else if (board->red_bar == 0)
        {
            return true;
        }
    }
}

void make_move(dice d[], board *b, board_info *gb, game *g, int howFar, int i, int m, bool dublet) // making move on the board
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(6, 2 + i);
    printf("Choose field to move %i pawn from:", i);
    char *txt = text(6, 3 + i);
    if (txt[0] == NULLCHAR)
    {
        return;
    }
    int moveFrom = atoi(txt);
    if (check_move(b, howFar, moveFrom, g))
    {
        if (b->fields[moveFrom - 1].player == red)
        {
            howFar = -howFar;
        }
        move_pawn(b, moveFrom, howFar, g);
    }
    else
    {
        return;
    }
}

void make_2_moves_r(dice d[], board *b, board_info *gb, game *g, bool dublet) // making 2 moves as 1 pawn for red
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(6, 3);
    printf("Choose field to move pawn from:");
    char *txt = text(6, 4);
    if (txt[0] == NULLCHAR)
    {
        return;
    }
    int m = atoi(txt);
    int d0 = d[0].value;
    int d1 = d[1].value;
    if (dublet)
    {
        d0 = 2 * d0;
        d1 = 2 * d1;
    }
    if (check_move(b, d0, m, g))
    {
        move_pawn(b, m, -d0, g);
        if (check_move(b, d1, m - d0, g))
        {
            move_pawn(b, m - d0, -d1, g);
        }
    }
    else if (check_move(b, d1, m, g))
    {
        move_pawn(b, m, -d1, g);
        if (check_move(b, d0, m - d1, g))
        {
            move_pawn(b, m - d1, -d0, g);
        }
    }
    else
    {
        return;
    }
}

void make_2_moves_w(dice d[], board *b, board_info *gb, game *g, bool dublet) // making 2 moves as 1 pawn for white
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(6, 3);
    printf("Choose field to move pawn from:");
    char *txt = text(6, 4);
    if (txt[0] == NULLCHAR)
    {
        return;
    }
    int m = atoi(txt);
    int d0 = d[0].value;
    int d1 = d[1].value;
    if (dublet)
    {
        d0 = 2 * d0;
        d1 = 2 * d1;
    }
    if (check_move(b, d0, m, g))
    {
        move_pawn(b, m, d0, g);
        if (check_move(b, d1, m + d0, g))
        {
            move_pawn(b, m + d0, d1, g);
        }
        else
        {
            return;
        }
    }
    else if (check_move(b, d1, m, g))
    {
        move_pawn(b, m, d1, g);
        if (check_move(b, d0, m + d1, g))
        {
            move_pawn(b, m + d1, d0, g);
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }
}

void make_turn2(dice d[], board *b, board_info *gb, game *g, bool dub, char c) // making turn for 3 pawns or 4 pawns
{
    if (c == 0x33 && dub == true)
    {
        for (int i = 1; i < 3; i++)
        {
            make_move(d, b, gb, g, d[0].value, i, 1, dub);
        }
        make_move(d, b, gb, g, 2 * d[0].value, 3, 1, dub);
    }
    else if (c == 0x34 && dub == true)
    {
        for (int i = 1; i < 5; i++)
        {
            make_move(d, b, gb, g, d[0].value, i, 1, dub);
        }
    }
    else
    {
        return;
    }
    put_pawns(b, gb);
}

void make_turn1(dice d[], board *b, board_info *gb, game *g, bool dub, char c) // making turn for 1 pawn or 2 pawns
{
    if (c == 0x31)
    {
        if (g->turn == white)
        {
            make_2_moves_w(d, b, gb, g, dub);
        }
        else
        {
            make_2_moves_r(d, b, gb, g, dub);
        }
    }
    else if (c == 0x32)
    {
        if (dub)
        {
            for (int i = 1; i < 3; i++)
            {
                make_move(d, b, gb, g, 2 * d[0].value, i, 1, dub);
            }
        }
        else
        {
            make_move(d, b, gb, g, d[0].value, 1, 1, dub);
            make_move(d, b, gb, g, d[1].value, 2, 1, dub);
        }
    }
    else
    {
        return;
    }
    put_pawns(b, gb);
}

void choose_quantity(dice dices[], board *board, board_info *gboard, game *game, bool dublet) // scanning input from user to
{                                                                                             // acknowledge how many pawns to move
    textbackground(BLACK);
    textcolor(WHITE);

    gotoxy(6, 2);
    cputs("Choose the quantity of pawns to move:");

    char quantity;
    quantity = getch();
    if (quantity == 0x31 || quantity == 0x32)
    {
        make_turn1(dices, board, gboard, game, dublet, quantity);
    }
    else if (quantity == 0x33 || quantity == 0x34)
    {
        make_turn2(dices, board, gboard, game, dublet, quantity);
    }
    else
    {
        return;
    }
}

void in_game(board_info *gboard, dice dices[], game *game) // initalize starting informations of the game
{
    print_fields_numbers(gboard);
    print_board(gboard);
    print_dices(dices, 2);
}

void save_game(board *board, game *game, dice *dices) // saving game to file
{
    FILE *f;
    f = fopen("save.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        fprintf(f, "%d\n", board->fields[i].player);
        fprintf(f, "%d\n", board->fields[i].height);
    }
    for (int i = 0; i < 2; i++)
    {
        fprintf(f, "%d\n", dices[i].value);
    }
    fprintf(f, "%d\n", board->white_bar);
    fprintf(f, "%d\n", board->red_bar);
    fprintf(f, "%d\n", board->white_home);
    fprintf(f, "%d\n", board->red_home);
    fprintf(f, "%d\n", game->turn);
    fclose(f);
}

void new_game(board *board, dice *dices, game *game) // starting new game
{
    init_pawns(*board);
    game->turn = who_starts();
    roll(dices);
}

void load_game(board *board, dice *dices, game *game) // loading game from saved file
{
    FILE *f;
    f = fopen("save.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        fscanf(f, "%d", &board->fields[i].player);
        fscanf(f, "%d", &board->fields[i].height);
    }
    for (int i = 0; i < 2; i++)
    {
        fscanf(f, "%d", &dices[i].value);
    }
    fscanf(f, "%d", &board->white_bar);
    fscanf(f, "%d", &board->red_bar);
    fscanf(f, "%d", &board->white_home);
    fscanf(f, "%d", &board->red_home);
    fscanf(f, "%d", &game->turn);
    fclose(f);
}

void init_game(board *board, board_info *gboard, game *game, dice dices[]) // initializing basic game informations like ui, pawns etc.
{
    init_pawns(*board);
    init_bars(board);
    roll(dices);
    game->turn = who_starts();
    BarAndHome(board);
    UserInterface(game);
}

void play_game(char zn, dice dices[], board *board, board_info *gboard, game *game, bool dublet, bool ingame) // analizing input from user
{
    if (zn == 's')
    {
        save_game(board, game, dices);
    }
    else if (zn == 'l')
    {
        ingame = true;
        load_game(board, dices, game);
    }
    if (zn == 'm')
    {
        dublet = checkDublet(dices);
        game->turn = tura(game);
        if (game->turn == white && board->white_bar != 0)
        {
            ChooseDiceForBar(dices, board, gboard, game);
        }
        else if (game->turn == red && board->red_bar != 0)
        {
            ChooseDiceForBar(dices, board, gboard, game);
        }
        else
        {
            choose_quantity(dices, board, gboard, game, dublet);
        }
        roll(dices);
    }
    else
    {
        return;
    }
}

void CheckForWinner(board *board)
{
    if (board->white_home == 15)
    {
        clrscr();
        gotoxy(10, 10);
        cputs("White Won!");
    }
    else if (board->red_home == 15)
    {
        clrscr();
        gotoxy(10, 10);
        cputs("Red Won!");
    }
    else
    {
        return;
    }
}
