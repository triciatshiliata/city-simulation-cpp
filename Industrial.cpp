/** \page zone2_page Industrial functionality
*
* Handled by: Sydney Jones and Patricia Tshiliata
*
* Written by: Sydney Jones
*
* \section purpose Purpose:
*
* The purpose of the Industrial class is to handle the growth behavior and characteristics of industrial zones in the simulation.
* The growth of the Industrial cells is dependent on priority,(population size, adjacent populations, and x/y coordinates etc.
* determine the priority of the cell.) and rules specific to that zone. The transformations unique to industrial zones include
* the production of goods and the generation of pollution. Industrial zones supply goods to commercial zones at a rate of one
* unit per population. However, each unit of goods can only be sold at a single commercial cell. Each cell generates pollution in
* an amount equal to its population, and this pollution spreads to adjacent cells, decreasing by one unit per cell away from the
* source. When the industrial growth function is called in int main(), Industrial growth is applied to industrial 'I' cells,
* pollution spreads to adjacent cells and goods are provided to the commercial zones.
*
* \section data_storage Data Storage/Maintenance:
* Data in the Industrial class is controlled through the manipulation of a 2D vector, with important components
* also being managed through a cell class. The 2D vector (newLayout) stores the updated gameboard after each
* iteration of growth. The Industrial class uses a vector named eligibleCells in the growth function to keep track of industrial
* coordinates and sort them accordingly. The coordinates based on population are sorted and rearranged based
* on population size, total adjacent populations, and smaller Y and X coordinates. Cell sorting is conducted using vectors since
* it necessitates the rearrangement of cells. However, growth evaluation occurs using a for loop that iterates through the cells
* after sorting. After sorting has been applied the industrial zone growth rules are applied, these rules cause growth based on
* the cell's population if there are at least 2 available workers, and  their adjacency to cells or powerlines. Cell population
* and board goods are both incremented while worker count is decremented twice after growth rules are applied.
*
* \section functionality Functionality Component:
*
* The overall major functionality of the Industrial class involves managing and growing cells,
* applying this cell growth to the gameboard layout, spreading pollution to adjacent cells, and supplying goods to the
* commerical zone to other zones to aid in the processing of their own growth rules.
* The cells are managed through sorting and the of growth of cells involves using branching statements.
* The isAdjacentToPopulation and isAdjacentToPowerline functions provide utility for checking conditions related to neighboring
* cells.
* All of the zones: residential, commercial, and industrial, require these functions to apply  the conditional growth rules.
*/


#include<iostream>
#include"Industrial.h"
#include"Cell.h"
#include <algorithm>

using namespace std;

/**
 * @file Industrial.cpp
 *
 * Implementation file for the Industrial class, which represents the industrial zones on the game board.
 */

/**
 * @brief Constructor for the Industrial class.
 * @param Residential object is initialized using the gameboard.
 */
Industrial::Industrial(gameBoard& board) {
    //worker vector is the same size as the board
    //workers.resize(board.getHeight(), std::vector<std::vector<Worker>>(board.getWidth(), std::vector<Worker>()));
}

/**
 * @brief Grows the industrial cells on the gameboard based on population, adjacency, and worker rules.
 *
 * This function iterates over all industrial cells, sorts them based on population, total adjacent populations,
 * and coordinates (Y/X), and then applies growth rules to each cell. The growth rules include increasing the population,
 * pollution, and goods count based on conditions laid out in the project instructions. Workers are decremented as they
 * are assigned to work.
 *
 * @param board Reference to the gameboard.
 */
