#include <GL/glut.h>

void display() {
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // simple 2D box
    gluOrtho2D(-1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
        glColor3f(1,0,0); glVertex2f(-0.6f, -0.6f);
        glColor3f(0,1,0); glVertex2f( 0.6f, -0.6f);
        glColor3f(0,0,1); glVertex2f( 0.0f,  0.6f);
    glEnd();

    glFlush(); // single buffer
}

int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Hello Triangle");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
