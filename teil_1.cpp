// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL

	double i = 0.0;
void Init()
{
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}

bool up = true;
int maxCOlor = 0xffffff;


void setColorStuff(int C) 
{
	int B = C % 256;
	int G = ((C - B) / 256) % 256;
	int R = ((C - B) / 256*256) - G / 256;

	glColor4f((float)R / 256., (float)G / 256., (float)B / 256., 1.);

}


void RenderScene() //Zeichenfunktion
{
	if (i <= 0.)
		up = true;
	if (i >= 1.)
		up = false;

	i = i + (up ? +0.05 : -0.05);
	std::cout << i << std::endl;

	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.7, 0.0, 1.0);

	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

	//glColor4f(1.0, 0.0, 0.0, 0.5); // unten links rot
	//glBegin(GL_POLYGON);
	//for (float ii = 0; ii < 200; ii++)
	//{
	//	float theta = 2.0f * 3.1415926f * float(ii) / float(200);//get the current angle

	//	float x = 0.5 * cosf(theta);//calculate the x component
	//	float y = 0.5 * sinf(theta);//calculate the y component
	//	//glColor4f((ii + 1.) / 200. * i, 0., 1. * i, 1.);

	//	int color = 0 + (maxCOlor / 199) * ii;
	//	setColorStuff(color);


	//	//glColor4f(i, 1.0-i,1.0,1.0);
	//	glVertex3f(x + 0, y + 0, -1.0);//output vertex

	//}
	//glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1.0, 0.0, 0.0, 0.5); // unten links rot
	glVertex3f(-0.5, -0.5, -0.5);
	glColor4f(0.0, 0.0, 1.0, 0.5); // alles andere blau
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();


	glBegin(GL_POLYGON);
	glColor4f(0., 1., 0., 1.);
	glVertex3f(-0.5, -0.5, -1.);
	glVertex3f(0.5, -0.5, -1.);
	glVertex3f(0.5, 0.5, -1.);
	glVertex3f(-0.5, 0.5, -1.);
	glEnd();


	glutSwapBuffers();

	//i += 0.01;
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
	// Frustum definieren (siehe unten)
	glOrtho(-1.0, 1.0, -1.0, 1.0, 0.3, 1.3);
	// Matrix für Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);


}

void Animate(int value)
{
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
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
