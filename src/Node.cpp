#include <Node.h>

Node::Node(glm::mat4 transform) {
	transform_ = transform;
}

void Node::SetShape(Shape shape) {
	shape_ = shape;
}