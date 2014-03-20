#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>


class Camera {
public:
  Camera();
  Camera(glm::mat4 view, glm::mat4 projection);
  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();
private:
  glm::mat4 projection_;
  glm::mat4 view_;
};

#endif // CAMERA_H