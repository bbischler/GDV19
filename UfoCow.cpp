// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014
#define _USE_MATH_DEFINES
#define NUM_TEXTURES 6 

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <soil.h>
#include "math.h"

#include "Wuerfel.h"
float angle = 0.0;
float bewegunHoch = 0.3;
float kameraY = -0.001;
float kameraZ = 0;
float warpCounter = 1;
bool warp = false;
bool dropTheCow = false;
bool connected = false;
bool kameraYgesperrt = false;
float EIMER_PosX = 0.0;
float EIMER_PosZ = 0.0;
float EIMER_PosY = -2.0;
float fRotation = 315.0;
float ufoblink = 0.0;
char eimerDir = 'r';
char eimerZDir = 'u';
bool contactCowUFO = false;
bool contactCowEimer = false;
float COW_PosX  = -2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4)));

float COW_PosY = -0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5)));
float COW_PosZ = 1.0;
float UFO_PosX = 0.0;
float UFO_PosY = 0.5;
float UFO_PosZ = 0.0;
float UFO_Speed_X = 0.05;
float UFO_Speed_Y = 0.1;
float UFO_Speed_Z = 0.05;

GLenum filterMode = GL_LINEAR;   //Init-Wert fuer die Texturfilterung
GLuint texNum = 0;               //Startwert fuer "level of detail"
GLuint texture[NUM_TEXTURES];    //Textur-Pointer-Array

static void LoadGLTextures() {
	texture[0] = SOIL_load_OGL_texture("moon.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	printf(SOIL_last_result());


	texture[1] = SOIL_load_OGL_texture("universe.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	printf(SOIL_last_result());
	

	texture[2] = SOIL_load_OGL_texture("universe.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	printf(SOIL_last_result());


}

void Init()
{
	LoadGLTextures();
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen
	// Hier: Code, der einmalig zu Beginn ausgefuehrt wird
	glClearColor(1.0, 1.0, 0.0, 1.0);  // Hintergrund in Weiss


	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 1., 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Licht Nr. 0 rechts oben
	glEnable(GL_COLOR_MATERIAL);
	
}


void ufo() {
	glPushMatrix();
	glTranslatef(UFO_PosX, UFO_PosY, UFO_PosZ);

	//Kugel
	glPushMatrix();
	glColor4f(1.0, 1.0, 0.58, 0.7); // Helles Gelb
	glutSolidSphere(0.2, 20, 20);	
	glTranslatef(0., -0.15, 0.);
	glRotatef(-90., 1., 0., 0.);
	glColor4f(1.0-(ufoblink/0.4), 1.0-ufoblink, ufoblink, 1.); // Dunkles Blau-Grau
	glutSolidCone(0.4, 0.25, 20, 20);
	glPopMatrix();

	if (warp || connected) {
		glPushMatrix();
		glTranslatef(0., -0.65, 0.);
		glRotatef(-90., 1., 0., 0.);
		glColor4f(0.84, 0.96, 0.1, warpCounter);
		glutSolidCone(0.2, 0.8, 200, 200);
		glPopMatrix();
	}

	glPopMatrix();

}

void eimer(float fSeitenL) {
	glTranslatef(EIMER_PosX, EIMER_PosY, EIMER_PosZ);
	
	glBegin(GL_POLYGON);   //Vorderseite
	if (contactCowEimer == true) {
		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);	//Farbe
	}
	else {
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);	//Farbe
	}
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rechte Seite
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Rueckseite
	glVertex3f(+fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);   //Linke Seite
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 2.0f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);   //Bodenflaeche
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 2.0f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();
}

void cow() {
	glTranslatef(COW_PosX, COW_PosY, COW_PosZ);
	glScalef(1.3, 1.3, 1.3);					//verzerren

	glPushMatrix();
	//glRotatef(fRotation, 0.0f, 1.0f, 0.0f);
	//Körper
	glPushMatrix();
	glRotatef(-90., 0., 1., 0.);
	if (contactCowUFO == true){
		glColor4f(0.2, 0.7, 0.8, 1.0); // Dunkles Blau-Grau
	} else {
		glColor4f(0.45, 0.14, 1.0, 1.0); // Dunkles Blau-Grau
	}
	glutSolidCylinder(0.05, 0.15, 20, 20);
	glPopMatrix();

	//Schwanz
	glPushMatrix();
	glTranslatef(0., -0., 0.0);
	glRotatef(-90., 0., 1., 0.);
	glRotatef(135., 1., 0., 0.);
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();

	//Beine
	glPushMatrix();
	glTranslatef(0., -0.1, 0.04);
	glRotatef(-90., 1., 0., 0.);
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0., -0.1, -0.04);
	glRotatef(-90., 1., 0., 0.);
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.1, 0.04);
	glRotatef(-90., 1., 0., 0.);
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.1, -0.04);
	glRotatef(-90., 1., 0., 0.);
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();


	
	//Hals
	glPushMatrix();
	glTranslatef(-0.15, 0.05, 0.);
	glRotatef(-90., 1., 0., 0.);
	glRotatef(-45., 0., 1., 0.);
	glutSolidCylinder(0.02, 0.05, 20, 20);
	glPopMatrix();

	//Kopf
	glPushMatrix();
	glTranslatef(-0.18, 0.08, 0.);
	glRotatef(-90., 1., 0., 0.);
	glRotatef(-90., 0., 1., 0.);
	glutSolidCone(0.04, 0.06, 20, 20);
	glPopMatrix();

	//Ohren
	glPushMatrix();
	glTranslatef(-0.19, 0.1, 0.02);
	glRotatef(90., 1., 0., 0.);
	glRotatef(180., 0., 1., 0.);
	glutSolidCone(0.01, 0.06, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.19, 0.1, -0.02);
	glRotatef(90., 1., 0., 0.);
	glRotatef(180., 0., 1., 0.);
	glutSolidCone(0.01, 0.06, 20, 20);
	glPopMatrix();
	glPopMatrix();
}

