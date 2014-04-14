#include "Simulation.h"
#include <chrono>
#include <ctime>

//! Setup a default physics world with an infinite ground plane.
Simulation::Simulation()
{
    counter_ = 0;

    bt_creature_collidies_with = collisiontypes::COL_GROUND;
    ground_collidies_with = collisiontypes::COL_CREATURE;


    //init world
    broad_phase_ = new btDbvtBroadphase();
    collision_configuration_ = new btDefaultCollisionConfiguration();
    dispatcher_ = new btCollisionDispatcher(collision_configuration_);
    solver_ = new btSequentialImpulseConstraintSolver;
    dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_,broad_phase_,solver_,collision_configuration_);

    //environment
    dynamics_world_->setGravity(btVector3(0,-10,0));
    ground_shape_ = new btStaticPlaneShape(btVector3(0,1,0),1);
    ground_motion_state_ = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo ground_rigid_bodyCI(0,ground_motion_state_,ground_shape_,btVector3(0,0,0));
    ground_rigid_body_ = new btRigidBody(ground_rigid_bodyCI);
    ground_rigid_body_->setFriction(1.0f);
    dynamics_world_->addRigidBody(ground_rigid_body_, collisiontypes::COL_GROUND, ground_collidies_with);
}

//! Destructor. Delete all dynamic allocated things for Bullet.
Simulation::~Simulation(void)
{
    //TODO: kill all rigid bodies an joints in Creature etc.

    std::vector<btRigidBody*> rigid_bodies;
    std::vector<btHingeConstraint*> joints;
    
    for(int i = 0; i < bt_population_.size(); ++i) {

        rigid_bodies = bt_population_[i]->GetRigidBodies();
        joints = bt_population_[i]->GetJoints();
    
        for(int i=0; i < rigid_bodies.size(); i++){
            dynamics_world_->removeRigidBody(rigid_bodies[i]);

        }
        //Add joints
        for(int i=0; i < joints.size(); i++){
            dynamics_world_->removeConstraint(joints[i]);
        }
    }


    for(int i = 0; i < bt_population_.size(); ++i) {
        delete bt_population_[i];
    }


    dynamics_world_->removeRigidBody(ground_rigid_body_);
    delete ground_rigid_body_->getMotionState();
    delete ground_rigid_body_;

    delete ground_shape_;


    delete dynamics_world_;
    delete solver_;
    delete collision_configuration_;
    delete dispatcher_;
    delete broad_phase_;

}

//! Adds a creature from the Evolution process to the physical world.
void Simulation::AddCreature(Creature creature) {
    creature_ = creature;
    
    bullet_creature_ = new BulletCreature(creature_);

    std::vector<btRigidBody*> rigid_bodies = bullet_creature_->GetRigidBodies();
    std::vector<btHingeConstraint*> joints = bullet_creature_->GetJoints();
    

    //Add bodies
    for(int i=0; i < rigid_bodies.size(); i++){
        dynamics_world_->addRigidBody(rigid_bodies[i],collisiontypes::COL_CREATURE, bt_creature_collidies_with);

    }
    //Add joints
    for(int i=0; i < joints.size(); i++){
        dynamics_world_->addConstraint(joints[i], true);
    }

}

/*! Removes the creature's rigid bodies and joints.
 Can only be called if a creature has been added.
OBSOLETE: This is now obsolete because we dont need to remove
creatures in Simulation, just let the destructor deal with it.
 */
void Simulation::RemoveCreature() {

    //TODO: this will only be used for rendering purposes


    std::vector<btRigidBody*> rigid_bodies = bullet_creature_->GetRigidBodies();
    std::vector<btHingeConstraint*> joints = bullet_creature_->GetJoints();
    

    for(int i=0; i < rigid_bodies.size(); i++){
        dynamics_world_->removeRigidBody(rigid_bodies[i]);

    }
    //Add joints
    for(int i=0; i < joints.size(); i++){
        dynamics_world_->removeConstraint(joints[i]);
    }

    delete bullet_creature_;
    bullet_creature_ = NULL;
    //creature_ = NULL;
    counter_ = 0.0f;
}

