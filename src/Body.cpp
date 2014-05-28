#include "include/Body.h"

#ifndef M_PI
  #define M_PI 3.14159265359
#endif

//! Function used to get the total number of BodyTrees in a BodyTree.
/*!
\return The total number of BodyTree elements in a BodyTree.
*/
int BodyTree::GetNumberOfElements(){
  int result = 0;
  if (body_list.size() == 0)
    result = 0; // Itself
  else {
    for (int i = 0; i < body_list.size(); ++i){
      result += body_list[i].GetNumberOfElements();
    }
  }
  return result + 1; // Children + itself
}

//! Function used to get the mass of a BodyTree.
/*!
\return Only the mass of the current box and not its children.
*/
float BodyTree::GetMass(){
  return box_dim.x * box_dim.y * box_dim.z * density;
}

//! Function used to get the position of the lowest point of the BodyTree.
/*!
  This function is recursive and used to set the y-position of a creature.
  When setting the position of a creature; it will be built from its root
  (its head). Therefore, one needs to know where to position the root to make
  the creature stand on the ground to begin with.
\return The lowest coordinate of the BodyTree.
*/
float BodyTree::GetLowestPoint() {
  // Base case
  if (body_list.size() == 0) {
    return - box_dim.y + root_joint.connection_root.y
        - root_joint.connection_branch.y;
  } else { // Recursion
    float lowest_child = 0;
    for (int i = 0; i < body_list.size(); ++i){
      float lowest = body_list[i].GetLowestPoint();
      if (lowest < lowest_child)
        lowest_child = lowest +
              root_joint.connection_root.y -
              root_joint.connection_branch.y;
    }
    return lowest_child;
  }
}

//! Constructor of the Body class.
/*!
  A Body will be created depending of the creature type set in the
  SettingsManager.
*/
Body::Body(){
  int creature_type = SettingsManager::Instance()->GetCreatureType();

  switch(creature_type){
    case PONY:
      body_root_ = BodyFactory::CreatePony();
      break;
    case WORM:
      body_root_ = BodyFactory::CreateWorm();
      break;
    case CRAWLER:
      body_root_ = BodyFactory::CreateCrawler();
      break;
    case HUMAN:
      body_root_ = BodyFactory::CreateHuman();
      break;
    case TABLE:
      body_root_ = BodyFactory::CreateLeggedBox();
      break;
    case FROG:
      body_root_ = BodyFactory::CreateFrog(2);
      break;
    default:
      std::cout << "not valid creature.. creating worm as default!" <<
              std::endl;
      body_root_ = BodyFactory::CreateWorm();
      break;
  }
}

//! Get function.
/*!
  \return The root of the BodyTree (head of the creature).
*/
BodyTree Body::GetBodyRoot() {
  return body_root_;
}

//! Counting the total number of Joints in the BodyTree
/*!
  \return The total number of Joints in the BodyTree.
*/
int Body::GetTotalNumberOfJoints(){
  return body_root_.GetNumberOfElements() - 1; // Do not count itself
}

//! Creating a worm creature and returning its head.
/*!
\param worm_length is the number of segments the worm is built of.
\return A BodyTree structure for the head of the worm.
*/
BodyTree BodyFactory::CreateWorm(int worm_length){
  float density = 1000.0f;
  float friction_body = 0.5f;

  // varje segment på masken
  BodyTree body_segment;
  body_segment.box_dim = Vec3(0.1,0.05,0.1);
  body_segment.density = density;
  body_segment.friction = friction_body;

  // joint
  Joint joint;
  joint.connection_root = Vec3(0.0f,0.0f,-body_segment.box_dim.z);
  joint.connection_branch = Vec3(0.0f,0.0f,body_segment.box_dim.z);
  joint.hinge_orientation = Vec3(0.0, M_PI/2, 0.0);

  joint.upper_limit = M_PI*0.3;
  joint.lower_limit = -M_PI*0.3;

  body_segment.root_joint = joint;

  BodyTree parent = body_segment;
  BodyTree child = body_segment;

  for(int i=0; i<worm_length; i++){
    parent.body_list.push_back(child);
    parent.root_joint = joint;
    child = parent;
    parent = body_segment;
  }
  
  // Trying another texture for the head
  child.material.SetDiffuseTexture("test_texture");
  return child;
}

