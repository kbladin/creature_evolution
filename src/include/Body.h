#ifndef BODY_H
#define BODY_H

#include <vector>
#include "vec3.h"
#include "SettingsManager.h"
#include "TextureManager.h"

//! Joint describes the connection between instances of BodyTree.
/*!
  All variables except strength needs to be explicitly set after creating a
  joint. connection_root is the position on the parent where to put the
  connection. connection_branch is the position on the child where to put
  the connection. hinge_orientation is the EulerZYX-angles of how the joint
  is oriented. When angles are 0,0,0; the orientation is along the x-axis and
  the rotation is around the z-axis. upper_limit is the max angle the rotation
  can have. This should be a positive float value not greater than 2*pi.
  lower_limit works the same as upper_limit but with negative values. strength
  is calculated implicitly from the masses of the connected BodyTrees i
  not explicitly set. 
*/

struct Joint {
  // strength does not need to be explicitly set. 
  Joint() : strength(-1){}
  Vec3 connection_root;
  Vec3 connection_branch;
  Vec3 hinge_orientation;
  float upper_limit;
  float lower_limit;
  float strength;
};

//! A BodyTree is the tree structure describing the body.
/*!
  Several BodyTrees can be connected in a tree structure to build the creatures
  body. Every BodyTree has a root Joint which describes how it is connected
  to its parent. The root of the tree (which is defined as the head of the
  creature) have this Joint as a dummy Joint since it is not connected to
  a parent BodyTree. box_dim describes the dimensions on the box. 0,0,0 is the
  center of the box and when a dimension is set, it grows in both directions.
  Therefore 1,1,1 will give a box with dimensions 2,2,2. density is the density
  in kg/m^3 of the box. friction is a parameter between 0.0 and 1.0. The tree
  structure is composed by the body_list of each BodyTree. This is a
  std::vector of all the children.
*/

struct BodyTree {
  // A shape type should be defined instead of box_dim if we want to use
  // other shapes
  Vec3 box_dim;
  float density;
  float friction;
  //skipping orientation for now
  //Vec3 orientation;
  Joint root_joint;
  Material material;
  std::vector<BodyTree> body_list;

  int GetNumberOfElements();
  float GetMass();
  int GetNumberOfLeaves();
  float GetLowestPoint();
};

enum CreatureType{
  PONY, WORM, CRAWLER, HUMAN, TABLE, FROG
};

//! A Body contains the base of the BodyTree and is used to build the BulletCreature

class Body {
public:
  Body();
  BodyTree GetBodyRoot();
  int GetTotalNumberOfJoints();
private:
  BodyTree body_root_;
};

//! The class BodyFactory contains the functions for building the physical creatures

class BodyFactory {
public:
  // Creatures
  static BodyTree CreateLeggedBox(float scale = 1);
  static BodyTree CreateHuman();
  static BodyTree CreateWorm(int worm_length = 5);
  static BodyTree CreateCrawler(int length = 5);
  static BodyTree CreatePony();
  static BodyTree CreateFrog(float scale);
private:
  // Body parts
  static BodyTree CreateLeg(Vec3 scale);
  static BodyTree CreateArm(Vec3 scale);
  static BodyTree CreateFrogLeg(float scale);
};

#endif //BODY_H
