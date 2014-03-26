#include "CreatureEvolution.h"

CreatureEvolution::CreatureEvolution() {
	evolution_manager_ = new EvolutionManager();
	sim_world_ = new Simulation();
	scene_ = new SceneManager();
	renderer_ = new Renderer(scene_);
}

CreatureEvolution::~CreatureEvolution() {
	delete sim_world_;
	delete renderer_;
	delete scene_;
	delete evolution_manager_;
}

void CreatureEvolution::StartEvolution() {
	evolution_manager_->startEvolutionProcess(); // start the whole evolution process! 
	evolution_manager_->printBestFitnessValues();
}


void CreatureEvolution::LoadBestCreature() {
	Creature best = evolution_manager_->getBestCreatureFromLastGeneration();
	WormBulletCreature *worm = new WormBulletCreature(best.GetChromosome().GetGene(), btVector3(0,0,0));
	sim_world_->AddCreatureToWorld(worm);
	scene_->CreateNodesFromBulletCreature(worm);

}

void CreatureEvolution::Run() {
	StartEvolution();
	LoadBestCreature();
}

void CreatureEvolution::StepTheWorld() {
	sim_world_->Step(1/60.0f);
}
void CreatureEvolution::UpdateTheWorld() {
	scene_->UpdateNodes();
}

void CreatureEvolution::RenderTheWorld() {
	renderer_->render();
}