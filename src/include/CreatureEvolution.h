#ifndef CREATUREEVOLUTION_H
#define CREATUREEVOLUTION_H

#include "Simulation.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "EvolutionManager.h"
#include "Creature.h"

#include <memory>

class CreatureEvolution {

public:
	CreatureEvolution();
	~CreatureEvolution();
	
	void StepTheWorld();
	void UpdateTheWorld();
	void RenderTheWorld();
	void InitWorld();

	void StartEvolution();
	void LoadBestCreature();
	void Run();


private:
	Simulation* sim_world_;
	Renderer* renderer_;
	//SceneManager* scene_;
	EvolutionManager* evolution_manager_;
	Creature draw_creature;
};



#endif // CREATUREEVOLUTION_H
