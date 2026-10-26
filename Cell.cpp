#include <iostream>
#include "Cell.h"

/**
 * @file Cell.cpp
 *
 * Implementation file for the Cell class, representing a cell in the gameboard. Holds attributes such as char type, population #, pollution #, etc.
 */


 /**
 * @brief Default constructor for the Cell class.
 *
 * Initializes the Cell with default values indicating improper construction.
 */
//default constructor
Cell::Cell() {
    //blanks and -1's to indicate constructor not called properly, if that is even possible
    type = ' ';
    population = -1;
    workers = -1;
    workerAvailable = false;
    goods = -1;
    pollution = -1;
}

/**
 * @brief Parameterized constructor for the Cell class.
 *
 * @param t The type of the cell (character).
 *
 * Initializes the Cell with the specified type and default values.
 */
Cell::Cell(char t) {
    type = t;   //set the character
    //everything is initially blank
    population = 0;
    workers = 0;
    workerAvailable = true;
    goods = 0;
    pollution = 0;
}

/**
 * @brief Getter function for the type of the cell.
 *
 * @return The type of the cell.
 */
//GETS
char Cell::getType() const {
    return type;
}
char Cell::setType(char t){
    this->type = t;
    return t;
}

/**
 * @brief Getter function for the population of the cell.
 *
 * @return The population of the cell.
 */
int Cell::getPopulation() const {
    return population;
}

/**
 * @brief Getter function for the number of workers in the cell.
 *
 * @return The number of workers in the cell.
 */
int Cell::getWorkers() const {
    return workers;
}

//SETS
/**
 * @brief Setter function for the population of the cell.
 *
 * @param population The new population value.
 */
void Cell::setPopulation(int population) {
    this->population = population;
}


/**
 * @brief Checks if the cell is adjacent to a powerline on the game board. Created with the intention to be used across all zone files.
 *
 * @param board The gameboard.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @return True if adjacent to a powerline, false otherwise.
 */
bool Cell::isAdjacentToPowerline(const gameBoard& board, int x, int y) const {
    if (y > 0 && board.getCellType(x, y - 1) == 'T') {
        return true;
    }

    //right of the cell
    if (y < board.getWidth() - 1 && board.getCellType(x, y + 1) == 'T') {
        return true;
    }

    //above the cell
    if (x > 0 && board.getCellType(x - 1, y) == 'T') {
        return true;
    }

    //below the cell
    if (x < board.getHeight() - 1 && board.getCellType(x + 1, y) == 'T') {
        return true;
    }

    //diagonals!
    //upper left
    if (x > 0 && y > 0 && board.getCellType(x - 1, y - 1) == 'T') {
        return true;
    }

    //upper right
    if (x > 0 && y < board.getWidth() - 1 && board.getCellType(x - 1, y + 1) == 'T') {
        return true;
    }

    //lower left
    if (x < board.getHeight() - 1 && y > 0 && board.getCellType(x + 1, y - 1) == 'T') {
        return true;
    }

    //lower right
    if (x < board.getHeight() - 1 && y < board.getWidth() - 1 && board.getCellType(x + 1, y + 1) == 'T') {
        return true;
    }

    return false;
}

/**
 * @brief Checks if the cell is adjacent to a cell on the gameboard, based on population of the adjacent cell and how many there are.
 *
 * @param board The game board.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @param minPopulation The minimum population required of the neighboring cell.
 * @param requiredNeighbors The required number of neighboring cells.
 * @return True if adjacent to the required number of populated cells, false otherwise.
 */
bool Cell::isAdjacentToPopulation(const gameBoard& board, int x, int y, int minPopulation, int requiredNeighbors) const {
    int populatedNeighbors = 0;

    //checking all the neighboring cells
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            //DONT check the cell itself
            if (i == 0 && j == 0)
                continue;

            //coordinates of the neighboring cell
            int newX = x + i;
            int newY = y + j;

            //is the neighboring cell within the bounds of the board?
            if (newX >= 0 && newX < board.getHeight() && newY >= 0 && newY < board.getWidth()) {
                //check if the neighboring cell has a population >= to the minimum population
                if (board.getCellPopulation(newX, newY) >= minPopulation) {
                    //note: this only counts for the individual cell, growth SHOULD not spiral now
                    populatedNeighbors++;
                }
            }
        }
    }

    //if the proper number of neighbors and the proper population #, return true
    if (populatedNeighbors >= requiredNeighbors) {
        return true;
    } else {    //otherwise, return false
        return false;
    }
}

/**
 * @brief Getter function for the pollution level of the cell.
 *
 * @return The pollution level of the cell.
 */
int Cell::getPollution() const {
    return pollution;
}

/**
 * @brief Setter function for the pollution level of the cell.
 *
 * @param newPollution The new pollution level.
 */
void Cell::setPollution(int newPollution) {   //these coordinates
    this->pollution  = newPollution;
}

/**
 * @brief Getter function for the goods in the cell.
 *
 * @return The goods in the cell.
 */
int Cell::getGoods() const {
    return goods;
}

/**
 * @brief Setter function for the goods in the cell.
 *
 * @param goods The new goods value.
 */
void Cell::setGoods(int goods) {
    this->goods = goods;
}
