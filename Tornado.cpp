#include "Tornado.h"

void tornadoCheck(gameBoard& board, bool& tornadoSpawn){
    
    
    
    
    int levelT = 0;
    int limT, xT, yT, temp;
    int pT = 0;

    for (int i = 0; i < board.getHeight(); i++){
        for (int j = 0; j < board.getWidth(); j++){
            pT = pT + board.getCellPollution(i,j);
        }
    }
    std::cout << "Tot Poll is : " << pT << std::endl;
    int zT = 0; // random number 0 - 99, if z <= lim, tornado spawned
    for (int i = 0; i < board.getHeight(); i++){
        for (int j = 0; j < board.getWidth(); j++){
            zT = rand() % 100;
             // random number 0 - 99, if z <= lim, tornado spawned
            
            if (pT == 0){
                levelT = 0;
                limT = 9; //9%
            }
            else if (pT < 4 && pT > 0){
                levelT = 1;  
                limT = 14; //12%
            }
            else if (pT < 8 && pT > 3){
                levelT = 2;    
                limT = 24; //25%
            }
            else if (pT > 7){
                levelT = 3;    
                limT = 32; //33%
            }


            if (zT<=limT){
                yT = j;
                xT = i;
                std::cout << "A level " << levelT << " tornado has spawned @ (" << xT << ", " << yT << ")!\n";
                tornadoSpawn = true;
                
                break;
            }
        }
        if (tornadoSpawn){
            tornadoSimulation(board, levelT, xT, yT, tornadoSpawn);
            break;
        }
    }
}

void tornadoSimulation(gameBoard& b, int lT, int xt, int yt, bool& spawned){
    
    std::vector<std::vector<Cell>> newLayout = b.getLayout();
    int direction, oldPop, temp;
    int popRed = 0;                                             //  7  0  1  
    direction = rand() % 8;                                     //  6     2   --> tornado directions
                                                                //  5  4  3
    if (lT > 0){
    switch(direction){                                          
        case (0):
            std::cout << "The tornado is traveling north!\n";      
            break;                                                   
        case (1):
            std::cout << "The tornado is traveling northeast!\n";
            break;
        case (2):
            std::cout << "The tornado is traveling east!\n";
            break;
        case (3):
            std::cout << "The tornado is traveling southeast!\n";
            break;
        case (4):
            std::cout << "The tornado is traveling south!\n";
            break;
        case (5):
            std::cout << "The tornado is traveling southwest!\n";
            break;
        case (6):
            std::cout << "The tornado is traveling west!\n";
            break;
        case (7):
            std::cout << "The tornado is traveling northwest!\n";
            break;
    }
    }
 
    // if lT == 0, length is zero.
    if (lT == 0){
        if (newLayout[xt][yt].getPopulation() > 0){
            newLayout[xt][yt].setPopulation(newLayout[xt][yt].getPopulation() - 1);
            popRed = popRed + 1;
        }
    }

    if (lT == 1){
        for (int i = 0; i < 3; ++i){ //length = 3
            if (newLayout[xt][yt].getPopulation() > 0){
                newLayout[xt][yt].setPopulation(newLayout[xt][yt].getPopulation() - 1);
                popRed = popRed + 1;
            }
            //if 0, (xt, --yt)
            //if 1, (++xt, --yt)
            //if 2, (++xt, yt)
            //if 3, (++xt, ++yt)
            //if 4, (xt, ++yt)
            //if 5, (--xt, ++yt)
            //if 6, (--xt, yt)
            //if 7, (--xt, --yt)

        switch(direction){                                          
            case (0):
                --yt; 
                break;                                                   
            case (1):
                ++xt;
                --yt;
                break;
            case (2):
                ++xt;
                break;
            case (3):
                ++xt;
                ++yt;
                break;
            case (4):
                ++yt;
                break;
            case (5):
                --xt;
                ++yt;
                break;
            case (6):
                --xt;
                break;
            case (7):
                --xt;
                --yt;
                break;
        }

        if (xt < 0 || yt < 0 || xt > b.getWidth() || yt > b.getHeight()){
            break;
        }
        } 
        
    }
    else if (lT == 2){
        for (int i = 0; i < 5; ++i){//length = 5
            oldPop = newLayout[xt][yt].getPopulation();
            if (newLayout[xt][yt].getPopulation() > 0){
                newLayout[xt][yt].setPopulation(newLayout[xt][yt].getPopulation() - 2);
                temp = newLayout[xt][yt].getPopulation();
                
                if(newLayout[xt][yt].getPopulation() < 0){
                    newLayout[xt][yt].setPopulation(0);
                    temp = newLayout[xt][yt].getPopulation();
                    oldPop = oldPop - temp;
                }
                oldPop = oldPop - temp;
                popRed = popRed + oldPop;
            }
        switch(direction){                                          
        case (0):
            --yt; 
            break;                                                   
        case (1):
            ++xt;
            --yt;
            break;
        case (2):
            ++xt;
            break;
        case (3):
            ++xt;
            ++yt;
            break;
        case (4):
            ++yt;
            break;
        case (5):
            --xt;
            ++yt;
            break;
        case (6):
            --xt;
            break;
        case (7):
            --xt;
            --yt;
            break;
        }

        if (xt < 0 || yt < 0 || xt > b.getWidth() || yt > b.getHeight()){
            break;
        }
        }
    }
    else if (lT == 3){
        for (int i = 0; i < 10; ++i){//length = 5
            oldPop = newLayout[xt][yt].getPopulation();
            
            newLayout[xt][yt].setPopulation(0);
            temp = newLayout[xt][yt].getPopulation();
                
            popRed = popRed + oldPop;
            
            switch(direction){                                         
                case (0):
                    --yt; 
                    break;                                                   
                case (1):
                    ++xt;
                    --yt;
                    break;
                case (2):
                    ++xt;
                    break;
                case (3):
                    ++xt;
                    ++yt;
                    break;
                case (4):
                    ++yt;
                    break;
                case (5):
                    --xt;
                    ++yt;
                break;
                case (6):
                    --xt;
                    break;
                case (7):
                    --xt;
                   --yt;
                    break;
                default:
                    break;
            }

            if (xt < 0 || yt < 0 || xt >= b.getWidth() || yt >= b.getHeight()){
                break;
            }  
        }
    }
    
    b.setLayout(newLayout);
    spawned = false;
    std::cout << "Total population reduced by tornado: " << popRed << "\n";
}

