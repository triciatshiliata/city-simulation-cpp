#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H
#include <iostream>

#include "gameBoard.h"
#include "Cell.h"

//needed forward class decs
class gameBoard;
class Cell;


class Residential {

public:
    private:
    //std::vector<std::vector<std::vector<Worker>>> workers;  //vector of workers
    public:
    Residential(gameBoard& board); //default constructor, for workers
    //function dealing with residential growth
    void growResidential(gameBoard& board);
    //functions dealing with powerline and population adjacency, main function in cell.cpp
    bool isAdjacentToPowerline(const gameBoard& board, int x, int y);
    bool isAdjacentToPopulation(const gameBoard& board, int x, int y, int minPopulation, int requiredNeighbors);
    //worker functions
    void assignWorkers(gameBoard& board, int x, int y, int numWorkers);
};

#endif
