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
  // Initialize the second light source
  lights_[1].intensity = 200.0f;
  lights_[1].position = glm::vec4(0.0f, 10.0f, 0.0f, 1.0f);
  lights_[1].spot_cutoff = 10.0f;
  lights_[1].spot_exponent = 150.0f;

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

LightSource Scene::GetLight(int i){
  return lights_[i];
}

void Scene::Render() {
   //To make sure we use the same name
  const char* shader_name = "Basic";
  ShaderManager::Instance()->UseProgram(shader_name);

  // One light source takes 16 * sizeof(float) in size
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->Uniform1fv(
                  "light_data",
                  16 * N_LIGHTS,
                  &lights_[0].intensity);

  glUseProgram(0);

  //draw nodes
  for(Node& n : nodes_) {
      n.Render(&cam_);
  }
}

void Scene::Update() {
  // Update Camera
  btVector3 target = sim_->GetLastCreatureCoords();
  cam_.SetTarget(glm::vec3(target.getX(),target.getY(),target.getZ()));
  cam_.UpdateMatrices();

  // Update Light source
  lights_[1].spot_direction = cam_.GetTarget() - glm::vec3(lights_[1].position);
  for(Node& n : nodes_) {
      n.UpdateNode();
  }
  sim_->Step(1.0f/30.0f);
}

void Scene::StartSimulation(std::vector<Creature> viz_creatures) {
    sim_ = new Simulation();
    sim_->AddPopulation(viz_creatures, true);
    nodes_ = sim_->GetNodes();
}

void Scene::EndSimulation() {
    delete sim_;
    //nodes_.clear();
    for (Node& node : nodes_) {
      node.DeleteBuffers();
    }
}

void Scene::RestartSimulation(std::vector<Creature> viz_creatures) {
    EndSimulation();
    StartSimulation(viz_creatures);

    cam_.SetTarget(glm::vec3(0.0,0.0,0.0));

}

