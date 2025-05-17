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

void rotateRelativeToPoint(float angle, float px, float py) {
    glTranslatef(px, py, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-px, -py, 0.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    drawAxes();
    
    glColor3f(1.0, 0.0, 0.0);
    drawFigure();
    
    glLoadIdentity();
    glColor3f(0.0, 1.0, 0.0);
    rotateRelativeToPoint(-45, -0.2, -0.2);
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
    glutCreateWindow("2D Rotation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
