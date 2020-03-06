#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>

void startGame(int &randNum, int &guess);
bool checkAnswer(int &randNum, int &guess);
bool checkContinue();