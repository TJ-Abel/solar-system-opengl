cat > solar.cpp << 'EOF'
#include <GL/glut.h>
#include <cmath>   // fmodf, cosf, sinf

// -------- Globals --------
float angleMercury=0, angleVenus=0, angleEarth=0;
float zoom = 38.0f;      // Camera zoom distance
bool  paused = false;    // Pause toggle
bool  showOrbits = true; // Toggle orbit rings

// -------- Window / Camera --------
void reshape(int w,int h){
    if(h==0) h=1;
    float a=(float)w/(float)h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(60.0, a, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

// -------- Helpers --------
void drawSphere(float r, float R,float G,float B){
    glColor3f(R,G,B);
    glutSolidSphere(r, 24, 24);
}

void drawOrbit(float radius){
    const int segs = 128;
    const float TWO_PI = 6.28318530718f;
    glBegin(GL_LINE_LOOP);
      for(int i=0;i<segs;i++){
          float t = (i/(float)segs) * TWO_PI;
          float x = radius * cosf(t);
          float z = radius * sinf(t);
          glVertex3f(x, 0.0f, z);
      }
    glEnd();
}

// -------- Render --------
void display(){
    glClearColor(0.02f,0.02f,0.05f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Nice-looking orbit lines
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(1.5f);

    glLoadIdentity();
    gluLookAt(0, 12, zoom,  0,0,0,  0,1,0);

    // ----- Orbits (XZ plane) -----
    if(showOrbits){
        glColor4f(0.85f, 0.85f, 0.9f, 0.6f);
        drawOrbit(6.0f);   // Mercury orbit
        drawOrbit(10.0f);  // Venus orbit
        drawOrbit(14.0f);  // Earth orbit

        // Moon orbit around Earth: draw in Earth's local frame
        glPushMatrix();
          glRotatef(angleEarth, 0,1,0);
          glTranslatef(14, 0, 0);
          glColor4f(0.9f, 0.9f, 0.95f, 0.6f);
          drawOrbit(2.0f);
        glPopMatrix();
    }

    // ----- Bodies -----
    // Sun
    glPushMatrix(); drawSphere(2.0f, 1.0f,1.0f,0.0f); glPopMatrix();

    // Mercury
    glPushMatrix();
      glRotatef(angleMercury, 0,1,0);
      glTranslatef(6,0,0);
      drawSphere(0.6f, 0.7f,0.7f,0.7f);
    glPopMatrix();

    // Venus
    glPushMatrix();
      glRotatef(angleVenus, 0,1,0);
      glTranslatef(10,0,0);
      drawSphere(0.8f, 1.0f,0.5f,0.0f);
    glPopMatrix();

    // Earth + Moon
    glPushMatrix();
      glRotatef(angleEarth, 0,1,0);
      glTranslatef(14,0,0);
      drawSphere(0.9f, 0.0f,0.0f,1.0f);

      glRotatef(angleEarth*12.0f, 0,1,0);
      glTranslatef(2,0,0);
      drawSphere(0.3f, 0.8f,0.8f,0.8f);
    glPopMatrix();

    glutSwapBuffers();
}

// -------- Animation --------
void update(int){
    if(!paused){
        angleMercury = fmodf(angleMercury+4.0f, 360.0f);
        angleVenus   = fmodf(angleVenus+2.0f,   360.0f);
        angleEarth   = fmodf(angleEarth+1.0f,   360.0f);
    }
    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

// -------- Input --------
void keyboard(unsigned char key, int, int){
    switch(key){
        case '+': zoom -= 1.0f; if(zoom < 10) zoom = 10; break;
        case '-': zoom += 1.0f; if(zoom > 80) zoom = 80; break;
        case 'p': case 'P': paused = !paused; break;
        case 'o': case 'O': showOrbits = !showOrbits; break;
        case 27: exit(0); // ESC
    }
    glutPostRedisplay();
}

// -------- Main --------
int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Interactive Solar System + Orbits");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(50, update, 0);
    glutMainLoop();
    return 0;
}
EOF