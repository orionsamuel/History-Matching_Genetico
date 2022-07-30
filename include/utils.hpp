#include <string>

using namespace std;

const string inputOil = "../Input/oleo/oleo";
const string inputWater = "../Input/agua/agua";
const string inputGas = "../Input/gas/gas";
const string simulationFile = "../Input/SPE9.DATA";
const string fileName = "SPE9";
const string permeabilityFile = "PERMVALUES.DATA";

#define SIZE_POPULATION 150
#define N_GENERATIONS 15

#define CROSSOVER_RATE 80
#define MUTATION_RATE 50

#define MIN_POROSITY 0.1
#define MAX_POROSITY 0.3

#define MIN_PERMEABILITY 0.0
#define MAX_PERMEABILITY 800.0

#define WATER_WEIGHT 0.2
#define OIL_WEIGHT 0.5  
#define GAS_WEIGHT 0.3

#define TOTAL_CELLS 24 * 25 * 15    

#define N_PERMEABILITY 3
#define N_POROSITY 15


#define N_METRICS 3

struct individual{
    double porosity[N_POROSITY];
    double permeability[TOTAL_CELLS];
    double error_rank;
};

struct result{
    double water;
    double oil;
    double gas;
};

struct mutationValue{
    double porosity;
    double permeability;
};