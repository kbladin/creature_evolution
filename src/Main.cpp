#include <QApplication>
#include <QDesktopWidget>

#include "SettingsManager.h"
#include "CreatureEvolution.h"

#include "MainCEWindow.h"


int main(int argc, char **argv) {
    QApplication app(argc, argv);

	SettingsManager::Instance()->setMaxGenerations(5);
	SettingsManager::Instance()->setPopulationSize(5);
	SettingsManager::Instance()->setCrossover(0.8);
	SettingsManager::Instance()->setElitism(0.2);
	SettingsManager::Instance()->setMutation(0.8);

	CreatureEvolution* CE = new CreatureEvolution();

    MainCEWindow window(CE);
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
