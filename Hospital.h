#ifndef HOSPITAL_H_INCLUDED
#define HOSPITAL_H_INCLUDED


#include <string>
#include"gameBoard.h"

class Hospital {
private:
    //removing int size it's not needed because I will use capacity and pollution level to determine treated patients
    int capacity;
    int treatedPatients;
    int pollutionLevel;  // Pollution level in the hospital's vicinity
    float treatmentEffect;

public:
    
   
    Hospital(gameBoard& hospital);//gameboard hospital constructor
    void HospitalGrowth(gameBoard& hospital);

    void patientsfromPollution(); //used to calculate patients that need to be treated 6 patients to be treated per 1 pollution count.

    void treatPatients(int patients);//number of patients treated + the 6 patients per pollution or the available capacity value treated

    void calculateTreatmentEffect();//calculates the effect of treating patients with current pollution level on the initial treatment effect = 100.  

    void printHospitalData();//outputs capacity, treatedPatients, pollutionLevel, and treatmentEffect
};




#endif // HOSPITAL_H_INCLUDED
