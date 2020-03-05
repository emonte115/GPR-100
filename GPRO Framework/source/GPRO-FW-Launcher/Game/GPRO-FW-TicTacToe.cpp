
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;


//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_TICTACTOE_PLAYERS					2
#define GS_TICTACTOE_BOARD_WIDTH				3
#define GS_TICTACTOE_BOARD_HEIGHT				3

enum gs_tictactoe_space_state
{
	// invalid space state
	gs_tictactoe_space_invalid = -1,

	// states visible to both players
	gs_tictactoe_space_open,	// space is open
	gs_tictactoe_space_o,		// space is taken by O player
	gs_tictactoe_space_x,		// space is taken by X player
};
#ifndef __cplusplus
typedef		enum gs_tictactoe_space_state		gs_tictactoe_space_state;
#endif	// !__cplusplus

// tic-tac-toe game state
typedef		unsigned char						gs_tictactoe_index;
typedef		gs_tictactoe_space_state			gs_tictactoe[GS_TICTACTOE_BOARD_WIDTH][GS_TICTACTOE_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,w,h)			(x < w && y < h)
#define GS_TICTACTOE_VALID(x,y)					GS_VALIDATE_COORDINATE(x,y,GS_TICTACTOE_BOARD_WIDTH,GS_TICTACTOE_BOARD_HEIGHT)


inline gs_tictactoe_space_state gs_tictactoe_getSpaceState(gs_tictactoe const game, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos]);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_space_state gs_tictactoe_setSpaceState(gs_tictactoe game, gs_tictactoe_space_state const state, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos] = state);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_index gs_tictactoe_reset(gs_tictactoe game)
{
	gs_tictactoe_index xpos, ypos, total;
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
			game[xpos][ypos] = gs_tictactoe_space_open;
	total = (xpos * ypos);
	return total;
}


//-----------------------------------------------------------------------------
// DEFINITIONS

//variables
const string BORDER = "-+-+-";

//function declarations
void drawBoard(gs_tictactoe game, int player);
void takeTurn(gs_tictactoe game, int player);
bool win(gs_tictactoe game);
char displaySpaceState(gs_tictactoe_space_state state);

int launchTicTacToe()
{
	gs_tictactoe game;// = { 0 };
	int player = 0;

	gs_tictactoe_reset(game);
	system("CLS");
	drawBoard(game, player);

	for (int i = (GS_TICTACTOE_BOARD_WIDTH * GS_TICTACTOE_BOARD_HEIGHT); i > 0; i--) {
		takeTurn(game, player + 1);
		player = !player;
		if (win(game))
			break;
	}
	if (!win(game)) {
		cout << "It's a tie!\n";
	}

	system("pause");
	system("CLS");

	return 0;
}

void drawBoard(gs_tictactoe game, int player) {
	gs_tictactoe_index xpos, ypos;

	cout << "TIC-TAC-TOE\n" 
		<< "Player " << player << " turn\n\n";
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos) {
		if (xpos != 0)
			cout << BORDER << endl;
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos) {
			//don't print line at the front
			if (ypos != 0)
				cout << "|";
			cout << displaySpaceState(game[xpos][ypos]);
		}
		cout << endl;
	}
	cout << endl;
}

void takeTurn(gs_tictactoe game, int player) {
	int xpos, ypos;
	gs_tictactoe_space_state state;

	do {
		cout << "Where do you want to place your " << displaySpaceState(gs_tictactoe_space_state(player)) << "?\n";
		cout << "Row: ";
		cin >> xpos;
		xpos--;
		cout << "Column: ";
		cin >> ypos;
		ypos--;
		state = gs_tictactoe_getSpaceState(game, xpos, ypos);

		if (state > 0) {
			cout << "Space already taken\n\n";
			continue;
		}
		state = gs_tictactoe_setSpaceState(game, gs_tictactoe_space_state(player), xpos, ypos);
		if (state < 0) {
			cout << "Invalid Space\n\n";
			continue;
		}

		break;
	} while (1);

	system("CLS");
	drawBoard(game, player);
}

bool win(gs_tictactoe game) {
	gs_tictactoe_index xpos, ypos;
	gs_tictactoe_space_state state;

	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos) {
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos) {
			state = gs_tictactoe_getSpaceState(game, xpos, ypos);

			if (state > 0) { //if there is an x or an o in the first spot
				if (state == gs_tictactoe_getSpaceState(game, xpos + 1, ypos)) {//if there is a second horizontally
					if (state == gs_tictactoe_getSpaceState(game, xpos + 2, ypos)) {//if there is a third horizontally
						system("CLS");
						drawBoard(game, state);
						cout << endl << displaySpaceState(state) << "'s win!\n";
						return true;
					}
					else
						break;
				}
				else if (state == gs_tictactoe_getSpaceState(game, xpos, ypos + 1)) {//if there is a second vertically
					if (state == gs_tictactoe_getSpaceState(game, xpos, ypos + 2)) {//if there is a third vertically
						system("CLS");
						drawBoard(game, state);
						cout << endl << displaySpaceState(state) << "'s win!\n";
						return true;
					}
					else
						break;
				}
				else if (state == gs_tictactoe_getSpaceState(game, xpos + 1, ypos + 1)) {//if there is a second diagonally
					if (state == gs_tictactoe_getSpaceState(game, xpos + 2, ypos + 2)) {//if there is a third diagonally
						system("CLS");
						drawBoard(game, state);
						cout << endl << displaySpaceState(state) << "'s win!\n";
						return true;
					}
					else
						break;
				}
				else
					break;
			}
		}
	}
	return false;
}


char displaySpaceState(gs_tictactoe_space_state state) {
	switch (state)
	{
	case gs_tictactoe_space_o:
		return 'O';
		break;
	case gs_tictactoe_space_x:
		return 'X';
		break;
	default:
		return ' ';
		break;
	}
}
//-----------------------------------------------------------------------------
