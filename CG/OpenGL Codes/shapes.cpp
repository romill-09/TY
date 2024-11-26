#include <bits/stdc++.h>
#include <GL/glut.h>

void A() {
    glBegin(GL_LINE_LOOP);
    glVertex2i(30, 90);
    glVertex2i(70, 80);
    glVertex2i(22, 30);
    glVertex2i(75, 32);
    glVertex2i(30, 90);
    glEnd();
}

void B() {
    glBegin(GL_LINE_LOOP);
    glVertex2i(120, 120);
    glVertex2i(170, 110);
    glVertex2i(165, 100);
    glVertex2i(135, 108);
    glVertex2i(128, 95);
    glVertex2i(145, 90);
    glVertex2i(140, 80);
    glVertex2i(120, 85);
    glVertex2i(110, 45);
    glVertex2i(100, 55);
    glVertex2i(120, 120);
    glEnd();
}

void C() {
    glBegin(GL_LINE_LOOP);
    glVertex2i(190, 80);
    glVertex2i(250, 78);
    glVertex2i(240, 50);
    glVertex2i(252, 30);
    glVertex2i(215, 20);
    glVertex2i(180, 35);
    glVertex2i(180, 60);
    glVertex2i(190, 80);
    glEnd();
}

void D() {
    glBegin(GL_LINE_LOOP);
    glVertex2i(260, 30);
    glVertex2i(310, 70);
    glVertex2i(280, 110);
    glEnd();
}

void Hexagon(int xc, int yc, int r) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 6; ++i) {
        glVertex2i(xc + r * cos(i * M_PI / 3), yc + r * sin(i * M_PI / 3));
    }
    glEnd();
}

void Decagon(int xc, int yc, int r) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; ++i) {
        glVertex2i(xc + r * cos(i * M_PI / 5), yc + r * sin(i * M_PI / 5));
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0, 1.0, 0.0);
    
    A();
    B();
    Hexagon(360, 70, 40);
    C();
    D();
    Decagon(460, 70, 40);
    
    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 150);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 150);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Shapes");

    init();
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}
