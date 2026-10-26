/** \page zone5_page Pollution Spread Function
 * Written by Ronil Doshi
 *
 * \section purpose_sec Purpose
 * The counter runs at the end of the simulation to tally the spread of pollution over the game map.
 *
 * \section data_storage_sec Data Storage
 * Data about how much pollution is produced by a cell is stored in its cell object. The updated data after the counter is finished running is then passed back to the cells.
 *
 * \section functionality_sec Functionality
 * The counter works by iterating through the entire 2d vector game board. When the loop reaches a cell representing an industrial area with pollution greater than 1, a second loop spreads the pollution to neighboring vector coordinates, proportional to the distance from the polluting cell.
 */



/**
 * @file gameBoard.cpp
 * @brief Implementation of the gameBoard class for managing the gameboard state.
 */

#include "gameBoard.h"
#include <iomanip>

/**
 * @brief Constructor for the gameBoard class.
 * @param file An input file stream containing the initial state of the gameboard.
 */
gameBoard::gameBoard(std::ifstream& file)
{
    workerCount = 0;
    goodsCount = 0;

	std::string line;
	while (getline(file, line))
	{
		std::vector<Cell> row;
		std::stringstream s(line);
        char val;
		while (s.get(val))  //read character
        {
            if (val != ',')
            {
                row.push_back(Cell(val));  //make cell object with the character type, push it into the vector
            }
        }
        layout.push_back(row);
	}

}

/**
 * @brief Simulates the growth of pollution on the game board.
 * The pollution spreads from industrial cells with pollution levels greater than 1 to non-Industrial neighboring cells.
 */
void gameBoard::pollutionGrowth()
{
    std::vector<std::vector<Cell>> pollutionMap = layout;

    for (int i = 0; i < getHeight(); i++) {
        for (int j = 0; j < getWidth(); j++)
        {
            if (getCellType(i, j) == 'I' && getCellPollution(i, j) > 1) { // thus will only spread for values greater than 1
                int polluteDistance = getCell(i, j).getPollution();

                for (int a = -1; a <= 1; a++) {
                    for (int b = -1; b <= 1; b++) {
                        int newRow = i + a;
                        int newCol = j + b;


                        if ((newRow > -1 && newRow < getHeight()) && (newCol > -1 && newCol < getWidth()) && pollutionMap[newRow][newCol].getPollution() == 0)
                        {
                            pollutionMap[newRow][newCol].setPollution(pollutionMap[newRow][newCol].getPollution() + (polluteDistance - 1));
                        }
                    }
                }


            }

        }


    }

    layout = pollutionMap;

}


/**
 * @brief Outputs the current state of the game board.
 * If a cell has a population > 0, population is outputted. Otherwise character is outputted.
 */
void gameBoard::output()
{
    std::cout << std::endl << "Map: " << std::endl;

    for (auto& row : layout)
    {
        for (auto& cell : row)
        {
            //if a cell population is 0 print the character
            if (cell.getPopulation() == 0)
            {
                std::cout << std::fixed << std::setw(2) << cell.getType() << " ";
            } else{ //above 0? print the population number
                std::cout << std::fixed << std::setw(2) << cell.getPopulation() << " ";
            }

        }
        std::cout << std::endl;
    }
}

/**
 * @brief Outputs the final pollution map of the game board.
 * If a cell has a pollution total of 0, print the character instead.
 */
void gameBoard::outputPollutionMap()
{
    std::cout << std::endl << "FINAL POLLUTION MAP:\n";
    for (auto& row : layout)
    {
        for (auto& cell : row)
        {

            if (cell.getPollution() == 0) // if cell pollution is zero, prints its type
            {
                std::cout << std::fixed << std::setw(2) << cell.getType() << " ";
            }
            else { // otherwise prints its pollution
                std::cout << std::fixed << std::setw(2) << cell.getPollution() << " ";
            }

        }
        std::cout << std::endl;
    }

}

/**
 * @brief Gets the current layout of the game board.
 * @return A const reference to the 2D vector representing the layout.
 */
const std::vector<std::vector<Cell>>& gameBoard::getLayout() const {
    return layout;
}

/**
 * @brief Gets the number of rows in the game board.
 * @return The number of rows in the game board.
 */
