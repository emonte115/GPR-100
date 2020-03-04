// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
using namespace std;

int launchTicTacToe();
int launchBattleship();

int main()
{
	int choice;
	do {
		cout << "1. Tic-Tac-Toe\n"
			<< "2. BattleShip\n"
			<< "3. Exit\n"
			<< "\tEnter Choice: ";
		cin >> choice;

		if (choice == 1) {
			launchTicTacToe();
		}
		else if (choice == 2) {
			launchBattleship();
		}
		else if (choice == 3) {
			break;
		}
		else {
			cout << "Please enter a valid number\n\n";
		}
	} while (1);
}
