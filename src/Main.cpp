
// 🐢

#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include "SettingsManager.h"
#include "CreatureEvolution.h"

#include "RenderWindow.h"

int main(int argc, char **argv) {
    //QGuiApplication app(argc, argv);


	SettingsManager::Instance()->setMaxGenerations(5);
	SettingsManager::Instance()->setPopulationSize(5);
	SettingsManager::Instance()->setCrossover(0.8);
	SettingsManager::Instance()->setElitism(0.2);
	SettingsManager::Instance()->setMutation(0.8);

	CreatureEvolution* CE = new CreatureEvolution();
	CE->Run();

    //QWindow window;
    //QSurfaceFormat format;
    //format.setSamples(16);

//    RenderWindow window(CE);
    //window.setVisible(true);

//    window.setAnimating(true);

    //return app.exec();
    delete CE;
    return 0;
}
