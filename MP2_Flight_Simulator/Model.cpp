//
//  MountainSea.cpp
//  MP2_Flight_Simulator
//
//  Created by XuYiwen on 3/2/16.
//  Copyright © 2016 evx. All rights reserved.
//

#include "Model.hpp"

int
MountainSea::seed(float x, float y){
    static int a = 1588635695, b = 1117695901;
    int xi = *(int *)&x;
    int yi = *(int *)&y;
    return ((xi * a) % b) - ((yi * b) % a);
}

void
MountainSea::mountain(float x0, float y0, float z0,
                float x1, float y1, float z1,
                float x2, float y2, float z2, float s){
    float x01,y01,z01,x12,y12,z12,x20,y20,z20;
    
    if (s < polysize) {
        x01 = x1 - x0;
        y01 = y1 - y0;
        z01 = z1 - z0;
        
        x12 = x2 - x1;
        y12 = y2 - y1;
        z12 = z2 - z1;
        
        x20 = x0 - x2;
        y20 = y0 - y2;
        z20 = z0 - z2;
        
        float nx = y01*(-z20) - (-y20)*z01;
        float ny = z01*(-x20) - (-z20)*x01;
        float nz = x01*(-y20) - (-x20)*y01;
        
        float den = sqrt(nx*nx + ny*ny + nz*nz);
        
        if (den > 0.0) {
            nx /= den;
            ny /= den;
            nz /= den;
        }
        
        glNormal3f(nx,ny,nz);
        glBegin(GL_TRIANGLES);
        glVertex3f(x0,y0,z0);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
        glEnd();
        
        return;
    }
    
    x01 = 0.5*(x0 + x1);
    y01 = 0.5*(y0 + y1);
    z01 = 0.5*(z0 + z1);
    
    x12 = 0.5*(x1 + x2);
    y12 = 0.5*(y1 + y2);
    z12 = 0.5*(z1 + z2);
    
    x20 = 0.5*(x2 + x0);
    y20 = 0.5*(y2 + y0);
    z20 = 0.5*(z2 + z0);
    
    s *= 0.5;
    
    srand(seed(x01,y01));
    z01 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    srand(seed(x12,y12));
    z12 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    srand(seed(x20,y20));
    z20 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    
    mountain(x0,y0,z0,x01,y01,z01,x20,y20,z20,s);
    mountain(x1,y1,z1,x12,y12,z12,x01,y01,z01,s);
    mountain(x2,y2,z2,x20,y20,z20,x12,y12,z12,s);
    mountain(x01,y01,z01,x12,y12,z12,x20,y20,z20,s);
}
void
MountainSea::drawAll(){
    drawLight();
    drawMountain();
    drawSea();
}

void
MountainSea::drawMountain(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tanspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
    mountain(0.0,0.0,0.0, 1.0,0.0,0.0, 0.0,1.0,0.0, 1.0);
    mountain(1.0,1.0,0.0, 0.0,1.0,0.0, 1.0,0.0,0.0, 1.0);
}

void
MountainSea::drawSea(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
    glNormal3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,sealevel);
    glVertex3f(1.0,0.0,sealevel);
    glVertex3f(1.0,1.0,sealevel);
    glVertex3f(0.0,1.0,sealevel);
    glEnd();
}

void
MountainSea::drawLight(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    glClearColor (0.5, 0.5, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}