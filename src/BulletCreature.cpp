#include "BulletCreature.h"

BulletCreature::BulletCreature(Creature* blueprint) {
    blueprint_ = blueprint;
    blueprint->InitBulletBody(m_bodies_,m_joints_);
}

BulletCreature::~BulletCreature(void) {
    for(int i=0; i < m_joints_.size(); i++){
        delete m_joints_[i];
        m_joints_[i] = 0;
    }

    for(int i=0; i < m_bodies_.size(); i++){
        delete m_bodies_[i]->getMotionState();
        delete m_bodies_[i];
        m_bodies_[i] = 0;
    }
}

void BulletCreature::UpdateMotors(const vector<float>& input) {
    std::vector<float> signal = blueprint_->CalculateBrainOutput(input);
    for(int i=0; i < m_joints_.size(); i++) {
        m_joints_[i]->enableAngularMotor(true, 20.0*signal[i], 10.0);
    }
}
