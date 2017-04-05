#include <windows.h>
#include <windowsx.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>

//Creamos una clase que administre por separado al OpenGL
//como fuera del lazo de windows
#include "Graphics.h"
#define Timer1 100
#pragma comment(lib, "glu32.lib")

LRESULT CALLBACK WindowProc(HWND hWnd, 	UINT message, WPARAM wParam, LPARAM lParam);
void SetUpPixelFormat(HDC hDC);

//debemos declarar una variable global que maneje el acceso al dispositivo grafico
HDC gHDC;

//Declaramos al puntero del objeto 
Graph *OGLobj;

bool renderiza=false;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPSTR lpCmdLine, int nCmdShow){
	HWND hWnd;
	WNDCLASSEX wc;    
	ZeroMemory(&wc, sizeof(WNDCLASSEX));    
	wc.cbSize = sizeof(WNDCLASSEX);  
	wc.style = CS_HREDRAW | CS_VREDRAW; 	
	wc.lpfnWndProc = WindowProc; 	
	wc.hInstance = hInstance;   	
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 	
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;	
	wc.lpszClassName = L"Proyecto Final"; 	
	RegisterClassEx(&wc);     
	RECT wr = {0, 0, 800, 600};    
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindowEx(NULL,
		L"Proyecto Final",
		L"Proyecto Final Progra II",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hWnd, nCmdShow);
	//Creamos al objeto y se lo pasamos al puntero
	OGLobj = new Graph(hWnd);
	// inicializamos el objeto Timer a la cantidad de milisegundos deseada
	SetTimer(hWnd,Timer1,10,NULL);
	MSG msg = {0};      
	while(TRUE){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg); 		   
			DispatchMessage(&msg);
			if(msg.message == WM_QUIT)              
			break;
		}
		else{
			//en este lazo estara ejecutandose el render
			//"renderiza" controla si se hace el render o no a través del timer Timer1
			if (renderiza){
				OGLobj->Render(gHDC);   
				renderiza=false;
			}
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	static HGLRC hRC;
	static HDC hDC;
	int ancho, alto;
	switch(message){
		//este case se ejecuta cuando se crea la ventana, aqui asociamos al 
		//opengl con el dispositivo
	case WM_CREATE:
		hDC=GetDC(hWnd);
		gHDC=hDC;
		SetUpPixelFormat(hDC);
		hRC=wglCreateContext(hDC);
		wglMakeCurrent(hDC,hRC);
		break;
	case WM_TIMER:
		//OGLobj->angulo+=1.5;
	case WM_KEYDOWN:
		switch (wParam){
		case 'R':{
					 if (OGLobj-> rotar<359){
						 OGLobj->rotar++;
					 }
					 else
						 OGLobj->rotar = 0;
					 break;
		}
		case 'E':{
			
					 if (OGLobj->escala<10){
						// PlaySound(TEXT("FTLCover.wav"), NULL, SND_FILENAME);
						 OGLobj->escala++;
					 }
					 else
						 OGLobj->escala= 0;
					 break;
		}
		case 'W':{
					 if (OGLobj->poscy <600)
					 {
						 OGLobj->poscy++;
						 //OGLobj->angulo++;
					 }
					 else
						 OGLobj->poscy = 0;
					 break;
		}
		case 'S':{
					 if (OGLobj->poscy < 600)
					 {
						 OGLobj->poscy--;
						 //OGLobj->angulo--;
					 }
					 else
						 OGLobj->poscy = 0;
					 break;
		}
		case 'D':{
					 if (OGLobj->poscz < 600){
						 OGLobj->poscz++;
						 //OGLobj->angulo--;
					 }
					 else
						 OGLobj->poscz = 0;
					 break;
		}
		case 'A':{
					 if (OGLobj->poscz < 600){
						 OGLobj->poscz--;
						 //OGLobj->angulo++;
					 }
					 else
						 OGLobj->poscz = 0;
					 break;
		}
		case 'I':{
					 if (OGLobj->dircy <600){
						 OGLobj->dircy++;
					 }
					 else
						 OGLobj->dircy = 0;
					 break;
		}
		case 'K':{
					 if (OGLobj->dircy <600){
						 OGLobj->dircy--;
					 }
					 else
						 OGLobj->dircy = 0;
					 break;
		}
		case 'L':{
					 if (OGLobj->dircx <600){
						 OGLobj->dircx--;
					 }
					 else
						 OGLobj->dircx = 0;
					 break;
		}
		case 'J':{
					 if (OGLobj->dircx <600){
						 OGLobj->dircx++;
					 }
					 else
						 OGLobj->dircx = 0;
					 break;
		}
		case 'F':{
					 if (OGLobj->fluz<100){
						 OGLobj->fluz++;
					 }
					 else
						 OGLobj->fluz = 0;
					 break;
		}case 'G':{
					 if (OGLobj->xluz <100){
						 OGLobj->xluz++;
					 }
					 else
						 OGLobj->xluz = 0;
					 break;
		}case 'V':{
			if (OGLobj->y <100){
				OGLobj->yluz++;
			}
			else
				OGLobj->yluz = 0;
			break;
		}
		case 'B':{
			if (OGLobj->zluz <100){
				OGLobj->zluz++;
			}
			else
				OGLobj->zluz = 0;
			break;
		}
		}
		if (OGLobj->estado == 1)
			OGLobj->angulo -= 0.5f;
		else
			OGLobj->angulo += 0.5f;
		if (OGLobj->angulo >= 15.0f)
			OGLobj->estado = 1;
		else if (OGLobj->angulo <= -15.0f)
			OGLobj->estado = 0;
		OGLobj->paso += 0.05;
		if (OGLobj->cRed<=1)
			OGLobj->cRed += 0.01;
		else
			OGLobj->cRed = 0;
		// para el movimiento de la tetera
		if (OGLobj->paso2<20)
			OGLobj->paso2 += 0.1;
		else
			OGLobj->paso2 = 0.1;
		// para el movimien
		renderiza=true;
		break;
case WM_DESTROY:{
					KillTimer(hWnd,Timer1);
					//en caso de salir desocupar los recursos del opengl
					wglMakeCurrent(hDC,NULL);
					wglDeleteContext(hRC);
					PostQuitMessage(0);  
					return 0;
}
		break;   
case WM_SIZE:{
				 //esta opcion del switch se ejecuta una sola vez al arrancar y si se
				 //afecta el tamaño de la misma se dispara de nuevo
				 alto = HIWORD(lParam);
				 ancho= LOWORD(lParam);
				 if (alto==0)
					 alto=1;
				 glViewport(0,0,ancho,alto);
				 glMatrixMode(GL_PROJECTION);
				 glLoadIdentity();
				 gluPerspective(45.0f, (GLfloat)ancho/(GLfloat)alto,1.0f,1000.0f);
				 glMatrixMode(GL_MODELVIEW);
				 glLoadIdentity();
}
		break;
}
return DefWindowProc (hWnd, message, wParam, lParam);
}
void SetUpPixelFormat(HDC hDC){
	int PixForm;
	static PIXELFORMATDESCRIPTOR pixfordes = {
		sizeof(PIXELFORMATDESCRIPTOR), //tamaño de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tamaño del color en 32 bits
		0,0,0,0,0,0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0,0,0,0, //no hay bits de acumulacion
		16, //tamaño del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0,0,0 //mascaras de capas ignoradas
	};
	PixForm=ChoosePixelFormat(hDC, &pixfordes);
	SetPixelFormat(hDC, PixForm, &pixfordes);
}