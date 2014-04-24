#include "Body.h"

#ifdef _WIN32
    #define M_PI 3.14159265359
#endif

int BodyTree::GetNumberOfLeaves(){
    int result = 0;
    if (body_list.size() == 0)
        result = 0; // Itself
    else {
        for (int i = 0; i < body_list.size(); ++i){
            result += body_list[i].GetNumberOfLeaves();
        }
    }
    return result + 1; // Children + itself
}

Body::Body(){
    //simple legged creature for testing
    int creature_type = SettingsManager::Instance()->GetCreatureType();

    // TODO: add switch
    switch(creature_type){
        case PONY:
            body_root_ = CreatePony();
            break;
        case WORM:
            body_root_ = CreateWorm();
            break;
        case TURTLE:
            body_root_ = CreateTurtle();
            break;
        case SHEEP:
            body_root_ = CreateSheep();
            break;
        case CRAWLER:
            body_root_ = CreateCrawler();
            break;
        default:
            std::cout << "not valid creature.. uses Pony!";
            body_root_ = CreatePony();
            break;
    }
}

BodyTree Body::GetBodyRoot() {
    return body_root_;
}

int Body::GetTotalNumberOfJoints(){
    return body_root_.GetNumberOfLeaves() - 1; // Do not count itself
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

BodyTree Body::CreateSheep(){

    float density = 1000;
    float friction = 0.7;

    //Make head
    BodyTree head;
    head.box_dim = Vec3(0.15,0.15,0.25);
    head.mass = head.box_dim.x * head.box_dim.y * head.box_dim.z * density;
    head.friction = friction;

    BodyTree tail;
    tail.box_dim = Vec3(0.05,0.05,0.15);
    tail.mass = tail.box_dim.x * tail.box_dim.y * tail.box_dim.z * density;
    tail.friction = friction;


    //Make legs
    BodyTree leg;
    leg.box_dim = Vec3(0.1,0.15,0.1);
    leg.mass = leg.box_dim.x * leg.box_dim.y * leg.box_dim.z * density;
    leg.friction = friction;

    BodyTree lower_leg = leg;
    BodyTree upper_leg = leg;
    
    Joint joint;
    joint.connection_root = Vec3(0.0,-leg.box_dim.y,0.0);
    joint.connection_branch = Vec3(0.0,leg.box_dim.y/2.0,0.0);
    joint.hinge_orientation = Vec3(0.0,M_PI/2,0.0);
    joint.upper_limit = M_PI*0.3;
    joint.lower_limit = -M_PI*0.3;

    //connect lower legs
    // upper_leg.body_list.push_back(lower_leg);
    // upper_leg.joint_list.push_back(joint);

    //Define the main body and connect everything to it
    BodyTree main_body;

    //main_body.box_dim = Vec3(0.8,0.5,1.5);

    main_body.box_dim = Vec3(0.3,0.2,0.6);//SettingsManager::Instance()->GetMainBodyDimension();
    main_body.mass = main_body.box_dim.x * main_body.box_dim.y * main_body.box_dim.z * density;

    main_body.friction = friction;
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

BodyTree Body::CreateCrawler(){

    float density = 1000;
    float friction = 0.7;

    // Torso
    BodyTree body_segment;
    body_segment.box_dim = Vec3(0.1,0.05,0.2);
    body_segment.mass = body_segment.box_dim.x * body_segment.box_dim.y * body_segment.box_dim.z * density;
    body_segment.friction = friction * 0.2;

    BodyTree current_segment = body_segment;
    BodyTree previous_segment = body_segment;

    // Leg
    BodyTree leg;
    leg.box_dim = Vec3(0.1,0.05,0.05);
    leg.mass = leg.box_dim.x * leg.box_dim.y * leg.box_dim.z * density;
    leg.friction = friction;

    BodyTree lower_leg = leg;
    BodyTree upper_leg = leg;

    // joints
    Joint joint;
    joint.connection_root = Vec3(0.0f,0.0f,body_segment.box_dim.z);
    joint.connection_branch = Vec3(0.0f,0.0f,-body_segment.box_dim.z);
    joint.hinge_orientation = Vec3(M_PI/2,0.0,0.0);
    joint.upper_limit = M_PI*0.2;
    joint.lower_limit = -M_PI*0.2;

    Joint left_leg_joint;
    left_leg_joint.connection_root = Vec3(body_segment.box_dim.x,0.0f,0.0f);
    left_leg_joint.connection_branch = Vec3(-body_segment.box_dim.x,0.0f,0.0f);
    left_leg_joint.hinge_orientation = Vec3(0.0,0.0,M_PI/2);
    left_leg_joint.upper_limit = M_PI*0.2;
    left_leg_joint.lower_limit = -M_PI*0.2;

    Joint right_leg_joint;
    right_leg_joint.connection_root = Vec3(-body_segment.box_dim.x,0.0f,0.0f);
    right_leg_joint.connection_branch = Vec3(body_segment.box_dim.x,0.0f,0.0f);
    right_leg_joint.hinge_orientation = Vec3(0.0,0.0,M_PI/2);
    right_leg_joint.upper_limit = M_PI*0.2;
    right_leg_joint.lower_limit = -M_PI*0.2;

    int n_segs = 3;

    for(int i=0; i<n_segs-1; i++){
        current_segment.body_list.push_back(previous_segment);
        current_segment.joint_list.push_back(joint);
        current_segment.body_list.push_back(leg);
        current_segment.joint_list.push_back(left_leg_joint);
        current_segment.body_list.push_back(leg);
        current_segment.joint_list.push_back(right_leg_joint);
        previous_segment = current_segment;
        current_segment = body_segment;
    }

    return previous_segment;
}