//! Creating a crawler creature and returning its head.
/*!
  This is a lizard like creature with segments and legs.
  \param length is the number of segments the creature is built of.
  \return A BodyTree structure for the head of the creature.
*/
BodyTree BodyFactory::CreateCrawler(int length){
  float density = 1000.0f;
  float friction_body = 0.5f;

  // Body
  BodyTree body_segment;
  body_segment.box_dim = Vec3(0.1,0.05,0.15);
  body_segment.density = density;
  body_segment.friction = friction_body;

  // Leg
  BodyTree left_leg;
  left_leg.box_dim = Vec3(0.1,0.05,0.05);
  left_leg.density = density;
  left_leg.friction = friction_body;
  BodyTree right_leg = left_leg;

  // joint
  Joint joint;
  joint.connection_root = Vec3(0.0f,0.0f,-body_segment.box_dim.z);
  joint.connection_branch = Vec3(0.0f,0.0f,body_segment.box_dim.z);
  joint.hinge_orientation = Vec3(M_PI/2, 0.0, 0.0);

  joint.upper_limit = M_PI*0.3;
  joint.lower_limit = -M_PI*0.3;

  // Leg joint
  Joint left_leg_joint;
  left_leg_joint.connection_root = Vec3(body_segment.box_dim.x,0.0f,0.0f);
  left_leg_joint.connection_branch = Vec3(-left_leg.box_dim.x,0.0f,0.0f);
  left_leg_joint.hinge_orientation = Vec3(0.0, 0.0, 0.0);
  left_leg_joint.upper_limit = M_PI*0.3;
  left_leg_joint.lower_limit = -M_PI*0.3;

  Joint right_leg_joint = left_leg_joint;
  left_leg_joint.connection_root = Vec3(-left_leg.box_dim.x,0.0f,0.0f);
  left_leg_joint.connection_branch = Vec3(body_segment.box_dim.x,0.0f,0.0f);

  body_segment.root_joint = joint;
  left_leg.root_joint = left_leg_joint;
  right_leg.root_joint = right_leg_joint;

  BodyTree parent = body_segment;
  BodyTree child = body_segment;

  for(int i=0; i<length - 1; i++){

    child = parent;
    parent = body_segment;

    parent.body_list.push_back(left_leg);
    parent.body_list.push_back(right_leg);

    parent.body_list.push_back(child);
    parent.root_joint = joint;
  }

  // Head
  body_segment.body_list.push_back(child);

  return body_segment;
}

//! Creating a pony creature and returning its head.
/*!
  This is a simple description of a pony.
  \return A BodyTree structure for the head of the creature.
*/
BodyTree BodyFactory::CreatePony(){

  float density = 1000.0f;

  BodyTree torso;
  torso.box_dim = Vec3(0.25, 0.17, 0.4);
  torso.density = density;
  torso.friction = 0.5;

  BodyTree right_front_leg;// = BodyFactory::CreateLeg(Vec3(1,1,1));
  right_front_leg.box_dim = Vec3(0.07, 0.15, 0.07);
  right_front_leg.density = density;
  right_front_leg.friction = 0.8;

  BodyTree head;
  head.box_dim = Vec3(0.12, 0.12, 0.2);
  head.density = density;
  head.friction = 0.5;

  Joint neck_joint;
  neck_joint.connection_root = Vec3(0.0,0.0f,-head.box_dim.z);
  neck_joint.connection_branch = Vec3(
            0.0,
            torso.box_dim.y,
            torso.box_dim.z - 0.1);
  neck_joint.hinge_orientation = Vec3(0.0, M_PI/2, 0.0);
  neck_joint.upper_limit = M_PI*0.3;
  neck_joint.lower_limit = -M_PI*0.3;

  right_front_leg.root_joint.connection_root = Vec3(
          torso.box_dim.x - right_front_leg.box_dim.x,
          -torso.box_dim.y,
          -torso.box_dim.z + right_front_leg.box_dim.z);
  right_front_leg.root_joint.connection_branch =
          Vec3(0.0, right_front_leg.box_dim.y, 0.0);
  right_front_leg.root_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  right_front_leg.root_joint.upper_limit = M_PI*0.3;
  right_front_leg.root_joint.lower_limit = -M_PI*0.3;

  BodyTree left_front_leg = right_front_leg;
  left_front_leg.root_joint.connection_root = Vec3(
          -torso.box_dim.x + left_front_leg.box_dim.x,
          -torso.box_dim.y,
          -torso.box_dim.z + left_front_leg.box_dim.z);
  BodyTree right_back_leg = right_front_leg;
  right_back_leg.root_joint.connection_root = Vec3(
          torso.box_dim.x - right_back_leg.box_dim.x,
          -torso.box_dim.y,
          torso.box_dim.z - right_back_leg.box_dim.z);
  BodyTree left_back_leg = right_front_leg;
  left_back_leg.root_joint.connection_root = Vec3(
          -torso.box_dim.x + left_back_leg.box_dim.x,
          -torso.box_dim.y,
          torso.box_dim.z - left_back_leg.box_dim.z);

  head.root_joint.strength = 10;
  right_front_leg.root_joint.strength = 10;
  left_front_leg.root_joint.strength = 10;
  right_back_leg.root_joint.strength = 10;
  left_back_leg.root_joint.strength = 10;

  torso.root_joint = neck_joint;

  torso.body_list.push_back(right_front_leg);
  torso.body_list.push_back(left_front_leg);
  torso.body_list.push_back(right_back_leg);
  torso.body_list.push_back(left_back_leg);

  head.body_list.push_back(torso);

  return head;

}

