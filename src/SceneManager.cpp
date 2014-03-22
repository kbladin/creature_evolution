#include "SceneManager.h"

void SceneManager::SetCamera(Camera cam) {
	cam_ = cam;
}

void SceneManager::AddNode(std::shared_ptr<Node> node_ptr) {
	nodelist_.push_back(node_ptr);
}

void SceneManager::CreateNodesFromBulletCreature(WormBulletCreature* worm) {
    
    std::vector<btRigidBody*> rigid_bodies_to_add = worm->GetRigidBodies();
    std::cout << "Rigid bodies from Worm loaded..." << std::endl;
    std::cout << "Number of rigid bodies in worm: " << rigid_bodies_to_add.size() << std::endl;



    for(int i = 0; i < rigid_bodies_to_add.size(); ++i) {
        
        std::shared_ptr<PhysicsNode> node_to_add(
                new PhysicsNode(rigid_bodies_to_add[i]));
        std::cout << "Shared ptr to PhysicsNode created" << "[" << i << "]" << std::endl;

        btTransform transform;

        rigid_bodies_to_add[i]->getMotionState()->getWorldTransform(transform);
        glm::mat4 full_transform(1.0f);
        transform.getOpenGLMatrix(glm::value_ptr(full_transform));
        

        std::cout << "Transform extracted" << "[" << i << "]" << std::endl;


        btBoxShape* btshape = (btBoxShape*) 
            rigid_bodies_to_add[i]->getCollisionShape();
        
        std::cout << "Collision shape extracted" << "[" << i << "]" << std::endl;

        btVector3 scale = btshape->getHalfExtentsWithoutMargin();

        full_transform = full_transform;
        
        node_to_add->SetTransform(full_transform);
        std::cout << "Transform set on node" << "[" << i << "]" << std::endl;
        
        Box shape_to_add(scale.getX(), scale.getY(),
                 scale.getZ());

        std::cout << "Shape created" << "[" << i << "]" << std::endl;

        node_to_add->SetShape(shape_to_add);
        std::cout << "Shape attached to Node" << "[" << i << "]" << std::endl;

        AddNode(node_to_add);
        std::cout << "Node added to nodelist" << "[" << i << "]" << std::endl;

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

void SceneManager::InitShapes() {
    for(int i = 0; i < nodelist_.size(); ++i) {
        nodelist_[i]->InitShape();
    }   
}