#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <Node.h>
#include <Camera.h>
#include <memory>
#include <btBulletDynamicsCommon.h>

class SceneManager {
  
  public:
    // SceneManager();
    SceneManager(btDiscreteDynamicsWorld* dynamicsWorld);
    ~SceneManager() {};
    void SetCamera(Camera cam);
    void UpdateSceneNodes();
    btDiscreteDynamicsWorld* GetPhysicsWorld();
    void AddNode(std::shared_ptr<Node> node);
    void SetSceneNodes();
    void PrintPhysicsNodes();
    void RenderNodes();
  private:
    btDiscreteDynamicsWorld* physics_world_;

    std::vector<std::shared_ptr<Node> > nodelist_;
    Camera cam_;
    
};

#endif //SCENEMANAGER_H