//! Creating a human creature and returning its head.
/*!
  An advanced description of a human. Probably a bit too advanced for the
  current brain to handle. Mostly lying on the ground and shaking but can
  possibly do some interesting movements (or poses).
  \return A BodyTree structure for the head of the creature.
*/
BodyTree BodyFactory::CreateHuman() {
  // Create all body parts and joints
  BodyTree head;
  head.box_dim = Vec3(0.07, 0.1, 0.1);
  head.density = 1000.0f;
  head.friction = 0.5;

  BodyTree neck;
  neck.box_dim = Vec3(0.05, 0.07, 0.05);
  neck.density = 1000.0f;
  neck.friction = 0.5;

  Joint neck_head_joint;
  neck_head_joint.connection_root = Vec3(0.0,0.0,0.0f);
  neck_head_joint.connection_branch = Vec3(0.0f,neck.box_dim.y,0.0f);
  neck_head_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  neck_head_joint.upper_limit = M_PI * 0.4;
  neck_head_joint.lower_limit = -M_PI * 0.4;

  BodyTree rib_cage;
  rib_cage.box_dim = Vec3(0.15, 0.15, 0.1);
  rib_cage.density = 1000.0f;
  rib_cage.friction = 0.5;

  Joint neck_rib_cage_joint;
  neck_rib_cage_joint.connection_root = Vec3(0.0,-neck.box_dim.y,0.0f);
  neck_rib_cage_joint.connection_branch = Vec3(0.0f,rib_cage.box_dim.y,0.0f);
  neck_rib_cage_joint.hinge_orientation = Vec3(M_PI/2,0.0,0.0);
  neck_rib_cage_joint.upper_limit = M_PI * 0.4;
  neck_rib_cage_joint.lower_limit = -M_PI * 0.4;

  BodyTree left_shoulder;
  left_shoulder.box_dim = Vec3(0.07, 0.07, 0.07);
  left_shoulder.density = 1000.0f;
  left_shoulder.friction = 0.5;

  BodyTree right_shoulder = left_shoulder;

  Joint left_shoulder_rib_cage_joint;
  left_shoulder_rib_cage_joint.connection_root = Vec3(
          -rib_cage.box_dim.x,
          rib_cage.box_dim.y - left_shoulder.box_dim.y,
          0.0f);
  left_shoulder_rib_cage_joint.connection_branch = Vec3(
          left_shoulder.box_dim.x,
          0.0f,
          0.0f);
  left_shoulder_rib_cage_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  left_shoulder_rib_cage_joint.upper_limit = M_PI * 0.7;
  left_shoulder_rib_cage_joint.lower_limit = -M_PI * 0.3;

  Joint right_shoulder_rib_cage_joint = left_shoulder_rib_cage_joint;
  right_shoulder_rib_cage_joint.connection_root = Vec3(
          rib_cage.box_dim.x,
          rib_cage.box_dim.y - left_shoulder.box_dim.y,
          0.0f);
  right_shoulder_rib_cage_joint.connection_branch = Vec3(
          -right_shoulder.box_dim.x,
          0.0f,
          0.0f);

  BodyTree left_arm = BodyFactory::CreateArm(Vec3(1,1,1));
  BodyTree right_arm = left_arm;

  Joint left_arm_shoulder_joint;
  left_arm_shoulder_joint.connection_root = Vec3(0.0,0.0,0.0);
  left_arm_shoulder_joint.connection_branch = Vec3(
          0.0,
          left_arm.box_dim.y,
          0.0);
  left_arm_shoulder_joint.hinge_orientation = Vec3(0.0,0.0,0.0);
  left_arm_shoulder_joint.upper_limit = M_PI * 0.7;
  left_arm_shoulder_joint.lower_limit = 0.0;

  Joint right_arm_shoulder_joint = left_arm_shoulder_joint;
  right_arm_shoulder_joint.hinge_orientation = Vec3(0.0,0.0,0.0);
  right_arm_shoulder_joint.upper_limit = M_PI * 0.0;
  right_arm_shoulder_joint.lower_limit = -M_PI * 0.7;

  BodyTree belly;
  belly.box_dim = Vec3(0.15, 0.07, 0.1);
  belly.density = 1000.0f;
  belly.friction = 0.5;

  Joint spine_joint_upper;
  spine_joint_upper.connection_root = Vec3(0.0,-rib_cage.box_dim.y,0.0f);
  spine_joint_upper.connection_branch = Vec3(0.0f,belly.box_dim.y,0.0f);
  spine_joint_upper.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  spine_joint_upper.upper_limit = M_PI * 0.2;
  spine_joint_upper.lower_limit = -M_PI * 0.2;

  Joint spine_joint_lower = spine_joint_upper;
  spine_joint_lower.connection_root = Vec3(0.0,-belly.box_dim.y,0.0f);

  BodyTree pelvis;
  pelvis.box_dim = Vec3(0.15, 0.1, 0.1);
  pelvis.density = 1000.0f;
  pelvis.friction = 0.5;

  BodyTree right_hip_bone;
  right_hip_bone.box_dim = Vec3(0.07, 0.07, 0.07);
  right_hip_bone.density = 1000.0f;
  right_hip_bone.friction = 0.5;

  BodyTree left_hip_bone = right_hip_bone;

  Joint left_hip;
  left_hip.connection_root = Vec3(
          -pelvis.box_dim.x + left_hip_bone.box_dim.x/2,
          -pelvis.box_dim.y,
          0.0f);
  left_hip.connection_branch = Vec3(0.0f,right_hip_bone.box_dim.y,0.0f);
  left_hip.hinge_orientation = Vec3(M_PI/2,0.0,0.0);
  left_hip.upper_limit = 0.0;
  left_hip.lower_limit = -M_PI * 0.4;

  Joint right_hip = left_hip;
  right_hip.connection_root = Vec3(
          pelvis.box_dim.x  - right_hip_bone.box_dim.x/2,
          -pelvis.box_dim.y,
          0.0f);
  right_hip.upper_limit = M_PI * 0.4;
  right_hip.lower_limit = 0.0;

  BodyTree right_leg = BodyFactory::CreateLeg(Vec3(1,1,1));
  right_leg.root_joint.connection_root = Vec3(0.0, 0.0, 0.0);
  right_leg.root_joint.connection_branch =
          Vec3(0.0, right_leg.box_dim.y, 0.0);
  right_leg.root_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  right_leg.root_joint.upper_limit = M_PI*0.5;
  right_leg.root_joint.lower_limit = 0.0;

  BodyTree left_leg = right_leg;

  // Connect the joints
  right_hip_bone.root_joint = right_hip;
  left_hip_bone.root_joint = left_hip;

  left_arm.root_joint = left_arm_shoulder_joint;
  right_arm.root_joint = right_arm_shoulder_joint;

  left_shoulder.root_joint = left_shoulder_rib_cage_joint;
  right_shoulder.root_joint = right_shoulder_rib_cage_joint;

  pelvis.root_joint = spine_joint_lower;
  belly.root_joint = spine_joint_upper;
  rib_cage.root_joint = neck_rib_cage_joint;
  neck.root_joint = neck_head_joint;
  rib_cage.root_joint = neck_rib_cage_joint;

  // Add all branches
  right_hip_bone.body_list.push_back(right_leg);
  left_hip_bone.body_list.push_back(left_leg);

  pelvis.body_list.push_back(right_hip_bone);
  pelvis.body_list.push_back(left_hip_bone);

  belly.body_list.push_back(pelvis);
  rib_cage.body_list.push_back(belly);
  left_shoulder.body_list.push_back(left_arm);
  right_shoulder.body_list.push_back(right_arm);
  rib_cage.body_list.push_back(left_shoulder);
  rib_cage.body_list.push_back(right_shoulder);

  neck.body_list.push_back(rib_cage);
  head.body_list.push_back(neck);

  return head;
}

