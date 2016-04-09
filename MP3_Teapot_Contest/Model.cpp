//
//  Model.cpp
//  teapot
//
//  Created by XuYiwen on 4/6/16.
//  Copyright © 2016 evx. All rights reserved.
//

#include "Model.hpp"

void Teapot::load_obj(char* filename){
    objLoader *objData = new objLoader();
    objData->load(filename);
    
    numFaces = objData->faceCount;
    numVertices = objData->vertexCount;
    faceList = (Face*) malloc(numFaces * sizeof (Face)); //need to free
    vertexList = (Vertex*) malloc(numVertices * sizeof (Vertex)); //need to free
    
    //get all vertices from obj
    for (int i = 0; i < numVertices; i++) {
        GLfloat x = (*(objData->vertexList[i])).e[0];
        GLfloat y = (*(objData->vertexList[i])).e[1];
        GLfloat z = (*(objData->vertexList[i])).e[2];
        
        // set position coordinates of vertex
        vertexList[i].position.x = x;
        vertexList[i].position.y = y;
        vertexList[i].position.z = z;
        
        // set texture coordinates of vertex
        GLfloat theta = atan2(z,x);
        vertexList[i].texture.u = (theta + M_PI)/( 2 * M_PI);
        vertexList[i].texture.v = (y/2.0);
        
        // initial normal vector to zero;
        vertexList[i].normal.x = 0;
        vertexList[i].normal.y = 0;
        vertexList[i].normal.z = 0;
    }
    
    //get all faces
    for (int i = 0; i < numFaces; i++) {
        obj_face* objFace = objData->faceList[i];
        int vertex_count = objFace->vertex_count;
        faceList[i].vertices = (Vertex**) malloc(vertex_count * sizeof (Vertex*));
        
        // assign vertex to face
        faceList[i].num_vertices = vertex_count;
        for (int j = 0; j < vertex_count; j++) {
            faceList[i].vertices[j] = &vertexList[objFace->vertex_index[j]];
        }
        
        // compute pre-face normal
        vec3 norm = perFaceNormal(faceList[i]);
        
        // accumulator norm vector to each vertex
        for (int j = 0; j < vertex_count; j++) {
            faceList[i].vertices[j]->normal.x += norm.x;
            faceList[i].vertices[j]->normal.y += norm.y;
            faceList[i].vertices[j]->normal.z += norm.z;
        }
    }
    
    //normalize all vertices to get pre-vertex normal vector
    for (int i = 0; i < numVertices; i++) {
        normalize(&vertexList[i].normal);
    }
    delete(objData);
    
    std::cout << ".obj loaded in " << std::endl;
}

void Teapot::load_texture(char* filename){
    
    // load texture from file
    tex_img = readPPM(filename, &tex_w, &tex_h);
    tex_img = flip_image(tex_img, tex_w, tex_h);
    
    // Generate texture name and bind it
    glGenTextures(1,&tex_active);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_active);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Link to image
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex_w, tex_h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_img);
    
    // free loaded data
    free(tex_img);
    std::cout << "tex: " << tex_active << std::endl;
}

void Teapot::load_environmnet(char* filename){
    // load texture from file
    env_img = readPPM(filename, &env_w, &env_h);
    env_img = flip_image(env_img, env_w, env_h);
    
    // Generate texture name and bind it
    glGenTextures(1,&env_active);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, env_active);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Combine texture
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    
    // Link to image
    glTexImage2D(GL_TEXTURE_2D, 0, 3, env_w, env_h, 0, GL_RGB, GL_UNSIGNED_BYTE, env_img);
    
    // free loaded data
    free(env_img);
    std::cout << "env: " << env_active << std::endl;

}

void Teapot::active(int type){
    switch (type) {
        case TEX:
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, tex_active);
            
            //Mulfiply Color and Texture
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            break;
        case ENV:
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, env_active);
            // Ignore Color and show texture
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            break;
        default: // MIX
            glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, tex_active);
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, env_active);
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
            
            // Sample RGB, multiply by previous texunit result
            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
            glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS);
            glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
            break;
    }
}
void Teapot::set_coord(int type){
    switch (type) {
        case TEX:
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, tex_active);
            
            // Generate texture coordinates rotate as teapot
//            glEnable(GL_TEXTURE_GEN_S);
//            glEnable(GL_TEXTURE_GEN_T);
//            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            break;
        case ENV:
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, env_active);
            
            // Generate fixed coordinates do not rotate as teapot
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
            break;
        default:
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, tex_active);
            
            // Generate texture coordinates rotate as teapot
            //            glEnable(GL_TEXTURE_GEN_S);
            //            glEnable(GL_TEXTURE_GEN_T);
            //            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            //            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, env_active);
            
            // Generate fixed coordinates do not rotate as teapot
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
            
            break;
    }
}

void Teapot::display(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, potamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, potdiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, potspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 5.0);
    
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < numFaces;i++){
        Face f = faceList[i];
        for (int j = 0; j< f.num_vertices;j++){
            Vertex vtx = *f.vertices[j];
            glNormal3f(vtx.normal.x, vtx.normal.y, vtx.normal.z);
            glTexCoord2f(vtx.texture.u, vtx.texture.v);
            glVertex3f(vtx.position.x, vtx.position.y, vtx.position.z);
        }
    }
    glEnd();
    
    // Disable Texture Coordinates
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void Light::light_on(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
}

unsigned char * flip_image(unsigned char * image, int width, int height){
    const int RGB = 3;
    unsigned char imageArray[width][height][RGB];
    
    // Convert the 1-D input array into a 3-D array
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            for (int k = 0; k < RGB; ++k){
                imageArray[i][j][k] = image[i*RGB + j*width*RGB + k];
            }
        }
    }
    
    // Flip the image
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height/2; ++j){
            for (int k = 0; k < RGB; ++k){
                unsigned char temp = imageArray[i][j][k];
                imageArray[i][j][k] = imageArray[i][height - j - 1][k];
                imageArray[i][height - j - 1][k] = temp;
            }
        }
    }
    
    // Convert the 3-D array into a 1-D array
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            for (int k = 0; k < RGB; ++k){
                image[i*RGB + j*width*RGB + k] = imageArray[i][j][k];
            }
        }
    }
    
    return image;
}