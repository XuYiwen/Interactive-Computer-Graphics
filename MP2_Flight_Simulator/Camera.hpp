//
//  Camera.hpp
//  MP2_Flight_Simulator
//
//  Created by XuYiwen on 3/3/16.
//  Copyright © 2016 evx. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <iostream>

#define PAUSE 0
#define MOVE 1

#define NO_ROTATE 0
#define ROLL_LEFT 1
#define ROLL_RIGHT 2
#define PITCH_LEFT 3
#define PITCH_RIGHT 4
#define YAW_LEFT 5
#define YAW_RIGHT 6

class Camera{
public:
    GLfloat eye[3] = {0.0, 0.0, 0.25};
    GLfloat center[3] = {0.5, 0.5, 0.25};
    GLfloat up[3] = {0.0, 0.0, 1.0};

    GLfloat modelView[16];
    
    bool fwdStat = MOVE;
    GLint rotDir = NO_ROTATE;
    
    GLfloat fwdSpeed = 0.0005;
    GLfloat rotSpeed = 0.5;
    
    void update(void);
    void status(void);
};


#endif /* Camera_hpp */
