//
//  Model.hpp
//  teapot
//
//  Created by XuYiwen on 4/6/16.
//  Copyright © 2016 evx. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "helper.hpp"
#include "objLoader.h"
#include "readppm.h"

#define MIX 1
#define TEX 2
#define ENV 3

class Teapot{
public:
    // Attributes
    int numFaces;
    int numVertices;
    Face* faceList;
    Vertex* vertexList;
    
    // Texture
    GLuint tex_active;
    unsigned char * tex_img;
    int tex_w,tex_h;

    // Spheremap
    GLuint env_active;
    unsigned char * env_img;
    int env_w,env_h;
    
    // Material Properties
    GLfloat potamb[4] = {0.1, 0.1, 0.1, 1.0};
    GLfloat potdiff[4] ={0.0, 0.0, 0.0, 1.0};
    GLfloat potspec[4] = {0.5, 0.5, 0.5, 1.0};
    
    // Load and initialization
    void load_obj(char* filename);
    void load_texture(char* filename);
    void load_environmnet(char* filename);
    
    // Active texture or spheremap
    void active(int type);
    
    // Set Coordinates
    void set_coord(int type);

    void display();
    
};

class Light{
public:
    GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lpos[4] = {10.0, 10.0, 10.0, 0.0};
    
    void light_on();
};

unsigned char * flip_image(unsigned char * image, int width, int height);

#endif /* Model_hpp */
