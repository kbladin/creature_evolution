
// 🐢

#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "WindowsManager.h"
#include "SettingsManager.h"
#include "Evolution.h"
#include "Creature.h"
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "QtWindowManager.h"
#include "WindowsManager.h"
#include "CreatureEvolution.h"



int main(int argc, char **argv) {

	CreatureEvolution* CE = new CreatureEvolution();
	QGuiApplication app(argc, argv);

	qmlRegisterType<QtWindowManager>("CreatureEvolution",1,0,"QtWindowManager");

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl::fromLocalFile("ui.qml"));

	QtWindowManager* qtwm = rootQml->findChild<QtWindowManager *>("qtwindowmanager");
	qtwm->Init(CE);

	view.show();

	return app.exec();

	/*CreatureEvolution* CE = new CreatureEvolution();
	WindowsManager* WM = new WindowsManager(640,480, CE);
	QtWindowManager
	WM->setVariables();
	CE->Run();
	WM->DisplayAndRender();

	delete CE;
	delete WM;

	return 0;*/
}