/*
 * main.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: andre
 */

#include "inc.h"

Platform *p1;
Block *b1;

bool dispFlag = false;
float camDistance[3] = {0,0,0};
float angle[3] = {0,0,0};
bool keyStates[255];
GLuint brickTextureID;
Stage *fase;
TextScreen *initialScreen,*failScreen,*succesScreen,*gameOverScreen;
Screen *gameScreen;
gameStates gameState = OpeningScreen;


char FasesString[2][100];
int onStage = 0;

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
	//glViewport (0, 0, (GLsizei) 400, (GLsizei) 400);
	glClearColor (0.0, 0.0, 0.0, 0.0);
		       glShadeModel (GL_FLAT);

		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(0,1,0,10);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();



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


	switch(gameState) {
		case OpeningScreen:
			gameScreen = initialScreen;
			if(keyStates[13] == true || keyStates['m'] == true) {
				keyStates[13] = false;
				keyStates['m'] = false;
				gameState = StageScreen;
				glutSwapBuffers();
				glutPostRedisplay();
			}
			if(dispFlag == false) {
				glutPostRedisplay();
				dispFlag = true;
			}
			break;
		case StageScreen:
			dispFlag = false;
			if(!fase) fase = new Stage(FasesString[onStage]);
			gameScreen = fase;

			// Check for out of platform
			if(fase->b1->isBlockOutOfPlatform(fase->p1->PlatformMatrix)) {
				//cout << "Out of Platform!\n";
				gameState = FailScreen;
				fase = NULL;
				glutSwapBuffers();
				glutPostRedisplay();
				//return;
			}

			// Check if objective reached
			if(fase && fase->b1->isBlockOnPosition(fase->p1->Goal)) {
				gameState = OpeningScreen;
				onStage++;
				if(onStage == MAX_NUMBER_STAGES) {
					gameState = GameOverScreen;
				}
				fase = NULL;

				//glMatrixMode(GL_MODELVIEW);
				//glLoadIdentity();
				glutPostRedisplay();
				//return;
			}
			break;

		// Morreu
		case FailScreen:

			gameScreen = failScreen;
			if(dispFlag == false) {
				glutPostRedisplay();
				dispFlag = true;
			}
			if(keyStates[13] == true || keyStates['m'] == true) {
				keyStates[13] = false;
				keyStates['m'] = false;
				gameState = StageScreen;
				glutSwapBuffers();
				glutPostRedisplay();
			}
			//glMatrixMode(GL_MODELVIEW);
			//glLoadIdentity();
			break;

		// Passou de fase
		case SuccessScreen:

				gameScreen = succesScreen;
				if(dispFlag == false) {
					glutPostRedisplay();
					dispFlag = true;
				}
				if(keyStates[13] == true || keyStates['m'] == true) {
					keyStates[13] = false;
					keyStates['m'] = false;
					gameState = StageScreen;
					glutSwapBuffers();
					glutPostRedisplay();
				}
				//glMatrixMode(GL_MODELVIEW);
				//glLoadIdentity();
				break;

		// Fim das Fases
		case GameOverScreen:

				gameScreen = gameOverScreen;
				if(dispFlag == false) {
					glutPostRedisplay();
					dispFlag = true;
				}
				//glMatrixMode(GL_MODELVIEW);
				//glLoadIdentity();
				break;

	}
	gameScreen->Render();


	//fase->Render();
}


int main(int argc, char** argv) {

	// Init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(1200,800);
	glutInitWindowSize(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT);
	int intMainWindowID;
	intMainWindowID = glutCreateWindow("Bloxorz Clone");

	//p1 = new Platform("../platforms/blox.txt");

	//b1 = new Block(p1->StartPosition);
	strcpy(FasesString[0],"../platforms/plat.txt");
	strcpy(FasesString[1],"../platforms/blox.txt");
	//fase = new Stage("../platforms/blox.txt");

	initialScreen = new TextScreen("Bem-vindo ao Bloxorz Clone","Tecle M para Matar");
	failScreen = new TextScreen("FAIL","Disque M para Matar");
	succesScreen = new TextScreen("GREAT SUCCESS","Disque M para Matar");
	gameOverScreen = new TextScreen("GAME OVER","Parabens! Voce zerou :D");

	gameScreen = initialScreen;

	// Loading Texture
	int w,h;
	//glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &brickTextureID);


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
