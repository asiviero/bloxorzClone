/*
 * main.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#include "inc.h"

Platform *p1;
Block *b1;

float camDistance[3] = {0,0,0};
float angle[3] = {0,0,0};
bool keyStates[255];
GLuint brickTextureID;

GLuint loadTexture(const string filename, int &width, int &height)
 {
   //header for testing if it is a png
   png_byte header[8];

   //open file as binary
   FILE *fp = fopen(filename.c_str(), "rb");
   if (!fp) {
     return TEXTURE_LOAD_ERROR;
   }

   //read the header
   fread(header, 1, 8, fp);

   //test if png
   int is_png = !png_sig_cmp(header, 0, 8);
   if (!is_png) {
     fclose(fp);
     return TEXTURE_LOAD_ERROR;
   }

   //create png struct
   png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
       NULL, NULL);
   if (!png_ptr) {
     fclose(fp);
     return (TEXTURE_LOAD_ERROR);
   }

   //create png info struct
   png_infop info_ptr = png_create_info_struct(png_ptr);
   if (!info_ptr) {
     png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
     fclose(fp);
     return (TEXTURE_LOAD_ERROR);
   }

   //create png info struct
   png_infop end_info = png_create_info_struct(png_ptr);
   if (!end_info) {
     png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
     fclose(fp);
     return (TEXTURE_LOAD_ERROR);
   }

   //png error stuff, not sure libpng man suggests this.
   if (setjmp(png_jmpbuf(png_ptr))) {
     png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
     fclose(fp);
     return (TEXTURE_LOAD_ERROR);
   }

   //init png reading
   png_init_io(png_ptr, fp);

   //let libpng know you already read the first 8 bytes
   png_set_sig_bytes(png_ptr, 8);

   // read all the info up to the image data
   png_read_info(png_ptr, info_ptr);

   //variables to pass to get info
   int bit_depth, color_type;
   png_uint_32 twidth, theight;

   // get info about png
   png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
       NULL, NULL, NULL);

   //update width and height based on png info
   width = twidth;
   height = theight;

   // Update the png info struct.
   png_read_update_info(png_ptr, info_ptr);

   // Row size in bytes.
   int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

   // Allocate the image_data as a big block, to be given to opengl
   png_byte *image_data = new png_byte[rowbytes * height];
   if (!image_data) {
     //clean up memory and close stuff
     png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
     fclose(fp);
     return TEXTURE_LOAD_ERROR;
   }

   //row_pointers is for pointing to image_data for reading the png with libpng
   png_bytep *row_pointers = new png_bytep[height];
   if (!row_pointers) {
     //clean up memory and close stuff
     png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
     delete[] image_data;
     fclose(fp);
     return TEXTURE_LOAD_ERROR;
   }
   // set the individual row_pointers to point at the correct offsets of image_data
   for (int i = 0; i < height; ++i)
     row_pointers[height - 1 - i] = image_data + i * rowbytes;

   //read the png into image_data through row_pointers
   png_read_image(png_ptr, row_pointers);

   //Now generate the OpenGL texture object
   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, width, height, 0,
       GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*) image_data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   //clean up memory and close stuff
   png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
   delete[] image_data;
   delete[] row_pointers;
   fclose(fp);

   return texture;
 }


// A very simple function to flush the screen and load the "cube"
void initScreen (void)
{
/*  select clearing (background) color       */
    //glClearColor (1.0, 1.0, 1.0, 0.0);
    glClearColor (0.0, 0.0, 0.0, 0.0);
       glShadeModel (GL_FLAT);
/*  initialize viewing values  */
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0, MAX_PLATFORM_SIZE_X, 0, MAX_PLATFORM_SIZE_Y, 0, 100);
    glLoadIdentity();
    glFrustum(0,MAX_PLATFORM_SIZE_X,0,MAX_PLATFORM_SIZE_Y,-100,100);
    glMatrixMode(GL_MODELVIEW);*/
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);
   glMatrixMode (GL_MODELVIEW);
}



