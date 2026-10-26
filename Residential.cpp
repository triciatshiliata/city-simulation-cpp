/** \page zone1_page Residential functionality
 *
 * Handled by: Eden Kutch and Connor Jones
 *
 * Written by: Eden Kutch
 *
 * \section purpose Purpose:
 *
 * The purpose of the Residential class is to handle the growing and updating of the residential 'R' cells on the gameboard.
 * The growth of the Residential cells is highly dependent on decision-making priority (Higher population cells get more priority,
 * higher total adjacent populations, coordinates, etc), as well as rules specific to that zone (Dependent on cell population count
 * and adjacency). Another important component of the residential areas/class is that the residential zone supplies workers to the
 * other zones. This is important because the Industrial and Commercial zones need workers in order to simulate their growth too.
 * When int main() calls this growth function: Residential growth is applied to the residential cells, workers are added, and the cells
 * are updated on the board as the timesteps progress.
 *
 * \section data_storage Data Storage/Maintenance:
 *
 * Data in the Residential class is managed through the manipulation of a 2D vector, with important components
 * also being managed through a cell class. The cell class was designed to be used for all zones as it can store basic data like character
 * type, population count, pollution count, etc. The 2D vector (named newLayout) stores the updated state of the gameboard after each
 * iteration of growth. The Residential class in particular further utilizes a vector named eligibleCells in the growth function to keep
 * track of residential coordinates and sort them accordingly. The sorting process involves rearranging the coordinates based on population
 * (individual cell and adjacent cells), as well as smaller Y and X coordinates. Cell sorting is managed with vectors as this requires
 * repositioning the cells, however growth is evaluated with a for loop that iterates through the cells post-sorting. After sorting has
 * been applied the zone/growth rules themselves are applied, these influence growth based on the cell's population, and adjacency to
 * cells/powerlines. Finally cell population (and thus worker count, as residential provides workers) is incremented. Cell population is
 * shown on the board, while worker count is kept in the gameboard for industrial/commercial cells to decrement as the workers are used.
 *
 * \section functionality Functionality Component:
 *
 * The overall major functionality of the Residential class involves manipulating and growing cells,
 * applying this cell growth to the gameboard layout, and supplying workers to other zones to aid in the processing of their own growth rules.
 * The process of manipulating the cells involves sorting, and the process of growing cells involves conditional statements (for, if, etc).
 * The isAdjacentToPopulation and isAdjacentToPowerline functions in particular provide utility for checking conditions related to neighboring
 * cells and were later moved to the cell class for the other zones to use. This is because all of the zones are fairly similar in their growth,
 * and all of them require these functions to apply conditional rules. The development of residential zone functionality was also important in
 * understanding the overall logic. Once this zone was completed, the other zones had a structure to learn and build off of.
 *
 * \section images Image diagrams to visualize the flow process in Residential.cpp:
 *
 * @image html class_residential__coll__graph.png
 *
 * @image html class_residential_acc8e964663258732ecd688c06c3b1ca4_cgraph.png
 *
 * @image html class_residential_a70679ffc6dbc7a8b20adfd569b3aca40_cgraph.png
 *
 * @image html class_residential_a5bcae1bb8e962ef96a5e097aaea2c1ce_cgraph.png
 */

#include <iostream>
#include <algorithm>
#include "Residential.h"

/**
 * @file Residential.cpp
 *
 * Implementation file for the Residential class, which represents the residential zones on the game board.
 */

/**
 * @brief Constructor for the Residential class.
 * @param Residential object is initialized using the gameboard.
 */
Residential::Residential(gameBoard& board) {
    //worker vector is the same size as the board
    //workers.resize(board.getHeight(), std::vector<std::vector<Worker>>(board.getWidth(), std::vector<Worker>()));


}

/**
 * @brief Grows the residential cells on the gameboard based on population and adjacency rules.
 *
 * This function iterates over all residential cells, sorts them based on population, total adjacent populations,
 * and coordinates (Y/X), and then applies growth rules to each cell. The growth rules include increasing the population
 * and worker count based on conditions laid out in the project instructions.
 *
 * @param board Reference to the gameboard.
 */

void Residential::growResidential(gameBoard& board) {
    //store new state
    std::vector<std::vector<Cell>> newLayout = board.getLayout();
    //vector of cells that can grow (according to zone type)
    std::vector<std::pair<int, int>> eligibleCells;

    //instead of applying rules here, push back all residential cells into a vector, then sort below.
        for (int i = 0; i < board.getHeight(); ++i) {
        for (int j = 0; j < board.getWidth(); ++j) {
                if (board.getCellType(i, j) == 'R'){
            eligibleCells.push_back({i, j});
                }
        }
    }

    //sort from the beginning to the end of the vector of eligible cells. keeping i and j from for loop to prevent confusion.
    //the below sources helped with understanding this functionality + how to return higher vs. lower compared element
    //https://stackoverflow.com/questions/30797011/sorting-a-vector-inside-a-custom-class-c-using-stdsort
    //https://stackoverflow.com/questions/37368787/c-sort-one-vector-based-on-another-one
    //https://cplusplus.com/forum/beginner/284206/
    //the below sources helped with writing the sort header
    //https://stackoverflow.com/questions/37368787/c-sort-one-vector-based-on-another-one
    //https://stackoverflow.com/questions/68225770/sorting-vector-of-pair-using-lambda-predicate-crashing-with-memory-corruption
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

    //old rules moved here like usual. residential population of 4 needs 8 adjacent cells with population of 4.
    if (isAdjacentToPopulation(board, i, j, 4, 8) && board.getCellPopulation(i, j) == 4) {
    //if qualifies, +1 population/worker
        newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1); board.incrementWorkerCount();

    }

    //residential populations of 3 require 6 neighbors with population of 3
    else if (isAdjacentToPopulation(board, i, j, 3, 6) && board.getCellPopulation(i, j) == 3) {
    //if qualifies, +1 population/worker
        newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1); board.incrementWorkerCount();
    }

    //residential populations of 2 require 4 neighbors with population of 2
    else if (isAdjacentToPopulation(board, i, j, 2, 4) && board.getCellPopulation(i, j) == 2) {
    //if qualifies, +1 population/worker
        newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1); board.incrementWorkerCount();
    }

    //residential populations of 1 require 2 neighbors with population of 1
    else if (isAdjacentToPopulation(board, i, j, 1, 2) && board.getCellPopulation(i, j) == 1) {
    //if qualifies, +1 population/worker
            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1); board.incrementWorkerCount();
    }
    //residential cells with 0 population need 1 neighbor with a population of 1
    else if (isAdjacentToPopulation(board, i, j, 1, 1) && board.getCellPopulation(i, j) == 0) {

            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1); board.incrementWorkerCount();
    }

    //or, if that 0 population cell is next to a powerline, it can grow
    else if (isAdjacentToPowerline(board, i, j) && board.getCellPopulation(i, j) == 0) {

            newLayout[i][j].setPopulation(board.getCellPopulation(i, j) + 1); board.incrementWorkerCount();

        }
    }
    //finally set the layout
    board.setLayout(newLayout);
}



/**
 * @brief This function checks if a cell is adjacent to a powerline or not, and increases population if necessary
 * @param board The gameboard.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @return Return true if the cell is adjacent to a powerline, false otherwise.
 */
bool Residential::isAdjacentToPowerline(const gameBoard& board, int x, int y) {
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
bool Residential::isAdjacentToPopulation(const gameBoard& board, int x, int y, int minPopulation, int requiredNeighbors) {
    return board.getCell(x, y).isAdjacentToPopulation(board, x, y, minPopulation, requiredNeighbors);
}
