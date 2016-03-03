//
//  main.cpp
//  MP2_Flight_Simulator
//
//  Created by XuYiwen on 3/2/16.
//  Copyright © 2016 evx. All rights reserved.
//

#include "Model.hpp"
#include "Shader.hpp"

Model model;

void
init(void){
    // Load Shader
    GLuint program = InitShader( "v_shader.glsl","f_shader.glsl");
    glUseProgram(program);
    
    GLfloat white[] = {1.0,1.0,1.0,1.0};
    GLfloat lpos[] = {0.0,1.0,0.0,0.0};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    glClearColor (0.5, 0.5, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    
//    model.drawMountain();
//    model.drawSea();
}

void display(void)
{
    static GLfloat angle = 0.0;
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    
    glLoadIdentity ();
    gluLookAt (0.5, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef (-0.5, -0.5, 0.0); 
    
    model.drawMountain();
    model.drawSea();
    
    glutSwapBuffers();
    glFlush ();
    
    angle += 0.5;
    
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
            model.polysize *= 0.5;
            break;
        case 'c':
            model.polysize *= 2.0;
            break;
        case 27:
            exit(0);
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
    glutMainLoop();
    return 0;
}