//return # of rows in the gameboard
int gameBoard::getHeight() const {
    return layout.size();
}

/**
 * @brief Gets the number of columns in the game board.
 * @return The number of columns in the game board.
 */
//return # of columns in the gameboard
int gameBoard::getWidth() const {
    return layout[0].size();
}

/**
 * @brief Gets the type of the cell at the specified coordinates.
 * @param x The row index.
 * @param y The column index.
 * @return The char type of the cell at the row, col index.
 */
//return cell chara
char gameBoard::getCellType(int x, int y) const {
    return getCell(x, y).getType();
}

/**
 * @brief Gets the population of the cell at the specified coordinates.
 * @param x The row index.
 * @param y The column index.
 * @return The # population of the cell at the row, col index.
 */
//return cell population #
int gameBoard::getCellPopulation(int x, int y) const {
    return layout[x][y].getPopulation();
}

/**
 * @brief Gets the pollution level of the cell at the specified coordinates.
 * @param x The row index.
 * @param y The column index.
 * @return The # pollution of the cell at the row, col index.
 */
//return cell pollution #
int gameBoard::getCellPollution(int x, int y)
{
    return layout[x][y].getPollution();
}

/**
 * @brief Updates the layout of the game board with a new layout (after growth of some kind).
 * @param newLayout The new 2D vector representing the layout of the game board.
 */
//update the board layout
void gameBoard::setLayout(const std::vector<std::vector<Cell>>& newLayout) {
    layout = newLayout;
}

/**
 * @brief Gets the cell at the specified coordinates.
 * @param x The row index.
 * @param y The column index.
 * @return A const reference to the Cell object at the specified coordinates.
 */
//
const Cell& gameBoard::getCell(int x, int y) const {
    return layout[x][y];
}

/**
 * @brief Gets the current # of workers on the game board.
 * @return The number of workers.
 */
int gameBoard::getWorkerCount() const {
    return workerCount;
}

/**
 * @brief Increments the # of workers on the game board.
 */
void gameBoard::incrementWorkerCount() {
    workerCount++;
}

/**
 * @brief Decrements the # of workers on the game board.
 */
void gameBoard::decrementWorkerCount() {
     workerCount--;
}

/**
 * @brief Gets the current # of goods on the game board.
 * @return The number of goods.
 */
int gameBoard::getGoodsCount() const {
    return goodsCount;
}

/**
 * @brief Increments the # of goods on the game board.
 */
void gameBoard::incrementGoods() {
    goodsCount ++;
}

/**
 * @brief Decrements the # of goods on the game board.
 */
void gameBoard::decrementGoodsCount() {
        goodsCount--;
}

/**
 * @brief Calculates the total population from all adjacent cells around a specified cell.
 * @param x The row index of the specified cell.
 * @param y The column index of the specified cell.
 * @return The total population of all neighboring cells.
 */
//calculate total populations from all adjacent cells around a cell. helps with sorting by priority in res/indus/comm files
int gameBoard::calculateTotalAdjacentPopulation(int x, int y) {
    //initialize at 0
    int totalPopulation = 0;

    //iterate over 3x3, centered at the cell we are comparing
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            //calculating neighboring coordinates
            int newX = x + i;
            int newY = y + j;

            //dont need to add the cell we are comparing
            if (i == 0 && j == 0)
                continue;

            //neighboring cells needs to be in bounds
            if (newX >= 0 && newX < getHeight() && newY >= 0 && newY < getWidth()) {
                //add the populations of all neighboring cells
                totalPopulation += getCellPopulation(newX, newY);
            }
        }
    }

    //return population of all neighboring cells
    return totalPopulation;
}

//for usage in the unit tests
void gameBoard::setLayoutCellPopulation(int x, int y, int population) {
    layout[x][y].setPopulation(population);
}
int gameBoard::CalculateTotalPollution(){
        int totalPollution = 0;

        for(int i = 0; i < getHeight(); ++i){
                for(int j = 0; j < getWidth(); ++j){
                        totalPollution += getCellPollution(i,j);
                    
                }
        }

        return totalPollution;
}

void gameBoard::setWorkerCount(int w){
        this->workerCount = w;
}

void gameBoard::setGoodsCount(int g){
        this->goodsCount = g;
}