void fsmFunction(void) {
	/*glEnable(GL_DEPTH_TEST);
	glClear (GL_COLOR_BUFFER_BIT);
//	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-10+camDistance,0,0,0,0,1,0);

	glTranslatef(0,0,-camDistance);

	// Draw the Brick
//	glPushMatrix();
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		glVertex3f(b1->Position[0][X_AXIS],b1->Position[0][Y_AXIS],0);
		glVertex3f(b1->Position[0][X_AXIS]+1,b1->Position[0][Y_AXIS],0);
		glVertex3f(b1->Position[0][X_AXIS]+1,b1->Position[0][Y_AXIS]+1,0);
		glVertex3f(b1->Position[0][X_AXIS],b1->Position[0][Y_AXIS]+1,0);
	glEnd();
//	glPopMatrix();


	glFlush();
	//glutSwapBuffers();

	//glutPostRedisplay();*/

	/*
	cout << "Plat Goal: " << p1->Goal[X_AXIS] << " " << p1->Goal[Y_AXIS] << "\n";
//	cout << "Plat Starting Point: " << p1->StartPosition[0][X_AXIS] << " " << p1->StartPosition[0][Y_AXIS] << " " << p1->StartPosition[1][X_AXIS] << " " << p1->StartPosition[1][Y_AXIS] <<"\n";
	cout << "Block Point: " << b1->Position[0][X_AXIS] << " " << b1->Position[0][Y_AXIS] << " " << b1->Position[1][X_AXIS] << " " << b1->Position[1][Y_AXIS] <<"\n";

	*/

	glEnable(GL_DEPTH_TEST);
	   glClear (GL_COLOR_BUFFER_BIT);
	   glColor3f (1.0, 1.0, 1.0);
	   glLoadIdentity ();             /* clear the matrix */
	   glRotatef(angle[X_AXIS],1,0,0);
	   glRotatef(angle[Y_AXIS],0,1,0);
	   glRotatef(angle[Z_AXIS],0,0,1);

	   glTranslatef(-MAX_PLATFORM_SIZE_X/2,-MAX_PLATFORM_SIZE_Y/2,0);
	   gluLookAt (-camDistance[X_AXIS], -camDistance[Y_AXIS], 10.0-camDistance[Z_AXIS],
			   -camDistance[X_AXIS], -camDistance[Y_AXIS], -camDistance[Z_AXIS], 0.0, 1.0, 0.0);

       /* viewing transformation  */

	   //glTranslatef(0,0,10);

	   //glScalef (1.0, 1.0, 1.0);      /* modeling transformation */
	   //glutWireCube (1.0);

	   p1->Render();
	   b1->Render();

	   glFlush ();
	   performKeyOperations();
	   	   cout << "Block Point: " << b1->Position[0][X_AXIS] << " " << b1->Position[0][Y_AXIS] << " " << b1->Position[1][X_AXIS] << " " << b1->Position[1][Y_AXIS] <<"\n";

	   	// Check for out of platform
	   		if(b1->isBlockOutOfPlatform(p1->PlatformMatrix)) {
	   			cout << "Out of Platform!\n";
	   		}

	   		// Check if objective reached
	   		if(b1->isBlockOnPosition(p1->Goal)) {
	   			cout << "Objective Reached!\n";
	   		}

}


int main(int argc, char** argv) {

	// Init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(1200,800);
	glutInitWindowSize(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT);
	int intMainWindowID;
	intMainWindowID = glutCreateWindow("Bloxorz Clone");

	p1 = new Platform("../platforms/blox.txt");

	b1 = new Block(p1->StartPosition);

	// Loading Texture
	int w,h;
	//glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &brickTextureID);

	if(fopen("../img/brick.png","r")) cout << "Abriu!\n";
	brickTextureID = loadTexture("../img/brick.png",w,h);
	//glBindTexture(GL_TEXTURE_2D, brickTextureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, your_data);

	initializeKeyStates();
	glutKeyboardFunc(keyboardHandler);
	glutKeyboardUpFunc(keyboardUpHandler);
	glutSpecialFunc(specialKeysHandler);

	initScreen();
	glutDisplayFunc(fsmFunction);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}