//! Creating a table with human legs.
/*!
  \param scale is the non absolute scale of the creature.
  \return A BodyTree structure for the box torso where the legs are connected.
*/
BodyTree BodyFactory::CreateLeggedBox(float scale) {

  BodyTree torso;
  torso.box_dim = Vec3(0.3 * scale, 0.1 * scale, 0.5 * scale);
  torso.density = 10.0f;
  torso.friction = 0.5;

  BodyTree right_front_leg = BodyFactory::CreateLeg(
          Vec3(scale, 0.5*scale, scale));
  right_front_leg.root_joint.connection_root = Vec3(
          torso.box_dim.x - right_front_leg.box_dim.x,
          -torso.box_dim.y,
          -torso.box_dim.z + right_front_leg.box_dim.z);
  right_front_leg.root_joint.connection_branch =
          Vec3(0.0, right_front_leg.box_dim.y, 0.0);
  right_front_leg.root_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  right_front_leg.root_joint.upper_limit = M_PI*0.2f;
  right_front_leg.root_joint.lower_limit = 0.0f;

  BodyTree left_front_leg = right_front_leg;
  left_front_leg.root_joint.connection_root = Vec3(
          -torso.box_dim.x + left_front_leg.box_dim.x,
          -torso.box_dim.y,
          -torso.box_dim.z + left_front_leg.box_dim.z);
  BodyTree right_back_leg = right_front_leg;
  right_back_leg.root_joint.connection_root = Vec3(
          torso.box_dim.x - right_back_leg.box_dim.x,
          -torso.box_dim.y,
          torso.box_dim.z - right_back_leg.box_dim.z);
  BodyTree left_back_leg = right_front_leg;
  left_back_leg.root_joint.connection_root = Vec3(
          -torso.box_dim.x + left_back_leg.box_dim.x,
          -torso.box_dim.y,
          torso.box_dim.z - left_back_leg.box_dim.z);

  torso.body_list.push_back(right_front_leg);
  torso.body_list.push_back(left_front_leg);
  torso.body_list.push_back(right_back_leg);
  torso.body_list.push_back(left_back_leg);

  return torso;
}

