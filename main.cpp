#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "conio2.h"
#include "conio2.cpp"
#include "backgammon.h"
#include "backgammon.cpp"
#include <time.h>

int main()
{
	int zn = 0;
#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Franciszek, Okrucinski, 193413");
	board_info gb;
	game game;
	dice dices[DICE_NUMBER];
	board b;
	start();								  // start screen
	init_game(&b, &gb, &game, dices); // initializing structures
	_setcursortype(_NOCURSOR);
	do
	{
		textbackground(BLACK);
		clrscr();
		textcolor(7);
		put_pawns(&b, &gb);
		CheckForWinner(&b);
		BarAndHome(&b);
		UserInterface(&game);
		in_game(&gb, dices, &game);
		zn = getch();
		play_game(zn, dices, &b, &gb, &game, dublet, ingame);
		if (zn == 'n')
		{
			ingame = true;
			init_bars(&b);
			new_game(&b, dices, &game);
		}
	} while (zn != 'q'); // play game until q is pressed
	return 0;
}