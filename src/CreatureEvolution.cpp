#include "CreatureEvolution.h"

CreatureEvolution::CreatureEvolution() {
	std::cout << "Creating creature evolution..." << std::endl;
	evolution_manager_ = new EvolutionManager();
	sim_world_ = new Simulation();
	scene_ = new SceneManager();
	renderer_ = new Renderer(scene_);
	std::cout << "Done!" << std::endl;
}

CreatureEvolution::~CreatureEvolution() {
	delete evolution_manager_;
	delete renderer_;
	delete scene_;
	delete sim_world_;
}

void CreatureEvolution::StartEvolution() {
	evolution_manager_->startEvolutionProcess(); // start the whole evolution process! 
}


void CreatureEvolution::LoadBestCreature() {
    Creature best = evolution_manager_->GetBestCreatureFromLastGeneration();
    sim_world_->AddCreature(best);
    scene_->CreateNodesFromSimulation(sim_world_);
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

void CreatureEvolution::InitWorld() {
	renderer_->Init();
}
