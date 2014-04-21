#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Entity.h"
#include "Camera.h"
#include "Simulation.h"

class Scene {
  public:
    static Scene* Instance();

    Scene();
    ~Scene();

    void AddEntity(Entity* entity);
    void RemoveEntity();
    void Clean();

    void SetCamera(Camera cam);
    Camera* GetCamera();

  private:
    void UpdatePhysics();

    static Scene* instance_;
    Simulation sim_;
    Camera cam_;

    std::vector<Entity*> entities;
};

#endif  // SCENE_H
