#include "../include/functions.hpp"

void functions::simulation(int idIteration){
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

double functions::rand_double(double min, double max){
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double>distr(min, max);

    double num = distr(eng);

    return num;
}

double functions::max(double num1, double num2){
    if(num1 > num2){
        return num1;
    }else{
        return num2;
    }
}

double functions::min(double num1, double num2){
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
        const char* rm =Command("rm -f ../Output/0/*");
        system(rm);
    }
}