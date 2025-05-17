#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

int x, y, r;

void bresenham_circle()
{
    int xi = 0, yi = r;
    int p = 3 - 2 * r;

    glBegin(GL_POINTS);
    while (xi <= yi)
    {
        // Plot the points in all 8 octants
        glVertex2i(xi + x, yi + y);
        glVertex2i(-xi + x, yi + y);
        glVertex2i(xi + x, -yi + y);
        glVertex2i(-xi + x, -yi + y);
        glVertex2i(yi + x, xi + y);
        glVertex2i(-yi + x, xi + y);
        glVertex2i(yi + x, -xi + y);
        glVertex2i(-yi + x, -xi + y);

        if (p < 0)
        {
            p += 4 * xi + 6;
        }
        else
        {
            yi--;
            p += 4 * (xi - yi) + 10;
        }

        xi++;
    }

    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
      glVertex2i(-300, 0);
      glVertex2i(300, 0);
      glVertex2i(0, -280);
      glVertex2i(0, 280);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    bresenham_circle();

    glFlush();
}

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300, 300, -280, 280);
}

int main(int argc, char** argv)
{
    cout << "X Coordinate: ";
    cin >> x;

    cout << "Y Coordinate: ";
    cin >> y;

    cout << "Radius: ";
    cin >> r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bresenham's Circle Drawing");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();

    return 0;
}
