#ifndef _GRR
#define _GRR
#include <windows.h>
#include <windowsx.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include "glext.h"
#include "figuras.h"

class Camara{
public:
	float poscx, poscy, poscz, dircx, dircy, dircz, rotar, escala, fluz, xluz, yluz, zluz;
	Camara(){
	}
	void CamaraUpdate(){
		gluLookAt(poscx, poscy, poscz,
			dircx, dircy, dircz,
			0, 1, 0);
	}
};
class Graph: public Camara{
public:	
	//float angulo;
	GLfloat angulo, paso, paso2;
	GLfloat x, y, z, cRed, cGreen, cBlue;
	GLint estado;
	Graph(HWND hWnd){
		//experimenten cambiandole de valores a la camara
		poscx = 25;
		poscy = 20;
		poscz = -40;
		dircx = 0;
		dircy = 0;
		dircz = 0;
		escala = 1;
		angulo = 0;
		rotar = 0;
		estado = 1;
		angulo = 0.0f;
		paso = 0;
		paso2 = 0;
		fluz = 20;
		xluz = 60;
		yluz = 10;
		zluz = 0;
		x = 0; y= 0; z=0; cRed=0; cGreen=0; cBlue=0;
		glShadeModel(GL_SMOOTH);
		//habilitamos el control de profundidad en el render
		glEnable(GL_DEPTH_TEST);
		//habilitamos la iluminacion
		glEnable(GL_LIGHTING);
		// habilitamos la luz 0 o primer luz
		glEnable(GL_LIGHT0);
		//habilitamos la forma de reflejar la luz
		glEnable(GL_COLOR_MATERIAL);
	}
	void dibujarCabeza(float xPos, float yPos, float zPos) {
		glPushMatrix();
		glPushMatrix();
		dibujarCono(xPos, yPos+1.0, zPos);
		glPopMatrix();
		glTranslatef(xPos, yPos, zPos);
		glScalef(2.0f, 2.0f, 2.0f);  // La cabeza es un cubo de 2x2x2 
		glColor3f(1.0f, 1.0f, 1.0f); // Color blanco				
		glutSolidSphere(1, 40, 10);
		glPopMatrix();
	}
	void dibujarTorso(float xPos, float yPos, float zPos) {
		glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glScalef(3.0f, 5.0f, 2.0f);  // El cuerpo es un cubo de 3x5x2
		glColor3f(0.0f, 0.0f, 1.0f); // Color azul
		glutSolidCube(1);
		glPopMatrix();
	}
	void dibujarBrazo(float xPos, float yPos, float zPos, float angulo) {
		glPushMatrix();
		// Este segmento de código es el que provoca que nuestro robot
		// tenga el efecto de que esta BRACEANDO.
		// Chequen esta parte por favor y busquen entenderla, 
		// ya que aquí es donde uno de los trucos mas importantes de este ejemplo.
		glTranslatef(0.0f, 4.0f, 0.0f);
		glRotatef(angulo, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -4.0f, 0.0f);
		//
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 4.0f, 1.0f);				// El brazo es un cubo de 1x4x1
		glColor3f(1, 0.5, 0);			// Color rojo
		glutSolidSphere(0.5, 40, 10);
		glPopMatrix();
	}
	void dibujarPierna(float xPos, float yPos, float zPos, float angulo) {
		glPushMatrix();
		// Este segmento de código es el que provoca que nuestro robot
		// tenga el efecto de que esta CAMINANDO.
		// Chequen como también estamos provocando que el pie se mueva
		// junto con la pierna.
		glTranslatef(0.0f, 0.5f, 0.0f);
		glRotatef(angulo, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.5f, 0.0f);
		//
		glTranslatef(xPos, yPos, zPos);
		dibujarPie(0.0f, -2.8f, 1.0f);			// Mandamos llamar la función que dibuja el pie, 
		// tomando como eje la ubicación de la pierna
		glScalef(1.0f, 5.0f, 1.0f);				// La pierna es un cubo de 1x5x1
		glColor3f(1.0f, 1.0f, 0.0f);			// Color amarillo
		glutSolidSphere(0.5, 40, 10);
		glPopMatrix();
	}
	void dibujarPie(float xPos, float yPos, float zPos) {
		glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 0.5f, 3.0f);			// El pie es un cubo de 1x.5x3
		glColor3f(1.0f, 1.0f, 1.0f);		// Color blanco
		glutSolidCube(1.0f);
		glPopMatrix();
	}
	// Esta es la función principal de nuestro personaje, es la que vamos a mandar llamar
	// cada vez que queramos dibujar un robot en pantalla.
	// Dentro nos posicionamos en el origen, para que apartir de ahí, dibujar cada una de las 
	// partes que conforman el robot y sea más facil para nosotros ubicarnos.
	void dibujarRobot() {
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		//glRotatef(90,0,1,0);
		dibujarCabeza(0.0f, 3.5f, 0.0f);
		dibujarTorso(0.0f, 0.0f, 0.0f);
		dibujarBrazo(2.0f, 0.0f, 0.0f, angulo);
		dibujarPierna(1.0f, -5.2f, 0.0f, -1.0f * angulo);
		dibujarBrazo(-2.0f, 0.0f, 0.0f, -1.0f * angulo);
		dibujarPierna(-1.0f, -5.2f, 0.0f, angulo);
		glPopMatrix();
	}
	//el metodo render toma el dispositivo sobre el cual va a dibujar
	//y hace su tarea ya conocida
	void Render(HDC hDC){
		//borramos el buffer de color y el z para el control de profundidad a la 
		//hora del render a nivel pixel.
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.5f, 0.0f, 1.0f); // se establece el color de fondo
		GLfloat LightAmb2[] = { 0.0, 0.0,0.0, 0.0 };
		GLfloat LightPos[] = { fluz, xluz, yluz, zluz };
		//GLfloat LightPos[] = { 20.0, 60.0, 10.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb2);
		glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
		//esta instruccion  limpia la matriz que acumula las transformaciones hechas
		//que implican movimiento y/o deformaciones.
		glLoadIdentity();
		//poscx=x; poscy=y; poscz=z;
		CamaraUpdate();
		//----------------------------------------------------------------------//
		glPushMatrix();
		glTranslatef(paso2,paso2,-paso2);
		glColor3f(1, 0, 0);
		glutSolidSphere(4, 100, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 15, 0);
		glRotatef(rotar*5, 0, 1, 0);
		glColor3f(cRed, 0, 0);
		glutSolidTeapot(5);
		glPopMatrix();
		// Dibujamos el piso.
		glColor3f(0, 0.5, 0);
		glBegin(GL_QUADS);
		glVertex3f(-100, -10, 100);
		glVertex3f(100, -10, 100);
		glVertex3f(100, -10, -100);
		glVertex3f(-100, -10, -100);
		glEnd();
		// Posicionamos un robot en x = 20 y utilizando la variable "paso" vamos decrementando
		// la traslación para dar el efecto de que nuestro robot esta caminando hacia la izquierda
		glPushMatrix();
		glTranslatef(-20 + paso, -1, -20);
		glRotatef(paso, paso, paso, paso);
		dibujarRobot(); // robot 5
		glPopMatrix();
		//primera pata
		glPushMatrix();
		glTranslatef(-9, 0, -9);
		glScalef(1.0, 10.0, 1.0);
		glColor3f(1, 0.5, 0);
		glutSolidCube(2);
		glPopMatrix();
		//segunda pata
		glPushMatrix();
		glTranslatef(-9, 0, 9);
		glScalef(1.0, 10.0, 1.0);
		glColor3f(1, 0.5, 0);
		glutSolidCube(2);
		glPopMatrix();
		//tercera pata
		glPushMatrix();
		glTranslatef(9, escala-10, -9);
		glScalef(1.0, escala, 1.0);
		glColor3f(1, 0.5, 0);
		glutSolidCube(2);
		glPopMatrix();
		//cuarta pata
		glPushMatrix();
		glTranslatef(9, 0, 9);
		glScalef(1.0, 10, 1.0);
		glColor3f(1, 0.5, 0);
		glutSolidCube(2);
		glPopMatrix();
		//plano de la mesa
		glPushMatrix();
		glTranslatef(0, 10, 0);
		glScalef(10, 1, 10.0);
		glColor3f(1, 0.5, 0);
		glutSolidCube(2);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(paso2, 10, 10);
		glColor3f(0, 0, 1);
		glutSolidCube(3);
		glPopMatrix();
		//----------------------------------------------------------------------//
		SwapBuffers(hDC);
	}
};
#endif 