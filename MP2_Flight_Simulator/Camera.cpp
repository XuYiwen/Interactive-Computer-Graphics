//
//  Camera.cpp
//  MP2_Flight_Simulator
//
//  Created by XuYiwen on 3/3/16.
//  Copyright © 2016 evx. All rights reserved.
//

#include "Camera.hpp"


void Camera::update(void){
    // load current model view matrix
    glMatrixMode(GL_MODELVIEW);
    glGetFloatv(GL_MODELVIEW_MATRIX, modelView);
    
    // Form new model view
    glLoadIdentity();
    if (rotDir != NO_ROTATE) {
        switch (rotDir) {
            case ROLL_LEFT:
                glRotatef(rotSpeed, 0, 0, -1);
                break;
            case ROLL_RIGHT:
                glRotatef(-rotSpeed, 0, 0, -1);
                break;
            case PITCH_LEFT:
                glRotatef(-rotSpeed, 1, 0, 0);
                break;
            case PITCH_RIGHT:
                glRotatef(rotSpeed, 1, 0, 0);
                break;
            case YAW_LEFT:
                glRotatef(-rotSpeed, 0, 1, 0);
                break;
            case YAW_RIGHT:
                glRotatef(rotSpeed, 0, 1, 0);
                break;
        }
        rotDir = NO_ROTATE;
    }
    if (fwdStat == MOVE){
        glTranslatef(0, 0, fwdSpeed);
    }
    glMultMatrixf(modelView);
}
void Camera::status(){
    
}
