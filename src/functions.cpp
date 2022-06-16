#include "../include/functions.hpp"

void functions::Simulation(int idIteration, string file){
    system(Command("cp ../summaryplot.py ../Output/"+to_string(idIteration)));

    if(idIteration == 0){
        for(int i = 0; i < SIZE_POPULATION; i++){
            cout << "Executando a simulação no indivíduo " << i << " da iteração " << idIteration << endl;
            system(Command("mpirun -np 4 flow ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".DATA >> out.txt"));
            system(Command("python3 ../Output/"+to_string(idIteration)+"/summaryplot.py WOPR:PROD WWPR:PROD ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".DATA >> out.txt"));
            system(Command("mv WOPR:PROD.txt ../Output/"+to_string(idIteration)+"/oleo/"+to_string(i)+".txt"));
            system(Command("mv WWPR:PROD.txt ../Output/"+to_string(idIteration)+"/agua/"+to_string(i)+".txt"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".DBG"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".EGRID"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".INFOSTEP"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".INIT"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".PRT"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".SMSPEC"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".UNRST"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".UNSMRY"));
        }
    }else{
        for(int i = SIZE_POPULATION; i < (SIZE_POPULATION + ((SIZE_POPULATION * CROSSOVER_RATE) / 100)); i++){
            cout << "Executando a simulação no indivíduo " << i << " da iteração " << idIteration << endl;
            system(Command("mpirun -np 4 flow ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".DATA >> out.txt"));
            system(Command("python3 ../Output/"+to_string(idIteration)+"/summaryplot.py WOPR:PROD WWPR:PROD ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".DATA >> out.txt"));
            system(Command("mv WOPR:PROD.txt ../Output/"+to_string(idIteration)+"/oleo/"+to_string(i)+".txt"));
            system(Command("mv WWPR:PROD.txt ../Output/"+to_string(idIteration)+"/agua/"+to_string(i)+".txt"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".DBG"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".EGRID"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".INFOSTEP"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".INIT"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".PRT"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".SMSPEC"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".UNRST"));
            system(Command("rm ../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".UNSMRY"));
        }
    }

    system(Command("rm  ../Output/"+to_string(idIteration)+"/summaryplot.py"));
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

    if(dp == NULL){;
        system(Command("mkdir ../Output/"+to_string(idIteration)));
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/agua"));
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/oleo"));
    }else{
        const char* rm = Command("rm -f ../Output/"+to_string(idIteration)+"/*");
        system(rm);
    }

}

void functions::WriteSimulationFile(int idIteration, string inputFile, string file, vector<individual> population){
    for(int i = 0; i < SIZE_POPULATION; i++){
        ifstream input(inputFile, ios::in);
        ofstream output("../Output/"+to_string(idIteration)+"/"+to_string(i)+"-"+file+".DATA", ios::out);
        string line;
        int count = 0;

        while(!input.eof()){
            getline(input, line);
            if(count == 92){
                output << "    " << TOTAL_CELLS << "*" << population[i].porosity << " /"  << endl;
            }else if(count == 96){
                output << "    " << "100*" << population[i].permeability_x[0] << " 100*" << population[i].permeability_x[1] << " 100*" << population[i].permeability_x[2] << " /" << endl;
            }else if(count == 100){
                output << "    " << "100*" << population[i].permeability_y[0] << " 100*" << population[i].permeability_y[1] << " 100*" << population[i].permeability_y[2] << " /"  << endl;
            }else if(count == 105){
                output << "    " << "100*" << population[i].permeability_z[0] << " 100*" << population [i].permeability_z[1] << " 100*" << population[i].permeability_z[2] << " /"  << endl;
            }else{
                output << line << endl;
            }

            count++;
        }

        input.close();
        output.close();
    }
    
}

void functions::WriteErrorFile(int idIteration, vector<individual> population){
    ofstream errorFile("../Output/"+to_string(idIteration)+"/error.txt", ios::out);
    
    for(int i = 0; i < SIZE_POPULATION; i++){
        errorFile << population[i].error_rank << endl;
    }

    errorFile.close();
}