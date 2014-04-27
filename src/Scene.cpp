#include "Scene.h"
#include <btBulletDynamicsCommon.h>
#include "Plane.h"

Scene* Scene::instance_ = NULL;

Scene* Scene::Instance() {
if (!instance_) {
    instance_ = new Scene();
  }
  return instance_;
}

Scene::Scene() {
  std::vector<Creature> start_creature;
  StartSimulation(start_creature);
}

Scene::~Scene() {
  EndSimulation();
}

void Scene::SetCamera(Camera cam) {
  cam_ = cam;
}

Camera* Scene::GetCamera() {
  return &cam_;
}

void Scene::Render() {
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

  //update cam
  btVector3 target = sim_->GetLastCreatureCoords();
  cam_.SetTarget(glm::vec3(target.getX(),target.getY(),target.getZ()));
  cam_.UpdateMatrices();

  //draw nodes
  for(Node& n : nodes_) {
      n.Render(&cam_);
  }
}

void Scene::Update() {
  for(Node& n : nodes_) {
      n.UpdateNode();
  }
  sim_->Step(1.0f/30.0f);

}

void Scene::StartSimulation(std::vector<Creature> viz_creatures) {
    sim_ = new Simulation();
    sim_->AddPopulation(viz_creatures);
    nodes_ = sim_->GetNodes();
}

void Scene::EndSimulation() {
    delete sim_;
    nodes_.clear();
}

void Scene::RestartSimulation(std::vector<Creature> viz_creatures) {
    EndSimulation();
    StartSimulation(viz_creatures);

    cam_.SetTarget(glm::vec3(0.0,0.0,0.0));

}

