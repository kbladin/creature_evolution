#include "Camera.h"

Camera::Camera() {
	//create default camera
  projection_ = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	view_       = glm::lookAt(glm::vec3(-10,3,0),
                              glm::vec3(0,0,0),
                              glm::vec3(0,1,0)
                            );
}

Camera::Camera(glm::mat4 view, glm::mat4 projection) {
	view_ = view;
	projection_ = projection;
}

glm::mat4 Camera::GetViewMatrix(){
  return view_;
}

glm::mat4 Camera::GetProjectionMatrix(){
  return projection_;
}