void Industrial::IndustrialGrowth(gameBoard& board) {
    //store new state
    std::vector<std::vector<Cell>> newLayout = board.getLayout();
    //vector of cells that can grow (according to zone type)
    std::vector<std::pair<int, int>> eligibleCells;

    //iterate over each cell in the gameboard
    //push back all industrial cells into a vector, then sort below.
    for (int i = 0; i < board.getHeight(); ++i) {
        for (int j = 0; j < board.getWidth(); ++j) {
                if (board.getCellType(i, j) == 'I'){
            eligibleCells.push_back({i, j});
                }
        }
    }

    //the below sources helped with understanding this functionality + how to return higher vs. lower compared element
    //https://stackoverflow.com/questions/30797011/sorting-a-vector-inside-a-custom-class-c-using-stdsort
    //https://stackoverflow.com/questions/37368787/c-sort-one-vector-based-on-another-one
    //https://cplusplus.com/forum/beginner/284206/
    //the below sources helped with writing the sort header
    //https://stackoverflow.com/questions/37368787/c-sort-one-vector-based-on-another-one
    //https://stackoverflow.com/questions/68225770/sorting-vector-of-pair-using-lambda-predicate-crashing-with-memory-corruption
    //sort from the beginning to the end of the vector of eligible cells
     std::sort(eligibleCells.begin(), eligibleCells.end(), [&](const auto& i, const auto& j) {
        int popI = board.getCellPopulation(i.first, i.second);
        int popJ = board.getCellPopulation(j.first, j.second);

        //first comparison, population #
        //main will already call growth in order C > I > R
        if (popI > popJ) {
            return true;
        } else if (popI < popJ) {
            return false;
        }

        //then sort by total adjacent populations if populations are equal
        int adjacentPopI = board.calculateTotalAdjacentPopulation(i.first, i.second);
        int adjacentPopJ = board.calculateTotalAdjacentPopulation(j.first, j.second);

        if (adjacentPopI > adjacentPopJ) {
            return true;
        } else if (adjacentPopI < adjacentPopJ) {
            return false;
        }

        //sort by Y coordinate if total adjacent populations are equal
        if (i.first < j.first) {
            return true;
        } else if (i.first > j.first) {
            return false;
        }

        //sort by X coordinate if Y coordinates are equal
        return i.second < j.second;
        //all sorted!
    });

    //iterate over each element in eligiblecells vector, testing if conditions satisfied here post-sorting as opposed to before
    //looped with coordinates to access the value of vector elements
    //still looped with coordinates labeled i/j like in the beginning loop
    for (const auto& coords : eligibleCells) {
        int i = coords.first;
        int j = coords.second;

        //industrial populations of 2 require at least 2 workers + 4 neighbors with population of 2
        if (board.getCellPopulation(i, j) == 2 && isAdjacentToPopulation(board, i, j, 2, 4) && board.getWorkerCount() >= 2) {
            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1);
                board.decrementWorkerCount();
                board.decrementWorkerCount();
                board.incrementGoods();
                newLayout[i][j].setPollution(newLayout[i][j].getPopulation());
        }

        //industrial populations of 1 require at least 2 workers + 2 neighbors with population of 1
        else if (board.getCellPopulation(i, j) == 1 && isAdjacentToPopulation(board, i, j, 1, 2) && board.getWorkerCount() >= 2) {
            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1);
                board.decrementWorkerCount();
                board.decrementWorkerCount();
                board.incrementGoods();
                newLayout[i][j].setPollution(newLayout[i][j].getPopulation());
        }

        //industrial populations of 0 require at least 2 workers + 1 neighbors with population of 1
        else if (board.getCellPopulation(i, j) == 0 && isAdjacentToPopulation(board, i, j, 1, 1) && board.getWorkerCount() >= 2) {
            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1);
                board.decrementWorkerCount();
                board.decrementWorkerCount();
                board.incrementGoods();
                newLayout[i][j].setPollution(newLayout[i][j].getPopulation());
        }

        //industrial population of 0 require at least 2 workers + adjacency to a powerline
        else if (board.getCellPopulation(i, j) == 0 && isAdjacentToPowerline(board, i, j) && board.getWorkerCount() >= 2) {
            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1);
                board.decrementWorkerCount();
                board.decrementWorkerCount();
                board.incrementGoods();
                newLayout[i][j].setPollution(newLayout[i][j].getPopulation());

        }
    }
    //update layout
    board.setLayout(newLayout);
}

/**
 * @brief This function checks if a cell is adjacent to a powerline or not, and increases population if necessary
 * @param board The gameboard.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @return Return true if the cell is adjacent to a powerline, false otherwise.
 */
bool Industrial::isAdjacentToPowerline(const gameBoard& board, int x, int y){
	return board.getCell(x, y).isAdjacentToPowerline(board, x, y);
}
/**
 * @brief Check if a cell is adjacent to # cells with # population.
 * @param board The gameboard.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @param minPopulation (The minimum population required for the adjacent cells.)
 * @param requiredNeighbors (The required number of neighboring cells with at least minPopulation.)
 * @return True if the cell is adjacent to the specified rules in parameters, false otherwise.
 */
bool Industrial::isAdjacentToPopulation(const gameBoard& board, int x, int y,int minPopulation, int requiredNeighbors){
	return board.getCell(x, y).isAdjacentToPopulation(board,x,y,minPopulation,requiredNeighbors);
}
/**
 * @brief Getter function for the # available workers.
 *
 * @return The # of available workers.
 */
int Industrial::getAvailableWorkers()const{
	return availableWorkers;
}
/**
 * @brief Setter function for the # available workers
 *
 * @param workers The new # available workers value.
 */
void Industrial::setAvailableWorkers(int workers) {
    availableWorkers = workers;
}
