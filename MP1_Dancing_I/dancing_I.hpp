//
//  dancing_I.hpp
//  code_yard
//
//  Created by Yiwen_Xu on 2/6/16.
//  Copyright © 2016 evx. All rights reserved.
//

#ifndef dancing_I_hpp
#define dancing_I_hpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <GLUT/glut.h>

// The Structure of I Shpe
//    0-----------11
//    |           |
//    1---2   9---10
//        |   |
//        |   |
//        |   |
//    4---3   8---7
//    |           |
//    5-----------6

class dancing_I{

private:
    const float VertexList[12][2] = {
        { -0.6,  1.0},
        { -0.6,  0.6},
        { -0.2,  0.6},
        { -0.2, -0.6},
        { -0.6, -0.6},
        { -0.6, -1.0},
        {  0.6, -1.0},
        {  0.6, -0.6},
        {  0.2, -0.6},
        {  0.2,  0.6},
        {  0.6,  0.6},
        {  0.6,  1.0},
    };
    const int fill_order [22]= {
        -1,     1,0,2,11,9,10,      -2,
        -1,     9,2,8,3,            -2,
        -1,     4,5,3,6,8,7,        -2,
    }; // -1 = glBegin | -2 = glEnd;
    
    float t = 0;
    float scale = 1.0, basicScale = 1.0, maxScale = 0.5f;
    float rotate = 0.0f, rotateDir[3] = {0,1,0},rotateSpeed = 0.5f;
    float centerX = 0.0, centerY = 0.0;
    
    bool showAni = true;
    bool showFill = true;
    bool showBorder = true;
    bool showOutline = true;
    
    float borderWeight = 3.5;
    float outlineWeight = 1.2;
    
public:
    void display(void);
    void draw_fill(void);
    void draw_outline(void);
    void draw_border(void);
    void update(long long int & time);
    
    void getXY(int ind, float & x, float & y);
    bool getAni();
    void setAni();
    void setFill();
    void setBorder();
    void setOutline();
};

#endif /* dancing_I_hpp */
