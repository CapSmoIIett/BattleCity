// Для основы логики игры был выбран С++, из за острой необходимости в классах
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h> 
#include <GL/glut.h>


int main (int argc, char* argv[])
{
    glutInit(&argc, argv);
   
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(800,600);
    glutCreateWindow("OpenGl");

    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    //glutReshapeFunc(reshape);
    //glutDisplayFunc(Display);

    glutMainLoop();

    return 0;

}