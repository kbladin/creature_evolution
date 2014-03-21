#include "RenderWindow.h"

RenderWindow::RenderWindow(CreatureEvolution* ce) {
	m_frame = 0;
	creature_evo_ = ce;
}
RenderWindow::~RenderWindow() {
	delete creature_evo_;
}

void RenderWindow::initialize() {
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
}

void RenderWindow::render() {
	creature_evo_->StepTheWorld();
	creature_evo_->UpdateTheWorld();
	creature_evo_->RenderTheWorld();
	++m_frame;
}