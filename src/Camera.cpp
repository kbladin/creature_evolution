#include "Camera.h"

Camera::Camera() {
  projection_ = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  //create default camera
  view_ = glm::lookAt(glm::vec3(-10,3,0),
                      glm::vec3(0,0,0),
                      glm::vec3(0,1,0));	
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

void Camera::SetTarget(WormBulletCreature* target){
  target_ = target;
}

void Camera::UpdateMatrices(){
  time_t timer;
  if (target_){
    glm::mat4 local_translate = glm::translate(glm::vec3(0.0f, 0.0f, -10.0f));
    glm::mat4 rotate_y = glm::rotate(
            glm::mat4(1.0f),
            45.0f,
            glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotate_x = glm::rotate(
            glm::mat4(1.0f),
            45.0f,
            glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 global_translate = glm::translate(glm::vec3(
            -target_->GetCenterOfMass().x(),
            -target_->GetCenterOfMass().y(),
            -target_->GetCenterOfMass().z()));
    view_ = local_translate * rotate_x * rotate_y * global_translate; 
    /*view_ = glm::lookAt(glm::vec3(-10,3,0),
                      glm::vec3(
                        target_->GetCenterOfMass().x(),
                        target_->GetCenterOfMass().y(),
                        target_->GetCenterOfMass().z()),
                      glm::vec3(0,1,0));*/
  }
  int width = SettingsManager::Instance()->GetFrameWidth();
  int height = SettingsManager::Instance()->GetFrameHeight();
  float aspect = width/(float)height;
  projection_ = glm::perspective(45.0f, aspect, 0.1f, 100.0f);
}