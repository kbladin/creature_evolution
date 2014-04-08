#ifndef CAMERA_H
#define CAMERA_H

//C++
#include <time.h>
// External
#include <glm/glm.hpp>
#include <glm/ext.hpp>
// Internal
#include "WormBulletCreature.h"
#include "SettingsManager.h"

class Camera {
public:
  Camera();
  Camera(glm::mat4 view, glm::mat4 projection);
  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix();
  void SetTarget(WormBulletCreature* target);
  void UpdateMatrices();
  void IncrementXrotation(float h);
  void IncrementYrotation(float h);
private:
  template <class T>
  void Delay(T& input, T end_val, float speed);
  //float rotation_x_ = 0.0f;
  //float rotation_y_ = 0.0f;
  glm::mat4 projection_;
  glm::mat4 view_;
  WormBulletCreature* target_;

  // Values used to delay the camera
  glm::vec3 local_translate_goal_ = glm::vec3(0.0f, 0.0f, -10.0f);
  glm::vec3 global_translate_goal_;
  float rotate_x_goal_ = 0.0f;
  float rotate_y_goal_ = 0.0f;

  glm::vec3 local_translate_ = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 global_translate_ = glm::vec3(0.0f, 0.0f, 0.0f);;
  float rotate_x_ = 0.0f;
  float rotate_y_ = 0.0f;
};

#endif // CAMERA_H