#include <QApplication>
#include <QDesktopWidget>

#include "SettingsManager.h"

#include "MainCEWindow.h"


int main(int argc, char **argv) {
    QApplication app(argc, argv);
/*
    SettingsManager::Instance()->SetMaxGenerations(10);
    SettingsManager::Instance()->SetPopulationSize(10);

	SettingsManager::Instance()->SetCrossover(0.8f);
	SettingsManager::Instance()->SetElitism(0.2f);
	SettingsManager::Instance()->SetMutation(0.8f);
*/
    SettingsManager::Instance()->SetFitnessDistanceForward(0.2f);
    SettingsManager::Instance()->SetFitnessMaxHeight(1.0f);
    SettingsManager::Instance()->SetFitnessEnergy(0.4f);


    SettingsManager::Instance()->SetCreatureType(CreatureType::SHEEP);
    SettingsManager::Instance()->SetMainBodyDimension(Vec3(0.1,0.1,0.2));
    qRegisterMetaType<Creature>();
    
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
}
