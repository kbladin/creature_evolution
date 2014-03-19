#include <Node.h>
#include <iostream>

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

void Node::Render() {
	shape_.Render(transform_);
}
