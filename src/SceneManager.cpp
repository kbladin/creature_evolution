#include "SceneManager.h"

SceneManager* SceneManager::instance_ = NULL;

SceneManager::SceneManager(){
  //Fulplan!!!
  Plane plane_shape(glm::vec3(1.0f) * 100.0f);
  std::shared_ptr<Node> node_to_add(new Node());
  node_to_add->SetShape(plane_shape);
  AddNode(node_to_add);
}

SceneManager* SceneManager::Instance(){
  if (!instance_){
    instance_ = new SceneManager();
  }
  return instance_;
}

void SceneManager::SetCamera(Camera cam) {
  cam_ = cam;
}

Camera* SceneManager::GetCamera(){
  return &cam_;
}

void SceneManager::AddNode(std::shared_ptr<Node> node_ptr) {
  nodelist_.push_back(node_ptr);
}

void SceneManager::CreateNodesFromBulletCreature(WormBulletCreature* worm) {  
  std::vector<btRigidBody*> rigid_bodies_to_add = worm->GetRigidBodies();

  for(int i = 0; i < rigid_bodies_to_add.size(); ++i) {
    std::shared_ptr<PhysicsNode> node_to_add(
        new PhysicsNode(rigid_bodies_to_add[i]));
    btTransform transform;

    rigid_bodies_to_add[i]->getMotionState()->getWorldTransform(transform);
    glm::mat4 full_transform(1.0f);
    transform.getOpenGLMatrix(glm::value_ptr(full_transform));
    
    btBoxShape* btshape = (btBoxShape*) 
        rigid_bodies_to_add[i]->getCollisionShape();

    btVector3 scale = btshape->getHalfExtentsWithoutMargin();
    
    node_to_add->SetTransform(full_transform);
    
    Box shape_to_add(scale.getX(), scale.getY(),
        scale.getZ());

    node_to_add->SetShape(shape_to_add);
    AddNode(node_to_add);
  }
}

void SceneManager::PrintPhysicsNodes() {
	for(int i = 0; i < nodelist_.size(); ++i) {
		nodelist_[i]->DebugPrint();
	}
}

void SceneManager::RenderNodes() {
  // To make sure we use the same name
  const char* shader_name = "Basic";
  ShaderManager::Instance()->UseProgram(shader_name);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->Uniform1f("light_intensity", light_.intensity);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->Uniform3fv("light_color", 1, &light_.color.x);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->Uniform3fv(
                  "light_position_worldspace",
                  1,
                  &light_.position.x);
  glUseProgram(0);

  cam_.UpdateMatrices();
  for (int i = 0; i  < nodelist_.size(); ++i) {
    nodelist_[i]->Render(cam_);
  }
}

void SceneManager::UpdateNodes() {
  for(int i = 0; i < nodelist_.size(); ++i) {
    nodelist_[i]->UpdateNode();
  }
}

void SceneManager::InitShapes() {
  for(int i = 0; i < nodelist_.size(); ++i) {
    nodelist_[i]->InitShape();
  }   
}