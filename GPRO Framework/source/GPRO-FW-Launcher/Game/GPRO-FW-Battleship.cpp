
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

//variables
bool error = false;
string border;
struct Ships {

};

//function declarations
void drawBoard(gs_battleship game, gs_battleship_index player);
void setUpBoard(gs_battleship game);

void takeTurn(gs_battleship game, int player);
bool win(gs_battleship game, gs_battleship_index player);

void placeShip(gs_battleship game, gs_battleship_index player, gs_battleship_space_state shipType, int direction, int x, int y);
string getShipName(gs_battleship_space_state shipType);
int getShipUnits(gs_battleship_space_state shipType);

char displaySpaceState(gs_battleship_space_state state);
char displayOppState(gs_battleship_space_state state);
void getCoordinates(int& x, int& y);
void cont();
void displayTitle();
//int letterToNumber(char letter);

int launchBattleship()
{
	gs_battleship game;// = { 0 };
	int player = 0;
	border.assign((GS_BATTLESHIP_BOARD_WIDTH * 2) + 1, '-');

	gs_battleship_reset(game);

	setUpBoard(game);
	do {
		drawBoard(game, player);
		do {
			takeTurn(game, player);
		} while (error);
		player = !player;
	} while (!win(game, player));
	system("CLS");
	cout << "Player " << !player + 1 << " wins!\nCongratulations!";

	return 0;
}

/*------------------------------SET UP FUNCTIONS------------------------------*/
void drawBoard(gs_battleship game, gs_battleship_index player)
{
	cout << "BATTLESHIP\n"
		<< "Player " << player + 1 << " turn\n\n";

	cout << "Opponent Board:\n";
	for (int i = 1; i <= GS_BATTLESHIP_BOARD_WIDTH; i++) {
		cout << " " << i;
	}
	cout << endl << border << endl;
	for (int y = 0; y < GS_BATTLESHIP_BOARD_HEIGHT; y++) {
		for (int x = 0; x < GS_BATTLESHIP_BOARD_WIDTH; x++) {
			cout << "|" << displayOppState(game[!player][x][y]);
		}
		cout << "| " << y + 1 << endl;
	}
	cout << border << endl << endl;

	cout << "Your Board:\n";
	for (int i = 1; i <= GS_BATTLESHIP_BOARD_WIDTH; i++) {
		cout << " " << i;
	}
	cout << endl << border << endl;
	for (int y = 0; y < GS_BATTLESHIP_BOARD_HEIGHT; y++) {
		for (int x = 0; x < GS_BATTLESHIP_BOARD_WIDTH; x++) {
			cout << "|" << displaySpaceState(game[player][x][y]);
		}
		cout << "| " << y + 1 << endl;
	}
	cout << border << endl << endl;
}

void setUpBoard(gs_battleship game) 
{
	gs_battleship_index player = 0, xpos = 0, ypos = 0;
	gs_battleship_space_state shipType;

	cout << "Welcome to\n";
	//displayTitle();

	for (player = 0; player < GS_BATTLESHIP_PLAYERS; ++player) {
		drawBoard(game, player);
		cout << "Player " << player + 1 << " set up your ships\n\n";
		for (shipType = gs_battleship_space_patrol2; shipType <= gs_battleship_space_carrier5;) {
			int direction, x = 0, y = 0;
			//ask for ship placement until it is valid
			do {
				cout << "What direction do you want your " << getShipName(shipType) << " to be placed?\n";
				cout << "Press 1 for vertical or 2 for horizontal: ";
				cin >> direction;

				//if time: make it so that its letters and numbers
				cout << "Where do you want your " << getShipName(shipType) << " placed?" << endl;
				//getCoordinates(x, y);
				x = shipType-2;
				y = shipType-2;

				placeShip(game, player, shipType, direction, x, y);
			} while (error);

			drawBoard(game, player);
			shipType = gs_battleship_space_state(shipType + 1);
		}
		cont();
	}
}

/*------------------------------GAMEPLAY FUNCTIONS------------------------------*/
void takeTurn(gs_battleship game, int player) {
	int x, y;
	gs_battleship_space_state state;

	cout << "Player " << player + 1 << " guess a position\n";
	getCoordinates(x, y);
	state = gs_battleship_getSpaceState(game, !player, x, y);
	error = false;

	if (state == gs_battleship_space_open) {
		system("CLS");
		gs_battleship_setSpaceState(game, gs_battleship_space_miss, !player, x, y);
		drawBoard(game, player);
		cout << "Missed!\n";
	}
	else if (state > 2) {//if ship is hit
		system("CLS");
		gs_battleship_setSpaceState(game, gs_battleship_space_hit, !player, x, y);
		drawBoard(game, player);
		cout << "Hit!\n";
	}
	else if (state == gs_battleship_space_invalid) {
		cout << "Invalid Coordinate\n\n";
		error = true;
		return;
	}
	else {//if space already guessed
		cout << "You already guessed that, try again\n\n";
		error = true;
		return;
	}
	cont();
}

