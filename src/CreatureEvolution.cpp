#include "CreatureEvolution.h"

CreatureEvolution::CreatureEvolution() {
	std::cout << "Creating creature evolution..." << std::endl;
	evolution_manager_ = new EvolutionManager();
	sim_world_ = new Simulation(true);
	//scene_ = new SceneManager();
	renderer_ = new Renderer(SceneManager::Instance());
	std::cout << "Done!" << std::endl;
}

CreatureEvolution::~CreatureEvolution() {
	delete evolution_manager_;
	delete renderer_;
	//delete scene_;
	delete sim_world_;
}

void CreatureEvolution::StartEvolution() {
    evolution_manager_->startEvolutionProcess(); // start the whole evolution process!
}

void CreatureEvolution::LoadBestCreature() {
    draw_creature = evolution_manager_->GetBestCreatureFromLastGeneration();
    std::cout << "Best Creature: " << draw_creature.GetFitness() << std::endl;
    sim_world_->AddCreature(draw_creature);

	SceneManager::Instance()->CreateNodesFromSimulation(sim_world_);
  	//ShaderManager::Instance();
	//should be able to InitWorld here
	InitWorld();
	SceneManager::Instance()->GetCamera()->SetTarget(sim_world_->GetCurrentBulletCreature());
}

void CreatureEvolution::LoadAllBestCreatures() {
	std::vector<Creature> creatures_to_draw = evolution_manager_->GetAllBestCreatures();
	sim_world_->AddPopulation(creatures_to_draw);

	SceneManager::Instance()->CreateNodesFromSimulation(sim_world_);
	InitWorld();
	SceneManager::Instance()->GetCamera()->SetTarget(sim_world_->GetCurrentBulletCreature());

}

void CreatureEvolution::Run() {
	StartEvolution();
	//LoadBestCreature();
}

void CreatureEvolution::StepTheWorld() {
	//sim_world_->Step(1/60.0f);
	sim_world_->StepPopulation(1/60.0f);
}
void CreatureEvolution::UpdateTheWorld() {
	SceneManager::Instance()->UpdateNodes();
}

void CreatureEvolution::RenderTheWorld() {
	renderer_->render();
}

void CreatureEvolution::InitWorld() {
	renderer_->Init();
}
