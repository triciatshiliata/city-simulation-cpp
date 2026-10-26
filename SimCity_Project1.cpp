/*! \mainpage Main Page
 *
 * Simcity - CSCE 2110.002 Project 1
 * ------------------------
 *
 * \par Created by
 * Eden Kutch, Patricia Tshiliata, Ronil Doshi, Sydney Jones, Connor Johnson
 *
 *
 *
 *
 * Our project is a Sims City-style program designed to simulate the growth and manipulation of a virtual city environment, either over a specified number of time steps or when growth halts - whichever condition is satisfied first. The program opens from a configuration, and the time step count, refresh rate, and map file are grabbed from this config .txt file. The simulation involves three types of zones: Residential, Commercial, and Industrial. Each zone has its own growth rules, and the simulation tracks population changes, worker production/distribution, goods production, and pollution levels/dispersal. Each zone heavily influences the other, so it is vital that conditions in regards to sorting and applying growth to the cells are correctly implemented.
 *
 *
 * Major functionality components:
 * - \ref zone0_page "Input"
 * - \ref zone1_page "Residential zone"
 * - \ref zone2_page "Industrial zone"
 * - \ref zone3_page "Commercial zone"
 * - \ref zone4_page "Pollution functionality"
 * - \ref zone6_page "Output"
 *
 * System workflow:
 * -# Initialization: The configuration file is opened and read to set up the simulation. The gameboard is initialized from the region file within the config .txt file. The time steps are then iterated through, and growth pertaining to each zone is applied.
 * -# Residential growth: The residential class handles the growth and updating of residential ('R') cells on the gameboard. The growth process is handled in regards to sorting conditions, zone rules, considerations of population count, adjacency to powerlines, and characteristic of neighboring cells. The residential zone supplies workers to the commercial and industrial zones.
 * -# Industrial growth: The industrial class handles the growth and updating of industrial ('I') cells on the gameboard. The industrial class takes workers from the residential class, and produces goods. The commercial zone uses these goods to assign workers and goods to jobs. The industrial zone also produces pollution that can spread to other zones.
 * -# Commercial growth: The commercial class handles the growth and updating of commercial ('C') cells on the gameboard. The commercial class takes workers and goods from the residential and industrial classes.
 * -# Pollution functionality: The pollution functionality takes the pollution count from the industrial zones and disperses it to adjacent cells on the gameboard at a rate of pollution-1 per adjacency advancement.
 * -# Output: The output functionality loops through the timesteps, and stops when timesteps or growth end - whichever happens first. The map is outputted in its initial state, as growth is applied, and finally when simulation ends. Population and pollution maps are both displayed, along with totals of workers, goods, population, and pollution. Coordinates can also be analyzed.
 *
 */

 /*
 notes for wiki

 For the high-level description page, the team must provide a brief description of each of the major functionality components,
 how they work together, and some of the major data structures across the entire project. This information should not be
 copied and pasted from the project instructions. The page must also contain a diagram of the entire system, based on the one
 created during recitations. The diagram must be created digitally (i.e. using PowerPoint, Photoshop, Paint.net, UMLet, etc.),
 must be easy to read and understand, and cannot be a photographed or scanned image.

 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>   //refresh
#include <thread>   //refresh
#include "gameBoard.h"
#include "Residential.h"
#include "Commercial.h"
#include "Industrial.h"
#include "unitTesting.h"
#include "Cell.h"
#include "Hospital.h"
#include "firstResponse.h"
#include "Season.h"
#include "Tornado.h"

/** \page zone0_page Input
 * Handled by: Ronil Doshi
 * Written by: Ronil Doshi
 *
 * \section purpose Purpose:
 *
 * The initializer runs at the start of the simulation to read data from the configuration file and generate the game board from the inputted data.
The initial game data is located in a CSV file which is referenced in the configuration file. An ifstream object reads the configuration file to determine the initial timestep, refresh rate, and game-data file. A 1-1 copy of the CSV file is stored in an array of vectors, and the data on the csv file determines the starting type of the array cell that is created.

 *
 * \section data_storage Data Storage:
 *
 * The initial game data is stored in a csv file which is referenced in the config file. When the game data is read, the board is initialized as a 2d vector of cell objects.
 *
 * \section functionality Functionality Component:
 *
 * The initializer reads the config file with an ifstream object. The csv file is parsed for its cell data using the comma as the delimiter. The cell’s type is initialized according to the value in the CSV file and it’s population, pollution, worker count, inter alia, are initialized to zero until the simulation is run.
 *
 */

