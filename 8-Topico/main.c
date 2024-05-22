#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void init(void){
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void pe() {
  glPushMatrix();
    glTranslatef(0, 1.25, 0);
    glScalef (0.5, 2.5, 0.5);
    glutWireCube (1.0);
  glPopMatrix();
}

void haste() {
  glPushMatrix();
    glTranslatef (0, 1.5, 0);
    glRotatef((90-26.5), 0, 0, 1);
    glScalef(0.25, 5.0, 0.25);
    glutWireCube(1.0);
  glPopMatrix();  

  glPushMatrix();
    glTranslatef (0, 1.5, 0);
    glRotatef((90-26.5)*-1, 0, 0, 1);
    glScalef(0.25, 5.0, 0.25);
    glutWireCube(1.0);
  glPopMatrix();
}

void base_cadeira() {
  glPushMatrix();
    glTranslatef(2, 0, 2);
    pe();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2, 0, 2);
    pe();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2, 0, -2);
    pe();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(2, 0, -2);
    pe();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 0, 2);
    haste();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 0, -2);
    haste();
  glPopMatrix();

  glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, 2);
    haste();
  glPopMatrix();

  glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, -2);
    haste();
  glPopMatrix();
}

void cadeira() {
  
  base_cadeira();

  // poltrona
  glPushMatrix();
    glTranslatef(0, 2.5, 0);
    glScalef(5, 0.5, 5);
    glutWireCube(1.0);
  glPopMatrix();

  // encosto
  glPushMatrix();
    glTranslatef(2.5, 5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(5, 0.5, 5);
    glutWireCube(1.0);
  glPopMatrix();
}

void mesa() {
  glPushMatrix();
    glTranslatef(2, 0, 2);
    pe();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2, 0, 2);
    pe();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2, 0, -2);
    pe();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(2, 0, -2);
    pe();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 2.5, 0);
    glScalef(5, 0.5, 5);
    glutWireCube(1.0);
  glPopMatrix();
}

void display(void){
  glClear (GL_COLOR_BUFFER_BIT);

  glPushMatrix();
    glTranslatef(3, 0, 1.5);
    glScalef(0.5, 0.5, 0.5);
    cadeira();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(3, 0, -1.5);
    glScalef(0.5, 0.5, 0.5);
    cadeira();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-3, 0, 1.5);
    glRotatef(180, 0, 1, 0);
    glScalef(0.5, 0.5, 0.5);
    cadeira();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-3, 0, -1.5);
    glRotatef(180, 0, 1, 0);
    glScalef(0.5, 0.5, 0.5);
    cadeira();
  glPopMatrix();

  glPushMatrix();
    glScalef(1, 1, 2);
    mesa();
  glPopMatrix();



  glutSwapBuffers();
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(85, (GLfloat) w/(GLfloat) h, 1, 50.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluLookAt(5,0,0,0,0,0,0,1,0);  // (0, 0, 5, 0, 0, 0, 0, 1, 0) vemos de z olhando o plano xy
  				 // (5, 0, 0, 0, 0, 0, 0, 1, 0) Vemos de x olhando o plano yz
  gluLookAt(10,10,10,0,0,0,0,1,0);
}


int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (900, 900);
  glutInitWindowPosition (900, 30);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}




