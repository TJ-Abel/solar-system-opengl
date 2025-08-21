#include <GL/glut.h>

void drawAxes(float L){
    glBegin(GL_LINES);
      glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(L,0,0); // X
      glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,L,0); // Y
      glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,L); // Z
    glEnd();
}

void reshape(int w,int h){
    if(h==0) h=1;
    float a=(float)w/(float)h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(60.0,a,0.1,200.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(){
    glClearColor(0.08f,0.08f,0.1f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glLoadIdentity();
    gluLookAt(15,10,25,  0,0,0,  0,1,0);

    drawAxes(10.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
    glColor3f(1,1,1);
    glutWireCube(8.0);

    glutSwapBuffers();
}

int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Debug Axes + Cube");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
