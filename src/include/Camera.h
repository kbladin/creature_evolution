#ifndef CAMERA_H
#define CAMERA_H

// External
#include <glm/glm.hpp>
#include <glm/ext.hpp>


class Camera {
public:
  Camera();
  Camera(glm::mat4 view, glm::mat4 projection);
  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix();
private:
  glm::mat4 projection_;
  glm::mat4 view_;
};

#endif // CAMERA_H