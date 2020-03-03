
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;


//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_BATTLESHIP_PLAYERS				2
#define GS_BATTLESHIP_BOARD_WIDTH			10
#define GS_BATTLESHIP_BOARD_HEIGHT			10

enum gs_battleship_space_state
{
	// invalid space state
	gs_battleship_space_invalid = -1,

	// states visible to both players
	gs_battleship_space_open,			// space is open and unguessed
	gs_battleship_space_miss,			// space was guessed and missed
	gs_battleship_space_hit,			// space was guessed and hit

	// states hidden from opponent player
	gs_battleship_space_patrol2,		// 2-unit patrol boat
	gs_battleship_space_submarine3,		// 3-unit submarine
	gs_battleship_space_destroyer3,		// 3-unit destroyer
	gs_battleship_space_battleship4,	// 4-unit battleship
	gs_battleship_space_carrier5,		// 5-unit carrier
};
#ifndef __cplusplus
typedef		enum gs_battleship_space_state	gs_battleship_space_state;
#endif	// !__cplusplus

// battleship game state
typedef		unsigned char					gs_battleship_index;
typedef		gs_battleship_space_state		gs_battleship[GS_BATTLESHIP_PLAYERS][GS_BATTLESHIP_BOARD_WIDTH][GS_BATTLESHIP_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,z,w,h,d)		(x < w && y < h && z < d)
#define GS_BATTLESHIP_VALID(p,x,y)				GS_VALIDATE_COORDINATE(x,y,p,GS_BATTLESHIP_BOARD_WIDTH,GS_BATTLESHIP_BOARD_HEIGHT,GS_BATTLESHIP_PLAYERS)


inline gs_battleship_space_state gs_battleship_getSpaceState(gs_battleship const game, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos]);
	return gs_battleship_space_invalid;
}

inline gs_battleship_space_state gs_battleship_setSpaceState(gs_battleship game, gs_battleship_space_state const state, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos] = state);
	return gs_battleship_space_invalid;
}

inline gs_battleship_index gs_battleship_reset(gs_battleship game)
{
	gs_battleship_index player, xpos, ypos, total;
	for (player = 0; player < GS_BATTLESHIP_PLAYERS; ++player)
		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
			for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
				game[player][xpos][ypos] = gs_battleship_space_open;
	total = (player * xpos * ypos);
	return total;
}


//-----------------------------------------------------------------------------
// DEFINITIONS

bool error;
string border;

void drawBoard(gs_battleship game, gs_battleship_index player);
void setUpBoard(gs_battleship game);
void placeShip(gs_battleship game, gs_battleship_index player, int shipType, int direction, int x, int y);
string getShipName();
int getShipUnits(gs_battleship_space_state ship);
char displaySpaceState(gs_battleship_space_state state);

int launchBattleship()
{
	gs_battleship game;// = { 0 };

	border.assign((GS_BATTLESHIP_BOARD_WIDTH * 2) + 1, '-');
	drawBoard(game, 0);
	gs_battleship_setSpaceState(game, gs_battleship_space_miss, 0, 2, 2);
	drawBoard(game, 0);
	drawBoard(game, 1);
	//setUpBoard(game);

	gs_battleship_reset(game);



	return 0;
}

/*------------------------------SET UP FUNCTIONS------------------------------*/
void drawBoard(gs_battleship game, gs_battleship_index player)
{
	cout << "BATTLESHIP\n"
		<< "Player " << player + 1 << " turn\n\n"
		<< border << endl;
	for (int y = 0; y < GS_BATTLESHIP_BOARD_HEIGHT; y++) {
		for (int x = 0; x < GS_BATTLESHIP_BOARD_WIDTH; x++) {
			cout << "|" << displaySpaceState(game[player][x][y]);
		}
		cout << "|" << endl;
	}
	cout << border << endl << endl;
}

void setUpBoard(gs_battleship game) 
{
	gs_battleship_index player, xpos = 0, ypos = 0;
	int shipType;

	for (player = 0; player < GS_BATTLESHIP_PLAYERS; ++player) {
		cout << "Player " << player + 1 << " set up your ships";
		for (shipType = 3; shipType < 8; ++shipType) {
			int direction, x, y;

			cout << "What direction do you want your " << shipType << " to be placed?\n";
			cout << "Press 1 for vertical or 2 for horizontal: ";
			cin >> direction;
			
			cout << "Where do you want your ship placed?" << endl << "x: ";
			cin >> x;
			cout << "y: ";
			cin >> y;

			placeShip(game, player, shipType, direction, x, y);
		}
	}
}

/*------------------------------SHIP FUNCTIONS------------------------------*/
void placeShip(gs_battleship game, gs_battleship_index player, int shipType, int direction, int x, int y)
{
	gs_battleship_index xpos = 0, ypos = 0;
	gs_battleship_space_state ship = gs_battleship_space_state(shipType);

	//make ship vertical
	if (direction == 1) {
		for (int i = 0; i < getShipUnits(ship); i++) {
			ypos = y + i;
			gs_battleship_setSpaceState(game, ship, player, xpos, ypos);
		}
	}
	//make ship horizontal
	else if (direction == 2) {
		for (int i = 0; i < getShipUnits(ship); i++) {
			xpos = x + i;
			gs_battleship_setSpaceState(game, ship, player, xpos, ypos);
		}
	}

}

string getShipName() {
	return "";
}
int getShipUnits(gs_battleship_space_state ship) {
	switch (ship) {
	case gs_battleship_space_patrol2:
		return 2;
		break;
	case gs_battleship_space_submarine3:
		return 3;
		break;
	case gs_battleship_space_destroyer3:
		return 3;
		break;
	case gs_battleship_space_battleship4:
		return 4;
		break;
	case gs_battleship_space_carrier5:
		return 5;
		break;
	default:
		return 0;
		break;
	}
}

/*------------------------------OTHER FUNCTIONS------------------------------*/
char displaySpaceState(gs_battleship_space_state state) {
	switch (state) 
	{
	case gs_battleship_space_miss:
		return 'X';
		break;
	case gs_battleship_space_hit:
		return 'O';
		break;
	default:
		return '_';
		break;
	}
}

//-----------------------------------------------------------------------------
