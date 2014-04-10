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
};

#endif //SCENEMANAGER_H
