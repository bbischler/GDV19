/* ----------------------------------------------------------- */
/* OpenGL-Testprogramm (quick and dirty)                       */
/*  Transparente Textur auf Flaeche ausgeben                   */
/* ----------------------------------------------------------- */
/* Datei: Texture_with_SOIL.cpp                                */
/*	                                                           */
/* Autor: W.-D. Groch                                          */
/* letzte Aenderung:	Groch   27.06.2014                     */
/* ----------------------------------------------------------- */

#include <iostream>      
#include <GL/glut.h>   // laedt alles für OpenGL
#include <soil.h>

GLfloat extent = 1.0;  // Mass fuer die Ausdehnung des Modells
GLfloat winkel =0.0;   // Rotationswinkel
GLuint tex_2d;         // Textur-ID

void Init()	
{
	// Transparenz einsetzen (z.B. fuer Billboards)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	// Hier: Code, der einmalig zu Beginn ausgefuehrt wird
	glClearColor(1.0, 1.0, 0.0, 1.0);  // Hintergrund in Weiss
	// Textur einlesen usw.
	tex_2d = SOIL_load_OGL_texture("TREE1.PNG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT );
	glBindTexture(GL_TEXTURE_2D, tex_2d);

	printf( SOIL_last_result());

}

void RenderScene(void)
{
   // Hier: Code, der in jedem Frame ausgefuehrt werden muss
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Puffer loeschen
   glLoadIdentity ();
   gluLookAt (0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Kamera von vorne

   // Rotierende Platte mit transparenter Textur
   glRotatef(winkel, 0.0f, 1.0f, 0.0f);   
   glEnable(GL_TEXTURE_2D);
   glBegin(GL_QUADS);
	   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	   glTexCoord2f(0.0f, 0.0f);   glVertex3f(-1.0f, -1.0f, 0.0f);
	   glTexCoord2f(1.0f, 0.0f);   glVertex3f(1.0f, -1.0f, 0.0f);
	   glTexCoord2f(1.0f, 1.0f);   glVertex3f(1.0f, 1.0f, 0.0f);
	   glTexCoord2f(0.0f, 1.0f);   glVertex3f(-1.0f, 1.0f, 0.0f);
   glEnd();
   glDisable(GL_TEXTURE_2D);

   glutSwapBuffers();   
}

void Reshape(int width,int height)
{
   // Hier: Reaktionen auf eine Veraenderung der Groesse des Graphikfensters 
   glMatrixMode(GL_PROJECTION); // Matrix fuer Transf. Frustum->Viewport
   glLoadIdentity(); // Projection-Matrix als Einheitsmatrix initialisieren
   glViewport(0, 0, width, height);
   gluPerspective(75.0, 1.0, 1.0, +3.0*extent);
   glMatrixMode(GL_MODELVIEW); // Modellierungs/Viewing-Matrix
}
 
void Animate (int value)    
{
   // Berechnungen, die zu einer Animation der Szene erforderlich sind
   winkel = winkel + 5.0f; 
   if (winkel>360.0f)
       winkel = winkel-360.0f;
   // RenderScene aufrufen
   glutPostRedisplay();
   // Timer wieder registrieren; Animate also nach wait_msec Milli-Sekunden wieder aufrufen
   int wait_msec = 20;
   glutTimerFunc(wait_msec, Animate, ++value);           
}


int main(int argc, char **argv)
{
   printf ("Testprogramm: transparente Textur einlesen und ausgeben. \n");
   printf ("(Falls die Platte weiss angezeigt wird, wurde das Bild nicht gefunden.)\n\n");
   glutInit ( &argc, argv );
   glutInitDisplayMode ( GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH );
   glutInitWindowSize ( 600,600 );
   glutCreateWindow ("*** Platte mit transparenter Textur ***");
   glutDisplayFunc ( RenderScene );
   glutReshapeFunc ( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc(10,Animate,0);                 
   Init();
   glutMainLoop ();
   return 0;
}