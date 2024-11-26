#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

float x_1, x_2, y_1, y_2;

void display(void) {
    int dx = x_2 - x_1;
    int dy = y_2 - y_1;
    int D = 2 * dy - dx;
    int y = y_1;

    glBegin(GL_POINTS);
    glVertex2i(x_1, y_1);
    glEnd();

    for (int x = x_1 + 1; x <= x_2; x++) {
        if (D >= 0) {
            y++;
            D += 2 * (dy - dx);
        } else {
            D += 2 * dy;
        }
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }

    glFlush();
}

void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 40.0, 0.0, 40.0);
}

int main(int argc, char** argv) {
    cout << "Value of x1: ";
    cin >> x_1;
    cout << "Value of y1: ";
    cin >> y_1;
    cout << "Value of x2: ";
    cin >> x_2;
    cout << "Value of y2: ";
    cin >> y_2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Midpoint Line Drawing");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
