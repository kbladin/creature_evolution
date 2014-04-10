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

struct LightSource {
  float intensity = 5000.0f;
  glm::vec3 position = glm::vec3(0.0f, 40.0f, 0.0f);
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
};

#endif //SCENEMANAGER_H