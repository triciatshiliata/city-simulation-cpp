#pragma once
#include "gameBoard.h"
#include "Cell.h"
#include <iostream>

class Cell;
class gameBoard;

/**
 * @file Commercial.h
 *
 * Header file for the Commercial class, which represents commercial zones on the game board.
 */

class Commercial {
public:
    //constructor
    Commercial(gameBoard& board);

    //function to simulate growth
    void growCommercial(gameBoard& board);

    //functions dealing with powerline and population adjacency
    bool isAdjacentToPowerline(const gameBoard& board, int x, int y);
    bool isAdjacentToPopulation(const gameBoard& board, int x, int y, int minPopulation, int requiredNeighbors);

private:
    //vector to store workers for each cell
    //std::vector<std::vector<std::vector<Worker>>> workers;

};
