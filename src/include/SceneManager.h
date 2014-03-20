#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <Node.h>
#include <Camera.h>
#include <memory>
#include <btBulletDynamicsCommon.h>
#include <WormBulletCreature.h>

class WormBulletCreature;

class SceneManager {
  
  public:
    ~SceneManager() {};
    void SetCamera(Camera cam);
    void AddNode(std::shared_ptr<Node> node);
    void PrintPhysicsNodes();
    void RenderNodes();
    void CreateNodesFromBulletCreature(WormBulletCreature* worm);
    void UpdateNodes();
  private:
    btDiscreteDynamicsWorld* physics_world_;

    std::vector<std::shared_ptr<Node> > nodelist_;
    Camera cam_;
    
};

#endif //SCENEMANAGER_H