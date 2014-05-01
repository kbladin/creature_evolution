#include <QApplication>
#include <QDesktopWidget>

#include "SettingsManager.h"

#include "MainCEWindow.h"
#include "SImulation.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
/*
    SettingsManager::Instance()->SetMaxGenerations(10);
    SettingsManager::Instance()->SetPopulationSize(10);

	SettingsManager::Instance()->SetCrossover(0.8f);
	SettingsManager::Instance()->SetElitism(0.2f);
	SettingsManager::Instance()->SetMutation(0.8f);
*/

    SettingsManager::Instance()->SetCreatureType(CreatureType::SHEEP);
    SettingsManager::Instance()->SetMainBodyDimension(Vec3(0.1,0.1,0.2));
    qRegisterMetaType<Creature>();

    SettingsManager::Instance()->SetWorldType(WorldType::PLANE);

    MainCEWindow window;

    window.resize(window.sizeHint());

    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();

    int widgetArea = window.width() * window.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();

    return app.exec();

/*
    int i=0;
    while(true) {
        Simulation sim;
        Population pop;
        pop.resize(20);
        sim.AddPopulation(pop);
        for(int j=0; j<100; j++)
            sim.Step(1.0/60.0);

        std::cout << "test " << i << std::endl;
        i++;
    }
*/
}
