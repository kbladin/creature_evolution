
// 🐢

#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include "SettingsManager.h"
#include "CreatureEvolution.h"

#include "RenderWindow.h"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);


	SettingsManager::Instance()->setMaxGenerations(5);
	SettingsManager::Instance()->setPopulationSize(5);
	SettingsManager::Instance()->setCrossover(0.8);
	SettingsManager::Instance()->setElitism(0.2);
	SettingsManager::Instance()->setMutation(0.8);

	CreatureEvolution* CE = new CreatureEvolution();
	CE->Run();

    QSurfaceFormat format;
    format.setDepthBufferSize( 24 );
    format.setMajorVersion( 3 );
    format.setMinorVersion( 2 );
    format.setSamples( 4 );
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile( QSurfaceFormat::CoreProfile );

    RenderWindow window(CE);
    window.setFormat(format);
    window.resize(640, 480);
    window.show();
    window.setAnimating(true);

    return app.exec();
    
	return 0;
}
