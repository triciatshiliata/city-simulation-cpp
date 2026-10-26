#ifndef TORNADO_H
#define TORNADO_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "gameBoard.h"
#include "Cell.h"

class gameBoard;
class Cell;


void tornadoCheck(gameBoard& board, bool& tornadoSpawn);
void tornadoSimulation(gameBoard& b, int lt, int xt, int yt, bool& spawned);



#endif


