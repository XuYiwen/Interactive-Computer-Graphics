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

Model model;
Camera cam;

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

}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    
    // display model
    cam.update();
    model.drawLight();
    model.drawMountain();
    model.drawSea();
    
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
            break;
        case '+':
        case '=':
            model.sealevel += 0.01;
            break;
        case 'f':
        case 'F':
            model.polysize *= 0.5;
            break;
        case 'c':
        case 'C':
            model.polysize *= 2.0;
            break;
        case 'a':
        case 'A':
            cam.rotDir = ROLL_LEFT;
            break;
        case 'd':
        case 'D':
            cam.rotDir = ROLL_RIGHT;
            break;
        case 'w':
        case 'W':
            cam.rotDir = PITCH_LEFT;
            break;
        case 's':
        case 'S':
            cam.rotDir = PITCH_RIGHT;
            break;
        case 'q':
        case 'Q':
            cam.rotDir = YAW_LEFT;
            break;
        case 'e':
        case 'E':
            cam.rotDir = YAW_RIGHT;
            break;
    
        case 'p': // Pause Auto Forward
        case 'P':
            cam.fwdStat = (cam.fwdStat == MOVE)? PAUSE : MOVE;
            break;
        case 27: // ESC
            exit(0);
            break;
    }
}

void arrowKeys(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
            cam.rotSpeed *= 1.2;
            break;
        case GLUT_KEY_RIGHT:
            cam.rotSpeed /= 1.2;
            break;
        case GLUT_KEY_UP:
            cam.fwdSpeed *= 1.2;
            break;
        case GLUT_KEY_DOWN:
            cam.fwdSpeed /= 1.2;
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