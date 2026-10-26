#include <iostream>
#include <cassert>
#include <fstream>
#include "gameBoard.h"
#include "Residential.h"
#include "Commercial.h"
#include "Industrial.h"

// ANSI color codes for text color
#define ANSI_COLOR_GREEN "\033[32m" //for passing tests
#define ANSI_COLOR_RED "\033[31m"   //for failing tests
#define ANSI_COLOR_RESET "\033[0m"  //regular text color
#define ANSI_COLOR_YELLOW "\033[33m" //for fully passing tests
#define ANSI_COLOR_PINK "\033[95m" //for final messages

/*

my unit testing will, when it is finished, test:
- regular growth rules
- regular worker/goods/pollution rules
- edge population cases (negative populations, very large ones)
- edge growth cases (negative pollution, workers, goods)

milestone 1 goals:
- res powerline check [x]
- res adjacency check (0, 1, 2, 3, 4) [x]
    + setting adjacent populations here for testing [x]
- res worker increase [x]

*/

//source: https://stackoverflow.com/questions/4039025/using-a-simple-assert-macro
//https://stackoverflow.com/questions/25745890/c-macro-for-print-colour-based-on-source-file
#define ASSERT_WITH_COLOR(condition, message) \
if (!(condition)) { \
    std::cout << ANSI_COLOR_RED << "Assertion Failed: " << message << ANSI_COLOR_RESET << std::endl; \
    assert(condition); \
} else { \
    std::cout << ANSI_COLOR_GREEN << "Assertion Passed: " << message << ANSI_COLOR_RESET << std::endl; \
}