//! Creating a frog creature and returning its head.
/*!
  \param scale is the non absolute scale of the creature.
  \return A BodyTree structure for the head of the creature.
*/
BodyTree BodyFactory::CreateFrog(float scale){
  // Body parts
  BodyTree head;
  head.box_dim = Vec3(0.05, 0.025, 0.05) * scale;
  head.density = 1000.0f;
  head.friction = 0.2;

  BodyTree torso;
  torso.box_dim = Vec3(0.07, 0.03, 0.1) * scale;
  torso.density = 1000.0f;
  torso.friction = 0.2;

  BodyTree left_leg = CreateFrogLeg(scale);
  BodyTree right_leg = left_leg;

  BodyTree upper_arm;
  upper_arm.box_dim = Vec3(0.02, 0.04, 0.02) * scale;
  upper_arm.density = 1000.0f;
  upper_arm.friction = 0.2;

  BodyTree left_upper_arm = upper_arm;
  BodyTree right_upper_arm = upper_arm;

  BodyTree left_lower_arm = upper_arm;
  left_lower_arm.friction = 0.8;
  BodyTree right_lower_arm = upper_arm;
  right_lower_arm.friction = 0.8;

  BodyTree left_eye;
  left_eye.box_dim = Vec3(0.015, 0.015, 0.015) * scale;
  left_eye.density = 1000.0f;
  left_eye.friction = 0.2;

  BodyTree right_eye = left_eye;

  // Joints
  Joint neck_joint;
  neck_joint.connection_root = Vec3(0.0, 0.0, -head.box_dim.z);
  neck_joint.connection_branch = Vec3(0.0, torso.box_dim.y, torso.box_dim.z);
  neck_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  neck_joint.upper_limit = M_PI*0.2;
  neck_joint.lower_limit = -M_PI*0.2;
  
  Joint left_leg_joint;
  left_leg_joint.connection_root = Vec3(
          torso.box_dim.x,
          0.0,
          -torso.box_dim.z);
  left_leg_joint.connection_branch = Vec3(0.0, 0.0, -left_leg.box_dim.z);
  left_leg_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  left_leg_joint.upper_limit = M_PI*0.15;
  left_leg_joint.lower_limit = -M_PI*0.8;

  Joint right_leg_joint = left_leg_joint;
  left_leg_joint.connection_root = Vec3(
          -torso.box_dim.x,
          0.0,
          -torso.box_dim.z);
  left_leg_joint.connection_branch = Vec3(0.0, 0.0, -right_leg.box_dim.z);

  Joint left_shoulder_joint;
  left_shoulder_joint.connection_root = Vec3(
          -torso.box_dim.x,
          -torso.box_dim.y,
          torso.box_dim.z);
  left_shoulder_joint.connection_branch = Vec3(0.0, upper_arm.box_dim.y, 0.0);
  left_shoulder_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  left_shoulder_joint.upper_limit = M_PI*0.4;
  left_shoulder_joint.lower_limit = -M_PI*0.4;

  Joint right_shoulder_joint = left_shoulder_joint;
  right_shoulder_joint.connection_root = Vec3(
          torso.box_dim.x,
          -torso.box_dim.y,
          torso.box_dim.z);
  right_shoulder_joint.connection_branch = Vec3(0.0, upper_arm.box_dim.y, 0.0);

  Joint elbow_joint;
  elbow_joint.connection_root = Vec3(0.0, -upper_arm.box_dim.y, 0.0);
  elbow_joint.connection_branch = Vec3(0.0, right_lower_arm.box_dim.y, 0.0);
  elbow_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  elbow_joint.upper_limit = M_PI*0.4;
  elbow_joint.lower_limit = -M_PI*0.0;

  Joint left_eye_joint;
  left_eye_joint.connection_root = Vec3(
          head.box_dim.x - left_eye.box_dim.x,
          head.box_dim.y,
          0.0);
  left_eye_joint.connection_branch = Vec3(0.0, -left_eye.box_dim.y, 0.0);
  left_eye_joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  left_eye_joint.upper_limit = M_PI*0.0;
  left_eye_joint.lower_limit = -M_PI*0.0;

  Joint right_eye_joint = left_eye_joint;
  right_eye_joint.connection_root = Vec3(
          -head.box_dim.x + left_eye.box_dim.x,
          head.box_dim.y,
          0.0);
  right_eye_joint.connection_branch = Vec3(0.0, -right_eye.box_dim.y, 0.0);

  // Connect
  left_leg.root_joint = left_leg_joint;
  right_leg.root_joint = right_leg_joint;
  torso.root_joint = neck_joint;
  left_upper_arm.root_joint = left_shoulder_joint;
  right_upper_arm.root_joint = right_shoulder_joint;
  right_lower_arm.root_joint = elbow_joint;
  left_lower_arm.root_joint = elbow_joint;
  left_eye.root_joint = left_eye_joint;
  right_eye.root_joint = right_eye_joint;
  // Add
  right_upper_arm.body_list.push_back(right_lower_arm);
  left_upper_arm.body_list.push_back(left_lower_arm);
  torso.body_list.push_back(left_leg);
  torso.body_list.push_back(right_leg);
  torso.body_list.push_back(left_upper_arm);
  torso.body_list.push_back(right_upper_arm);
  head.body_list.push_back(torso);
  head.body_list.push_back(left_eye);
  head.body_list.push_back(right_eye);

  return head;
}

