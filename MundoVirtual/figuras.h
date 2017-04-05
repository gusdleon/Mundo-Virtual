#include <windows.h>
#include <windowsx.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include "glext.h"
void dibujarCono(float xPos, float yPos, float zPos){
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	glRotatef(-90,1,0,0);
	//glScalef(1.0f, 2.0f, 1.0f);  // La cabeza es un cubo de 2x2x2 
	glColor3f(0.3f, 0.8f, 1.0f); 				
	glutSolidCone(1,5,32,32);
	glPopMatrix();
}