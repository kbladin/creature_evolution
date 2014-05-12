#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Camera.h"
#include "Creature.h"

class Node;
class Simulation;

struct LightSource {
  float intensity;
  glm::vec3 color;
  glm::vec4 position;
  float constant_attenuation, linear_attenuation, quadratic_attenuation;
  float spot_cutoff, spot_exponent;
  glm::vec3 spot_direction;
  LightSource() {
    intensity = 50.0f;
    color = glm::vec3(1.0f, 0.9f, 0.8f);
    position = glm::vec4(10.0f,5.0f,20.0f,1.0f); // w == 0.0 ? => directional
    constant_attenuation = 0.0f;
    linear_attenuation = 0.0f;
    quadratic_attenuation = 1.0f;
    spot_cutoff = 100.0f; // spot_cutoff > 90.0 ? => point light
    spot_exponent = 10.0f;
    spot_direction = glm::vec3(0.0f,-1.0f,0.0f);
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
    LightSource GetLight(int i);
    void StartSimulation(std::vector<Creature> viz_creatures);
    void EndSimulation();
    void RestartSimulation(std::vector<Creature> viz_creatures);

    static const int N_LIGHTS = 2; // Should match the one in the shader
  private:
    static Scene* instance_;
    Simulation* sim_;
    Camera cam_;
    LightSource lights_[N_LIGHTS];

    std::vector<Node> nodes_;
};

#endif  // SCENE_H