void testResidentialGrowth() {
    //unit testing will open a specifically made unit-testing map
    std::ifstream file("unitTestingMap.csv");
    if (!file.is_open()) {
        std::cout << "Error: Could not open unitTestingMap.csv\n";
        return;
    }
    gameBoard board(file);

    // Assert the initial worker count is 0
    ASSERT_WITH_COLOR(board.getWorkerCount() == 0, "Initial worker count is set to 0.");

    //x coord, y coord, population # to set. below i am changing the populations on the board to allow for sufficient testing
    //testing adjacency to 1 cell with population of 1

    std::cout << std::endl << "PRE-TESTING map: ";
    board.output();

    //RESIDENTIAL SETS
    board.setLayoutCellPopulation(0, 4, 1);

    //testing res cell with population of 1 next to 2 cells with populations of 1
    board.setLayoutCellPopulation(5, 5, 1); //res cell
    board.setLayoutCellPopulation(5, 4, 1);
    board.setLayoutCellPopulation(4, 4, 1); //two comm cells

    //testing res cell with population of 2 next to 4 cells with populations of 2
    board.setLayoutCellPopulation(9, 5, 2); //res cell
    board.setLayoutCellPopulation(10, 5, 2);
    board.setLayoutCellPopulation(8, 5, 2);
    board.setLayoutCellPopulation(9, 4, 2);
    board.setLayoutCellPopulation(9, 6, 2); //four comm cells

    //testing res cell with population of 3 next to 6 cells with populations of 3
    board.setLayoutCellPopulation(13, 5, 3);
    board.setLayoutCellPopulation(12, 5, 3);
    board.setLayoutCellPopulation(12, 4, 3);
    board.setLayoutCellPopulation(12, 6, 3);
    board.setLayoutCellPopulation(14, 5, 3);
    board.setLayoutCellPopulation(14, 4, 3);
    board.setLayoutCellPopulation(14, 6, 3);

    //testing res cell with population of 4 next to 8 cells with populations of 4
    board.setLayoutCellPopulation(17, 5, 4); //res cell
    board.setLayoutCellPopulation(17, 6, 4);
    board.setLayoutCellPopulation(17, 4, 4);
    board.setLayoutCellPopulation(16, 5, 4);
    board.setLayoutCellPopulation(16, 6, 4);
    board.setLayoutCellPopulation(16, 4, 4);
    board.setLayoutCellPopulation(18, 5, 4);
    board.setLayoutCellPopulation(18, 6, 4);
    board.setLayoutCellPopulation(18, 4, 4); //8 comm cells

    //INDUSTRIAL SETS
    //testing industrial pop of 0, powerline, 2 workers
    //nothing needed here

    //testing industrial pop of 0, 1 cell with 1 pop, 2 workers
    board.setLayoutCellPopulation(4, 10, 1);

    //testing industrial pop of 1, 2 cells with 1 pop, 2 workers
    board.setLayoutCellPopulation(9, 9, 1);
    board.setLayoutCellPopulation(8, 10, 1);
    board.setLayoutCellPopulation(8, 9, 1);

    //testing industrial pop of 2, 4 cells with 2 pop, 2 workers
    board.setLayoutCellPopulation(13, 9, 2);
    board.setLayoutCellPopulation(12, 10, 2);
    board.setLayoutCellPopulation(12, 9, 2);
    board.setLayoutCellPopulation(12, 8, 2);
    board.setLayoutCellPopulation(13, 8, 2);

    //COMMERCIAL SETS

    //pop 0 cell with 1 neighbor with 1 pop
    board.setLayoutCellPopulation(5, 12, 1);

    //pop 1 cell with 2 neighbors with 1 pop
    board.setLayoutCellPopulation(9, 13, 1);
    board.setLayoutCellPopulation(9, 12, 1);
    board.setLayoutCellPopulation(9, 14, 1);

    //print the initial board with the above population changes
    std::cout << std::endl << "Map AFTER population adjustments for testing: ";
    board.output();

    //ensure that the initial population of 'R' cell is 0
    //more of a test assert
    assert(board.getCellPopulation(0, 1) == 0);

    //apply residential growth method
    Residential residential(board);
    Industrial industrial(board);
    Commercial commercial(board);

    residential.growResidential(board);
    industrial.IndustrialGrowth(board);
    commercial.growCommercial(board);

    //output the game board after growth (for visual confirmation)
    std::cout << std::endl << "POST-TESTING map state: ";
    board.output();

    //ensure that the population of 'R' cell increases correctly, according to pre-calculated amounts
    //checking powerline rule
    std::cout << "Checking residential zone population rules (powerlines + adjacencies)" << std::endl;
    ASSERT_WITH_COLOR(board.getCellPopulation(0, 1) == 1, "Population at coordinates (0, 1) increased to 1 after growth.");
    //checking 1 neighboring cell with pop of 1 rule
    ASSERT_WITH_COLOR(board.getCellPopulation(1, 5) == 1, "Population at coordinates (1, 5) increased to 1 after growth.");
    //checking 2 neighboring cells with pop of 1 rule
    ASSERT_WITH_COLOR(board.getCellPopulation(5, 5) == 2, "Population at coordinates (5, 5) increased to 2 after growth.");
    //checking 4 neighboring cells with pop of 2 rule
    ASSERT_WITH_COLOR(board.getCellPopulation(9, 5) == 3, "Population at coordinates (9, 5) increased to 3 after growth.");
    //checking 6 neighboring cells with pop of 3 rule
    ASSERT_WITH_COLOR(board.getCellPopulation(13, 5) == 4, "Population at coordinates (9, 5) increased to 4 after growth.");
    //checking 8 neighboring cells with pop of 4 rule
    ASSERT_WITH_COLOR(board.getCellPopulation(17, 5) == 5, "Population at coordinates (9, 5) increased to 5 after growth.");
    std::cout << "Checking residential zone worker counts with above growth applied" << std::endl;
    // Assert the initial worker count is 0
    //std::cout << "Worker count after growth: " << board.getWorkerCount() << std::endl;
    ASSERT_WITH_COLOR(board.getWorkerCount() == 8, "Initial worker count is 22, decremented to 8 after 5 industrial and 4 commercial cells grew.");
    int totalPollution = 0;
    for (int i = 0; i < board.getHeight(); ++i) {
        for (int j = 0; j < board.getWidth(); ++j) {
                if(board.getCellType(i,j) == 'I')
                {
            totalPollution += board.getCellPollution(i, j);
                }
        }
    }

    //print that all residential cells printed properly, if no asserts failed
    std::cout << ANSI_COLOR_YELLOW << "Residential growth tests passed!" << ANSI_COLOR_RESET << std::endl;
    std:: cout << std::endl;
    //INDUSTRIAL TESTING
    std::cout << "Checking industrial zone population rules (powerlines + adjacencies)" << std::endl;
    ASSERT_WITH_COLOR(board.getCellPopulation(1, 9) == 1, "Population at coordinates (1, 9) increased to 1 after growth.");
    ASSERT_WITH_COLOR(board.getCellPopulation(5, 9) == 1, "Population at coordinates (5, 9) increased to 1 after growth.");
    ASSERT_WITH_COLOR(board.getCellPopulation(9, 9) == 2, "Population at coordinates (9, 9) increased to 2 after growth.");
    ASSERT_WITH_COLOR(board.getCellPopulation(13, 9) == 3, "Population at coordinates (13, 9) increased to 3 after growth.");
    std::cout << "Checking industrial zone pollution count" << std::endl;
    //std::cout << "Total pollution on the map: " << totalPollution << std::endl;
    ASSERT_WITH_COLOR(totalPollution == 8, "Pollution count is 8 after growth.");
    std::cout << "Checking industrial zone goods count" << std::endl;
    ASSERT_WITH_COLOR(board.getGoodsCount() == 1, "Goods count is 1 after growth.");

    std::cout << ANSI_COLOR_YELLOW << "Industrial growth tests passed!" << ANSI_COLOR_RESET << std::endl;
    std:: cout << std::endl;

    //COMMERCIAL TESTING

    std::cout << "Checking commercial zone population rules (powerlines + adjacencies)" << std::endl;

    ASSERT_WITH_COLOR(board.getCellPopulation(1, 13) == 1, "Population at coordinates (1, 12) increased to 1 after growth.");
    ASSERT_WITH_COLOR(board.getCellPopulation(5, 13) == 1, "Population at coordinates (5, 12) increased to 2 after growth.");
    ASSERT_WITH_COLOR(board.getCellPopulation(9, 13) == 2, "Population at coordinates (9, 13) increased to 2 after growth.");

    std::cout << ANSI_COLOR_YELLOW << "Commercial growth tests passed!" << ANSI_COLOR_RESET << std::endl;
    std:: cout << std::endl;
    std::cout << ANSI_COLOR_PINK  << "All tests passed!" << ANSI_COLOR_RESET << std::endl;
    std:: cout << std::endl;

}
