#ifndef QTWINDOWMANAGER_H
#define QTWINDOWMANAGER_H

#include <QtQuick/QQuickItem>
#include <CreatureEvolution.h>

class QtWindowManager : public QQuickItem {
	Q_OBJECT

public:
	QtWindowManager();
	~QtWindowManager();

public slots:
	void Paint();
	void CleanUp();
	void Sync();

private slots:
	void HandleWindowChanged(QQuickWindow *win);

private:

	CreatureEvolution* creature_evo_;

};

#endif // QTWINDOWMANAGER_H
