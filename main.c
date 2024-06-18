#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static int shoulder = 0, elbow = 0, polegar = 0, indicador = 0; 

void init(void){
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void){
  glClear (GL_COLOR_BUFFER_BIT);

  glPushMatrix();


  glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);


  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glutWireCube (1.0);
  glPopMatrix();

  glTranslatef (1.0, 0.0, 0.0);
  glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);

  glPushMatrix();
  glTranslatef (1.0, 0.0, 0.0);
  glScalef (2.0, 0.4, 1.0);
  glutWireCube (1.0);
  glPopMatrix();

  glTranslatef (2.0, 0.0, 0.0);
  // Dedo Polegar
  glPushMatrix();
  glTranslatef(0.125, -0.5, 0.0);
  glRotatef((GLfloat) polegar, 0.0, 0.0, 1.0);
  glScalef(0.25, 0.6, 0.25);
  glutWireCube(1.0);
  glPopMatrix();
 
 
  // Dedo Indicador
  glPushMatrix();
  glTranslatef(0.125, 0.0, 0.375);
  glRotatef((GLfloat) indicador, 0.0, 0.0, 1.0);
  glScalef(0.25, 0.6, 0.25);
  glutWireCube(1.0);
  glPopMatrix();

  /*
  // Dedo Médio
  glPushMatrix();
  glTranslatef(2.125, 0.0, -0.375);
  glScalef(0.25, 0.4, 0.25);
  glutWireCube(1.0);
  glPopMatrix();
  */

  glPopMatrix();
  glutSwapBuffers();
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(85, (GLfloat) w/(GLfloat) h, 0.1, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(5,0,0,0,0,0,0,1,0);  // (0, 0, 5, 0, 0, 0, 0, 1, 0) vemos de z olhando o plano xy
  				 // (5, 0, 0, 0, 0, 0, 0, 1, 0) Vemos de x olhando o plano yz
  //gluLookAt(0,0,5,0,0,0,0,1,0);
}

void keyboard (unsigned char key, int x, int y){
  switch (key) {
  case 'w':
    shoulder = (shoulder + 5) % 360;
    glutPostRedisplay();
    break;
  case 's':
    shoulder = (shoulder - 5) % 360;
    glutPostRedisplay();
    break;
  case 'p':
    elbow = (elbow + 5) % 360;
    glutPostRedisplay();
    break;
  case 'l':
    elbow = (elbow - 5) % 360;
    glutPostRedisplay();
    break;
  case 'o':
    polegar = (polegar + 5) % 360;
    glutPostRedisplay();
    break;
  case 'k':
    polegar = (polegar - 5) % 360;
    glutPostRedisplay();
    break;
  case 'i':
    indicador = (indicador + 5) % 360;
    glutPostRedisplay();
    break;
  case 'j':
    indicador = (indicador - 5) % 360;
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
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
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}



