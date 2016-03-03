//
//  model.hpp
//  MP2_Flight_Simulator
//
//  Created by XuYiwen on 3/2/16.
//  Copyright © 2016 evx. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>

class Model{
private:
    
    // material properties
    GLfloat tanamb[4]   = {0.2,0.15,0.1,1.0};
    GLfloat tandiff[4]  = {0.4,0.3,0.2,1.0};
    
    GLfloat seaamb[4]   = {0.0,0.0,0.2,1.0};
    GLfloat seadiff[4]  = {0.0,0.0,0.8,1.0};
    GLfloat seaspec[4]  = {0.5,0.5,1.0,1.0};
    
    // generate model
    int seed(float x, float y);
    void mountain(float x0, float y0, float z0,
                  float x1, float y1, float z1,
                  float x2, float y2, float z2, float s);
    
public:
    
    // model parameters
    float sealevel = 0.0;
    float polysize = 0.01f;
    
    //draw function
    void drawMountain(void);
    void drawSea(void);
};

#endif /* model_hpp */