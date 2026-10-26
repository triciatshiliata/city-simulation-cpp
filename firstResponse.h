#pragma once

#include <iostream>
#include "Cell.h"
#include "gameBoard.h"

using namespace std;



class firstResponse
{
	int interval;
	vector<std::pair<int, int>> populatedList;


public:


	firstResponse(gameBoard& board);

	vector<std::pair<int, int>> getPopulatedList(gameBoard& board);

	void checkCoverage(gameBoard& board);

	
	void printCoverage(gameBoard& board);
	
};

