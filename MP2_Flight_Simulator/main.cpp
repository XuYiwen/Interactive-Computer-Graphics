//
//  main.cpp
//  MP2_Flight_Simulator
//
//  Created by XuYiwen on 3/2/16.
//  Copyright © 2016 evx. All rights reserved.
//

#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#include <istream>
#include <string>
#include <sstream>
#define FONT GLUT_BITMAP_HELVETICA_12
using namespace std;

MountainSea model;
Camera cam;
string statStr;

void helper(void){
    using namespace std;
    cout << "<<<<<<<<<<<<< Keyboard Help >>>>>>>>>>>>>"<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "+/- | Edit Sea Level                     "<< endl;
    cout << "f/c | Edit Polygon Size                  "<< endl;
    cout << "p   | Start / Pause Forward              "<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "[a/d] ROLL  |  [w/s] PITCH  | [q/e] YAW  "<< endl;
    cout << "[UP/DOWN] Forward Speed                  "<< endl;
    cout << "[LEFT/RIGHT] Rotate Speed                "<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "Esc | Quit                               "<< endl;
}

void curStat(void)
{
    // save state and form new state
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, GLUT_WINDOW_WIDTH, 0.0, GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // display sentence
    glRasterPos2i(1, GLUT_WINDOW_HEIGHT-5);
    ostringstream stream;
    stream << "Last Update | " << statStr;
    string out = stream.str();
    int length = (int)out.length();
    for (int i = 0; i < length; i++)
    {
        glutBitmapCharacter(FONT, out[i]);
    }
    
    // back to original state
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}


void init(void){
    // Load Shader
    GLuint program = InitShader( "v_shader.glsl","f_shader.glsl");
    glUseProgram(program);
    
    // Set initial lookat
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (cam.eye[0],      cam.eye[1],     cam.eye[2],
               cam.center[0],   cam.center[1],  cam.center[2],
               cam.up[0],       cam.up[1],      cam.up[2]);
    glScalef(5.0, 5.0, 5.0);
    glTranslatef(-0.5, -0.5, 0);
    
    helper();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    
    // display model
    cam.update();
    model.drawAll();
    curStat();
    
    glutSwapBuffers();
    glFlush ();
    glutPostRedisplay();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(90.0,1.0,0.01,10.0);
    glMatrixMode (GL_MODELVIEW);
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case '-':
            model.sealevel -= 0.01;
            statStr = "Edit Sea Level";
            break;
        case '+':
        case '=':
            model.sealevel += 0.01;
            statStr = "Edit Sea Level";
            break;
        case 'f':
        case 'F':
            model.polysize *= 0.5;
            statStr = "Edit Polygon Size";
            break;
        case 'c':
        case 'C':
            model.polysize *= 2.0;
            statStr = "Edit Polygon Size";
            break;
        case 'a':
        case 'A':
            cam.rotDir = ROLL_LEFT;
            statStr = "Rolling";
            break;
        case 'd':
        case 'D':
            cam.rotDir = ROLL_RIGHT;
            statStr = "Rolling";
            break;
        case 'w':
        case 'W':
            cam.rotDir = PITCH_LEFT;
            statStr = "Pitching";
            break;
        case 's':
        case 'S':
            cam.rotDir = PITCH_RIGHT;
            statStr = "Pitching";
            break;
        case 'q':
        case 'Q':
            cam.rotDir = YAW_LEFT;
            statStr = "Yawing";
            break;
        case 'e':
        case 'E':
            cam.rotDir = YAW_RIGHT;
            statStr = "Yawing";
            break;
    
        case 'p': // Pause Auto Forward
        case 'P':
            cam.fwdStat = (cam.fwdStat == MOVE)? PAUSE : MOVE;
            statStr = "Stop or Pause";
            break;
        case 27: // ESC
            exit(0);
            break;          
    }
}

void arrowKeys(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
            cam.rotSpeed -= 1.2;
            statStr = "Decrease Rotate Speed";
            break;
        case GLUT_KEY_RIGHT:
            cam.rotSpeed *= 1.2;
            statStr = "Increase Rotate Speed";
            break;
        case GLUT_KEY_UP:
            cam.fwdSpeed *= 1.2;
            statStr = "Increase Forward Speed";
            break;
        case GLUT_KEY_DOWN:
            cam.fwdSpeed /= 1.2;
            statStr = "Decrease Forward Speed";
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ((const char*)"MP2 - Flight Simulator");
    
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowKeys);
    glutMainLoop();
    return 0;
}