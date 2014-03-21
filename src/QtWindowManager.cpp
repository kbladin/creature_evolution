#include "QtWindowManager.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLContext>

QtWindowManager::QtWindowManager() {
	//TEMPORARY!!
	SettingsManager::Instance()->setMaxGenerations(5);
	SettingsManager::Instance()->setPopulationSize(5);
	SettingsManager::Instance()->setCrossover(0.8f);
	SettingsManager::Instance()->setElitism(0.2f);
	SettingsManager::Instance()->setMutation(0.8f);

	connect(this, SIGNAL(windowChanged(QQuickWindow*)),
	 this, SLOT(HandleWindowChanged(QQuickWindow*)));
}

void QtWindowManager::HandleWindowChanged(QQuickWindow *win) {
	if(win) {
		 connect(win, SIGNAL(beforeRendering()),
		  this, SLOT(Paint()), Qt::DirectConnection);
        connect(win, SIGNAL(beforeSynchronizing()),
         this, SLOT(Sync()), Qt::DirectConnection);
	
		win->setClearBeforeRendering(false);
	}
}

void QtWindowManager::Init(CreatureEvolutuion* ce) {
	creature_evo_ = ce;

	creature_evo_->Run();
}

void QtWindowManager::Paint() {
	//call renderer etc here

	qreal ratio = window()->devicePixelRatio();
    int w = int(ratio * window()->width());
    int h = int(ratio * window()->height());

	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	creature_evo_->StepTheWorld();
	creature_evo_->UpdateTheWorld();
	creature_evo_->RenderTheWorld();
}

void QtWindowManager::CleanUp() {
	//hmm is this like a deconstructor?
}

void QtWindowManager::Sync() {
	//do nothing for now
}