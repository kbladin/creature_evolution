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
#include "WormBulletCreature.h"

struct PointLight {
  float intensity = 5000.0f;
  glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::vec3 position = glm::vec3(0.0f, 50.0f, 0.0f);
};

struct DirectionalLight {
  float intensity = 5000.0f;
  glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
};

//! 
class SceneManager {
public:
  static SceneManager* Instance();
  void InitShapes();
  void SetCamera(Camera cam);
  Camera* GetCamera();
  void AddNode(std::shared_ptr<Node> node);
  void PrintPhysicsNodes();
  void RenderNodes();
  void CreateNodesFromBulletCreature(WormBulletCreature* worm);
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