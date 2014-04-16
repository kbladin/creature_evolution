#include "SettingsManager.h"
#include "Body.h"

#ifdef _WIN32
    #define M_PI 3.14159265359
#endif
BodyTree Body::GetBodyRoot() {
    //simple legged creature for testing

    //Make head
    BodyTree head;
    head.box_dim = Vec3(0.05,0.05,0.1);
    head.mass = 0.25;
    head.friction = 1.0;

    //Make legs
    BodyTree leg;
    leg.box_dim = Vec3(0.02,0.1,0.02);
    leg.mass = 0.25;
    leg.friction = 1.0;

    BodyTree lower_leg = leg;

    //Upper legs
    BodyTree upper_leg = leg;
    Joint joint;
    joint.connection_root = Vec3(0.0,-leg.box_dim.y/2.0,0.0);
    joint.connection_branch = Vec3(0.0,leg.box_dim.y/2.0,0.0);
    joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
    joint.upper_limit = M_PI*0.2;
    joint.lower_limit = -M_PI*0.2;

    //Define the main body and connect everything to it
    BodyTree main_body;
    main_body.box_dim = SettingsManager::Instance()->GetMainBodyDimension();
    main_body.mass = 2.0;
    main_body.friction = 1.0;
    main_body.body_list = std::vector<BodyTree>(4,upper_leg);
    main_body.body_list.push_back(head);

    Joint left_front_joint = joint;
    left_front_joint.connection_root = Vec3(main_body.box_dim.x/2.0,-main_body.box_dim.y/2.0,main_body.box_dim.z/2.0);
    Joint right_front_joint = joint;
    right_front_joint.connection_root = Vec3(-main_body.box_dim.x/2.0,-main_body.box_dim.y/2.0,main_body.box_dim.z/2.0);
    Joint left_back_joint = joint;
    left_back_joint.connection_root = Vec3(main_body.box_dim.x/2.0,-main_body.box_dim.y/2.0,-main_body.box_dim.z/2.0);
    Joint right_back_joint = joint;
    right_back_joint.connection_root = Vec3(-main_body.box_dim.x/2.0,-main_body.box_dim.y/2.0,-main_body.box_dim.z/2.0);

    Joint head_joint = joint;
    head_joint.connection_root = Vec3(0.0,main_body.box_dim.y/2.0,main_body.box_dim.z*0.75);
    head_joint.connection_branch = Vec3(0.0,-head.box_dim.y/2.0,-head.box_dim.z*0.75);

    main_body.joint_list.push_back(left_front_joint);
    main_body.joint_list.push_back(right_front_joint);
    main_body.joint_list.push_back(left_back_joint);
    main_body.joint_list.push_back(right_back_joint);
    main_body.joint_list.push_back(head_joint);

    /*
    BodyTree main_body;
    main_body.box_dim = Vec3(0.1,0.1,0.2);
    main_body.mass = 2.0;
    main_body.friction = 1.0;
    main_body.body_list = std::vector<BodyTree>(1,main_body);

    Joint joint;
    joint.connection_root = Vec3(0.0,main_body.box_dim.y/2.0,0.0);
    joint.connection_branch = Vec3(0.0,-main_body.box_dim.y/2.0,0.0);
    joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
    joint.upper_limit = M_PI*0.2;
    joint.lower_limit = -M_PI*0.2;

    main_body.joint_list.push_back(joint);*/
    return main_body;
}
