#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "stb_image.h"

GLuint texID[6];  // Texture ID's for the three textures.

char* textureFileNames[6] = {   // file names for the files from which texture images are loaded
            "../texturas/container.jpg",
            "../texturas/brick001.jpg",
            "../texturas/marble.jpg",
            "../texturas/Earth-1024x512.jpg",
	    "../texturas/NightEarth-512x256.jpg",
	    "../texturas/mandelbrot.jpeg",

};

int BRASS         =  0;
int BRONZE        =  1;
int CHROME        =  2;
int COPPER        =  3;
int GOLD          =  4;
int PEWTER        =  5;
int SILVER        =  6;
int JADE          =  7;
int OBSIDIAN      =  8;
int PEARL         =  9;
int RUBY          = 10;
int TURQUOISE     = 11;
int BLACK_PLASTIC = 12;
int BLACK_RUBBER  = 13;

int LAST_MATERIAL = 14;

int material = -1;



float SPECULAR_EXPONENTS[] =
{
   27.897400, // BRASS
   25.600000, // BRONZE
   76.800003, // CHROME
   12.800000, // COPPER
   51.200001, // GOLD
   09.846150, // PEWTER
   51.200001, // SILVER
   76.800003, // EMERALD
   12.800000, // JADE
   38.400002, // OBSIDIAN
   11.264000, // PEARL
   76.800003, // RUBY
   12.800000, // TURQUOISE
   32.000000, // BLACK_PLASTIC
   10.000000  // BLACK_RUBBER
};


float MATERIAL_COLORS[][3][4] =
{
   // BRASS 0
   {
      {0.329412, 0.223529, 0.027451, 1.000000}, // Ambient RGBA
      {0.780392, 0.568627, 0.113725, 1.000000}, // Diffuse RGBA
      {0.992157, 0.941176, 0.807843, 1.000000}  // Specular RGBA
   },

   // BRONZE 1
   {
      {0.212500, 0.127500, 0.054000, 1.000000},
      {0.714000, 0.428400, 0.181440, 1.000000},
      {0.393548, 0.271906, 0.166721, 1.000000}
   },

   // CHROME 2
   {
      {0.250000, 0.250000, 0.250000, 1.000000},
      {0.400000, 0.400000, 0.400000, 1.000000},
      {0.774597, 0.774597, 0.774597, 1.000000}
   },

   // COPPER 3
   {
      {0.191250, 0.073500, 0.022500, 1.000000},
      {0.703800, 0.270480, 0.082800, 1.000000},
      {0.256777, 0.137622, 0.086014, 1.000000}
   },

   // GOLD 4
   {
      {0.247250, 0.199500, 0.074500, 1.000000},
      {0.751640, 0.606480, 0.226480, 1.000000},
      {0.628281, 0.555802, 0.366065, 1.000000}
   },

   // PEWTER 5
   {
      {0.105882, 0.058824, 0.113725, 1.000000},
      {0.427451, 0.470588, 0.541176, 1.000000},
      {0.333333, 0.333333, 0.521569, 1.000000}
   },

   // SILVER 6
   {
      {0.192250, 0.192250, 0.192250, 1.000000},
      {0.507540, 0.507540, 0.507540, 1.000000},
      {0.508273, 0.508273, 0.508273, 1.000000}
   },

   // EMERALD 7
   {
      {0.021500, 0.174500, 0.021500, 0.550000},
      {0.075680, 0.614240, 0.075680, 0.550000},
      {0.633000, 0.727811, 0.633000, 0.550000}
   },

   // JADE 8
   {
      {0.135000, 0.222500, 0.157500, 0.950000},
      {0.540000, 0.890000, 0.630000, 0.950000},
      {0.316228, 0.316228, 0.316228, 0.950000}
   },

   // OBSIDIAN 9
   {
      {0.053750, 0.050000, 0.066250, 0.820000},
      {0.182750, 0.170000, 0.225250, 0.820000},
      {0.332741, 0.328634, 0.346435, 0.820000}
   },

   // PEARL 10
   {
      {0.250000, 0.207250, 0.207250, 0.922000},
      {1.000000, 0.829000, 0.829000, 0.922000},
      {0.296648, 0.296648, 0.296648, 0.922000}
   },

   // RUBY 11
   {
      {0.174500, 0.011750, 0.011750, 0.550000},
      {0.614240, 0.041360, 0.041360, 0.550000},
      {0.727811, 0.626959, 0.626959, 0.550000}
   },

   // TURQUOISE 12
   {
      {0.100000, 0.187250, 0.174500, 0.800000},
      {0.396000, 0.741510, 0.691020, 0.800000},
      {0.297254, 0.308290, 0.306678, 0.800000}
   },

   // BLACK_PLASTIC 13
   {
      {0.000000, 0.000000, 0.000000, 1.000000},
      {0.010000, 0.010000, 0.010000, 1.000000},
      {0.500000, 0.500000, 0.500000, 1.000000}
   },

   // BLACK_RUBBER 14
   {
      {0.020000, 0.020000, 0.020000, 1.000000},
      {0.010000, 0.010000, 0.010000, 1.000000},
      {0.400000, 0.400000, 0.400000, 1.000000}
   }
};