//! Internal function for creating a human leg.
/*!
  \param scale is the non absolute scale of the leg.
  \return A BodyTree structure for upper leg.
*/
BodyTree BodyFactory::CreateLeg(Vec3 scale) {

  BodyTree upper_leg;
  upper_leg.box_dim = Vec3(0.07 * scale.x, 0.17 * scale.y, 0.07 * scale.z);
  upper_leg.density = 1000.0f;
  upper_leg.friction = 0.8;

  BodyTree lower_leg = upper_leg;

  lower_leg.box_dim = Vec3(0.05 * scale.x, 0.17 * scale.y, 0.05 * scale.z);

  BodyTree foot;
  foot.box_dim = Vec3(0.07 * scale.x, 0.03 * scale.y, 0.12 * scale.z);
  foot.density = 1000.0f;
  foot.friction = 0.9;

  // Joints
  Joint knee;
  knee.connection_root = Vec3(0.0f,-upper_leg.box_dim.y,0.0f);
  knee.connection_branch = Vec3(0.0f,lower_leg.box_dim.y,0.0f);
  knee.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  knee.upper_limit = 0.0;
  knee.lower_limit = -M_PI*0.9;

  Joint ancle;
  ancle.connection_root = Vec3(0.0f,-lower_leg.box_dim.y,0.0);
  ancle.connection_branch = Vec3(
          0.0f,
          0.0f,
          -foot.box_dim.z + lower_leg.box_dim.z);
  ancle.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  ancle.upper_limit = M_PI*0.1;
  ancle.lower_limit = -M_PI*0.25;

  foot.root_joint = ancle; 
  lower_leg.root_joint = knee;

  lower_leg.body_list.push_back(foot);
  upper_leg.body_list.push_back(lower_leg);

  return upper_leg;
}

