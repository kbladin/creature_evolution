#include "Camera.h"

//! Constructor, creates a default camera
/*!
  The default camera is located at (-10,3,0) and looks at (0,1,0).
*/
Camera::Camera() {
  projection_ = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  //create default camera
  view_ = glm::lookAt(glm::vec3(-10,3,0),
                      glm::vec3(0,0,0),
                      glm::vec3(0,1,0));	
}
//! Constructor that creates a camera from input matrices
/*!
  Sets the cameras view matrix and projection matrix as specified
  \param view matrix
  \param projection matrix
*/
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
//! Updates the internal matrices of the camera
/*!
  First the signals from input are delayed. This is for the camera to get a
  more smoother movement. Then the results are used to create the matrices that
  build up the view matrix. The projection matrix is default but uses the
  aspect ratio of the frame.
*/
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
//! Increment the x-rotation angle of the camera
void Camera::IncrementXrotation(float h){
  rotate_x_goal_ += h;
}
//! Increment the y-rotation angle of the camera
void Camera::IncrementYrotation(float h){
  rotate_y_goal_ += h;
}
//! Increment the z-position of the camera
void Camera::IncrementZposition(float h){
  local_translate_goal_ += glm::vec3(0.0f, 0.0f, h);
  local_translate_goal_.z = glm::clamp(local_translate_goal_.z, -100.0f, 0.0f);
}

//! Helper function for the camera
/*!
  This function takes class like float or glm::vec3. What it does is to delay
  a signal as if it was to follow y=1 as y=(1-e^(a*t)). The rise time depend
  on the speed parameter.
  \param input is the signal that will be changed to output
  (passed by reference)
  \param end_val is the value that the function should tend toward.
  \param speed determines the rise time. The higher, the faster.
  Speed should be between 0 and 1 and is otherwise clamped.
*/
template <class T>
void Camera::Delay(T& input, T end_val, float speed){
  if (speed < 0.0f && speed > 1.0f){
    speed = glm::clamp(speed, 0.0f, 1.0f);
    std::cout << "WARNING: clamping speed between 0.0 and 1.0" << std::endl;
  }
  input = (end_val - input) * speed + input;
}