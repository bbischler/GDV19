// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <soil.h>
#include "Wuerfel.h"

float fRotation = 315.0; // globale Variable :-( 

float UFO_PosX = 0.0;
float UFO_PosY = 0.5;
float UFO_PosZ = 0.0;
float UFO_Speed_X = 0.05;
float UFO_Speed_Y = 0.1;
float UFO_Speed_Z = 0.05;
bool cowHeadMotion = true;
float cowHeadRotation = 0.0;

void Init()
{
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen
	// Hier: Code, der einmalig zu Beginn ausgefuehrt wird
	glClearColor(1.0, 1.0, 0.0, 1.0);  // Hintergrund in Weiss
	// Textur einlesen usw.

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 0., 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Licht Nr. 0 rechts oben
	glEnable(GL_COLOR_MATERIAL);
	
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

	// RenderScene aufrufen.
	glutPostRedisplay();
}

void ufo() {

	glTranslatef(UFO_PosX, UFO_PosY, UFO_PosZ);

	//Kugel
	glPushMatrix();
	glColor4f(1.0, 1.0, 0.58, 0.3); // Helles Gelb
	glutSolidSphere(0.2, 20, 20);	
	glTranslatef(0., -0.15, 0.);
	glRotatef(-90., 1., 0., 0.);
	glColor4f(0.23, 0.23, 0.35, 1.0); // Dunkles Blau-Grau
	glutSolidCone(0.4, 0.25, 20, 20);
	glPopMatrix();

	//Kegel
	glPushMatrix();
	glTranslatef(0., -0.65, 0.);
	glRotatef(-90., 1., 0., 0.);
	glColor4f(0.8, 1.0, 0.7, 0.5); // Dunkles Blau-Grau
	glutSolidCone(0.2, 0.5, 200, 200);
	glPopMatrix();
}

void cow() {
	glTranslatef(0., -0.5, 0.);
	glPushMatrix();

	glRotatef(fRotation, 0.0f, 1.0f, 0.0f);
	//Körper
	glPushMatrix();
	glRotatef(-90., 0., 1., 0.);
	glColor4f(0.45, 0.14, 1.0, 1.0); // Dunkles Blau-Grau
	glutSolidCylinder(0.05, 0.15, 20, 20);
	glPopMatrix();

	//Schwanz
	glPushMatrix();
	glTranslatef(0., -0., 0.0);
	glRotatef(-90., 0., 1., 0.);
	glRotatef(135., 1., 0., 0.);
	glColor4f(0.45, 0.34, 0.6, 1.); // Dunkles Blau-Grau
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();

	//Beine
	glPushMatrix();
	glTranslatef(0., -0.1, 0.04);
	glRotatef(-90., 1., 0., 0.);
	glColor4f(0.45, 0.34, 0.6, 1.); // Dunkles Blau-Grau
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0., -0.1, -0.04);
	glRotatef(-90., 1., 0., 0.);
	glColor4f(0.45, 0.34, 0.6, 1.); // Dunkles Blau-Grau
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.1, 0.04);
	glRotatef(-90., 1., 0., 0.);
	glColor4f(0.45, 0.34, 0.6, 1.); // Dunkles Blau-Grau
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.1, -0.04);
	glRotatef(-90., 1., 0., 0.);
	glColor4f(0.45, 0.34, 0.6, 1.); // Dunkles Blau-Grau
	glutSolidCylinder(0.01, 0.1, 20, 20);
	glPopMatrix();


	glPushMatrix(); // Um Kopf und Hals zu bewegen
	if (cowHeadMotion == true) {
		glRotatef(cowHeadRotation, 1., 0., 0.);
	}
	//Hals
	glPushMatrix();
	glTranslatef(-0.15, 0.05, 0.);
	glRotatef(-90., 1., 0., 0.);
	glRotatef(-45., 0., 1., 0.);
	glColor4f(0.45, 0.34, 0.6, 1.); // Dunkles Blau-Grau
	glutSolidCylinder(0.02, 0.05, 20, 20);
	glPopMatrix();

	//Kopf
	glPushMatrix();
	glTranslatef(-0.18, 0.08, 0.);
	glRotatef(-90., 1., 0., 0.);
	glRotatef(-90., 0., 1., 0.);
	glColor4f(0.45, 0.34, 0.6, 1.); // Dunkles Blau-Grau
	glutSolidCone(0.04, 0.06, 20, 20);
	glPopMatrix();

	//Ohren
	glPushMatrix();
	glTranslatef(-0.19, 0.1, 0.02);
	glRotatef(90., 1., 0., 0.);
	glRotatef(180., 0., 1., 0.);
	glColor4f(0.25, 0.14, 0.3, 1.); // Dunkles Blau-Grau
	glutSolidCone(0.01, 0.06, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.19, 0.1, -0.02);
	glRotatef(90., 1., 0., 0.);
	glRotatef(180., 0., 1., 0.);
	glColor4f(0.25, 0.14, 0.3, 1.); // Dunkles Blau-Grau
	glutSolidCone(0.01, 0.06, 20, 20);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}




void RenderScene() //Zeichenfunktion
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.5, 1.0);

	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
	gluLookAt(0., 0., 1., 0., 0., 0., 0., 1., 0.);

	cow();
	ufo();
	
	glutSwapBuffers();
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
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
	// 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
	// inkrementiert und dem Callback wieder uebergeben. 

	// RenderScene aufrufen
	glutPostRedisplay();
	// Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
	int wait_msec = 10;
	glutTimerFunc(wait_msec, Animate, ++value);
	fRotation = fRotation - 1.0; // Rotationswinkel aendern
	if (fRotation <= 0.0) {
		fRotation = fRotation + 360.0;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(1000, 600);         // Fenster-Konfiguration
	glutCreateWindow("Bastian Bischler; Marco Hitsch");   // Fenster-Erzeugung
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardFunc);  // NEU
	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}
