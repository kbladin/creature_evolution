
// 🐢

#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include "SettingsManager.h"
#include "CreatureEvolution.h"

#include "RenderWindow.h"

int main(int argc, char **argv) {
	QGuiApplication app(argc, argv);

	CreatureEvolution* CE = new CreatureEvolution();
	CE.Run();
	QSurfaceFormat format;
    format.setSamples(16);

    RenderWindow window(CE);
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();

}