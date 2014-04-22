#include "PassiveObject.h"
#include "Node.h"
#include "Scene.h"

PassiveObject::PassiveObject() {
}

PassiveObject::~PassiveObject() {
  for (int i = 0; i < nodes_.size(); ++i) {
    delete nodes_[i];
  }
}

void PassiveObject::SetNode(Node* node) {
  nodes_.push_back(node);
}

void PassiveObject::Draw() {
  if(nodes_.empty())
    return;

  for (int i = 0; i < nodes_.size(); ++i) {
    nodes_[i]->Render(Scene::Instance()->GetCamera());
  }
}

void PassiveObject::Update() {
  
}