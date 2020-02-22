// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "foo.h"
#include "Number-Guesser.h"

using namespace std;

int main()
{
	/*int test = foo(1);
	cout << test;*/

	srand(time(NULL));

	do {
		startGame();

		while (!checkAnswer()) {
			cin >> guess;
		}
	} while (checkContinue());
}
