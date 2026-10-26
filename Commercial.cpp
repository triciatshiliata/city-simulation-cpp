/** \page zone3_page Commercial functionality
 *
 * \section purpose Purpose:
 *
 * The purpose of the Commercial class is to handle the growing and updating of the commercial 'C' cells on the gameboard.
 * The growth of the Commercial cells is highly dependent on decision-making priority (Higher population cells get more priority,
 * higher total adjacent populations, coordinates, etc), rules specific to that zone (Dependent on cell population count, adjacency,
 * worker count, good count), and properly decrementing workers/goods as they are assigned to jobs. An important component specific to
 * the Commercial zone/class is properly decrementing workers/goods. If the wrong amount is decremented, not only are counts thrown off,
 * but commercial zones may grow too often/not enough. Proper growth and conditional rules were vital for all of the zones to function
 * properly. When int main() calls this growth function: Commercial growth is applied to the commercial cells, workers are decremented,
 * goods are decremented, and the cells are updated on the board as the timesteps progress.
 *
 * \section data_storage Data storage and maintenance:
 *
 * Data in the Commercial class is managed through the manipulation of a 2D vector, with important components
 * also being managed through a cell class. The cell class was designed to be used for all zones as it can store basic data like character
 * type, population count, pollution count, etc. The 2D vector (named newLayout) stores the updated state of the gameboard after each
 * iteration of growth. The Commercial class further utilizes a vector named eligibleCells in the growth function to keep track of commercial
 * zone coordinates and sort them accordingly. The sorting process involves rearranging the coordinates based on population (individual cell
 * and adjacent cells), as well as smaller Y and X coordinates. Cell sorting is managed with vectors as this requires repositioning the cells,
 * however growth is evaluated with a for loop that iterates through the cells post-sorting. After sorting has been applied the zone/growth
 * rules themselves are applied, these influence growth based on the cell's population, adjacency to cells/powerlines, and worker/good count.
 * Finally cell population is incremented, and worker/good counts are decremented accordingly. Cell population is shown on the board when it is
 * above 0.
 *
 * \section functionality Functionality Component:
 *
 * The overall major functionality of the Commercial class involves manipulating and growing cells,
 * applying this cell growth to the gameboard layout, and decrementing workers and goods from the count in the gameboard. The process
 * of manipulating the cells involves sorting, and the process of growing cells involves conditional statements (for, if, etc). This zone,
 * and all zones, are fairly similar in growth. Zones growing and applying their rules properly is important so that all zones grow off
 * of each other and update the map properly. What makes Commercial unique is the assigning of workers and goods to jobs.
 *
 *
 * @image html _commercial_8cpp__incl.png
 *
 * <br>
 *
 * @image html _commercial_8h__dep__incl.png
 *
 * <br>
 *
 * @image html _commercial_8h__incl.png
 */


#include <iostream>
#include <algorithm>
#include "Commercial.h"

/**
 * @file Commercial.cpp
 *
 * Implementation file for the Commercial class, which represents the commercial zones on the game board.
 */

 /**
 * @brief Constructor for the Commercial class.
 * @param Residential object is initialized using the gameboard.
 */
Commercial::Commercial(gameBoard& board) {
    //worker and goods vectors will be the same size as the board
    //workers.resize(board.getHeight(), std::vector<std::vector<Worker>>(board.getWidth(), std::vector<Worker>()));
    //goods.resize(board.getHeight(), std::vector<std::vector<Goods>>(board.getWidth(), std::vector<Goods>()));
}


/**
 * @brief Grows the commercial cells on the gameboard based on population, adjacency, and worker/goods rules.
 *
 * This function iterates over all commercial cells, sorts them based on population, total adjacent populations,
 * and coordinates (Y/X), and then applies growth rules to each cell. The growth rules include increasing the population
 * based on conditions laid out in the project instructions. Workers/goods are decremented as they are assigned to jobs.
 *
 * @param board Reference to the gameboard.
 */
void Commercial::growCommercial(gameBoard& board) {
    //store new state
    std::vector<std::vector<Cell>> newLayout = board.getLayout();
    //vector of cells that can grow (according to zone type)
    std::vector<std::pair<int, int>> eligibleCells;

    //iterate over each cell in the gameboard
    //push back all commercial cells into a vector, then sort below.
        for (int i = 0; i < board.getHeight(); ++i) {
        for (int j = 0; j < board.getWidth(); ++j) {
                if (board.getCellType(i, j) == 'C'){
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

        //commercial populations of 1 require at least 1 worker + 1 good + 2 neighbors with population of 1
        if (board.getCellPopulation(i, j) == 1 && board.getWorkerCount() >= 1 && board.getGoodsCount() >= 1 && isAdjacentToPopulation(board, i, j, 1, 2)) {
            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1);
                    board.decrementWorkerCount();
                    board.decrementGoodsCount();
        }

        //commercial populations of 0 require at least 1 worker + 1 good + 1 neighbor with population of 1
        else if (board.getCellPopulation(i, j) == 0 && board.getWorkerCount() >= 1 && board.getGoodsCount() >= 1 && isAdjacentToPopulation(board, i, j, 1, 1)) {
            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1);
                    board.decrementWorkerCount();
                    board.decrementGoodsCount();

        }

        //commercial population of 0 require at least 1 worker + 1 good + adjacency to a powerline
        else if (board.getCellPopulation(i, j) == 0 && board.getWorkerCount() >= 1 && board.getGoodsCount() >= 1 && isAdjacentToPowerline(board, i, j)) {
            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1);
                    board.decrementWorkerCount();
                    board.decrementGoodsCount();
        }
    }
    //update layout
    board.setLayout(newLayout);
}

/**
 * @brief This function checks if a cell is adjacent to a powerline or not, and increases population if determined necessary.
 * @param board The gameboard.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @return Return true if the cell is adjacent to a powerline, false otherwise.
 */
bool Commercial::isAdjacentToPowerline(const gameBoard& board, int x, int y) {
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
bool Commercial::isAdjacentToPopulation(const gameBoard& board, int x, int y, int minPopulation, int requiredNeighbors) {
    return board.getCell(x, y).isAdjacentToPopulation(board, x, y, minPopulation, requiredNeighbors);
}