void moon(){
	glTranslatef(0.8, 0.8, 0.);
	glRotatef(fRotation, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-0.1f, -0.1f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(0.1f, -0.1f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(0.1f, 0.1f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-0.1f, 0.1f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void drawumwelt(GLfloat relativ) {
	glEnable(GL_TEXTURE_2D);              //Textur-Mapping anschalten

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

	glBegin(GL_POLYGON);   //Bodenflaeche
	glColor3f(0.24, 0.24, 0.26);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-relativ / 1.2f, -1.5, -relativ / 1.2f);
	glTexCoord2f(8.0, 0.0);
	glVertex3f(+relativ / 1.2f, -1.5, -relativ / 1.2f);
	glTexCoord2f(8.0, 8.0);
	glVertex3f(+relativ / 1.2f, -1.5, +relativ / 1.2f);
	glTexCoord2f(0.0, 8.0);
	glVertex3f(-relativ / 1.2f, -1.5, +relativ / 1.2f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);   //Rueckseite
	glColor3f(0.24, 0.24, 0.26);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(+relativ / 2.0f, +relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(+relativ / 2.0f, -relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-relativ / 2.0f, -relativ / 2.0f, -relativ / 2.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-relativ / 2.0f, +relativ / 2.0f, -relativ / 2.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);


}

void RenderScene() //Zeichenfunktion
{
	GLfloat relativ = 0.4;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.02, 0.04, 0.11, 1.0); // Hintergrund deep blue

	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
	//gluLookAt(0., 0., 1., 0., 0., 0., 0., 1., 0.);
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Kamera von vorne
	gluLookAt(0.8 * sin(angle / 180 * M_PI), bewegunHoch, 1.0, 0.0, kameraY, kameraZ, 0.0, 1, 0);

	

	glPushMatrix();
	moon();
	glPopMatrix();

	glPushMatrix();
	cow();
	glPopMatrix();

	glPushMatrix();
	ufo();
	glPopMatrix();

	glPushMatrix();
	eimer(0.5);
	glPopMatrix();


	glPushMatrix();
	drawumwelt( 10 );
	glPopMatrix();

	glutSwapBuffers();
}

void collisionDetectionCowUFO() {
	float dx = UFO_PosX - COW_PosX;
	float dy = UFO_PosY-0.5 - COW_PosY;
	float dz = UFO_PosZ - COW_PosZ;

	float distance = sqrt(dx * dx + dy * dy + dz * dz);

	if (distance <= 0.3 && warp && !dropTheCow) {
		contactCowUFO = true;
		connected = true;
		COW_PosX = UFO_PosX;
		COW_PosY = UFO_PosY - 0.6;
		COW_PosZ = UFO_PosZ;
	}
	else {
		contactCowUFO = false;
	}
}


void collisionDetectionCowEimer() {
	float dx = EIMER_PosX - COW_PosX;
	float dy = EIMER_PosY - COW_PosY;
	float dz = EIMER_PosZ - COW_PosZ;

	float distanceEimerCow = sqrt(dx * dx + dy * dy + dz * dz);

	if (distanceEimerCow <= 0.3) {
		contactCowEimer = true;
		COW_PosX = EIMER_PosX;
		COW_PosY = EIMER_PosY;
		COW_PosZ = EIMER_PosZ;
	}
	else {
		contactCowEimer = false;
	}
}

void Reshape(int width, int height)
{
	// Hier finden die Reaktionen auf eine Veränderung der Größe des 
	// Graphikfensters statt

	// Matrix für Transformation: Frustum->viewport
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen
	glLoadIdentity();
	// Viewport definieren
	glViewport(0, 0, width, height);

	// gluPerspective(senkr. Oeffnungsw., Seitenverh., zNear, zFar);
	gluPerspective(90., 1., 0.1, FLT_MAX);   // um den Arm ganz zu sehen Öffnungsweite auf 90°

	// Matrix für Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);
}

void Animate(int value)
{
	glutPostRedisplay();
	int wait_msec = 10;
	glutTimerFunc(wait_msec, Animate, ++value);
	fRotation = fRotation - 1.0; // Rotationswinkel aendern
	if (fRotation <= 0.0) {
		fRotation = fRotation + 360.0;
	}
	//ufo-warp
	if (warp && !connected) {
		warpCounter -= 0.005;
	}

	if (warpCounter <= 0.0 && !connected) {
		warp = !warp;
		warpCounter = 1.0;
	}
	if (connected) {
		warpCounter = 0.7;
	}
	//ufo-blink
	if (ufoblink < 1.0) {
		ufoblink += 0.005;
	}

	if (ufoblink >= 1.0) {
		ufoblink = 0.0;
	}

	//eimerX
	if (eimerDir == 'r') {
		EIMER_PosX += 0.002;
	}
	if (eimerDir == 'l') {
		EIMER_PosX -= 0.002;
	}
	if (EIMER_PosX >= 2.0) {
		eimerDir = 'l';
	}
	if (EIMER_PosX <= -2.0) {
		eimerDir = 'r'; 
	}

	//eimerZ
	if (eimerZDir == 'u') {
		EIMER_PosZ += 0.001;
	}
	if (eimerZDir == 'd') {
		EIMER_PosZ -= 0.001;
	}
	if (EIMER_PosZ >= 0.5) {
		eimerZDir = 'd';
	}
	if (EIMER_PosZ <= -0.5) { 
		eimerZDir = 'u';
	}

	//dropTheCow
	if (dropTheCow) {
		COW_PosY -= 0.02;
	}
	collisionDetectionCowUFO();

	if (dropTheCow) {
	collisionDetectionCowEimer();
	}
} 

void restartGame(){
	 angle = 0.0;
	 bewegunHoch = 0.3;
	 kameraY = -0.001;
	 kameraZ = 0;
	 warpCounter = 1;
	 warp = false;
	 dropTheCow = false;
	 connected = false;
	 EIMER_PosX = 0.0;
	 EIMER_PosZ = 0.0;
	 EIMER_PosY = -2.0;
	 fRotation = 315.0;
	 ufoblink = 0.0;
	 eimerDir = 'r';
	 eimerZDir = 'u';
	 contactCowUFO = false;
	 contactCowEimer = false;
	 COW_PosX = -2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4)));
	 COW_PosY = -0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5)));
	 COW_PosZ = 1.0;
	 UFO_PosX = 0.0;
	 UFO_PosY = 0.5;
	 UFO_PosZ = 0.0;
	 UFO_Speed_X = 0.05;
	 UFO_Speed_Y = 0.1;
	 UFO_Speed_Z = 0.05;
}

