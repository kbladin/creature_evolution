#ifndef PASSIVEOBJECT_H
#define PASSIVEOBJECT_H

#include <vector>
#include <Entity.h>

class Node;

class PassiveObject : public Entity {
  public:
    PassiveObject();
    ~PassiveObject();
    virtual void Draw();
    virtual void Update();
    void SetNode(Node* node);

  private:
    std::vector<Node*> nodes_;
};

#endif	// PASSIVEOBJECT_H