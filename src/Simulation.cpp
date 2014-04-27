#include "Simulation.h"

Simulation::Simulation() {
  broad_phase_ = new btDbvtBroadphase();
  collision_configuration_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collision_configuration_);
  solver_ = new btSequentialImpulseConstraintSolver;

  dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_,
  broad_phase_, solver_, collision_configuration_);

  time_to_simulate_ = 30;
  counter_ = 0.0;
  fps_ = 60;
  // no self collision
  bt_creature_collidies_with_ = collisiontypes::COL_GROUND;
  ground_collidies_with_ = collisiontypes::COL_CREATURE;

  SetupEnvironment();
}

Simulation::~Simulation()  {

  std::vector<btRigidBody*> rigid_bodies;
  std::vector<btHingeConstraint*> joints;

  for (int i = 0; i < bt_population_.size(); ++i) {
    rigid_bodies = bt_population_[i]->GetRigidBodies();
    joints = bt_population_[i]->GetJoints();

    // Remove joints
    for (int i = 0; i < joints.size(); i++) {
        dynamics_world_->removeConstraint(joints[i]);
    }

    // Remove bodies
    for (int i = 0; i < rigid_bodies.size(); i++) {
        dynamics_world_->removeRigidBody(rigid_bodies[i]);
    }


  }

  for (int i = 0; i < bt_population_.size(); ++i) {
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

void Simulation::SetupEnvironment() {
  dynamics_world_->setGravity(btVector3(0, -10, 0));
  ground_shape_ = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

  ground_motion_state_ =
    new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
    btVector3(0, -1, 0)));

  btRigidBody::btRigidBodyConstructionInfo ground_rigid_bodyCI(0,
    ground_motion_state_, ground_shape_, btVector3(0, 0, 0));

  ground_rigid_body_ = new btRigidBody(ground_rigid_bodyCI);
  ground_rigid_body_->setFriction(1.0f);

  dynamics_world_->addRigidBody(ground_rigid_body_,
    collisiontypes::COL_GROUND, ground_collidies_with_);
}

void Simulation::AddPopulation(Population population) {
  for (int i = 0; i < population.size(); ++i) {
    // no displacement, don't construct Nodes
    BulletCreature* btc = new BulletCreature(population[i], 0.0f);
    bt_population_.push_back(btc);
  }

  std::vector<btRigidBody*> rigid_bodies;
  std::vector<btHingeConstraint*> joints;

  for (int i = 0; i < bt_population_.size(); ++i) {
    rigid_bodies = bt_population_[i]->GetRigidBodies();
    joints = bt_population_[i]->GetJoints();

    // Add bodies
    for (int i = 0; i < rigid_bodies.size(); i++) {
        dynamics_world_->addRigidBody(rigid_bodies[i],
            collisiontypes::COL_CREATURE, bt_creature_collidies_with_);
    }
    // Add joints
    for (int i = 0; i < joints.size(); i++) {
        dynamics_world_->addConstraint(joints[i], true);
    }
  }
}

void Simulation::Step(float dt) {
  /*
    Step through all BulletCreatures and Creatures to update motors
    and feed Creature with performance data.
  */

  for (int i = 0; i < bt_population_.size(); ++i) {
    std::vector<float> input;
    input.push_back(1.0);

    std::vector<btHingeConstraint*> joints = bt_population_[i]->GetJoints();
    for(int i=0; i < joints.size(); i++) {
      input.push_back(joints[i]->getHingeAngle());
    }

    bt_population_[i]->UpdateMotors(input);
    bt_population_[i]->CollectData();
  }
  dynamics_world_->stepSimulation(dt, 1);
  counter_ += dt;
}

Population Simulation::SimulatePopulation() {
  float dt = 1.0f / static_cast<float>(fps_);

  for (int i = 0; i < fps_*time_to_simulate_; ++i) {
    Step(dt);
  }

  Population creatures_with_data;
  for (int i = 0; i < bt_population_.size(); ++i) {
    creatures_with_data.push_back(bt_population_[i]->GetCreature());
  }

  return creatures_with_data;
}

std::vector<Node> Simulation::GetNodes() {
    std::vector<Node> nodes;

    //add terrain
    nodes.push_back(Node(ground_rigid_body_));

    //add creatures
    for(BulletCreature* bt_creature : bt_population_) {
        std::vector<btRigidBody*> bodies = bt_creature->GetRigidBodies();
        for(btRigidBody* body : bodies) {
            nodes.push_back(Node(body));
        }
    }
    return nodes;
}

btVector3 Simulation::GetLastCreatureCoords() {
   if(bt_population_.size() > 0)
       return bt_population_.back()->GetCenterOfMass();
   else
       return btVector3(0.0,0.0,0.0);
}
