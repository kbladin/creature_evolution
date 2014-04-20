#ifndef CEMOTIONSTATE_H
#define CEMOTIONSTATE_H

#include <btBulletDynamicsCommon.h>
#include "Node.h"

class CEMotionState : public btMotionState {

public:
	CEMotionState(const btTransform &initpos, Node* node);
	virtual ~CEMotionState() {};

	void SetNode(Node* node);
	virtual void getWorldTransform(btTransform &worldTrans) const;
	virtual void setWorldTransform(const btTransform &worldTrans);

protected:
	Node* node_;
	btTransform init_pos_;

};

#endif // CEMOTIONSTATE_H