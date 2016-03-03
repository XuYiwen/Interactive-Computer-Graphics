//
//  Shader.cpp
//  MP2_Flight_Simulator
//
//  Created by Yiwen_Xu on 3/2/16.
//  Copyright © 2016 evx. All rights reserved.
//
//  Modified from source code in
//  - Interactive Computer Graphics with OpenGL, Ed 6
//  - Link: https://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/APPENDIX_A_EXAMPLES/MAC_VERSIONS/InitShader.cpp

#include "Shader.hpp"

// Create a NULL-terminated string by reading the provided file
static char*
readShader(const char* shaderFile)
{
    FILE* fp = fopen(shaderFile, "r");
    if ( fp == NULL ) { return NULL; }
    
    // count the file size
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    
    // read in to buffer
    fseek(fp, 0L, SEEK_SET);
    char* buff = new char[size + 1];
    fread(buff, 1, size, fp);
    buff[size] = '\0';
    
    fclose(fp);
    return buff;
}

// Create a GLSL program object from vertex and fragment shader files
GLuint
InitShader(const char* vShaderFile)
{
    struct Shader {
        const char*  filename;
        GLenum       type;
        GLchar*      source;
    }  shaderf = { vShaderFile, GL_VERTEX_SHADER, NULL };
    
    // create shader from file
    GLuint program = glCreateProgram();
    Shader& s = shaderf;
    s.source = readShader( s.filename );
    if ( shaderf.source == NULL ) {
        std::cerr << "Failed to read " << s.filename << std::endl;
        exit( EXIT_FAILURE );
    }
    GLuint shader = glCreateShader( s.type );
    glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
    
    // compile shader
    glCompileShader( shader );
    GLint  compiled;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
    if ( !compiled ) {
        std::cerr << s.filename << " failed to compile:" << std::endl;
        GLint  logSize;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
        char* logMsg = new char[logSize];
        glGetShaderInfoLog( shader, logSize, NULL, logMsg );
        std::cerr << logMsg << std::endl;
        delete [] logMsg;
        
        exit( EXIT_FAILURE );
    }
    
    // link shader to program
    delete [] s.source;
    glAttachShader( program, shader );
    glLinkProgram(program);
    GLint  linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        std::cerr << "Shader program failed to link" << std::endl;
        GLint  logSize;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
        char* logMsg = new char[logSize];
        glGetProgramInfoLog( program, logSize, NULL, logMsg );
        std::cerr << logMsg << std::endl;
        delete [] logMsg;
        
        exit( EXIT_FAILURE );
    }
    
    // use shader
    glUseProgram(program);
    
    return program;
}

