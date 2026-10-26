#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H
#include"gameBoard.h"

/**
 * @file Industrial.h
 *
 * Header file for the Industrial class, which represents industrial zones on the game board.
 */

class Industrial{
	private:
		int availableWorkers;
		int workerAvailable;
	public:
		//constructor 
		Industrial(gameBoard& board);
		
		//function to simulate growth
		void IndustrialGrowth(gameBoard& board);
		
		//adjacent to powerline and adjacent to population function
		bool isAdjacentToPowerline(const gameBoard& board, int x, int y);
		bool isAdjacentToPopulation(const gameBoard& board, int x, int y,int minPopulation, int requiredNeighbors);
		
		void assignWorkers(gameBoard& board, int x, int y, int numWorkers);
		//gets # of available workers
		int getAvailableWorkers()const;
		//sets # of new available workers
		int setWorkerAvailability(bool availability);

        void setAvailableWorkers(int workers);  // Added setAvailableWorkers function
};
#endif
