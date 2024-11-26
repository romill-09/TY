#include <GL/glut.h>
#include <cmath>

void drawAxes() {
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-1.0, 0.0); glVertex2f(1.0, 0.0);
    glVertex2f(0.0, -1.0); glVertex2f(0.0, 1.0);
    glEnd();
}

void drawFigure() {
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2, -0.2);
    glVertex2f(0.2, -0.2);
    glVertex2f(0.2, 0.2);
    glVertex2f(-0.2, 0.2);
    glEnd();
}

void shear(float shx, float shy, float tx, float ty) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-tx, -ty, 0.0);
    
    GLfloat matrix[16] = {
        1.0, shy, 0.0, 0.0,
        shx, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
   glLoadMatrixf(matrix);

   glTranslatef(0.1, 0.0, 0.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    drawAxes();
    
    glColor3f(1.0, 0.0, 0.0);
    drawFigure();
    
    glLoadIdentity();
    shear(0.5, 0.0, -0.2, -0.2);
    glColor3f(0.0, 1.0, 0.0);
    drawFigure();
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Shear");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
