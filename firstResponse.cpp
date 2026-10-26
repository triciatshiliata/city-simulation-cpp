#include "firstResponse.h"
#include <ctime>


// added commit message 

firstResponse::firstResponse(gameBoard& board) {

	interval = 2;
	populatedList = getPopulatedList(board);
	

}

vector<std::pair<int, int>> firstResponse::getPopulatedList(gameBoard& board) { // Creates a list of all Residential, Industral, and Commercial tiles so it can be randomly selected from.
	vector<vector<Cell>> layout = board.getLayout();

	vector<std::pair<int, int>>  relevantTiles;

	for (int i = 1; i < layout.size()-1; i++)
	{
		for (int j = 1; j < layout[i].size()-1; j++)
		{
			if (layout[i][j].getType() == 'R' || layout[i][j].getType() == 'C' || layout[i][j].getType() == 'I')
			{
				relevantTiles.emplace_back(i, j);
			}
		}
	}

	
	return relevantTiles;
}

void firstResponse::checkCoverage(gameBoard& board) { // this function checks three random populated tiles for nearby emergency services tiles

	
		

		vector<vector<Cell>> layout = board.getLayout();
		bool sufficient = false;

		std::pair<int, int> checkCell; // the current pair of coordinates to be tested


		int scanCounter = 3;
		bool foundSurroundedTile = false; // first, find a tile surrounded on all sides by I, R, or C tiles; such tiles will also be one of the three


		while (scanCounter > 0) {

			scanCounter--;


			while (!foundSurroundedTile) // repeat till a surrounded tile is found
			{
				checkCell = populatedList[rand() % populatedList.size()]; // pick a random coordinate from the populated list

				foundSurroundedTile = true; // assume its surrounded

				if (layout[checkCell.first - 1][checkCell.second].getType() == '-' && layout[checkCell.first - 1][checkCell.second].getType() == ' ')
				{
					foundSurroundedTile = false;
				}
				if (layout[checkCell.first + 1][checkCell.second].getType() == '-' && layout[checkCell.first + 1][checkCell.second].getType() == ' ')
				{
					foundSurroundedTile = false;
				}
				if (layout[checkCell.first][checkCell.second + 1].getType() == '-' && layout[checkCell.first][checkCell.second + 1].getType() == ' ')
				{
					foundSurroundedTile = false;
				}
				if (layout[checkCell.first][checkCell.second - 1].getType() == '-' && layout[checkCell.first][checkCell.second - 1].getType() == ' ')
				{
					foundSurroundedTile = false;
				}
				// and if it is not surrounded, run the loop again
				
			}

			// cout << "Found surrounded tile @ " << checkCell.first << "," << checkCell.second << endl;

			for (int i = checkCell.first - 3; i < checkCell.first + 3; i++) // this subscan checks if the surrounded tile has emergency services in a 7x7 area around it
			{
				for (int j = checkCell.second - 3; j < checkCell.second + 3; j++)
				{
					if ((i > 0 && i < layout.size()) && (j > 0 && j < layout[i].size()))
					{
						if (layout[i][j].getType() == 'F')
						{
							sufficient = true; // if it DOES, try again if you haven't already tried 3 times this timestep. 

							i = 1000; // dirty way to break the double loop
							j = 1000;
						}

					}
				}
			}

			if (!sufficient) // but if it DOESNT, build a new emergency station
			{
				cout << "Building new emergency station" << endl;

				unsigned seed = time(0);
				srand(seed);

				int x;
				int y;


				do {
					x = rand() % layout.size();
					y = rand() % layout[x].size();
					
				} while (layout[x][y].getType() != ' ');


				layout[x][y] = Cell('F');
				board.incrementWorkerCount();
				cout << "Emergency station constructed @ (" << x << "," << y << "). Unemployment fell by 1.\n";
				board.setLayout(layout);
				return;
			}
		} // and repeat this process until you find an inadequate tile, or you check three different tiles.
	
	
		cout << "Quarterly report showed coverage is adequate\n";
		
		
}
	

void firstResponse::printCoverage(gameBoard& board) {
	vector<vector<Cell>> layout = board.getLayout();

	int numStations = 0;
	int pop = 0;

	for (int i = 0; i < layout.size(); i++)
	{
		for (int j = 0; j < layout.size(); j++)
		{
			if (layout[i][j].getType() == 'F') numStations++;
			pop += layout[i][j].getPopulation();
		}
	}

	cout << "There are " << numStations << " first response stations.\nRatio of population to number of service stations is: " << pop / numStations << endl;

	if (pop / numStations > 6)
	{
		std::cout << "Crime and fires are rampant in the city." << endl;
	}
	else {
		std::cout << "Residents are happy with emergency services and feel proud of their safety." << endl;
	}
}
