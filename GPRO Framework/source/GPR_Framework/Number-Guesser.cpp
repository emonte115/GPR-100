#include "Number-Guesser.h"

using namespace std;

void startGame() {
	randNum = rand() % 10 + 1;

	cout << "Please enter a number 1-10: ";
	cin >> guess;
	cout << endl;
}

bool checkAnswer() {
	if (guess == randNum)
		return true;
	else if (guess > randNum && guess <= 10) 
		cout << "Too high, guess again\n";
	else if (guess < randNum && guess >= 1) 
		cout << "Too low, guess again\n";
	else
		cout << "Please enter a valid number\n";

	return false;
}

bool checkContinue() {
	return false;
}