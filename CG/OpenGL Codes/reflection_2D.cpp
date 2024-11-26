#include <GL/glut.h>

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

void reflect(int axis) {
    glPushMatrix();
    switch (axis) {
        case 1:  // Reflect about X-axis
            glScalef(1.0, -1.0, 0.0);
            break;
        case 2:  // Reflect about Y-axis
            glScalef(-1.0, 1.0, 0.0);
            break;
        case 3: 
            glScalef(-1.0, -1.0, 0.0);
            break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawAxes();
    
    glColor3f(1.0, 0.0, 0.0);
    drawFigure();
    
    glPushMatrix();
    reflect(1);
    glColor3f(0.0, 1.0, 0.0); 
    drawFigure();
    glPopMatrix();
    
    glPushMatrix();
    reflect(2);
    glColor3f(0.0, 0.0, 1.0); 
    drawFigure();
    glPopMatrix();
    
    // glPushMatrix();
    // reflect(3);
    // glColor3f(1.0, 1.0, 0.0);
    // drawFigure();
    // glPopMatrix();
    
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
    glutCreateWindow("2D Reflection");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}