int main()
{
    int mode = 0;   //0 for regular sim, 1 for unit testing
    std::ifstream readFile;
    std::ifstream regionFile;
    std::string configFileName, regionFileName;
    int timeSteps, refreshRate;
    bool tornadoSpawn = false;

    std::cout << "Enter mode (0 for regular sim, 1 for unit testing mode): ";
    std::cin >> mode;

    if (mode == 1)
    {
        std::cout << "Now in unit testing mode" << std::endl;
        regionFileName = "unitTestingMap.csv";

        regionFile.open(regionFileName);

        if(regionFile.is_open()){ //did file open?
            std::cout << "File opened" << std::endl;
        }
        else{
            //add a while loop to re-ask for the input if this case happens
            std::cout << "File did not open" << std::endl;
            return 1;
        }
        std::cout << "Initial state:" << std::endl;
        gameBoard current(regionFile);

        //manually adjust some population #'s

        //current.output();

        std::cout << "Finished testing state:" << std::endl;
        testResidentialGrowth();
        int userchoice;
std::cout << "Continue to main? (0 for yes, 1 to quit)" << std::endl;
std::cin >> userchoice;

// Flush the input buffer
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

if (userchoice == 0)
{
    std::cout << "Returning to main..." << std::endl;
}
else if (userchoice == 1)
{
    return 0;
}
else
{
    std::cout << "Invalid choice" << std::endl;
}


    }


    std::cout << "Enter the name of the config file: ";
    // filename = "C:\\Users\\ronil\\Documents\\CSCE_2110\\SimCity_Project1\\SimCity_Project1\\region1.csv";
    std::cin >> configFileName;

    readFile.open(configFileName);

    if(readFile.is_open()){ //did file open?
        std::cout << "File opened" << std::endl;
    }
    else{
        //add a while loop to re-ask for the input if this case happens
        std::cout << "File did not open" << std::endl;
        return 1;
    }

    std::getline(readFile, configFileName, ':');
    readFile >> regionFileName; //reads in region.csv

    std::getline(readFile, configFileName, ':');
    readFile >> timeSteps; //reads in timestep #

    std::getline(readFile, configFileName, ':');
    readFile >> refreshRate; //reads in refresh rate #



    std::cout << "Now opening: " << regionFileName << std::endl;

    //open the region file.csv
    regionFile.open(regionFileName);

    if(regionFile.is_open()){ //did file open?
        std::cout << "File opened" << std::endl;
    }
    else{
        //add a while loop to re-ask for the input if this case happens
        std::cout << "File did not open" << std::endl;
        return 1;
    }

    gameBoard current(regionFile);

    std::cout << std::endl << "Initial region state:" << std::endl;
    current.output();
    std::cout << "Total timesteps: " << timeSteps << std::endl;
    std::cout << "Refresh rate: " << refreshRate << std::endl;

    //keeping timestep count
    int currentTimeStep = 0;

    //use residential class
    Commercial commercial(current);
    Industrial industrial(current);
    Residential residential(current);
    Hospital hosp(current);
    firstResponse firstResponse(current);
    Season seasons;

    //looping through timesteps
     for (int i = 0; i < timeSteps; i++)
    {
        int currentLoopPop = 0;

        for (int row = 0; row < current.getHeight(); ++row)
            {
                for (int col = 0; col < current.getWidth(); ++col)
                {
                    //calculate the current loop population
                    currentLoopPop += current.getCellPopulation(row, col);
                }
            }

        //prioritize commercial -> industrial -> residential growth
        commercial.growCommercial(current);
        industrial.IndustrialGrowth(current);
        residential.growResidential(current);
        if (!tornadoSpawn){
            tornadoCheck(current, tornadoSpawn);
        }
        hosp.HospitalGrowth(current);
        hosp.patientsfromPollution();
        hosp.calculateTreatmentEffect();
        firstResponse.checkCoverage(current);
        

        int totalLoopPop = 0;

    for (int row = 0; row < current.getHeight(); ++row)
    {
        for (int col = 0; col < current.getWidth(); ++col)
        {
            //calculate the current loop population after growth is applied
            totalLoopPop += current.getCellPopulation(row, col);
        }
    }

    //calculate the change in population from timestep to timestep
    int populationChange = totalLoopPop - currentLoopPop;

    //display population increase
    std::cout << "Population increased by: " << populationChange << std::endl;

        //increment timestep count as the loop goes
        currentTimeStep++;

         //break the loop if populationChange is 0
        if (populationChange == 0)
        {
            //print the map one last time to show that there is no growth
            current.output();
            std::cout << std::endl << "[ Population change is 0. Exiting simulation. ]" << std::endl;
            std::cout << "Total timesteps: " << currentTimeStep << std::endl;
            break;
        }


/** \page zone6_page Output
 *
 * \section purpose Purpose:
 *
 * The purpose of the output is to present the states of the simulated region at each timestep, as well as the final state of the simulation. This includes the final state of the region, the populations of the zones, the total pollution in the region, and the final pollution state. The growth requirement for the simulation is implemented, which halts the simulation once there is no growth between subsequent timesteps. The user is given the choice of analyzing a specific area of the region, which too will output final population and pollution values, but only for the user-specified area.
 *
 * \section data_storage Data Storage:
 *
 * Data for the output relies on the completed simulation data and five integer counter variables, that keep track of total population (totPop), population in each zone (resPop, indPop, comPop), and for total pollution (pollution). This component relies on output and get functions from Cell and Gameboard, such as output, outputPollutionMap, getCellPopulation and Pollution, getHeight, and getWidth. These functions are called from "current", the gameboard used during the simulation. The output functions are used to output the final states of the entire region after completing the simulation, presenting both the final population state and a separate grid for the final pollution state of the region. The getHeight and Width funcitons are used during both the loop for the final total output, in which it prevent the loop from extending out of bounds, and for the user-specified region, where they are compared to the user inputted coordinates, which are similarily tested to see if they are out of bounds. The functions, getCellPopulation and Pollution, are utilized to add and assign to the population and pollution counters. These counters are incremented through a similar loop as the growth funcitons, which uses a nested for loop (for (i) { for (j) {}}) to search through the 2D gameboard and to access the specific cell coordinates (i, j). The counters are incremented if the specific conditions are met. For pollution and total population, there are no conditions and these counters are incremented during each step of the loop (totPop += current.getCellPopulation(i,j) / pollution += current.getCellPollution(i,j)). The three zone population counters are incremented when the getCellType funciton returns their specific character type (R, I, or C), where they are incremented in the same manner as total population and pollution. Once the loop is completed, the final values of these counters are output. For the user-input bounds to analyze, a menu is output to prompt user to continue or exit the program. If the user continues, they are prompted for two coordiante pairs, which correspond to the top left and bottom right coordinate pairs of the region they are analyzing. This prompt is done in a loop, where the user-coordiantes are checked for errors. These errors include if the end coordinate is behind the beginning coordinate, if the initial coordinates are less than (0,0),  and if the end coordinates are out of bounds of the inital region. Then the counters are reset to zero, and the same loop as before is ran, except from the inital coordiantes to the final coordinates, rather than from (0,0) to (getHeight, getWidth). The counters are output as the regional zone population and pollution.
 *
 * \section functionality Functionality Component:
 *
 * The functionality of the output is to present the data that was generated during the simulation of the city in a proper manner, as well as implement the user-input desired area search functionality. As the simulation is looping, the changes in population are recorded and output at each timestep. The current state of the entire board is output at each timestep as well. As the population of a cell grows, the way it is output changes, replacing the character representation for the population of that cell. This is done during the loop by chekcing if the cell's population is greater than zero, and if so, it is output instead of the character. The output of the region is stored on the Gameboard named "current", which is the state of the simulation at the current timestep. Counters for the population and pollution output are declared as integer variables. As the simulation is looping, the population is being checked if it stops growing, as this requires that the simulation must stop. This is done by comparing the total population calculated up to where the simulation is currently to the population at the current timestep. If the difference between the total and current population is equal zero, the simulation is halted. Once the simulation halts and the current gameboard is output, these counters are reset to zero. The purpose of this is to allow for the analysis of the user-input region to have fresh counters set to zero. For the user desired area, four integer variables are declared to store the two coordinate pairs that are the upper-left and lower-right corners of the desired area. These variables are x1, x2, y1, and y2, which as ordered pairs are (x1, y1) and (x2, y2). A boolean variable "success" is used to ensure that the user-input does not result in an error. If an error is detected in the input, the user is prompted to re-input the coordinates, and if it does not detect an error, the success boolean is set to true and the prompt loop ends. The user desired area output is generated similarly to the total area output, but instead of outputting the specific region for each time step, the final population and pollution values are output for that region.
 *
 * <br>
 * @image html _sim_city___project1_8cpp__incl.png
 */


        current.output();

        seasons.setSeason(currentTimeStep);
        seasons.seasonChange(current, currentTimeStep);
        seasons.printSeasonImpact(current);

        std::cout << std::endl << "At time step: " << currentTimeStep << "/" << timeSteps << std::endl;
        std::cout << "Current Worker Count: " << current.getWorkerCount() << std::endl;
        std::cout << "Current Goods Count: " << current.getGoodsCount() << std::endl;
        hosp=Hospital(current);
    }

     current.pollutionGrowth();

     current.outputPollutionMap();

    int totPop = 0;
    int resPop = 0;
    int indPop = 0;
    int comPop = 0;
    int pollution = 0;
    int hospCount = 0;

    // gets pop count for total/zones and pollution count

    for (int i = 0; i < current.getHeight(); ++i) {
        for (int j = 0; j < current.getWidth(); ++j) {

            totPop += current.getCellPopulation(i, j);      //total
            pollution += current.getCellPollution(i,j);     //pollution

            if (current.getCellType(i,j) == 'R'){           //residential
                resPop += current.getCellPopulation(i, j);
            }

            else if(current.getCellType(i,j) == 'I'){       //industrial
                indPop += current.getCellPopulation(i, j);
            }

            else if(current.getCellType(i,j) == 'C'){       //commercial
                comPop += current.getCellPopulation(i, j);
            }

        }
    }

    std::cout << std::endl
    << "Total Pollution : " << pollution << std::endl << std::endl  // output total pollution
    << "===Final Populations===\n\n"
    << "Total Population : " << totPop << std::endl                 // output population of total,residential,commercial,industrial
    << "Residential Population : " << resPop << std::endl
    << "Industrial Population : " << indPop << std::endl
    << "Commercial Population : " << comPop << std::endl <<hospCount <<std::endl <<std::endl;
    hosp.printHospitalData();
    std::cout << endl;
    firstResponse.printCoverage(current);


    //initialize menu
    char choice;


    do {
        std::cout << "a. Choose coordinates to analyze" << std::endl;
     std::cout << "q. Quit program" << std::endl;

     std::cin >> choice;

    if (choice == 'q')
    {
        std::cout << std::endl << "Quitting the program..." << std::endl;
        return 0;
    }


    // prompt new bounds (i, j) to analyze
    int x1, x2, y1, y2; // rectangular area to analyze (x1, y1) through (x2, y2)
    bool success; // bool to check if loop needed

        std::cout << "Enter region to analyze:\n\n";

        do{

            std::cout << "Entering initial coordinates:\n" << "X1: ";
            std::cin >> x1;
            std::cout << "Y1: ";
            std::cin >> y1;
            std::cout << "Entering final coordinates:\n" << "X2: ";
            std::cin >> x2;
            std::cout << "Y2: ";
            std::cin >> y2;
            std::cout << "You entered: (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")\n";

            if (x2 < x1 || y2 < y1 || x1 < 0 || y1 < 0 || x2 > current.getWidth() || y2 > current.getHeight()){ // checks if lower is greater, if upper is behind (0,0),
                std::cout << "Error! Bounds improperly set! Please try again.\n";
                success = false;
            }                                                                                                   // or lower is outside of original, all of which will return failure
            else {
                success = true;
            }
        } while (success != true);


        totPop = 0; //resets counters for new region analysis
        resPop = 0;
        indPop = 0;
        comPop = 0;
        pollution = 0;

        for (int i = x1; i < x2; ++i) {
            for (int j = y1; j < y2; ++j) {


            totPop += current.getCellPopulation(i, j);      //total
            pollution += current.getCellPollution(i,j);     //pollution

            if (current.getCellType(i,j) == 'R'){           //residential
                resPop += current.getCellPopulation(i, j);
            }

            else if(current.getCellType(i,j) == 'I'){       //industrial
                indPop += current.getCellPopulation(i, j);
            }

            else if(current.getCellType(i,j) == 'C'){       //commercial
                comPop += current.getCellPopulation(i, j);
            }

        }
    }

    std::cout << std::endl
    << "Total Regional Pollution : " << pollution << std::endl  // output regional pollution
    << "Total Population : " << totPop << std::endl                 // output regional population of total,residential,commercial,industrial
    << "Residential Population : " << resPop << std::endl
    << "Industrial Population : " << indPop << std::endl
    << "Commercial Population : " << comPop << std::endl << std::endl;
    hosp.printHospitalData();
    std::cout << std::endl;
    firstResponse.printCoverage(current);
    } while (choice != 'q');

return 0;

}
