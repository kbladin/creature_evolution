#include "Scene.h"
#include <btBulletDynamicsCommon.h>
#include "Plane.h"

#include "Node.h"
#include "Simulation.h"

Scene* Scene::instance_ = NULL;

//! Singleton function. Returning the instance if created.
Scene* Scene::Instance() {
if (!instance_) {
    instance_ = new Scene();
  }
  return instance_;
}

//! Constructor. Initializes the LightSources and starts the Simulation.
Scene::Scene() {
  // Initialize the second light source
  lights_[1].intensity = 200.0f;
  lights_[1].position = glm::vec4(0.0f, 10.0f, 0.0f, 1.0f);
  lights_[1].spot_cutoff = 10.0f;
  lights_[1].spot_exponent = 150.0f;

  // Initialize the third light source
  //lights_[2].intensity = 1.0f;
  //lights_[2].color = glm::vec3(0.8f, 0.8f, 1.0f);
  //lights_[2].position = glm::vec4(0.5f, 1.0f, 0.5f, 0.0f);

  std::vector<Creature> start_creature;
  StartSimulation(start_creature);
}

//! Destructor. Ends the Simulation.
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

//! Render all the objects.
/*!
  Sets the Basic (phong) ShaderProgram and uploads the LightSource data. Then
  render all Nodes.
*/
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

//! Updates all components of the Scene.
/*!
  Updates the Camera position, LightSource direction and all Nodes. Then step
  the simulation.
*/
void Scene::Update() {
  // Update Camera
  btVector3 target = sim_->GetLastCreatureCoords();
  cam_.SetTarget(glm::vec3(target.getX(),target.getY(),target.getZ()));
  cam_.UpdateMatrices();

  // Update Light source
  lights_[1].spot_direction = cam_.GetTarget() - glm::vec3(lights_[1].position);
  // Update the target light source
  lights_[0].position = glm::vec4(
          SettingsManager::Instance()->GetTargetPos().x,
          SettingsManager::Instance()->GetTargetPos().y,
          SettingsManager::Instance()->GetTargetPos().z,
          1.0f);

  for(Node& n : nodes_) {
      n.UpdateNode();
  }
  sim_->Step(1.0f/30.0f);
}

//! Creates a new Simulation and adding the Creatures.
/*!
  \param viz_creatures are the creatures that should be added to the
  simulation.
*/
void Scene::StartSimulation(std::vector<Creature> viz_creatures) {
    sim_ = new Simulation(true);
    sim_->AddPopulation(viz_creatures, true);
    nodes_ = sim_->GetNodes();
}

//! Deletes the Simulation and deleting all the buffers for the Nodes
void Scene::EndSimulation() {
    delete sim_;
    //nodes_.clear();
    for (Node& node : nodes_) {
      node.DeleteBuffers();
    }
}

//! Ends the current simulation and creates a new one, adding the Creatures.
/*!
  \param viz_creatures are the creatures that should be added to the
  simulation.
*/
void Scene::RestartSimulation(std::vector<Creature> viz_creatures) {
    EndSimulation();
    StartSimulation(viz_creatures);

    cam_.SetTarget(glm::vec3(0.0,0.0,0.0));
}
