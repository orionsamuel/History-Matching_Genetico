#include "../include/genetic.hpp"

genetic_algorithm::genetic_algorithm(){
    srand (time(0));
}

genetic_algorithm::~genetic_algorithm(){

}

void genetic_algorithm::FirstPopulation(){
    srand((unsigned)time(0));
    
    CreateResultDir(0);

    individual chromosome;

    for(int i = 0; i < N_POROSITY; i++){
        chromosome.porosity[i] = 0;
    }
    for(int i = 0; i < TOTAL_CELLS; i++){
        chromosome.permeability[i] = 0;
    }

    for(int i = 0; i < SIZE_POPULATION; i++){
        this->population.push_back(chromosome);
        this->population[i].error_rank = 0;
    }


    for(int i = 0; i < SIZE_POPULATION; i++){
        for(int j = 0; j < N_POROSITY; j++){
            this->population[i].porosity[j] = Rand_double(MIN_POROSITY, MAX_POROSITY);
            for(int k = 0; k < TOTAL_CELLS; k++){
                this->population[i].permeability[k] = Rand_double(MIN_PERMEABILITY, MAX_PERMEABILITY);
            }
        }
    }

    system(Command("cp ../Input/TOPSVALUES.DATA ../Output/"+to_string(0)+"/TOPSVALUES.DATA"));
 
    for(int i = 0; i < SIZE_POPULATION; i++){
        WriteSimulationFile(0, i, simulationFile, fileName, permeabilityFile, population);
    }
    
    Simulation(0, fileName);
    Fitness(0);
    sort(begin(this->population), end(this->population), Compare);
    WriteErrorFile(0, population);

    for(int i = 0; i < SIZE_POPULATION; i++){
        WriteSimulationFile(0, i, simulationFile, fileName, permeabilityFile, population);
    }
      
}

void genetic_algorithm::OtherPopulations(int idIteration){
    Crossover();
    
    CreateResultDir(idIteration);

    for(int i = 0; i < SIZE_POPULATION; i++){
        system(Command("cp ../Output/"+to_string(idIteration-1)+"/"+to_string(i)+"-"+fileName+".DATA ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+fileName+".DATA"));
        system(Command("cp ../Output/"+to_string(idIteration-1)+"/"+to_string(i)+"-"+permeabilityFile+" ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+permeabilityFile));
    }

    system(Command("cp ../Input/TOPSVALUES.DATA ../Output/"+to_string(idIteration)+"/TOPSVALUES.DATA"));

    for(int i = SIZE_POPULATION; i < (SIZE_POPULATION + this->crossover_rate); i++){
        WriteSimulationFile(idIteration, i, simulationFile, fileName, permeabilityFile, population);
    }

    Simulation(idIteration, fileName);
    Fitness(idIteration);
    sort(begin(this->population), end(this->population), Compare);

    WriteErrorFile(idIteration, population);

    system(Command("rm -f ../Output/"+to_string(idIteration)+"/*.DATA"));

    while(SIZE_POPULATION < this->population.size()){
        this->population.pop_back();
    }

    for(int i = 0; i < SIZE_POPULATION; i++){
        WriteSimulationFile(idIteration, i, simulationFile, fileName, permeabilityFile, population);
    }

}

void genetic_algorithm::Fitness(int idIteration){
    if(idIteration == 0){
        for(int i = 0; i < SIZE_POPULATION; i++){
            string oilOutputResult = "../Output/"+to_string(idIteration)+"/oleo/"+to_string(i)+".txt";
            string waterOutputResult = "../Output/"+to_string(idIteration)+"/agua/"+to_string(i)+".txt";
            string gasOutputResult = "../Output/"+to_string(idIteration)+"/gas/"+to_string(i)+".txt";
            this->population[i].error_rank = activationFunction(waterOutputResult, oilOutputResult, gasOutputResult, realResults, idIteration, i);
        }
    }else{
        for(int i = SIZE_POPULATION; i < (SIZE_POPULATION + this->crossover_rate); i++){
            string oilOutputResult = "../Output/"+to_string(idIteration)+"/oleo/"+to_string(i)+".txt";
            string waterOutputResult = "../Output/"+to_string(idIteration)+"/agua/"+to_string(i)+".txt";
            string gasOutputResult = "../Output/"+to_string(idIteration)+"/gas/"+to_string(i)+".txt";
            this->population[i].error_rank = activationFunction(waterOutputResult, oilOutputResult, gasOutputResult, realResults, idIteration, i);
        }
    }
}

void genetic_algorithm::Crossover(){
    for(int i = 0; i < crossover_rate; i++){
        this->children[i].error_rank = 0;
        for(int j = 0; j < N_POROSITY; j++){
            this->children[i].porosity[j] = 0;          
        }
        for(int j = 0; j < TOTAL_CELLS; j++){
            this->children[i].permeability[j] = 0;
        }  
    }

    int percentPorosity = rand() % N_POROSITY - 1;
    int percentPermeability = rand() % TOTAL_CELLS - 1;
    int count = 0;
    while(count < crossover_rate){
        for(int i = 0; i < percentPorosity; i++){
            this->children[count].porosity[i] = this->population[count+1].porosity[i];

            this->children[count+1].porosity[i] = this->population[count].porosity[i];
        }
        cout << "Aqui" << endl;
        for(int i = 0; i < percentPermeability; i++){
            this->children[count].permeability[i] = this->population[count+1].permeability[i];
            
            this->children[count+1].permeability[i] = this->population[count].permeability[i];   
        }

        for(int i = percentPorosity; i < N_POROSITY; i++){
            this->children[count].porosity[i] = this->population[count].porosity[i];

            this->children[count+1].porosity[i] = this->population[count+1].porosity[i];
        }
        for(int i = percentPermeability; i < TOTAL_CELLS; i++){
            this->children[count].permeability[i] = this->population[count].permeability[i];
            
            this->children[count+1].permeability[i] = this->population[count+1].permeability[i];   
        }

        count = count + 2;
    }


    Mutation();

    for(int i = 0; i < crossover_rate; i++){
        for(int j = 0; j < N_POROSITY; j++){
            this->children[i].porosity[j] = floor(this->children[i].porosity[j] * 100) / 100;
        }
        for(int k = 0; k < TOTAL_CELLS; k++){
            this->children[i].permeability[k] = floor(this->children[i].permeability[k] * 100) / 100;
        }
    }

    for(int i = 0; i < this->crossover_rate; i++){
        this->population.push_back(children[i]);
    }
}

void genetic_algorithm::Mutation(){
    for(int i = 0; i < this->mutation_rate; i++){
        int genePorosity = rand() % N_POROSITY;
        int genePermeability = rand() % TOTAL_CELLS;
        int tunning = rand() % 2;

        mutationValue newValue;

        if(tunning == 0){
            newValue = RandMutationValue(this->children[i], genePorosity, genePermeability, true);
        }else{
            newValue = RandMutationValue(this->children[i], genePorosity, genePermeability, false);
        }

        this->children[i].porosity[genePorosity] = newValue.porosity;
        this->children[i].permeability[genePermeability] = newValue.permeability;
        
    }
}

void genetic_algorithm::Init(){
    CreateOutputDir();
    
    string oilInputResult = ReadFileInput(inputOil);
    string waterInputResult = ReadFileInput(inputWater);
    string gasInputResult = ReadFileInput(inputGas);
    
    realResults = ConvertStringInputToDoubleResult(waterInputResult, oilInputResult, gasInputResult);    
    
    FirstPopulation();
    int count = 1;
    while(count < N_GENERATIONS){
        OtherPopulations(count);
        count++;
    }

}

