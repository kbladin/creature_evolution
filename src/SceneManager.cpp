#include "SceneManager.h"

SceneManager::SceneManager(){
  //Fulplan!!!
  Plane plane_shape(glm::vec3(1.0f) * 50.0f);
  std::shared_ptr<Node> node_to_add(new Node());
  node_to_add->SetShape(plane_shape);
  AddNode(node_to_add);
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
  cam_.UpdateMatrices();
  for(int i = 0; i  < nodelist_.size(); ++i) {
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