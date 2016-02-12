//
//  main.cpp
//  code_yard
//
//  Created by Yiwen_Xu on 2/6/16.
//  Copyright © 2016 evx. All rights reserved.
//

#include "dancing_I.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

dancing_I object;

static long long int frames = 0;
static int FPS = 30;

void helper(void);
void display(void);
void timer(int v);
void reshape (int w, int h);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char* argv[])
{
    helper();
    
    // Set openGL
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (200, 200);
    glutCreateWindow ((const char*)"MP1 - Dancing I");
    glClearColor(0.9,0.9,0.9,1.0); //background color
    
    // Set call-back functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000/FPS,timer,20);

    glutMainLoop();
    
    return 0;
}

/////////////////////// GL Helper Function ///////////////////////
void helper(void){
    using namespace std;
    cout << "<<<<<<<<<< Keyboard Help >>>>>>>>>>>"<< endl;
    cout << "a   | Show / Hide Animation         "<< endl;
    cout << "f   | Show / Hide Filled I          "<< endl;
    cout << "o   | Show / Hide Triangle Outline  "<< endl;
    cout << "b   | Show / Hide Border            "<< endl;
    
    cout << "Esc | Quit                          "<< endl;
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // reset OpenGL transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Setup Eye at (0,0,3), Look at (0,0,0), Up dir = y
    gluLookAt(0,0,3,0,0,0,0,1,0);
    
    object.display();
    
    glutSwapBuffers();
}

void timer(int v){
    if (object.getAni()){
        frames += 1;
        object.update(frames);
    }

    glutPostRedisplay(); // trigger redisplay
    glutTimerFunc(1000/FPS,timer,v); // restart timer again
}

void reshape (int w, int h){
    // reset drawing screen size
    glViewport(0, 0, w, h);
    float fAspect = ((float)w)/h;
    
    // reset OpenGL projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.f,fAspect,0.001f,30.f);
}

void keyboard(unsigned char key, int x, int y){
    
    if (key == 27)
    {
        // ESC hit, so quit
        printf("\n Demonstration Finished.\n");
        exit(0);
    }
    if (key == 'a' || key == 'A' ){
        object.setAni();
    }
    if( key == 'o' || key == 'O' ){
        object.setOutline();
    }
    if (key == 'f' || key == 'F' ){
        object.setFill();
    }
    if (key == 'b' || key == 'B' ){
        object.setBorder();
    }
}