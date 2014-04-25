#include "Scene.h"
#include <btBulletDynamicsCommon.h>
#include "Plane.h"
#include "PassiveObject.h"

Scene* Scene::instance_ = NULL;

Scene* Scene::Instance() {
if (!instance_) {
    instance_ = new Scene();
  }
  return instance_;
}

Scene::Scene() {
  sim_ = new EvoSimulation();

  physics_added = false;
  Plane plane_shape(glm::vec3(1.0f) * 100.0f);
  plane_shape.SetupBuffers();
  Node* node_to_add = new Node();
  node_to_add->SetShape(plane_shape);
  PassiveObject* plane = new PassiveObject();
  plane->SetNode(node_to_add);
  AddEntity(plane);
}

Scene::~Scene() {
  delete sim_;
  // kill shit

  for (int i = 0; i < entities.size(); ++i) {
    delete entities[i];
  }
  for (int i = 0; i < bt_creatures_.size(); ++i) {
    delete bt_creatures_[i];
  }
}

void Scene::SetCamera(Camera cam) {
  cam_ = cam;
}

Camera* Scene::GetCamera() {
  return &cam_;
}

void Scene::AddCreature(Creature creature, float disp) {/*
  BulletCreature* btc = new BulletCreature(creature,disp,true);
  bt_creatures_.push_back(btc);
  btDiscreteDynamicsWorld* bt_world = sim_.GetDynamicsWorld();
  std::vector<btRigidBody*> bodies = btc->GetRigidBodies();
  std::vector<btHingeConstraint*> joints = btc->GetJoints();

  for (int i = 0; i < bodies.size(); ++i) {
    bt_world->addRigidBody(
            bodies[i],
            collisiontypes::COL_CREATURE,
            sim_.GetCollisionType());
  }
  for (int i = 0; i < joints.size(); ++i) {
    bt_world->addConstraint(joints[i]);
  }

  std::cout << "SCENE: Added creature!" << std::endl; 
  Scene::Instance()->GetCamera()->SetTarget(btc);
   physics_added = true;*/
}

void Scene::AddEntity(Entity* entity) {
  entities.push_back(entity);
}

void Scene::Render() {
   //if(entities.empty() || !physics_added)
   //  return;
   //To make sure we use the same name
  const char* shader_name = "Basic";
  ShaderManager::Instance()->UseProgram(shader_name);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->Uniform1f("light_intensity", light_.intensity);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->Uniform3fv("light_color", 1, &light_.color.x);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->Uniform3fv(
                  "light_position_worldspace",
                  1,
                  &light_.position.x);
  glUseProgram(0);

  for (int i = 0; i < entities.size(); ++i) {
    entities[i]->Draw();

  }

  if(bt_creatures_.empty())
    return;
  
  cam_.UpdateMatrices();

  for (int i = 0; i < bt_creatures_.size(); ++i) {
    bt_creatures_[i]->Draw();
  }
}

void Scene::Update() {
  if(bt_creatures_.empty())
    return;

  sim_->Step(1.0f/60.0f);

}


void Scene::RestartSimulation(std::vector<Creature> viz_creatures) {
    delete sim_;
    sim_ = new EvoSimulation();
    sim_->AddPopulation(viz_creatures);
    bt_creatures_ = sim_->bt_population_;

    if(bt_creatures_.size() > 0)
        GetCamera()->SetTarget(bt_creatures_[0]);
}

