#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <random>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cmath>
#include "utils.hpp"

using namespace std;

class functions{
    public:

    void Simulation(int idIteration);
    double Rand_double(double min, double max);
    double Max(double num1, double num2);
    double Min(double num1, double num2);
    const vector<string> split(const string& s, const char& c);
    void CreateOutputDir();
    string ReadFileInput(string file);
    result* ConvertStringInputToDoubleResult(string water, string oil);
    const char* Command(string inputCommand);
    void CreateResultDir(int idIteration);
    void WriteSimulationFile(int idIteration, string inputFile, vector<individual> population);

    static bool Compare(const individual n, const individual m){
        return n.error_rank < m.error_rank;
    }

};