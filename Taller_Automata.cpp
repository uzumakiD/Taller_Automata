#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Pila.h"

using namespace std;

class Arco;

class Nodo{
	char estado;
	Nodo *siguiente;
	Arco *adyunto;

	friend class Grafo;

};


class Arco{
	char datoLeer, topePila, sacarPila;
	Nodo *destino;
	Arco *siguiente;

	friend class Grafo;
};

class Grafo{
    Nodo *h;


    public:

Nodo *crearNodo(char estadoI){
        Nodo *p;

        p = (Nodo*)malloc(sizeof(Nodo));
        if(p != NULL){
            p -> estado = estadoI;
            p -> siguiente = NULL;
            p -> adyunto = NULL;
        }else{
            printf("No se pudo reservar memoria\n");
        }

        return p;
    }

Arco *crearArco(char datoLeerI, char topePilaI, char sacarPilaI){

        Arco* p;

        p = (Arco*)malloc(sizeof(Arco));
        if(p != NULL){
            p ->datoLeer = datoLeerI;
            p ->topePila = topePilaI;
            p ->sacarPila = sacarPilaI;
            p -> siguiente = NULL;
            p -> destino = NULL;
        }else{
            printf("No se pudo reservar memoria\n");
        }

        return p;
    }
Nodo *ultimoNodo(Nodo *cabeza){
        Nodo *u;

        if(cabeza -> siguiente != NULL){
            u = ultimoNodo(cabeza -> siguiente);
        }else{
            u = cabeza;
        }

        return u;
    }

void insertarNodo(Nodo **cabeza, char x){
        Nodo *p, *i;

        p = crearNodo(x);
        if(*cabeza == NULL){
            *cabeza = p;
        }else{
            i = ultimoNodo(*cabeza);
            i -> siguiente = p;
        }
    }

Nodo *buscarNodo(Nodo *cabeza, char x){
	Nodo *b;

	if(cabeza == NULL){
		b = NULL;
	}else{
		if(cabeza ->estado == x){
			b = cabeza;
		}else{
			b = buscarNodo(cabeza -> siguiente, x);
		}

	}
	return b;
}

Arco *ultimoArco(Arco *arista){
	Arco *u;

	if(arista -> siguiente != NULL){
		u = ultimoArco(arista -> siguiente);
	}else{
		u = arista;
	}

	return u;
}

void insertarArco(Nodo **cabeza,char datoLeerI, char topePilaI, char sacarPilaI, char y, char z){
	Nodo *a, *b;
	Arco *d, *j;

	a = buscarNodo(*cabeza, y);
	b = buscarNodo(*cabeza, z);
	if(a != NULL && b != NULL){
		d = crearArco(datoLeerI, topePilaI, sacarPilaI);
		if(a -> adyunto == NULL){
			a -> adyunto = d;
			d -> destino = b;
		}else{
			j = ultimoArco(a -> adyunto);
			j -> siguiente = d;
			d -> destino = b;
		}
	}
}

void mostrarArco(Arco *arista){

	if(arista == NULL){
		return;
	}else{
		printf("[ %d, %d, %d ]-> ", arista ->datoLeer, arista->topePila, arista->sacarPila );
		mostrarArco(arista -> siguiente);
	}
}

void mostrar(Nodo *cabeza){

	if(cabeza == NULL){
		printf("[ NULL ]\n");
	}else{
		printf("[ %c ]-> ",cabeza ->estado);
		mostrarArco(cabeza -> adyunto);
		printf("\n");
		mostrar(cabeza -> siguiente);
	}
}

Arco *buscarArco(Arco *arista, char datoLeerI, char topePilaI, char sacarPilaI){
	Arco *b;

	if(arista != NULL){
		if((datoLeerI == arista ->datoLeer) && (topePilaI == arista->topePila)  && (sacarPilaI == arista->sacarPila)){
			b = arista;
		}else{
			b = buscarArco(arista -> siguiente, datoLeerI, topePilaI, sacarPilaI);
		}
	}else{
		b = NULL;
	}

	return b;
}

Arco *anteriorArco(Arco *arista, Arco *e){
	Arco *a;

	if(e != NULL){
		if(arista != NULL){
			if(arista -> siguiente == e){
				a = arista;
			}else{
				a = anteriorArco(arista -> siguiente, e);
			}
		}else{
			a = NULL;
		}
	}else{
		a = NULL;
	}

	return a;
}

bool existeArista(Arco *arista, Nodo *b){
	bool e;

	if(arista == NULL || b == NULL){
		e = false;
	}else{
		if(arista -> destino == b){
			e = true;
		}else{
			e = existeArista(arista -> siguiente, b);
		}
	}

	return e;
}

bool existeCamino(Arco *arista, Nodo *b){
	bool e;

	if(arista == NULL || b == NULL){
		e = false;
	}else{
		if(arista -> destino != NULL){
			if(arista -> destino == b){
				e = true;
			}else{
				e = existeCamino((arista -> destino) -> adyunto, b);
			}
		}else{
			e = false;
		}
	}

	return e;
}

Nodo* nodoCamino(Arco *arista, Nodo *b){
	Nodo *n, j;

	if(arista == NULL || b == NULL){
		n = NULL;
	}else{
		if(existeCamino(arista, b)){
			n = arista -> destino;
		}else{
			n = nodoCamino(arista -> siguiente, b);
		}
	}

	return n;
}

void mostrarCaminoXY(Nodo *a, Nodo *b, Arco *arista){

	if(a == NULL || arista == NULL){
		return;
	}else{
		if(existeCamino(arista, b)){
			printf("- > [ %c ]", (arista -> destino) ->estado);
			mostrarCaminoXY(nodoCamino(arista, b), b, nodoCamino(arista, b) -> adyunto);
		}
	}
}

void mostrarCaminos(Nodo *a, Nodo *b, Arco *arista){
	bool e;

	if(a == NULL || b == NULL || arista == NULL){
		return;
	}else{
		if(existeCamino(arista, b)){
			printf("[ %c ] ", a -> estado);
			mostrarCaminoXY(a, b, arista);
			printf("\n");
			mostrarCaminos(a, b, arista -> siguiente);
		}else{
			mostrarCaminos(a, b, arista -> siguiente);
		}
	}
}

void mostrarCamino(Nodo *a, Nodo *b, Arco *arista){

	if(a == NULL || b == NULL){
		return;
	}else{
		printf("[ %c ]", a -> estado);
		mostrarCaminoXY(a, b, arista);
	}
}

};




int main(){
	Nodo *lista = NULL;
	Grafo c;


	c.insertarNodo(&lista, 'a');
	c.insertarNodo(&lista, 'b');
	c.insertarNodo(&lista, 'd');
	c.insertarNodo(&lista, 'e');
	c.insertarNodo(&lista, 'f');

	c.insertarArco(&lista, 'A','B','C', 'c', 'b');
	c.insertarArco(&lista, 'A','B','C', 'b', 'd');
	c.insertarArco(&lista, 'A','B','C', 'b', 'c');
	c.insertarArco(&lista, 'A','B','C', 'c', 'e');
	c.insertarArco(&lista, 'A','B','C', 'd', 'e');
	c.insertarArco(&lista, 'A','B','C', 'f', 'e');

	c.mostrar(lista);

	Pila pila;

	pila.Apilar('a');
	pila.Apilar('b');

	pila.VerPila();

	system("pause");
	return 0;

}
