//
//  Explorer.h
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#ifndef Explorer_H
#define Explorer_H

#include "GlutHeader.h"


#include <vector>

class Explorer{
public:
    void setPosition(float xIn,float yIn);
    void draw();
    void setDirectionAngle(int directionAngle);
    int getX();
    int getY();
    int getDirectionAngle();
    void setMoveAngles(std::vector<int> moveAngleIn);
    std::vector<int> getMoveAngles();
    void throwArrow();
    void setVisible(bool val);
    bool getArrow();
    void init();

    
private:
    const double TORSO_HEIGHT= 0.3;
    const double TORSO_RADIUS =0.1;
    const double UPPER_ARM_HEIGHT =0.17;
    const double LOWER_ARM_HEIGHT= 0.13;
    const double LOWER_LEG_HEIGHT =0.15;
    const double UPPER_LEG_HEIGHT =0.2;
    const double LOWER_LEG_RADIUS = 0.05;
    const double UPPER_LEG_RADIUS  =0.05;
    const double UPPER_ARM_RADIUS  =0.05;
    const double LOWER_ARM_RADIUS  =0.05;
    const double HEAD_HEIGHT =0.11;
    const double HEAD_RADIUS =0.1;
    GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul;
    float x;
    float y;
    int directionAngle;
    std::vector<int> moveAngles;
    bool hasArrow;
    bool isVisible;
    void setArrow();
    void torso();
    void head();
    void left_upper_arm();
    void left_lower_arm();
    void right_upper_arm();
    void right_lower_arm();
    void left_upper_leg();
    void left_lower_leg();
    void right_upper_leg();
    void right_lower_leg();
    void initQuadrics();
    void drawExplorer();
    const GLfloat theta[11] = {90.0, 0.0, 0.0, 180.0, 0.0, 180.0, 0.0,180.0,0.0,180.0,0.0 }; /* initial joint angles */





    
};

#endif /* defined(__Wumpus__Explorer__) */
