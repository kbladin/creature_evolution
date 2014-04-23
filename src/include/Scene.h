#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Entity.h"
#include "Camera.h"
#include "VizSimulation.h"

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

class Scene {
  public:
    static Scene* Instance();

    Scene();
    ~Scene();

    void AddEntity(Entity* entity);
    void AddCreature(Creature creature, float disp);
    void RemoveEntity();
    void Clean();
    void Render();
    void Update();

    void SetCamera(Camera cam);
    Camera* GetCamera();
    float GetCurrentSimTime();

  private:
    void UpdatePhysics();

    static Scene* instance_;
    VizSimulation sim_;
    Camera cam_;
    PointLight light_;

    bool physics_added;

    std::vector<Entity*> entities;
    std::vector<BulletCreature*> bt_creatures_;
};

#endif  // SCENE_H
