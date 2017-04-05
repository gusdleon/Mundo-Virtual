#ifndef _Geom
#define _Geom
#define _USE_MATH_DEFINES
#include <math.h>

//estructura para manejar primitivos con posicion, normal y uv's
struct Vertices{
	float Posx, Posy, Posz;
	float Normx, Normy, Normz;
	float u, v;
};

//En honor a nuestros ancestros llamaremos "Maya" a la malla
//estructura que contiene datos de los vertices y sus indices
struct Maya{
	Vertices *maya;
	unsigned int *indices;
};




class Primitivos{
public:
	Primitivos() //mis pensamientos!
	{
	}

	//generamos los vertices a traves de coordenadas esfericas
	//conocimiento adquirido en la materia de Fund de las Graficas Computacionales
	Maya Esfera(int stacks, int slices, float radio, float inicio, float final)
	{
		//Cargamos la estructura con los espacios de memoria necesarios
		Vertices *verticesxyzSD=new Vertices[stacks*slices*3];
		unsigned int *indices=new unsigned int[stacks*slices*6];
		//generamos un objeto para poder transportar los punteros
		Maya salida;
		//a darle que es mole de olla!
		for(int i=0;i<slices;i++)
		{
			for(int j=0;j<stacks;j++)
			{
				int indice = ( i * stacks + j );
				verticesxyzSD[indice].Posx=radio*cos(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0)*
					cos(2.0*M_PI*(double)i/(slices-1));
				verticesxyzSD[indice].Posy=radio*sin(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0);
				verticesxyzSD[indice].Posz=radio*cos(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0)*
					sin(2.0*M_PI*(double)i/(slices-1));

				verticesxyzSD[indice].Normx=cos(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0)*
					cos(2.0*M_PI*(double)i/(slices-1));
				verticesxyzSD[indice].Normy=sin(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0);
				verticesxyzSD[indice].Normz=cos(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0)*
					sin(2.0*M_PI*(double)i/(slices-1));

				verticesxyzSD[indice].u=(float)1*(1-(float)i/(stacks-1));
				verticesxyzSD[indice].v=(float)1*(1-(float)j/(slices-1));
			}
		}

		//ahora la parte mas importante de crear vertices es el algoritmo para unirlos, en este caso sustituiremos
		//a un algoritmo con un un grupo de indices
		int indice=0;
		for(int i=0;i<slices-1;i++)
		{
			for(int j=0;j<stacks-1;j++)
			{				
				indices[indice++]=i * stacks + j;
				indices[indice++]=(i+1) * stacks + j+1;
				indices[indice++]=i * stacks + j+1;

				indices[indice++]=i * stacks + j;
				indices[indice++]=(i+1) * stacks + j;
				indices[indice++]=(i+1) * stacks + j+1;
			}
		}

		//una vez generados los damos a conocer a traves del objeto "salida"
		salida.maya=verticesxyzSD;
		salida.indices=indices;

		return salida;
	}
};
#endif