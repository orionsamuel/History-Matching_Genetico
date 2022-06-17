#include <string>

using namespace std;

const string inputOil = "../Input/oleo.txt";
const string inputWater = "../Input/agua.txt";
const string simulationFile = "../Input/SPE1CASE1.DATA";
const string fileName = "SPE1CASE1";


#define SIZE_POPULATION 100
#define N_GENERATIONS 10

#define CROSSOVER_RATE 80
#define MUTATION_RATE 50

#define MIN_POROSITY 0.1
#define MAX_POROSITY 0.3

#define MIN_PERMEABILITY 50.0
#define MAX_PERMEABILITY 500.0

#define WATER_WEIGHT 0.6
#define OIL_WEIGHT 0.4

#define N_PERMEABILITY 3
#define TOTAL_CELLS 300

#define N_METRICS 2

struct individual{
    double porosity;
    double permeability_x[N_PERMEABILITY];
    double permeability_y[N_PERMEABILITY];
    double permeability_z[N_PERMEABILITY];
    double error_rank;
};

struct result{
    double water;
    double oil;
};

struct mutationValue{
    double porosity;
    double permeability_x;
    double permeability_y;
    double permeability_z;
};


