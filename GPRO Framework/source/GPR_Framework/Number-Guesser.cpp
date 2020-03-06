#include "Number-Guesser.h"

using namespace std;

void startGame(int& randNum, int& guess) {
	randNum = rand() % 10 + 1;

	cout << "Please enter a number 1-10: ";
	cin >> guess;
	cout << endl;
}

bool checkAnswer(int &randNum, int &guess) {
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
	char answer;

	do {
		cin >> answer;
		answer = toupper(answer);

		if (answer == 'Y') {
			cout << endl;
			return true;
		}
		else if (answer == 'N') {
			return false;
		}
		else {
			cout << "Please enter Y or N: ";
		}
	} while (!(answer == 'Y' || answer == 'N'));

	return false;
}