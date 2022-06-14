#include "../include/functions.hpp"

void functions::Simulation(int idIteration){
    system("rm -f ../Output/output_simulation");
    if(idIteration == 0){
        for(int i = 0; i < SIZE_POPULATION; i++){
            cout << "Executando a simulação no indivíduo " << i << " da iteração " << idIteration << endl;
            string command = "cp ../Output/"+to_string(idIteration)+"/inputDS_"+to_string(i)+".dat ../../Codigo_Bifasico_Slab/simulacoes/dev/inputDS.dat";
            const char* file = (char*) command.c_str();
            system(file);
            system("./../../Codigo_Bifasico_Slab/rodarSimulador.sh >> output_simulation 2>> ../Output/output_simulation");
            command = "cp ../../Codigo_Bifasico_Slab/simulacoes/dev/out/resultadoVazaoAgua.dat ../Output/"+to_string(idIteration)+"/agua/vazaoAgua_"+to_string(i)+".dat";
            file = (char*) command.c_str();
            system(file);
            command = "cp ../../Codigo_Bifasico_Slab/simulacoes/dev/out/resultadoVazaoOleo.dat ../Output/"+to_string(idIteration)+"/oleo/vazaoOleo_"+to_string(i)+".dat";
            file = (char*) command.c_str();
            system(file);
        }
    }else{
        for(int i = SIZE_POPULATION; i < (SIZE_POPULATION + ((SIZE_POPULATION * CROSSOVER_RATE) / 100)); i++){
            cout << "Executando a simulação no indivíduo " << i << " da iteração " << idIteration << endl;
            string command = "cp ../Output/"+to_string(idIteration)+"/inputDS_"+to_string(i)+".dat ../../Codigo_Bifasico_Slab/simulacoes/dev/inputDS.dat";
            const char* file = (char*) command.c_str();
            system(file);
            system("./../../Codigo_Bifasico_Slab/rodarSimulador.sh >> output_simulation 2>> ../Output/output_simulation");
            command = "cp ../../Codigo_Bifasico_Slab/simulacoes/dev/out/resultadoVazaoAgua.dat ../Output/"+to_string(idIteration)+"/agua/vazaoAgua_"+to_string(i)+".dat";
            file = (char*) command.c_str();
            system(file);
            command = "cp ../../Codigo_Bifasico_Slab/simulacoes/dev/out/resultadoVazaoOleo.dat ../Output/"+to_string(idIteration)+"/oleo/vazaoOleo_"+to_string(i)+".dat";
            file = (char*) command.c_str();
            system(file);
        }
    }
}

double functions::Rand_double(double min, double max){
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double>distr(min, max);

    double num = distr(eng);
    
    num = floor(num *100) / 100;

    return num;
}

double functions::Max(double num1, double num2){
    if(num1 > num2){
        return num1;
    }else{
        return num2;
    }
}

double functions::Min(double num1, double num2){
    if(num1 < num2){
        return num1;
    }else{
        return num2;
    }
}

const vector<string> functions::split(const string& s, const char& c){
    string buff{""};
	vector<string> v;
	
	for(auto n:s){
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}

	if(buff != "") v.push_back(buff);
	
	return v;
}

void functions::CreateOutputDir(){
    DIR* dp = opendir("../Output/");

    if(dp == NULL){
        system("mkdir ../Output/");
    }else{
        system("rm -r -f ../Output/*");
    }
}

string functions::ReadFileInput(string file){
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

result* functions::ConvertStringInputToDoubleResult(string water, string oil){
    vector<string> waterSplit{split(water, ' ')};
    vector<string> oilSplit{split(oil, ' ')};

    result* results = new result[water.size()];

    for(int i = 0; i < waterSplit.size(); i++){
        results[i].water = stod(waterSplit[i]);
        results[i].oil = stod(oilSplit[i]);
    }

    return results;

}

const char* functions::Command(string inputCommand){
    const char* command = (char*) inputCommand.c_str();

    return command;
}

void functions::CreateResultDir(int idIteration){
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
        const char* rm =Command("rm -f ../Output/"+to_string(idIteration)+"/*");
        system(rm);
    }
}

void functions::WriteSimulationFile(int idIteration, string inputFile, vector<individual> population){
    ifstream input(inputFile);

    for(int i = 0; i < SIZE_POPULATION; i++){
        ofstream output("../Output/"+to_string(idIteration)+"/"+to_string(i)+".DATA");
        string line;
        int count = 0;

        while(!input.eof()){
            getline(input, line);
            if(count == 92){
                output << "    " << TOTAL_CELLS << "*" << population[i].porosity << endl;
            }else if(count == 96){
                output << "    " << "100*" << population[i].permeability_x[0] << " 100*" << population[i].permeability_x[1] << " 100*" << population[i].permeability_x[2] << endl;
            }else if(count == 100){
                output << "    " << "100*" << population[i].permeability_y[0] << " 100*" << population[i].permeability_y[1] << " 100*" << population[i].permeability_y[2] << endl;
            }else if(count == 105){
                output << "    " << "100*" << population[i].permeability_z[0] << " 100*" << population[i].permeability_z[1] << " 100*" << population[i].permeability_z[2] << endl;
            }else{
                output << line << endl;
            }
        }

        output.close();
    }

    input.close();
    
}