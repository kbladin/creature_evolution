#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

// C++
#include <iterator>
#include <vector>
#include <iostream>
#include <memory>
// External
#include <btBulletDynamicsCommon.h>
// Internal
#include "Camera.h"
#include "Node.h"
#include "Plane.h"
#include "Box.h"
#include "Creature.h"
#include "Simulation.h"

class Camera;

struct PointLight {
  float intensity;
  glm::vec3 color;
  glm::vec3 position;
  PointLight() {
      intensity = 5000.0f;
      color = glm::vec3(1.0f, 1.0f, 1.0f);
      position = glm::vec3(0.0f, 50.0f, 0.0f);
  }
};

struct DirectionalLight {
  float intensity;
  glm::vec3 color;
  glm::vec3 direction;
  DirectionalLight() {
      intensity = 5000.0f;
      color = glm::vec3(1.0f, 1.0f, 1.0f);
      direction = glm::vec3(0.0f, -1.0f, 0.0f);
  }
};

//! Handles all the scene nodes. Makes sure the Bullet world is tied to the Nodes.

class SceneManager {
public:
  static SceneManager* Instance();
  void InitShapes();
  void SetCamera(Camera cam);
  Camera* GetCamera();
  void AddNode(std::shared_ptr<Node> node);
  void PrintPhysicsNodes();
  void RenderNodes();
  void CreateNodesFromSimulation(Simulation* sim);
  void UpdateNodes();
private:
  SceneManager();
  ~SceneManager() {};

  static SceneManager* instance_;

  btDiscreteDynamicsWorld* physics_world_;

  std::vector<std::shared_ptr<Node> > nodelist_;
  Camera cam_;
  PointLight light_;
};

#endif //SCENEMANAGER_H
