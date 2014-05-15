#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
#include <fstream>
#include <time.h>

#include "SettingsManager.h"
#include "EvolutionManager.h"
#include "MainCEWindow.h"

using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

	SettingsManager::Instance()->SetCrossover(0.8f);
	SettingsManager::Instance()->SetElitism(0.2f);
    SettingsManager::Instance()->SetMutation(0.0f);
    SettingsManager::Instance()->SetMutationSigma(0.0f);
    SettingsManager::Instance()->SetMutationInternal(0.0f);
    SettingsManager::Instance()->SetFitnessDistanceLight(0.0f);
    SettingsManager::Instance()->SetFitnessDistanceZ(0.0f);
    SettingsManager::Instance()->SetFitnessMaxY(0.0f);
    SettingsManager::Instance()->SetFitnessAccumY(0.0f);
    SettingsManager::Instance()->SetFitnessAccumHeadY(0.0f);
    SettingsManager::Instance()->SetFitnessDeviationX(0.0f);
    SettingsManager::Instance()->SetFitnessEnergy(0.0f);
    

    SettingsManager::Instance()->SetCreatureType(CreatureType::WORM);


    clock_t t;

    SettingsManager::Instance()->joints_=1;
    SettingsManager::Instance()->SetPopulationSize(1);
    SettingsManager::Instance()->SetSimulationTime(6);
    SettingsManager::Instance()->SetMaxGenerations(1);

    ofstream myfile;
    myfile.open ("joints.txt");
    for(int i=0; i<300; i++)
    {
        EvolutionManager em;
        cout << "joints " << i << endl;

        t = clock();
        SettingsManager::Instance()->joints_=1+i;
        em.startEvolutionProcess();
        t = clock() - t;

        myfile << (float)t << endl;
    }
    myfile.close();

    SettingsManager::Instance()->joints_=1;
    SettingsManager::Instance()->SetPopulationSize(1);
    SettingsManager::Instance()->SetSimulationTime(1);
    SettingsManager::Instance()->SetMaxGenerations(1);

    myfile.open ("population.txt");
    for(int i=0; i<300; i++)
    {
        EvolutionManager em;
        cout << "population " << i << endl;

        t = clock();
        SettingsManager::Instance()->SetPopulationSize(1+i);
        em.startEvolutionProcess();
        t = clock() - t;

        myfile << (float)t << endl;
    }
    myfile.close();

    SettingsManager::Instance()->joints_=1;
    SettingsManager::Instance()->SetPopulationSize(1);
    SettingsManager::Instance()->SetSimulationTime(1);
    SettingsManager::Instance()->SetMaxGenerations(1);

    myfile.open ("simtime.txt");
    for(int i=0; i<300; i++)
    {
        EvolutionManager em;
        cout << "simtime " << i << endl;

        t = clock();
        SettingsManager::Instance()->SetSimulationTime(1+i);
        em.startEvolutionProcess();
        t = clock() - t;

        myfile << (float)t << endl;
    }
    myfile.close();

    SettingsManager::Instance()->joints_=1;
    SettingsManager::Instance()->SetPopulationSize(1);
    SettingsManager::Instance()->SetSimulationTime(1);
    SettingsManager::Instance()->SetMaxGenerations(1);

    myfile.open ("generations.txt");
    for(int i=0; i<300; i++)
    {
        EvolutionManager em;
        cout << "generations " << i << endl;

        t = clock();
        SettingsManager::Instance()->SetMaxGenerations(1+i);
        em.startEvolutionProcess();
        t = clock() - t;

        myfile << (float)t << endl;
    }
    myfile.close();


    return 0;
}
