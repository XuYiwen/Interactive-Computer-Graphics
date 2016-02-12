//
//  dancing_I.cpp
//  code_yard
//
//  Created by Yiwen_Xu on 2/6/16.
//  Copyright © 2016 evx. All rights reserved.
//

#include "dancing_I.hpp"
// The Structure of I Shape
//    0-----------11
//    |           |
//    1---2   9---10
//        |   |
//        |   |
//        |   |
//    4---3   8---7
//    |           |
//    5-----------6

void dancing_I:: display(void){
//    glRotatef(rotate,rotateDir[0],rotateDir[1],rotateDir[2]);
    
    if (showFill){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        draw_fill();
    }
    if (showOutline){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        draw_outline();
    }
    if (showBorder){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        draw_border();
    }
}
void dancing_I:: draw_fill(void){
    
    // draw I shape with triangles
    for (int i=0; i<22; i++){
        int ind = fill_order[i];
        
        if (ind == -1){
            glBegin(GL_TRIANGLE_STRIP);
        }else if (ind == -2){
            glEnd();
        }else{
            float x,y;
            getXY(ind, x, y);
            glColor3f(x/scale, y/scale,0.6);
            glVertex3f(x, y, 0);
        }
    }
}
void dancing_I::draw_outline(void){
    // draw triangles outlines
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(scale * outlineWeight);
    
    for (int i=0; i<22; i++){
        int ind = fill_order[i];
        
        if (ind == -1){
            glBegin(GL_TRIANGLE_STRIP);
        }else if (ind == -2){
            glEnd();
        }else{
            float x,y;
            getXY(ind, x, y);
            glVertex3f(x, y, 0);
        }
    }
}
void dancing_I::draw_border(void){
    // draw I border with line
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(scale * borderWeight);
    
    glBegin(GL_LINE_LOOP);
    for (int i=0; i<12; i++){
        float x,y;
        getXY(i, x, y);
        glVertex3f(x, y, 0);
    }
    glEnd();
}
void dancing_I::update(long long int & time){

    t = time * 0.05f;

    scale = basicScale + sin(t) * maxScale;
    
//    rotate += rotateSpeed;
//    int dir = (time / 100) % 8;
//    if (dir > 4)        rotateDir[2] += 0.1 * rotateSpeed;
//    else if (dir >2)    rotateDir[1] += 0.1 * rotateSpeed;
//    else                rotateDir[0] += 0.1 * rotateSpeed;
    
    centerX = cos(t)*0.5;
    centerY = sin(t)*0.5;
    
}
void dancing_I::getXY(int ind,float & x, float &y){
    int mod = 4;
    float bias = 0.3;
    float s = 0.05;
    float f = (ind % mod) * 4;
    
    x = VertexList[ind][0] * scale + centerX + cos(f * t + ind * bias) * s;
    y = VertexList[ind][1] * scale + centerX + sin(f * t + ind * bias) * s;
}
// Mode Setting
bool dancing_I::getAni(){
    return showAni;
}
void dancing_I::setAni(){
    showAni = !showAni;
}
void dancing_I::setFill(){
    showFill = !showFill;
}
void dancing_I::setBorder(){
    showBorder = !showBorder;
}
void dancing_I::setOutline(){
    showOutline = !showOutline;
}