//! Internal function for creating an arm for the human.
/*!
  \param scale is the non absolute scale of the arm.
  \return A BodyTree structure for upper arm.
*/
BodyTree BodyFactory::CreateArm(Vec3 scale) {
  BodyTree upper_arm;
  upper_arm.box_dim = Vec3(0.05 * scale.x, 0.15 * scale.y, 0.05 * scale.z);
  upper_arm.density = 1000.0f;
  upper_arm.friction = 0.8;

  BodyTree lower_arm = upper_arm;

  BodyTree hand;
  hand.box_dim = Vec3(0.025 * scale.x, 0.07 * scale.y, 0.05 * scale.z);
  hand.density = 1000.0f;
  hand.friction = 0.9;

  // Joints
  Joint elbow;
  elbow.connection_root = Vec3(0.0f,-upper_arm.box_dim.y,0.0f);
  elbow.connection_branch = Vec3(0.0f,lower_arm.box_dim.y,0.0f);
  elbow.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  elbow.upper_limit = M_PI*0.9;
  elbow.lower_limit = 0.0;

  Joint wrist;
  wrist.connection_root = Vec3(0.0f,-lower_arm.box_dim.y,0.0);
  wrist.connection_branch = Vec3(0.0f,hand.box_dim.y, 0.0);
  wrist.hinge_orientation = Vec3(M_PI/2,0.0,0.0);
  wrist.upper_limit = M_PI*0.1;
  wrist.lower_limit = -M_PI*0.3;

  hand.root_joint = wrist; 
  lower_arm.root_joint = elbow;

  lower_arm.body_list.push_back(hand);
  upper_arm.body_list.push_back(lower_arm);

  return upper_arm;
}

//! Internal function for creating a leg for the frog.
/*!
  \param scale is the non absolute scale of the leg.
  \return A BodyTree structure for the upper leg.
*/
BodyTree BodyFactory::CreateFrogLeg(float scale) {

  BodyTree upper_leg;
  upper_leg.box_dim = Vec3(0.02, 0.02, 0.08) * scale;
  upper_leg.density = 1000.0f;
  upper_leg.friction = 0.2;

  BodyTree lower_leg = upper_leg;
  lower_leg.box_dim = Vec3(0.02, 0.08, 0.02) * scale;

  BodyTree foot = upper_leg;
  foot.box_dim = Vec3(0.02, 0.01, 0.08) * scale;
  foot.density = 1000.0f;
  foot.friction = 0.9;

  // Joints
  Joint knee;
  knee.connection_root = Vec3(0.0f,0.0,upper_leg.box_dim.z);
  knee.connection_branch = Vec3(0.0f,lower_leg.box_dim.y,0.0f);
  knee.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  knee.upper_limit = M_PI*0.4;
  knee.lower_limit = -M_PI*0.4;

  Joint ancle;
  ancle.connection_root = Vec3(0.0f,-lower_leg.box_dim.y,0.0);
  ancle.connection_branch = Vec3(
          0.0f,
          0.0f,
          -foot.box_dim.z + lower_leg.box_dim.z);
  ancle.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
  ancle.upper_limit = M_PI*0.4;
  ancle.lower_limit = -M_PI*0.4;

  foot.root_joint = ancle; 
  lower_leg.root_joint = knee;

  lower_leg.body_list.push_back(foot);
  upper_leg.body_list.push_back(lower_leg);

  return upper_leg;
}