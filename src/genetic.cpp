#include "../include/genetic.hpp"

genetic_algorithm::genetic_algorithm(){
    srand (time(0));
}

genetic_algorithm::~genetic_algorithm(){

}

void genetic_algorithm::CreateOutputDir(){
    DIR* dp = opendir("../Output/");

    if(dp == NULL){
        system("mkdir ../Output/");
    }else{
        system("rm -r -f ../Output/*");
    }
}

string genetic_algorithm::ReadFileInput(string file){
    ifstream fileStream(file, ios::in);
    
    string line, content;

    while(!fileStream.eof()){
        getline(fileStream, line);
        content += line;
        content += " ";
    }

    fileStream.close();

    return content;
}

result* genetic_algorithm::ConvertStringInputToDoubleResult(string water, string oil){
    vector<string> waterSplit{split(water, ' ')};
    vector<string> oilSplit{split(oil, ' ')};

    result* results = new result[water.size()];

    for(int i = 0; i < waterSplit.size(); i++){
        this->realResults[i].water = stod(waterSplit[i]);
        this->realResults[i].oil = stod(oilSplit[i]);
    }

    return results;

}

const char* genetic_algorithm::Command(string inputCommand){
    const char* command = (char*) inputCommand.c_str();

    return command;
}

void genetic_algorithm::CreateResultDir(int idIteration){
    string command = "../Output/"+to_string(idIteration);
    const char* file = (char*) command.c_str();
    DIR* dp = opendir(file);

    if(dp == NULL){
        const char* mkdirIteration = Command("mkdir ../Output/"+to_string(idIteration));
        system(mkdirIteration);
        const char* mkdirWater = Command("mkdir ../Output/"+to_string(idIteration)+"/agua");
        system(mkdirWater);
        const char* mkdirOil = Command("mkdir ../Output/"+to_string(idIteration)+"/oleo");
        system(mkdirOil);
    }else{
        const char* rm =Command("rm -f ../Output/0/*");
        system(rm);
    }
}

void genetic_algorithm::FirstPopulation(){
    srand((unsigned)time(0));

    CreateResultDir(0);
    
    for(int i = 0; i < SIZE_POPULATION; i++){
        const char* cpInputFile = Command("cp "+simulationFile+" ../Output/0/"+to_string(i)+".DATA");
        system(cpInputFile);
    }

    individual initPopulation;

    for(int i = 0; i < 3; i++){
        initPopulation.porosity[i] = 0;
        initPopulation.permeability_x[i] = 0;
        initPopulation.permeability_y[i] = 0;
        initPopulation.permeability_z[i] = 0;
    }

    for(int i = 0; i < SIZE_POPULATION; i++){
        population.push_back(initPopulation);
        population[i].error_rank = 0;
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

