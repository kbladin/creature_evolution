#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Node.h"
#include "Camera.h"
#include "Simulation.h"

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

    void Render();
    void Update();

    void SetCamera(Camera cam);
    Camera* GetCamera();
    void StartSimulation(std::vector<Creature> viz_creatures);
    void EndSimulation();
    void RestartSimulation(std::vector<Creature> viz_creatures);
    void SelectObject(float x, float y);
    void UpdateSelectedObjectPosition(float x, float y);
  private:
    static Scene* instance_;
    Simulation* sim_;
    Camera cam_;
    PointLight light_;

    std::vector<Node> nodes_;
};

#endif  // SCENE_H
