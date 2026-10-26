#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Cell.h"
#include "Residential.h"

class gameBoard
{
private:
    int workerCount; // Total worker count
    int goodsCount;
	std::vector<std::vector<Cell>> layout;

public:
	gameBoard(std::ifstream& file);

	int getWorkerCount() const; //getter for worker count
    void incrementWorkerCount(); //increment worker count
    void decrementWorkerCount(); //decrement worker count

    int getGoodsCount() const; //getter for goods count
    void incrementGoods(); //increment goods count
    void decrementGoodsCount(); //decrement goods count

    void pollutionGrowth();
    void outputPollutionMap();

	void output();

	//grab board layout
	const std::vector<std::vector<Cell>>& getLayout() const;
	void setLayout(const std::vector<std::vector<Cell>>& newLayout);    //for when the layout changes

	//get board information
    int getHeight() const;
    int getWidth() const;
    char getCellType(int x, int y) const;
    int getCellPopulation(int x, int y) const;
    int getCellPollution(int x, int y);

    //moving adjacency functions to cell
    const Cell& getCell(int x, int y) const;
      int calculateTotalAdjacentPopulation(int x, int y);

    //unit testing function dec
    void setLayoutCellPopulation(int x, int y, int population);
    int CalculateTotalPollution();

    void setWorkerCount(int w);
    void setGoodsCount(int g);
};

#endif // GAMEBOARD_H
