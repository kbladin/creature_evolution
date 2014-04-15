#ifndef BODY_H
#define BODY_H

#include <vector>
#include "vec3.h"


struct Joint {
    //alternative to connection_root/branch is to give each BodyTree a position in worldspace and each joint a connection point in worldspace, which is better?
    Vec3 connection_root;
    Vec3 connection_branch;
    Vec3 hinge_orientation;
    float upper_limit;
    float lower_limit;
};

struct BodyTree {
    //a shape type should be defined instead of box_dim if we want to use other shapes
    Vec3 box_dim;
    float mass;
    float friction;
    //skipping orientation for now
    //Vec3 orientation;

    std::vector<Joint> joint_list;
    std::vector<BodyTree> body_list;
};

class Body {
public:
  Body(){}
  BodyTree GetBodyRoot();
};

#endif //BODY_H
