#include <iostream>
#include<string>
#include"Season.h"
#include"gameBoard.h"

using namespace std;

/*The season class is meant to generate a new season summer, fall, winter and spring, based on the time steps. The program is meant to go all the way to time step 20, every season might not be displayed when compile.

Summer season is displayed when time step are from 1 to 5, spring from 6 to 10, fall from 11 to 15, and winter from 16 to 20.
In the game summer is considered to be the most productive season so during summer new workers are added for every 3 previous workers. For Spring and fall we consider it a pretty steady season so it doesn't change unless the workers count have increase. we consider winter a low productivity season so workers and goods decreased.
*/

//Constructor set default values
Season::Season(){
        seasons = "SPRING";
        newGoodsCount = 0;
        newWorkerCount = 0;
        addedGoods = 0;
        addedWorkers = 0;
}

//setSeason to generate seasons according the the time step
void Season:: setSeason(int currentTimeStep){
        if(currentTimeStep >= 1 && currentTimeStep <=5){
                seasons = "SUMMER";
        }
        else if(currentTimeStep >= 6 && currentTimeStep <= 10) {
            seasons = "SPRING";
        }
        else if(currentTimeStep >= 11 && currentTimeStep <= 15) {
            seasons = "FALL";
        }
        else if(currentTimeStep >= 16 && currentTimeStep <= 20) {
            seasons = "WINTER";
        }
}
string Season:: getSeason()const{
        return seasons;
}


//this function set the conditions for seasons change
void Season::seasonChange(gameBoard& current, int currentTimeStep){

	int currWorkerCount = current.getWorkerCount();
	int currGoodsCount = current.getGoodsCount();

         if(seasons == "SPRING"){
                cout<<ANSI_COLOR_GREEN<<"THE CURRENT SEASON IS SPRING"<<ANSI_COLOR_RESET<<endl;;

                if(currentTimeStep >= 6 && currentTimeStep <=7){
                        newGoodsCount = 1 + currGoodsCount;
                        current.setGoodsCount(newGoodsCount);
                }
                else if(currentTimeStep >= 8 && currentTimeStep <=10){
                        newGoodsCount = 2 + currGoodsCount;
                        current.setGoodsCount(newGoodsCount);
                }

        }

         else if(seasons == "SUMMER"){
                cout<<ANSI_COLOR_YELLOW<<"THE CURRENT SEASON IS SUMMER"<<ANSI_COLOR_RESET<<endl;

                newWorkerCount = currWorkerCount + (currWorkerCount/3);
                current.setWorkerCount(newWorkerCount);


                newGoodsCount = currGoodsCount + (currGoodsCount/2);
                current.setGoodsCount(newGoodsCount);

        }


else if(seasons == "FALL"){
                cout<<ANSI_COLOR_ORANGE<<"THE CURRENT SEASON IS FALL"<<ANSI_COLOR_RESET<<endl;

                newGoodsCount = currGoodsCount + 1;
                current.setGoodsCount(newGoodsCount);
        }

        else if(seasons == "WINTER"){
 cout<<"THE CURRENT SEASON IS WINTER"<<endl;

                newWorkerCount = currWorkerCount - (currWorkerCount/3);
                current.setWorkerCount(newWorkerCount);

                newGoodsCount = currGoodsCount - (currGoodsCount/2);
                current.setGoodsCount(newGoodsCount);

        }
        cout<<endl;
        cout<<"Previous worker count: "<<currWorkerCount<<endl;
        cout<<"Previous goods count: "<<currGoodsCount<<endl;


}
//this function prints out the season impacts
void Season:: printSeasonImpact(gameBoard& current){
        cout<<"---Season Impact---"<<endl;

        int currWorkerCount = current.getWorkerCount();
        int currGoodsCount = current.getGoodsCount();
        if (seasons == "SPRING"){
                addedGoods = newGoodsCount - currGoodsCount;
                cout << "Good count may increase" << endl;
        }

        else if (seasons == "SUMMER"){
                addedWorkers = newWorkerCount - currWorkerCount;
                addedGoods = newGoodsCount - currGoodsCount;

                cout << "New workers added" << endl;
                cout << "Good count increase" << endl;
    }
        else if (seasons == "FALL"){

                addedGoods = newGoodsCount - currGoodsCount;
                cout << "Good count increase" << endl;
    }
        else if (seasons == "WINTER"){

                int removedWorkers = currWorkerCount - newWorkerCount;
                int removedGoods = currGoodsCount - newGoodsCount;
                cout << "Worker removed" << endl;
                cout << "Goods may decreased" << endl;
    }
}

