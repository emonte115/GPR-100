// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "foo.h"
#include "Number-Guesser.h"

using namespace std;

int randNum;
int guess;

int main()
{
	/*int test = foo(1);
	cout << test;*/

	srand(time(NULL));

	do {
		startGame(randNum, guess);

		while (!checkAnswer(randNum, guess)) {
			cin >> guess;
		}

		cout << endl << "You Win!\n\n" << "Do you want to play again? (Y/N): ";

	} while (checkContinue());

	cout << endl << "Good bye!\n";
}
