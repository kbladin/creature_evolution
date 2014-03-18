#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <Node.h>
#include <Camera.h>
#include <btBulletDynamicsCommon.h>

class SceneManager {
  
  public:
    // SceneManager();
    SceneManager(btDiscreteDynamicsWorld* dynamicsWorld);
    
    void SetCamera(Camera cam);
    void UpdateSceneNodes();

  private:
    btDiscreteDynamicsWorld* physics_world_;

    std::vector<Node> nodelist_;
    Camera cam_;
    
};

#endif //SCENEMANAGER_H