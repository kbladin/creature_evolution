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
    // Delay the signals
    float camera_speed = 0.1f;
    Delay(local_translate_, local_translate_goal_, camera_speed);
    Delay(rotate_x_, rotate_x_goal_, camera_speed);
    Delay(rotate_y_, rotate_y_goal_, camera_speed);
    global_translate_goal_ = glm::vec3(
            -target_->GetCenterOfMass().x(),
            -target_->GetCenterOfMass().y(),
            -target_->GetCenterOfMass().z());
    Delay(global_translate_, global_translate_goal_, camera_speed);

    // Create the matrices
    glm::mat4 local_translate_mat = glm::translate(local_translate_);
    glm::mat4 rotate_y_mat = glm::rotate(
            glm::mat4(1.0f),
            rotate_y_,
            glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotate_x_mat = glm::rotate(
            glm::mat4(1.0f),
            rotate_x_,
            glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 global_translate_mat = glm::translate(global_translate_);
    // Update the view matrix
    view_ =
            local_translate_mat *
            rotate_x_mat *
            rotate_y_mat *
            global_translate_mat; 
  }
  int width = SettingsManager::Instance()->GetFrameWidth();
  int height = SettingsManager::Instance()->GetFrameHeight();
  float aspect = width/(float)height;
  // Update the projection matrix
  projection_ = glm::perspective(45.0f, aspect, 0.1f, 100.0f);
}

void Camera::IncrementXrotation(float h){
  rotate_x_goal_ += h;
}
void Camera::IncrementYrotation(float h){
  rotate_y_goal_ += h;
}

template <class T>
void Camera::Delay(T& input, T end_val, float speed){
  if (speed < 0.0f && speed > 1.0f){
    speed = glm::clamp(speed, 0.0f, 1.0f);
    std::cout << "WARNING: clamping speed between 0.0 and 1.0" << std::endl;
  }
  input = (end_val - input) * speed + input;
}