void init(void){
  //glClearColor (0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_NORMALIZE);

  glShadeModel(GL_SMOOTH);

  glEnable(GL_LIGHTING);

  glEnable(GL_LIGHT0);


}

void pe() {
  glPushMatrix();
    glTranslatef(0, 1.25, 0);
    glScalef (0.5, 2.5, 0.5);
    glutSolidCube(1.0);
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
  material = BRONZE;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , MATERIAL_COLORS[material][2]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , MATERIAL_COLORS[material][0]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , MATERIAL_COLORS[material][1]);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SPECULAR_EXPONENTS[material]);
  
  base_cadeira();

  material = TURQUOISE;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , MATERIAL_COLORS[material][2]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , MATERIAL_COLORS[material][0]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , MATERIAL_COLORS[material][1]);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SPECULAR_EXPONENTS[material]);

  // poltrona
  glPushMatrix();
    glTranslatef(0, 2.5, 0);
    glScalef(5, 0.5, 5);
    glutSolidCube(1.0);
  glPopMatrix();

  // encosto
  glPushMatrix();
    glTranslatef(2.5, 5, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(5, 0.5, 5);
    glutSolidCube(1.0);
  glPopMatrix();
}

void mesa() {

  material = BRONZE;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , MATERIAL_COLORS[material][2]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , MATERIAL_COLORS[material][0]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , MATERIAL_COLORS[material][1]);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SPECULAR_EXPONENTS[material]);

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

  material = JADE;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , MATERIAL_COLORS[material][2]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , MATERIAL_COLORS[material][0]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , MATERIAL_COLORS[material][1]);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SPECULAR_EXPONENTS[material]);

  glPushMatrix();
    glTranslatef(0, 2.5, 0);
    glScalef(5, 0.5, 5);
    glutSolidCube(1.0);
  glPopMatrix();
}

void drawFace1() {
   glBindTexture( GL_TEXTURE_2D, texID[2] );
   glBegin(GL_POLYGON);
     glNormal3f(-1,  0,  0);

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
   glBindTexture( GL_TEXTURE_2D, texID[2] );
   glBegin(GL_POLYGON);
     glNormal3f(0, 0, -1);

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
     glNormal3f(1, 0, 0);

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
  glBindTexture( GL_TEXTURE_2D, texID[2] );
  glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);

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
  glBindTexture( GL_TEXTURE_2D, texID[1] );

  glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);

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
  glBindTexture( GL_TEXTURE_2D, texID[1] );

  glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);

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
    glScalef(17.0, 18.0, 17.0);
    drawFace1();
    drawFace2();
    drawFace3();
    drawFace4();
    drawFace5();
    drawFace6();
  glPopMatrix();
}

void display(void){
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);

  glPushMatrix();
    //glTranslatef(0, 0., 0);
    drawCube();
  glPopMatrix(); 

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
  gluPerspective(82, (GLfloat) w/(GLfloat) h, 0.09, 140.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluLookAt(5,0,0,0,0,0,0,1,0);  // (0, 0, 5, 0, 0, 0, 0, 1, 0) vemos de z olhando o plano xy
  				 // (5, 0, 0, 0, 0, 0, 0, 1, 0) Vemos de x olhando o plano yz
  gluLookAt(7,10,9,0,0,0,0,1,0);
}

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



int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (900, 900);
  glutInitWindowPosition (900, 30);
  glutCreateWindow (argv[0]);
  init ();
  loadTextures();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}




