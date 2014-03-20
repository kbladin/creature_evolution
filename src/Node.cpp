#include "Node.h"

Node::Node() {
	transform_ = glm::mat4(1.0f);
}

void Node::SetShape(Shape shape) {
	shape_ = shape;
}

void Node::DebugPrint() {
	std::cout << "Node transform: " << glm::to_string(transform_)
		 << std::endl;
}

void Node::SetTransform(glm::mat4 transform) {
	transform_ = transform;
}

void Node::SetPosition(glm::vec3 pos) {
	transform_ = glm::translate(glm::mat4(1.0f), pos);

}

void Node::Render(Camera camera) {
	shape_.Render(camera, transform_);
}

PhysicsNode::PhysicsNode(btRigidBody* body) {
	rigid_body_ = body;
}

void PhysicsNode::UpdateNode() {
	btTransform transform;

	rigid_body_->getMotionState()->getWorldTransform(transform);
	glm::mat4 full_transform(1.0f);
	transform.getOpenGLMatrix(glm::value_ptr(full_transform));
	
	SetTransform(full_transform);
}
