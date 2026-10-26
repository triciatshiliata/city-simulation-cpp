#include<iostream>
#include"Hospital.h"
#include"gameBoard.h"
#include"Cell.h"

using namespace std;

Hospital::Hospital(gameBoard& hospital){
	capacity = hospital.CalculateTotalPollution() * 6; // 6 rooms in hospital per pollution count;
	treatedPatients=0;//number of treated patients initialized to zero
	pollutionLevel = hospital.CalculateTotalPollution(); // pollution = hospital total pollution
	treatmentEffect = 0.0; // treatment effect initialized to zero
}


void Hospital::HospitalGrowth(gameBoard& hospital){//Hospital growth function
	vector<vector<Cell>> newLayout = hospital.getLayout();
	vector<pair<int, int>>eligibleCells;
	int hospitalCount = 0;
	int pollutionCount = hospital.CalculateTotalPollution();

	if(pollutionCount > 5 && pollutionCount < 8){
	for(int i=0; i<hospital.getHeight(); i++){
		for(int j=0; j<hospital.getWidth(); j++){

			if(newLayout[i][j].getType() == ' '){
				newLayout[i][j].setType('H');
				hospitalCount++;
				hospital.setLayout(newLayout);
				cout<<"Pollution count: "<<pollutionCount<<endl;
				cout<<"Number of City Hospital is: "<<hospitalCount<<endl;
				pollutionLevel=pollutionCount;
				return;
			}
		}
	}
	}

}


void Hospital::patientsfromPollution(){//calculates number of patients using pollution level
	int patients= pollutionLevel*6;// 6 patients per 1 pollution count
	treatedPatients=treatedPatients+patients;
	treatPatients(patients);//patients calculated is used in the treatPatients function
}
void Hospital::treatPatients(int patients){//determines priority of patient treatment based on how much capacity is left over.
	int patientsTreated;
	int capacityLeft = capacity - treatedPatients;
		if (capacityLeft>=patients){//if capacity left over is more than patients, patients treated = patients else patients treated = capacity left over.
			patientsTreated=patients;
		}
		else{
			patientsTreated = capacityLeft;
		}
	treatedPatients=treatedPatients+patientsTreated;

}
void Hospital::calculateTreatmentEffect(){
	float initial = 100.0; //initial treatment effect without pollution = 100
	int maxpollutionLevel = 8; //max of pollution for hospital from hospital growth conditions
	float treatmentRate = ((initial)/ (maxpollutionLevel*6)); //treatment rate = initial/maxpollution*6

	treatmentEffect = initial-(pollutionLevel*treatmentRate);//treatment effect = initial - (pollutionlevel*rate)
	//treatment effect can't be negative
	if (treatmentEffect<0){//if treatment effect is less than 0, treatment effect = 0
		treatmentEffect = 0;
	}

}
void Hospital::printHospitalData(){//output hospital capacity, pollution level, treated patients, and treatment effect
	cout<<"Hospital capacity: "<<capacity<<endl;
	cout<<"Pollution level: "<<pollutionLevel<<endl;
	cout<<"Patients Treated: "<<treatedPatients<<endl;
	cout<<"Treatment effect: "<<treatmentEffect<<endl;
}
