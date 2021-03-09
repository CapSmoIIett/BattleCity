// Для основы логики игры был выбран С++, из за острой необходимости в классах
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h> 
#include <GL/glut.h>
// Include GLFW
//#include <glad/glad.h>
//GLFWwindow* window;

// Include GLM
//#include <glm/glm.hpp>
/*
void init()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
 }

 void lineSegment()
 {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
        glBegin(GL_TRIANGLES);
            glVertex2i(40,120);
            glVertex2i(40,20);
            glVertex2i(80,20);
        glEnd();
    glFlush();
 }
 int main()
 {
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,300);
    glutCreateWindow("An Example OpenGL....");
    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();
    re
    turn 0;
 }
 */


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