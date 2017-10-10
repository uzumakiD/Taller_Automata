#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Pila.h"
#include <string>
#define T 11
#define COMODIN $
#define BRIGHT 1
#define GREEN 32
#define BLUE 34
#define BG_BLACK 40
using namespace std;
class Arco;
class Nodo {
	public:
	    char estado;
	int estadoAceptado;
	Nodo *siguiente;
	Arco *adyunto;
	friend class Grafo;
}
;
class Arco {
	public:
		char datoLeer, sacarPila1, apilar1, apilar2;
	Nodo *destino;
	Arco *siguiente;
	friend class Grafo;
}
;
class Grafo {
	Nodo *h;
	public:
	        Nodo *crearNodo(char estadoI, int estadoAceptadoI);
	Arco *crearArco(char datoLeerI, char  sacarPila1I,char apilar1I, char apilar2I);
	void insertarNodo(Nodo **cabeza, char estadoI, int estadoAceptadoI);
	Nodo *ultimoNodo(Nodo *cabeza);
	Nodo *buscarNodo(Nodo *cabeza, char estadoI);
	void insertarArco(Nodo **cabeza,char datoLeerI,char  sacarPila1I, char apilar1I,char apilar2I, char y, char z);
	Arco *ultimoArco(Arco *arista);
	Arco *buscaArco(Arco *arista);
}
;
Nodo* Grafo :: crearNodo(char estadoI, int estadoAceptadoI) {
	Nodo *p;
	p = (Nodo*)malloc(sizeof(Nodo));
	if(p != NULL) {
		p -> estado = estadoI;
		p ->estadoAceptado = estadoAceptadoI;
		p -> siguiente = NULL;
		p -> adyunto = NULL;
	} else {
		printf("No se pudo reservar memoria\n");
	}
	return p;
}
Arco* Grafo :: crearArco(char datoLeerI, char  sacarPila1I,char apilar1I, char apilar2I) {
	Arco* p;
	p = (Arco*)malloc(sizeof(Arco));
	if(p != NULL) {
		p ->datoLeer = datoLeerI;
		p ->sacarPila1 = sacarPila1I;
		p ->apilar1 = apilar1I;
		p ->apilar2 = apilar2I;
		p -> siguiente = NULL;
		p -> destino = NULL;
	} else {
		printf("No se pudo reservar memoria\n");
	}
	return p;
}
void  Grafo :: insertarNodo(Nodo **cabeza, char estadoI, int estadoAceptadoI) {
	Nodo *p, *i;
	p = crearNodo(estadoI, estadoAceptadoI);
	if(*cabeza == NULL) {
		*cabeza = p;
	} else {
		i = ultimoNodo(*cabeza);
		i -> siguiente = p;
	}
}
Nodo* Grafo ::  ultimoNodo(Nodo *cabeza) {
	Nodo *u;
	if(cabeza -> siguiente != NULL) {
		u = ultimoNodo(cabeza -> siguiente);
	} else {
		u = cabeza;
	}
	return u;
}
Nodo* Grafo :: buscarNodo(Nodo *cabeza, char estadoI) {
	Nodo *b;
	if(cabeza == NULL) {
		b = NULL;
	} else {
		if(cabeza ->estado == estadoI) {
			b = cabeza;
		} else {
			b = buscarNodo(cabeza -> siguiente, estadoI);
		}
	}
	return b;
}
void  Grafo :: insertarArco(Nodo **cabeza,char datoLeerI,char  sacarPila1I, char apilar1I,char apilar2I, char y, char z) {
	Nodo *a, *b;
	Arco *d, *j;
	a = buscarNodo(*cabeza, y);
	b = buscarNodo(*cabeza, z);
	if(a != NULL && b != NULL) {
		d = crearArco(datoLeerI, sacarPila1I, apilar1I, apilar2I);
		if(a -> adyunto == NULL) {
			a -> adyunto = d;
			d -> destino = b;
		} else {
			j = ultimoArco(a -> adyunto);
			j -> siguiente = d;
			d -> destino = b;
		}
	}
}
Arco* Grafo :: ultimoArco(Arco *arista) {
	Arco *u;
	if(arista -> siguiente != NULL) {
		u = ultimoArco(arista -> siguiente);
	} else {
		u = arista;
	}
	return u;
}
Arco* Grafo :: buscaArco(Arco *arista) {
	Arco *b;
	if(arista != NULL) {
		b= arista;
		buscaArco(arista -> siguiente);
		return b;
	} else {
		return b=NULL;
	}
}

