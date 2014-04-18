#include "Body.h"

#ifdef _WIN32
    #define M_PI 3.14159265359
#endif

BodyTree Body::GetBodyRoot() {
    //simple legged creature for testing
    int creature_type = SettingsManager::Instance()->GetCreatureType();

    // TODO: add switch
    switch(creature_type){
        case PONY:
            return CreatePony();
            break;
        case WORM:
            return CreateWorm();
            break;
        case TURTLE:
            return CreateTurtle();
            break;
        default:
            std::cout << "not valid creature.. uses Pony!";
            return CreatePony();
            break;
    }

}


BodyTree Body::CreatePony(){

    //Make head
    BodyTree head;
    head.box_dim = Vec3(0.3,0.3,0.65);
    head.mass = 3.0;
    head.friction = 1.0;

    BodyTree tail;
    tail.box_dim = Vec3(0.1,0.1,0.9);
    tail.mass = 1.0;
    tail.friction = 1.0;


    //Make legs
    BodyTree leg;
    leg.box_dim = Vec3(0.2,0.4,0.2);
    leg.mass = 15.0;
    leg.friction = 0.5;

    BodyTree lower_leg = leg;

    //Upper legs
    BodyTree upper_leg = leg;
    Joint joint;
    joint.connection_root = Vec3(0.0,-leg.box_dim.y,0.0);
    joint.connection_branch = Vec3(0.0,leg.box_dim.y/2.0,0.0);
    joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
    joint.upper_limit = M_PI*0.2;
    joint.lower_limit = -M_PI*0.2;

    //connect lower legs
    // upper_leg.body_list.push_back(lower_leg);
    // upper_leg.joint_list.push_back(joint);

    //Define the main body and connect everything to it
    BodyTree main_body;

    //main_body.box_dim = Vec3(0.8,0.5,1.5);

    main_body.box_dim = Vec3(0.5,0.5,1.8);//SettingsManager::Instance()->GetMainBodyDimension();
    main_body.mass = 180.0;

    main_body.friction = 1.0;
    main_body.body_list = std::vector<BodyTree>(4,upper_leg);
    main_body.body_list.push_back(head);
    main_body.body_list.push_back(tail);

    Joint left_front_joint = joint;
    left_front_joint.connection_root = Vec3(main_body.box_dim.x/2.0,-main_body.box_dim.y/1.0,main_body.box_dim.z/2.0);
    Joint right_front_joint = joint;
    right_front_joint.connection_root = Vec3(-main_body.box_dim.x/2.0,-main_body.box_dim.y/1.0,main_body.box_dim.z/2.0);
    Joint left_back_joint = joint;
    left_back_joint.connection_root = Vec3(main_body.box_dim.x/2.0,-main_body.box_dim.y/1.0,-main_body.box_dim.z/1.65);
    Joint right_back_joint = joint;
    right_back_joint.connection_root = Vec3(-main_body.box_dim.x/2.0,-main_body.box_dim.y/1.0,-main_body.box_dim.z/1.65);

    Joint head_joint = joint;
    head_joint.connection_root = Vec3(0.0,main_body.box_dim.y/2.0,main_body.box_dim.z*0.75);
    head_joint.connection_branch = Vec3(0.0,-head.box_dim.y/2.0,-head.box_dim.z*0.75);

    Joint tail_joint = joint;
    tail_joint.connection_root = Vec3(0.0,main_body.box_dim.y/2.0,-main_body.box_dim.z*0.75);
    tail_joint.connection_branch = Vec3(0.0,-tail.box_dim.y/2.0,tail.box_dim.z*0.75);

    main_body.joint_list.push_back(left_front_joint);
    main_body.joint_list.push_back(right_front_joint);
    main_body.joint_list.push_back(left_back_joint);
    main_body.joint_list.push_back(right_back_joint);
    main_body.joint_list.push_back(head_joint);
    main_body.joint_list.push_back(tail_joint);

    return main_body;

}

BodyTree Body::CreateTurtle(){

    BodyTree leg;
    leg.box_dim = Vec3(0.4,0.1,0.2);
    leg.mass = 5;
    leg.friction = 1;

    BodyTree body; 
    body.box_dim = Vec3(0.5,0.2,1);
    body.mass = 30;
    body.friction = 0.6;
    body.body_list = std::vector<BodyTree>(4, leg);

    Joint joint; 
    joint.connection_root = Vec3(0.0,-leg.box_dim.y,0.0);
    joint.connection_branch = Vec3(0.0,leg.box_dim.y/2.0,0.0);
    joint.hinge_orientation = Vec3(0.0,M_PI/2,M_PI/4);
    joint.upper_limit = M_PI*0.2;
    joint.lower_limit = -M_PI*0.2;

    Joint left_front_joint = joint;
    left_front_joint.connection_root = Vec3(body.box_dim.x,-body.box_dim.y/1.0,body.box_dim.z/2.0);
    Joint right_front_joint = joint;
    right_front_joint.connection_root = Vec3(-body.box_dim.x,-body.box_dim.y/1.0,body.box_dim.z/2.0);
    Joint left_back_joint = joint;
    left_back_joint.connection_root = Vec3(body.box_dim.x,-body.box_dim.y/1.0,-body.box_dim.z/1.65);
    Joint right_back_joint = joint;
    right_back_joint.connection_root = Vec3(-body.box_dim.x,-body.box_dim.y/1.0,-body.box_dim.z/1.65);

    body.joint_list.push_back(left_front_joint);
    body.joint_list.push_back(right_front_joint);
    body.joint_list.push_back(left_back_joint);
    body.joint_list.push_back(right_back_joint);

    return body; 



}

BodyTree Body::CreateWorm(){

    int worm_length = 5;

    // varje segment på masken
    BodyTree body_segment;
    body_segment.box_dim = Vec3(0.1,0.05,0.1);
    body_segment.mass = 2.5;
    body_segment.friction = 0.5;

    BodyTree current_segment = body_segment;
    BodyTree previous_segment = body_segment;

    // joints
    Joint joint;
    joint.connection_root = Vec3(0.0f,0.0f,body_segment.box_dim.z);
    joint.connection_branch = Vec3(0.0f,0.0f,-body_segment.box_dim.z);
    joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
    joint.upper_limit = M_PI*0.2;
    joint.lower_limit = -M_PI*0.2;

    for(int i=0; i<worm_length-1; i++){
        current_segment.body_list.push_back(previous_segment);
        current_segment.joint_list.push_back(joint); 
        previous_segment = current_segment;
        current_segment = body_segment;
    }

    return previous_segment;

}