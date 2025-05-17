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

void translate(float tx, float ty) {
    glTranslatef(tx, ty, 0.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    drawAxes();
    
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    drawFigure();
    glPopMatrix();
    
    glLoadIdentity();
    translate(0.5, 0.5);
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
    glutInitWindowPosition(200, 200);
    glutCreateWindow("2D Translation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
