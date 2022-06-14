#include "../include/genetic.hpp"

genetic_algorithm::genetic_algorithm(){
    srand (time(0));
}

genetic_algorithm::~genetic_algorithm(){

}

void genetic_algorithm::FirstPopulation(){
    srand((unsigned)time(0));

    CreateResultDir(0);
    
    for(int i = 0; i < SIZE_POPULATION; i++){
        const char* cpInputFile = Command("cp "+simulationFile+" ../Output/0/"+to_string(i)+".DATA");
        system(cpInputFile);
    }

    individual initPopulation;

    for(int i = 0; i < N_PERMEABILITY; i++){
        initPopulation.permeability_x[i] = 0;
        initPopulation.permeability_y[i] = 0;
        initPopulation.permeability_z[i] = 0;
    }

    for(int i = 0; i < SIZE_POPULATION; i++){
        this->population[i].porosity = 0;
        this->population.push_back(initPopulation);
        this->population[i].error_rank = 0;
    }

    for(int i = 0; i < SIZE_POPULATION; i++){
        for(int j = 0; j < N_PERMEABILITY; j++){

        }
    }

    
}

void genetic_algorithm::Init(){
    CreateOutputDir();

    string waterInputResult = ReadFileInput(inputWater);
    string oilInputResult = ReadFileInput(inputOil);

    realResults = ConvertStringInputToDoubleResult(waterInputResult, oilInputResult);

    FirstPopulation();
    int count = 1;
    while(count < N_GENERATIONS){
        OtherPopulations(count);
        count++;
    }

}

