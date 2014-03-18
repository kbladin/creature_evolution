#include <Camera.h>

Camera::Camera() {
	//create default camera
	view_ = glm::mat4(1.0f);
	projection_ = glm::mat4(1.0f);
}

Camera::Camera(glm::mat4 view, glm::mat4 projection) {
	view_ = view;
	projection_ = projection;
}