#include <GL/glut.h>
#include <stdio.h>
#include "stb_image.h"

/*  Draws a simple scene to show how to use texture objects.  Three texture images
 *  are loaded into three texture objects.  The scene contains three copies of the
 *  GLUT teapot, using the three different textures.
 *     The program uses the FreeImage image processing library to read the texture
 *  images from files.  It must be linked against that library along with the GL
 *  and glut libraries.  For example, using gcc on Linux
 *
 *      gcc -o teapots texture-objects.c -lGL -lglut -lfreeimage
 */

// --------------------------------- global variables --------------------------------

GLuint texID[6];  // Texture ID's for the three textures.

char* textureFileNames[6] = {   // file names for the files from which texture images are loaded
            "../texturas/container.jpg",
            "../texturas/brick001.jpg",
            "../texturas/marble.jpg",
            "../texturas/Earth-1024x512.jpg",
	    "../texturas/NightEarth-512x256.jpg",
	    "../texturas/mandelbrot.jpeg",

       };

float rotateX = 0;   // rotations for a simple viewing transform, applied to
float rotateY = 0;   //    each teapot, controlled by the arrow and HOME keys.


// ------------------------ OpenGL initialization and rendering -----------------------

void initGL() {
      // called by main() to initialize the OpenGL drawing context

    glClearColor(0.0, 0.0, 0.0, 1.0); // background color

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float white[4] = { 1, 1, 1, 1 };  // A white material, suitable for texturing.
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( -3.75,3.75, -1.5,1.5, -2,2 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}  // end initGL()

void drawFace1() {
   glBindTexture( GL_TEXTURE_2D, texID[0] ); 
   glBegin(GL_POLYGON);
     glNormal3f(1,  0,  0);

     glTexCoord2f(0, 0);
     glVertex3f(1, -1,  1);

     glTexCoord2f(1, 0);
     glVertex3f(1, -1, -1);

     glTexCoord2f(1, 1);
     glVertex3f(1,  1, -1);

     glTexCoord2f(0, 1);
     glVertex3f(1,  1,  1);
   glEnd();   
}

void drawFace2() {
   glBindTexture( GL_TEXTURE_2D, texID[1] );  
   glBegin(GL_POLYGON);
     glNormal3f(0, 0, 1);
     
     glTexCoord2f(0, 0);
     glVertex3f(1 , -1, 1);

     glTexCoord2f(-1, 0);
     glVertex3f(-1, -1, 1);

     glTexCoord2f(-1, 1);
     glVertex3f(-1,  1, 1);

     glTexCoord2f(0, 1);
     glVertex3f(1 ,  1, 1);
   glEnd();   
}

void drawFace3() {
  glBindTexture( GL_TEXTURE_2D, texID[2] );
  glBegin(GL_POLYGON);
     glNormal3f(-1, 0, 0);
    
     glTexCoord2f(0, 0);
     glVertex3f(-1, -1,  1);

     glTexCoord2f(1, 0);
     glVertex3f(-1, -1, -1);

     glTexCoord2f(1, 1);
     glVertex3f(-1,  1, -1);

     glTexCoord2f(0, 1);
     glVertex3f(-1,  1,  1);
  glEnd();
}

void drawFace4() {
  glBindTexture( GL_TEXTURE_2D, texID[3] );
  glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);

    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -1);

    glTexCoord2f(1, 1);
    glVertex3f( 1, -1, -1);
    glTexCoord2f(1, 0);
    glVertex3f( 1,  1, -1);
    glTexCoord2f(0, 0);
    glVertex3f(-1,  1, -1 );
  glEnd();
  
}

void drawFace5() {
  glBindTexture( GL_TEXTURE_2D, texID[4] );
  
  glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);

    glTexCoord2f(0, 0);
    glVertex3f(1, 1,  1);

    glTexCoord2f(0, 1);
    glVertex3f(1, 1, -1);

    glTexCoord2f(1, 1);
    glVertex3f(-1, 1, -1);

    glTexCoord2f(1, 0);
    glVertex3f(-1, 1, 1);

  glEnd();
}

void drawFace6() {
  glBindTexture( GL_TEXTURE_2D, texID[5] );
  
  glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);

    glTexCoord2f(0, 0);
    glVertex3f(1, -1, 1);

    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, 1);

    glTexCoord2f(1, 1);
    glVertex3f(-1, -1, -1);

    glTexCoord2f(1, 0);
    glVertex3f(1, -1, -1);
  glEnd();
}

void drawCube() {
   glPushMatrix();
   glScalef(0.8, 0.8, 0.8);
   drawFace1();
   drawFace2();
   drawFace3();
   drawFace4();
   drawFace5();
   drawFace6();
   glPopMatrix();
}


void display() {
       // Draws the scene, consisting of three teapots with different textures.

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    
    glPushMatrix();
    glTranslatef(0, 0.05, 0);
    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);
    drawCube();
    glPopMatrix();

    glutSwapBuffers();  // (required for double-buffered drawing)
}


// --------------- keyboard event function ---------------------------------------


void specialKeyFunction(int key, int x, int y) {
        // Change rotation amounts in response to arrow and home keys.
    if ( key == GLUT_KEY_LEFT )
       rotateY -= 15;
    else if ( key == GLUT_KEY_RIGHT )
       rotateY += 15;
    else if ( key == GLUT_KEY_DOWN)
       rotateX += 15;
    else if ( key == GLUT_KEY_UP )
       rotateX -= 15;
    else if ( key == GLUT_KEY_HOME )
       rotateX = rotateY = 0;
    glutPostRedisplay();
}


// --------------------- texture loading -----------------------------------------

/*  This function loads three textures from texture files, which must be available
 *  to the program when it is run.  Paths to the files are stored in the global
 *  array textureFileNames.  The function generates three texture object identifiers
 *  and stores them in the global array  textID  so that they can be used when
 *  binding textures in display().  It then loads the three texture images into
 *  the texture objects.  It calles glTexParameteri for each texture to change
 *  the minification filter to GL_LINEAR (without this, the texture won't work
 *  because there are no mipmaps for the textures).
 */
void loadTextures() {
	int width, height, nrChannels;
	unsigned char *data;

	glGenTextures(6, texID);

	for(int i = 0; i < 6;i++)
	{
	glBindTexture(GL_TEXTURE_2D, texID[i]);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture

	data = stbi_load(textureFileNames[i], &width, &height, &nrChannels, 0);

	if (data)
	{
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	    //glGenerateMipmap(GL_TEXTURE_2D);
	    glTexParameteri  (GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	}
	else
	{
		 printf("Failed to load texture\n");
	}
	stbi_image_free(data);
	}

}


// ----------------- main routine -------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(750,300);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Textura");
    initGL();
    loadTextures();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeyFunction);
    glutMainLoop();
    return 0;
}
