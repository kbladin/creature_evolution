#include "CEMotionState.h"
#include "Node.h"

CEMotionState::CEMotionState(const btTransform &initpos, Node* node) {
	node_ = node;
	init_pos_ = initpos;
}

void CEMotionState::SetNode(Node* node) {
	node_ = node;
}

void CEMotionState::getWorldTransform(btTransform &worldTrans) const {
	worldTrans = init_pos_;
}

void CEMotionState::setWorldTransform(const btTransform &worldTrans) {
	if(node_ == nullptr) {
		return; //return before node is set
	}

	glm::mat4 new_transform(1.0f);
  	worldTrans.getOpenGLMatrix(glm::value_ptr(new_transform));
  	node_->SetTransform(new_transform);
}
