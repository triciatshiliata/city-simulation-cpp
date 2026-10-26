#ifndef SEASON_H
#define SEASON_H
#include<iostream>
#include<string>
#include"gameBoard.h"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_ORANGE "\033[33m"
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_GRAY "\033[37m"
#define ANSI_COLOR_RESET "\033[0m"

class Season{
	private:
		int newGoodsCount;
		int newWorkerCount;
		std::string seasons;
		int addedGoods;
		int addedWorkers;


	
	public:
		Season();
		void seasonChange(gameBoard& current, int currentTimeStep);
		void setSeason(int currentTimeStep);
		std::string getSeason()const;
		void printSeasonImpact(gameBoard& current);

		
};
#endif
