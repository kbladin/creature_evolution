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
private:
  glm::mat4 projection_;
  glm::mat4 view_;
  WormBulletCreature* target_;
};

#endif // CAMERA_H