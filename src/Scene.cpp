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

void Scene::AddCreature(Creature creature) {
  BulletCreature* btc = new BulletCreature(creature,0.0f,true);
  bt_creatures_.push_back(btc);
  btDiscreteDynamicsWorld* bt_world = sim_.GetDynamicsWorld();
  std::vector<btRigidBody*> bodies = btc->GetRigidBodies();
  std::vector<btHingeConstraint*> joints = btc->GetJoints();

  for (int i = 0; i < bodies.size(); ++i) {
    bt_world->addRigidBody(bodies[i]);
  }
  for (int i = 0; i < joints.size(); ++i) {
    bt_world->addConstraint(joints[i]);
  }

  std::cout << "SCENE: Added creature!" << std::endl; 
  Scene::Instance()->GetCamera()->SetTarget(btc);
   physics_added = true;
}

void Scene::AddEntity(Entity* entity) {
  entities.push_back(entity);
}

void Scene::Render() {
  // if(entities.empty() || !physics_added)
  //   return;
  // To make sure we use the same name
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

  for (int i = 0; i < bt_creatures_.size(); ++i) {
    bt_creatures_[i]->Update();
  }

  sim_.Step(1.0f/60.0f);
}

float Scene::GetCurrentSimTime() {
  return sim_.GetCounterTime();
}

void Scene::Clean() {
  if(bt_creatures_.empty())
    return;

  btDiscreteDynamicsWorld* world = sim_.GetDynamicsWorld();
  std::vector<btRigidBody*> rigid_bodies;
  std::vector<btHingeConstraint*> joints;

  for(int i = 0; i < bt_creatures_.size(); ++i) {
    rigid_bodies = bt_creatures_[i]->GetRigidBodies();
    joints = bt_creatures_[i]->GetJoints();

    for(int i=0; i < rigid_bodies.size(); i++){
        world->removeRigidBody(rigid_bodies[i]);

    }
    //Add joints
    for(int i=0; i < joints.size(); i++){
        world->removeConstraint(joints[i]);
    }

  }
  
  for(int i = 0; i < bt_creatures_.size(); ++i) {
    delete bt_creatures_[i];
  }   

  bt_creatures_.clear();
  sim_.ResetTime();
}