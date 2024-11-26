#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

int x_1, y_1, x_2, y_2;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void bresenhamLine() {
    int dx = abs(x_2 - x_1);
    int dy = abs(y_2 - y_1);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    
    int x, y;
    
    if (x_1 > x_2) {
        x = x_2;
        y = y_2;
        x_2 = x_1;
    } else {
        x = x_1;
        y = y_1;
    }
    
    drawPixel(x, y);
    
    while (x < x_2) {
        x++;
        if (p < 0) {
            p += twoDy;
        } else {
            y++;
            p += twoDyMinusDx;
        }
        drawPixel(x, y);
    }
    
    glFlush();
}

void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 30.0, 0.0, 30.0);
}

int main(int argc, char** argv) {
    cout << "Enter the value of x1: ";
    cin >> x_1;
    cout << "Enter the value of y1: ";
    cin >> y_1;
    cout << "Enter the value of x2: ";
    cin >> x_2;
    cout << "Enter the value of y2: ";
    cin >> y_2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bresenham's Line Drawing");
    myInit();
    glutDisplayFunc(bresenhamLine);
    glutMainLoop();

    return 0;
}
