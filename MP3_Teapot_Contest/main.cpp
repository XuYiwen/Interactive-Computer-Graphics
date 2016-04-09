#include <GLUT/GLUT.h>
#include "Model.hpp"
#include "Shader.hpp"

double zpos = 0;
double xangle = 0;
double yangle = 0;


Teapot teapot;
Light light;
int type = MIX;

void init()
{
    // Initialize Perspective Projection in OpenGL
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(70.f, 1.0, 0.001f, 30.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Load in obj and textures
    teapot.load_obj("teapot.obj");
    teapot.load_texture("textures/04.ppm");
    teapot.load_environmnet("shperemaps/03.ppm");
    
	// Enable the Z-buffer to remove hidden surfaces
	glEnable(GL_DEPTH_TEST);
    
    // Load and link Shader
    GLuint program = InitShader( "shaders/teapot.vs","shaders/teapot.fs");
    glUseProgram(program);
    
    // Set the texture sources
    GLint tex0 = glGetUniformLocation(program, "texture");
    GLint tex1 = glGetUniformLocation(program, "envmap");
    glUniform1i(tex0, 0);
    glUniform1i(tex1, 1);
    
    // display helper
    using namespace std;
    cout << "<<<<<<<<<<<<< Keyboard Help >>>>>>>>>>>>>"<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "Esc | Quit                               "<< endl;
}

void display()
{
//    teapot.active(type);
//    teapot.set_coord(type);
    
	// Create the lookat vector
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.f, 2.f, 5.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f);
    
    light.light_on();
    
	// Apply matrix multiplication for any movement done by the user
	glTranslated(0.0, 0.0, zpos);
	glRotated(xangle, 1.0, 0.0, 0.0);
	glRotated(yangle, 0.0, 1.0, 0.0);
    
    teapot.display();

	// Disable Texture Coordinates
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

	// Enable double buffering
	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	float fAspect = ((float)w)/h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.f, fAspect, 0.001f, 30.f);
}

void helper(void){
    using namespace std;
    cout << "<<<<<<<<<<<<< Keyboard Help >>>>>>>>>>>>>"<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "W/S | Rotate teapot up or down           "<< endl;
    cout << "A/D | Rotate teapot left or right        "<< endl;
    cout << "Q/E | Move teapot forwards or backwards  "<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "Esc | Quit                               "<< endl;
}

void keyboard(unsigned char key, int x, int y){
	if (key == 'w' || key == 'W'){
		xangle -= 2;
	}

	if (key == 'a' || key == 'A'){
		yangle -= 2;
	}

	if (key == 's' || key == 'S'){
		xangle += 2;
	}

	if (key == 'd' || key == 'D'){
		yangle += 2;
	}
    
    if (key == 'q' || key == 'Q'){
		zpos += .5;
	}

	if (key == 'e' || key == 'E'){
		zpos -= .5;
	}

    // If F is pressed, switch between texture and environment
//	if (key == 'f' || key == 'F'){
//        type = (type == ENV)? MIX: type +1;
//	}
    
    // If Esc is pressed, exit
    if (key == 27){
        exit(0);
    }

}

int main(int argc, char ** argv)
{
    // Initialize an OpenGL window
    glutInit(&argc, (char**) argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow((const char*)"MP3 - Teapot Contest");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}