bool win(gs_battleship game, gs_battleship_index player) {
	for (int x = 0; x < GS_BATTLESHIP_BOARD_WIDTH; ++x) {
		for (int y = 0; y < GS_BATTLESHIP_BOARD_HEIGHT; ++y) {
			if (gs_battleship_getSpaceState(game, player, x, y) > 2) {
				return false;
			}
		}
	}
	return true;
}

/*------------------------------SHIP FUNCTIONS------------------------------*/
void placeShip(gs_battleship game, gs_battleship_index player, gs_battleship_space_state shipType, int direction, int x, int y)
{
	gs_battleship_index xpos = x, ypos = y;
	gs_battleship_space_state state;

	//make ship vertical
	if (direction == 1) {
		//Check to see if all spaces are ok
		for (int i = 0; i < getShipUnits(shipType); i++) {
			state = gs_battleship_getSpaceState(game, player, xpos, ypos + i);
			//if not, return error
			if (state != gs_battleship_space_open) {
				cout << "Invalid Placement\n\n";
				error = true;
				return;
			}
		}

		error = false;
		for (int i = 0; i < getShipUnits(shipType); i++) {
			gs_battleship_setSpaceState(game, shipType, player, xpos, ypos + i);
		}
	}
	//make ship horizontal
	else if (direction == 2) {

		//Check to see if all spaces are ok
		for (int i = 0; i < getShipUnits(shipType); i++) {
			state = gs_battleship_getSpaceState(game, player, xpos + i, ypos);
			//if not, return error
			if (state != gs_battleship_space_open) {
				cout << "Invalid Placement\n\n";
				error = true;
				return;
			}
		}

		error = false;
		for (int i = 0; i < getShipUnits(shipType); i++) {
			gs_battleship_setSpaceState(game, shipType, player, xpos + i, ypos);
		}
	}
	else {
		cout << "Invalid Placement\n\n";
		error = true;
		return;
	}
	cout << "Ship Placed\n\n";
}

string getShipName(gs_battleship_space_state shipType) {
	switch (shipType) {
	case gs_battleship_space_patrol2:
		return "Patrol Boat";
		break;
	case gs_battleship_space_submarine3:
		return "Submarine";
		break;
	case gs_battleship_space_destroyer3:
		return "Destroyer";
		break;
	case gs_battleship_space_battleship4:
		return "Battleship";
		break;
	case gs_battleship_space_carrier5:
		return "Carrier";
		break;
	default:
		return "";
		break;
	}
}
int getShipUnits(gs_battleship_space_state shipType) {
	switch (shipType) {
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
		return 'O';
		break;
	case gs_battleship_space_hit:
		return 'X';
		break;
	case gs_battleship_space_patrol2:
		return 'P';
		break;
	case gs_battleship_space_submarine3:
		return 'S';
		break;
	case gs_battleship_space_destroyer3:
		return 'D';
		break;
	case gs_battleship_space_battleship4:
		return 'B';
		break;
	case gs_battleship_space_carrier5:
		return 'C';
		break;
	default:
		return '_';
		break;
	}
}
char displayOppState(gs_battleship_space_state state) {
	switch (state)
	{
	case gs_battleship_space_miss:
		return 'O';
		break;
	case gs_battleship_space_hit:
		return 'X';
		break;
	default:
		return '_';
		break;
	}
}

void getCoordinates(int& x, int& y) {
	cout << "x: ";
	cin >> x;
	--x;
	cout << "y: ";
	cin >> y;
	--y;
}

void cont() {
	cout << "Other Player's Turn\n";
	system("pause");
	system("CLS");
}

void displayTitle() {
	cout << "______  ___ _____ _____ _      _____ _____ _   _ ___________" << endl
		<< "| ___ \/ _ \_   _|_   _| |    |  ___/  ___| | | |_   _| ___ \ " << endl
		<< "| |_/ / /_\ \| |   | | | |    | |__ \ `--.| |_| | | | | |_/ /" << endl
		<< "| ___ \  _  || |   | | | |    |  __| `--. \  _  | | | |  __/ " << endl
		<< "| |_/ / | | || |   | | | |____| |___/\__/ / | | |_| |_| |    " << endl
		<< "\____/\_| |_/\_/   \_/ \_____/\____/\____/\_| |_/\___/\_|    " << endl;
}

//-----------------------------------------------------------------------------