//! Adds a population and creates BulletCreatures
void Simulation::AddPopulation(std::vector<Creature> population) {
    population_ = population;

    for (int i = 0; i < population_.size(); ++i) {
        BulletCreature* bt_creature = new BulletCreature(population_[i]);
        bt_population_.push_back(bt_creature);
    }


    std::vector<btRigidBody*> rigid_bodies;
    std::vector<btHingeConstraint*> joints;

    for (int i = 0; i < bt_population_.size(); ++i) {
        rigid_bodies = bt_population_[i]->GetRigidBodies();
        joints = bt_population_[i]->GetJoints();

        // Add bodies
        for (int i = 0; i < rigid_bodies.size(); i++) {
            dynamics_world_->addRigidBody(rigid_bodies[i],
                collisiontypes::COL_CREATURE, bt_creature_collidies_with);
        }
        // Add joints
        for (int i = 0; i < joints.size(); i++) {
            dynamics_world_->addConstraint(joints[i], true);
        }
    }
}


//! Update the 'motors' on the creature and step the physical world.
void Simulation::Step(float dt)
{
    std::vector<float> input(1,counter_*5);
    bullet_creature_->UpdateMotors(input);

    dynamics_world_->stepSimulation(dt,1);
    counter_ += dt;
}

//! Steps the dynamic world for a population and updates motors etc
void Simulation::StepPopulation(float dt) {
    //TODO: grab output from creature Brain? Just current time now.
    std::vector<float> input(1,counter_*5);
    
    //TODO: loop over all creatures and update their motors
    for(int i = 0; i < bt_population_.size(); ++i) {
        bt_population_[i]->UpdateMotors(input);
        population_[i].UpdateVelocity(bt_population_[i]->GetCenterOfMass().getZ());
        // population_[i].UpdateDeviationX(bt_population_[i]->GetCenterOfMass().getX());
        // population_[i].UpdateDeviationY(bt_population_[i]->GetCenterOfMass().getY());
    }

    //This should in theory work the same way, i.e just step the simulation
    dynamics_world_->stepSimulation(dt,1);
    counter_ += dt;   
}

//! Returns the current btDiscreteDynamicsWorld pointer
btDiscreteDynamicsWorld* Simulation::GetDynamicsWorld()
{
    return dynamics_world_;
}

//! Starts the simulation process with a predetermined fps and time.
Creature Simulation::Simulate() {
    float height = 0.0f;
    int fps = 30;
    int n_seconds = 60;

    for (int i = 0; i < fps*n_seconds; ++i){
        //TODO: maybe loop over all creatures here?
        Step(1.0f/(float) fps);
    }

    //TODO: this has to be done for all creatures
    SimData d;
    d.distance = bullet_creature_->GetCenterOfMass().getZ();
    creature_.SetSimData(d);

    return creature_;
}


//! Simulates a population
std::vector<Creature> Simulation::SimulatePopulation() {
    int fps = 60;
    int n_seconds = 30;

    for (int i = 0; i < fps*n_seconds; ++i){
        StepPopulation(1.0f/(float) fps);
    }

    //TODO: this has to be done for all creatures
    for(int i = 0; i < population_.size(); ++i) {
        SimData d;
        d = population_[i].GetSimData();
        d.distance = bt_population_[i]->GetCenterOfMass().getZ();
        population_[i].SetSimData(d);
    }

    return population_;
}

//! Get rigid bodies from current BulletCreature
/*
This is only being used for rendering purposes.
*/
std::vector<btRigidBody*> Simulation::GetRigidBodies() {
    //TODO: this has to be done for all creatures
    return bullet_creature_->GetRigidBodies();
}

/*
TODO: this is only being used in order to grab a Camera target.
Maybe remove it/replace it with something more sophisticated
for viewing several creatures at once?

For now it stays since we currently only render one creature.
*/
BulletCreature* Simulation::GetCurrentBulletCreature() {
    return bullet_creature_;
}