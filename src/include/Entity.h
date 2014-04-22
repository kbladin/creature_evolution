#ifndef ENTITY_H
#define ENTITY_H

class Entity {

public:
	Entity() {};
	virtual ~Entity(){};
	virtual void Draw() = 0;
  virtual void Update() = 0;

};

#endif // ENTITY_H