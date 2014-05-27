#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Camera.h"
#include "Creature.h"
#include "SettingsManager.h"

class Node;
class Simulation;

//! Light data used when shading.
/*!
  The LightSources are global in the Scene and affects all objects in it.
  The Scene therefore has an array of LightSources.
  A high value of intensity results in a brighter LightSource. The color is
  defined with a vec3 of R, G and B values. The position is set by a vec4.
  If the w-value is set to 0.0, this vector is used as a directional vector
  instead of a position vector. constant_attenuation, linear_attenuation and
  quadratic_attenuation can all be used to set the attenuation of the
  LightSource. The total attenuation is the sum of all these values. The
  inverse of the attenuation is used to decrease the intensity as the distance
  increases. spot_cutoff is the angle of where the spotlight cuts of. If
  this value is greater than 90.0, the LightSource is a point light and not
  a spot light. spot_exponent determines the attenuation relative to the
  spot_direction of the lightsource. These will be set to default values if
  not explicitly set.
*/
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

//! This class handles the simulation of the physics world to be rendered.
/*!
  The Scene contains a Simulation, a Camera, all Nodes to be rendered and all
  LightSources used in the rendering process.
*/
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
  void RestartSimulation(std::vector<Creature> viz_creatures);

  static const int N_LIGHTS = 2; // Should be a constant in settingsmanager.
private:
  void StartSimulation(std::vector<Creature> viz_creatures);
  void EndSimulation();
  
  static Scene* instance_;
  Simulation* sim_;
  Camera cam_;
  LightSource lights_[N_LIGHTS];

  std::vector<Node> nodes_;
};

#endif  // SCENE_H
