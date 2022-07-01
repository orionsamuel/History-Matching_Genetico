import os
import subprocess

def init(n):
    simulation(n)

def simulation(n):
    if(not os.path.exists("Output_Simulation")):
        os.system("mkdir Output_Simulation")
        os.system("mkdir Output_Simulation/agua")
        os.system("mkdir Output_Simulation/oleo")
    else:
        os.system("rm -r -f Output_Simulation/*")
        os.system("mkdir Output_Simulation/agua")
        os.system("mkdir Output_Simulation/oleo")


    os.system("rm -f output_simulation")
    os.system("cp ../summaryplot.py Output_Simulation/")
    for i in range(n):
        print("Executando a simulação: "+str(i))
        os.system("cp ../Output/9/"+str(i)+"-SPE1CASE1.DATA "
                  +"Output_Simulation/")
        os.system("mpirun -np 4 flow Output_Simulation/"+str(i)+
                  "-SPE1CASE1.DATA")
        os.system("python3 Output_Simulation/summaryplot.py WOPR:PROD WGPR:PROD "
                  +"Output_Simulation/"+str(i)+"-SPE1CASE1.DATA")
        os.system("mv WOPR:PROD.txt Output_Simulation/"
                  "oleo/"+str(i)+".txt")
        os.system("mv WGPR:PROD.txt Output_Simulation/"
                  "agua/"+str(i)+".txt")
        os.system("rm Output_Simulation/"+str(i)+"-SPE1CASE1.DATA.DBG")
        os.system("rm Output_Simulation/"+str(i)+"-SPE1CASE1.DATA.EGRID")
        os.system("rm Output_Simulation/"+str(i)+"-SPE1CASE1.DATA.INFOSTEP")
        os.system("rm Output_Simulation/"+str(i)+"-SPE1CASE1.DATA.INIT")
        os.system("rm Output_Simulation/"+str(i)+"-SPE1CASE1.DATA.PRT")
        os.system("rm Output_Simulation/"+str(i)+"-SPE1CASE1.DATA.SMSPEC")
        os.system("rm Output_Simulation/"+str(i)+"-SPE1CASE1.DATA.UNRST")
        os.system("rm Output_Simulation/"+str(i)+"-SPE1CASE1.DATA.UNSMRY")

    os.system("rm Output_Simulation/summaryplot.py ")


if __name__ == '__main__':
    init(100)




