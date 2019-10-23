// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //l�dt alles f�r OpenGL
#include "Wuerfel.h" 

	double i = 0.0;
void Init()
{
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgef�hrt werden m�ssen
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

}



void RenderScene() //Zeichenfunktion
{
	

	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.7, 0.0, 1.0);

	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

	gluLookAt(1., 0., 0., 0., -1, 0., 0., 1., 0.); //vorne


	//glTranslatef(0., 0., -1.);
	Wuerfel(0.4);



	glutSwapBuffers();

}

void Reshape(int width, int height)
{
	// Hier finden die Reaktionen auf eine Ver�nderung der Gr��e des 
	// Graphikfensters statt

	// Matrix f�r Transformation: Frustum->viewport
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen
	glLoadIdentity();
	// Viewport definieren
	glViewport(0, 0, width, height);
	// Frustum definieren (siehe unten)
	glOrtho(-1., 1., -1, 1.0, 0.0, 1.0);
	// Matrix f�r Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);
}

void Animate(int value)
{
	// Hier werden Berechnungen durchgef�hrt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess l�uft im Hintergrund und wird alle 
	// 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
	// inkrementiert und dem Callback wieder uebergeben. 
	std::cout << "value=" << value << std::endl;
	// RenderScene aufrufen
	glutPostRedisplay();
	// Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
	int wait_msec = 10;
	glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(600, 600);         // Fenster-Konfiguration
	glutCreateWindow("Bastian Bischler; Marco Hitsch");   // Fenster-Erzeugung
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}
