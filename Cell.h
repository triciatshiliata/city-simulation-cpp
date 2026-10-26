#ifndef CELL_H
#define CELL_H
#include <string>
#include "gameBoard.h"
#include "Residential.h"

//needed forward class decs
class gameBoard;

/**
 * @file Cell.h
 *
 * Header file for the Cell class, representing a cell in the gameboard.
 */

/**
 * @class Cell
 *
 * @brief Represents a cell in a game board with various properties.
 */

class Cell {

public:

    int getPollution() const;
    void setPollution(int newPollution);
    //constructor
    Cell ();  //default constructor
    Cell(char t);  //pass the zone type

    //function decs
    char getType() const;
    char setType(char t);

    //setting the population
    void setPopulation(int population);
    int getPopulation() const;

    //worker functions
    int getWorkers() const;
    void setWorkers(int workers, int x, int y);
    bool isWorkerAvailable() const;
    void setWorkerAvailability(bool availability);

    //adjacency functions for all zones
    bool isAdjacentToPowerline(const gameBoard& board, int x, int y) const;
    bool isAdjacentToPopulation(const gameBoard& board, int x, int y, int minPopulation, int requiredNeighbors) const;

    //goods functions
     int getGoods() const;
     void setGoods(int goods);



private:

    char type;  //zone type
    int population;  //population
    int workers;  //industrial zone
    bool workerAvailable;
    int goods;       //commercial zone
    int pollution;   //for industrial zones

};

#endif // CELL_H