class Automata : public Grafo {
	Grafo grafo;
	char estado;
	public:
            Pila pilaSistema;
	        Pila pilaPalabra;
	void leerPalabra(Nodo *cabeza, string PalabraI);
	void desapilarPalabra(Pila pilaPalabra);
	void desapilarSistema(Pila pilaSistema);
	void apilar(Pila pilaSistema, char apilaI);
	void automta(Arco *arista, Pila pilaPalabra,Pila pilaSistema);
	void validar(Nodo *cabeza, Pila pilaPalabraI);
	void moverAutomata(Nodo *cabeza, Arco *arista, Pila pilaPalabraI);
}
;
void  Automata :: leerPalabra(Nodo *cabeza, string PalabraI) {
	for (int i=0; i<PalabraI.size(); i++) {
		pilaPalabra.entrarDato(PalabraI[i]);
	}
	pilaPalabra.mostrarDatos();
	 pilaSistema.entrarDato('#');
	moverAutomata(cabeza, cabeza->adyunto, pilaPalabra);
}
void Automata :: desapilarPalabra(Pila pilaPalabraI) {
	pilaPalabraI.sacarDato();
	pilaPalabra = pilaPalabraI;
}
void Automata :: desapilarSistema(Pila pilaSistemaI) {
	pilaSistemaI.sacarDato();
	pilaSistema=pilaSistemaI;
}
void Automata :: apilar(Pila pilaSistema, char apilaI) {
	pilaSistema.entrarDato(apilaI);
}
void Automata :: automta(Arco *arista, Pila pilaPalabra,Pila pilaSistema) {
	if(arista->datoLeer=='$') {
		if(arista->sacarPila1!='$') {
			desapilarSistema(pilaSistema);
		} else if (arista->apilar1!='$') {
			apilar(pilaSistema,(arista->apilar1));
		} else if(arista->apilar2!='$') {
			apilar(pilaSistema,(arista->apilar2));
		}
	} else(arista->datoLeer!='$'); {
		desapilarPalabra(pilaPalabra);
		cout << "-------------------";
		if(arista->sacarPila1!='$') {
			desapilarSistema(pilaSistema);
		} else if (arista->apilar1!='$') {
			apilar(pilaSistema,(arista->apilar1));
		} else if(arista->apilar2!='$') {
			apilar(pilaSistema,(arista->apilar2));
		}
	}
	return;
}
void Automata :: validar(Nodo *cabeza, Pila pilaPalabraI) {
	if (cabeza->estadoAceptado==2) {
		if(pilaPalabraI.cuantosDatos()==0) {
			cout<<"la palabra es valida";
		} else {
			cout<<"la palabra esta en nodo de aceptacion pero no es valida";
			pilaPalabra.mostrarDatos();
		}
	} else if(cabeza->estadoAceptado==1) {
		cout<<"palabra no valida";
	}
}
void Automata :: moverAutomata(Nodo *cabeza, Arco *arista, Pila pilaPalabraI) {
	Nodo *b;
	if(cabeza == NULL) {
		printf("no hay automata");
	} else {
        if(arista!=NULL) {
			if((arista->datoLeer==pilaPalabraI.mostrarTope()) and (arista->sacarPila1==pilaSistema.mostrarTope())) {
				 cout <<"++++++++++";
				estado= cabeza->estado;
				automta(arista, pilaPalabraI, pilaSistema);
				b = arista->destino;
                moverAutomata(b, b->adyunto, pilaPalabraI);
			}
		}if(arista->siguiente==NULL||pilaPalabra.cuantosDatos()==1) {
			cout <<pilaPalabraI.mostrarTope();
			validar(cabeza, pilaPalabra);
			return;
		} else {
			moverAutomata(cabeza, arista->siguiente, pilaPalabraI);
		}
	}
}
int main() {
	Nodo *lista = NULL;
	Grafo grafo;
	Pila pila;
	Automata automata;
	char estadoI, datoLeerI, sacarPila1I, apilar1I, apilar2I, estadoPartida, estadoLlegada;
	int num, estadoAceptadoI;
	string palabraI;
	int salirMenu = 0;
	while(salirMenu == 0) {
		printf("%c[%d;%d;%dm", 0x1B, BRIGHT,BLUE,BG_BLACK);
		cout<<"\n\n";
		cout<<"\t\t\tВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВ\n";
		cout<<"\t\t\tВ       AUTOMATA DE PILA         В\n";
		cout<<"\t\t\tВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВ\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 1  ->  Ingresar estado         В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 2  ->  Ingresar regla          В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 3  ->  Mostrar automata        В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 4  ->  validar palabra         В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 5  ->  Salir                   В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВ\n";
		cout<<"\t\t\tВ      Elija una opcion...       В\n";
		cout<<"\t\t\tВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВ\n";
		cin>>num;
		switch(num) {
			case 1:
			        cout<<"Ingrese un Estado(si es de aceptacion 1/0): \n";
			cin>>estadoI>>estadoAceptadoI;
			grafo.insertarNodo(&lista,estadoI, estadoAceptadoI);
			break;
			case 2:
			          cout<<"Ingrese una regla: Dato a leer, dato desapilar, Primer dato a apilar, segundo datooa apilar, estado de partida, estado de llegada: \n";
			cin>>datoLeerI >> sacarPila1I >> apilar1I>> apilar2I>> estadoPartida >> estadoLlegada;
			grafo.insertarArco(&lista, datoLeerI, sacarPila1I, apilar1I, apilar2I, estadoPartida, estadoLlegada);
			break;
			case 3:
			         // grafo.mostrar(lista);
			break;
			case 4:
			           cout << " Ingrese palabra: ";
			cin>> palabraI;
			automata.leerPalabra(lista,palabraI);
			break;
			case 5:
			          salirMenu=1;
			break;
			default:
			      printf( "Tienes que selecionar una opcion correcta.\n" );
		}
	}
}