void KeyboardFuncKey(int key, int x, int y)
{

	if (key == GLUT_KEY_RIGHT) {
		angle = (angle - 1.0);
	}

	else if (key == GLUT_KEY_LEFT) {
		angle = (angle + 1.0);
	}

	else if (key == GLUT_KEY_UP) {
		if (bewegunHoch < 1.0 && !kameraYgesperrt)
			bewegunHoch = bewegunHoch + 0.2;
	}

	else if (key == GLUT_KEY_DOWN) {
		if (bewegunHoch > 0.4 && !kameraYgesperrt)
			bewegunHoch = bewegunHoch - 0.2;
	}

	else if (key == GLUT_KEY_INSERT) {
		angle = 0;
		bewegunHoch = 0.3;
		kameraZ = 0;
		kameraY = -0.001;
		kameraYgesperrt = false;
	}

	// RenderScene aufrufen.
	glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'a')
		UFO_PosX -= UFO_Speed_X;

	if (key == 'd')
		UFO_PosX += UFO_Speed_X;

	if (key == 'w')
		UFO_PosY += UFO_Speed_Y;

	if (key == 's')
		UFO_PosY -= UFO_Speed_Y;

	if (key == 'q')
		UFO_PosZ -= UFO_Speed_Z;

	if (key == 'e')
		UFO_PosZ += UFO_Speed_Z;

	if (key == ' ') {
		if (!warp) 
			warp = true;
	}
	if (key == 'f') {
		if (connected) {
			dropTheCow = true;
			connected = false;
		}
		else
			dropTheCow = false;
	}
	if (key == 'r') {
		restartGame();
	}


	// RenderScene aufrufen.
	glutPostRedisplay();
}



void ZeigeHilfe() {
	std::cout << "Hilfe zur Bedienung: \n";
	std::cout << "Space: Warp-Power!!!! \n";
	std::cout << "R: Restart Game \n";
	std::cout << "Pfeiltaste Links: Ansicht nach Rechts drehen\n";
	std::cout << "Pfeiltaste Rechts: Ansicht nach Links drehen \n";
	std::cout << "Pfeiltaste Oben: Ansicht nach Oben drehen \n";
	std::cout << "Pfeiltaste Unten: Ansicht nach Unten drehen \n";
	std::cout << "Einfuegen: Ansicht zuruecksetzen.";
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(1000, 600);         // Fenster-Konfiguration
	glutCreateWindow("Bastian Bischler; Marco Hitsch");   // Fenster-Erzeugung
	ZeigeHilfe();

	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardFunc);  // NEU
	glutSpecialFunc(KeyboardFuncKey);

	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}
