#include <SceneManager.h>
#include <btBulletDynamicsCommon.h>
#include <iterator>
#include <vector>
#include <iostream>
#include <Box.h>
#include <WormBulletCreature.h>


void SceneManager::SetCamera(Camera cam) {
	cam_ = cam;
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

        full_transform = full_transform;
        
        node_to_add->SetTransform(full_transform);
        
        Box shape_to_add(scale.getX(), scale.getY(),
                 scale.getZ());

        shape_to_add.SetupBuffers();
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
    for(int i = 0; i  < nodelist_.size(); ++i) {
        nodelist_[i]->Render(cam_);
    }
}

void SceneManager::UpdateNodes() {
    for(int i = 0; i < nodelist_.size(); ++i) {
        nodelist_[i]->UpdateNode();
    }
}