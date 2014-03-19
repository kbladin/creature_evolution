#include <SceneManager.h>
#include <btBulletDynamicsCommon.h>
#include <iterator>
#include <vector>
#include <iostream>
#include <Box.h>

SceneManager::SceneManager(btDiscreteDynamicsWorld* dynamics_world) {
	physics_world_ = dynamics_world;
	UpdateSceneNodes();
}
btDiscreteDynamicsWorld* SceneManager::GetPhysicsWorld() {
	return physics_world_;
}

//! Updates all the nodes from the physics world.
void SceneManager::UpdateSceneNodes() {

    btCollisionObjectArray& collisionObjects = 
    	physics_world_->getCollisionObjectArray();
    
    for (int i=0; i<collisionObjects.size(); ++i) {
        btCollisionObject* colObj = collisionObjects[i];
        btRigidBody* body = btRigidBody::upcast(colObj);

        //make sure we only grab rigid bodies
        //TODO: exclude the ground plane somehow
        if(body && body->getMotionState()) {
        	//get our pointer       
        	void* userpointer = body->getUserPointer();
        	btTransform transform;
     		body->getMotionState()->getWorldTransform(transform);
     		glm::mat4 full_transform(1.0f);

     		transform.getOpenGLMatrix(glm::value_ptr(full_transform));

        	if(userpointer) {
				//cast our userpointer to a Node pointer in order
				//to grab the ascociated Node
				Node* test_ptr = static_cast<Node*>(userpointer);
				test_ptr->SetTransform(full_transform);
        	}

        }
        
    }
}

void SceneManager::SetCamera(Camera cam) {
	cam_ = cam;
}

void SceneManager::AddNode(std::shared_ptr<Node> node_ptr) {
	nodelist_.push_back(node_ptr);
}

void SceneManager::SetSceneNodes() {
    btCollisionObjectArray& collisionObjects = 
    	physics_world_->getCollisionObjectArray();
    for (int i=0; i<collisionObjects.size(); ++i) {
        btCollisionObject* colObj = collisionObjects[i];
        btRigidBody* body = btRigidBody::upcast(colObj);

        if(body && body->getMotionState()) {
	        std::shared_ptr<Node> node_to_add(new Node());
        	btTransform transform;
     		body->getMotionState()->getWorldTransform(transform);
     		glm::mat4 full_transform(1.0f);
     		transform.getOpenGLMatrix(glm::value_ptr(full_transform));
	        node_to_add->SetTransform(full_transform);
            //TODO: check and create appropriate Shape
            btBoxShape* btshape = (btBoxShape*) body->getCollisionShape();
            btVector3 scale = btshape->getHalfExtentsWithoutMargin();

            Box shape_to_add(glm::vec3(scale.getX(), scale.getY(),
                 scale.getZ()));
            shape_to_add.SetupBuffers();
            node_to_add->SetShape(shape_to_add);

	        AddNode(node_to_add);	        
	        body->setUserPointer(node_to_add.get());	
        	//std::cout << "Added node!" << std::endl;
        }
        
    }
}

void SceneManager::PrintPhysicsNodes() {
	for(int i = 0; i < nodelist_.size(); ++i) {
		nodelist_[i]->DebugPrint();
	}
}

void SceneManager::RenderNodes() {
    for(int i = 0; i  < nodelist_.size(); ++i) {
        nodelist_[i]->Render();
    }
}