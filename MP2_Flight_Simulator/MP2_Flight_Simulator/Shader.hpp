//
//  Shader.hpp
//  MP2_Flight_Simulator
//
//  Created by Yiwen_Xu on 3/2/16.
//  Copyright © 2016 evx. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include <iostream>
    
// Create a NULL-terminated string by reading the provided file
static char* readShader(const char* shaderFile);

// Create a GLSL program object from vertex and fragment shader files
GLuint InitShader(const char* vShaderFile);

#endif /* Shader_hpp */
