//
//  helper.cpp
//  teapot
//
//  Created by XuYiwen on 4/6/16.
//  Copyright © 2016 evx. All rights reserved.
//

#include "helper.hpp"

void normalize(vec3* v){
    GLfloat mag = sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
    v->x /= mag;
    v->y /= mag;
    v->z /= mag;
}

vec3 perFaceNormal(Face f){
    vec3 v0 = f.vertices[0]->position;
    vec3 v1 = f.vertices[1]->position;
    vec3 v2 = f.vertices[2]->position;
    
    vec3 v10 = {v1.x - v0.x, v1.y - v0.y, v1.z - v0.z};
    vec3 v20 = {v2.x - v0.x, v2.y - v0.y, v2.z - v0.z};
    
    // compute face normal
    vec3 norm = {0,0,0};
    norm.x = v10.y * v20.z - v10.z * v20.y;
    norm.y = v10.z * v20.x - v10.x * v20.z;
    norm.z = v10.x * v20.y - v10.y * v20.x;
    normalize(&norm);
    return norm;
}
