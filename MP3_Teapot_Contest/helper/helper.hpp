//
//  helper.hpp
//  teapot
//
//  Created by XuYiwen on 4/6/16.
//  Copyright © 2016 evx. All rights reserved.
//

#ifndef helper_hpp
#define helper_hpp

#include <GLUT/GLUT.h>
#include <stdio.h>
#include <math.h>

/**
 *  3 Dimension Vector
 */
struct vec3{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
void normalize(vec3* v);

/**
 *  2 Dimension Vector
 */
struct vec2{
    GLfloat u;
    GLfloat v;
};

/**
 *  Vertex
 */
struct Vertex{
    vec3 normal;
    vec3 position;
    vec2 texture;
};

/**
 *  Face
 */
struct Face{
    int num_vertices;
    Vertex ** vertices;
};
vec3 perFaceNormal(Face f);

#endif /* helper_hpp */
