#include <Camera.h>

Camera::Camera() {
	//create default camera
    projection_ = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	view_       = glm::lookAt(
                              glm::vec3(0,3,-5), // Camera is at (4,3,-3), in World Space
                              glm::vec3(0,0,0), // and looks at the origin
                              glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                              );
}

Camera::Camera(glm::mat4 view, glm::mat4 projection) {
	view_ = view;
	projection_ = projection;
}

glm::mat4 Camera::getViewMatrix(){
  return view_;
}

glm::mat4 Camera::getProjectionMatrix(){
  return projection_;
}
