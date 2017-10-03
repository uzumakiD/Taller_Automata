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

class Nodo{


public:

    char estado;
    int estadoAceptado;
	Nodo *siguiente;
	Arco *adyunto;

	friend class Grafo;

};


class Arco{
    public:
	char datoLeer, topePila, sacarPila1, sacarPila2, apilar1, apilar2;
	Nodo *destino;
	Arco *siguiente;

	friend class Grafo;
};

class Grafo{
    Nodo *h;


    public:

Nodo *crearNodo(char estadoI, int estadoAceptadoI){
        Nodo *p;

        p = (Nodo*)malloc(sizeof(Nodo));
        if(p != NULL){
            p -> estado = estadoI;
            p ->estadoAceptado = estadoAceptadoI;
            p -> siguiente = NULL;
            p -> adyunto = NULL;
        }else{
            printf("No se pudo reservar memoria\n");
        }

        return p;
    }

Arco *crearArco(char datoLeerI, char topePilaI, char  sacarPila1I, char sacarPila2I, char apilar1I,char apilar2I){

        Arco* p;

        p = (Arco*)malloc(sizeof(Arco));
        if(p != NULL){
            p ->datoLeer = datoLeerI;
            p ->topePila = topePilaI;
            p ->sacarPila1 = sacarPila1I;
            p ->sacarPila2 = sacarPila1I;
            p ->sacarPila2 = sacarPila2I;
            p ->apilar1 = apilar1I;
            p ->apilar2 = apilar2I;
            p -> siguiente = NULL;
            p -> destino = NULL;
        }else{
            printf("No se pudo reservar memoria\n");
        }

        return p;
    }

void insertarNodo(Nodo **cabeza, char estadoI, bool estadoAceptadoI){
        Nodo *p, *i;

        p = crearNodo(estadoI, estadoAceptadoI);
        if(*cabeza == NULL){
            *cabeza = p;
        }else{
            i = ultimoNodo(*cabeza);
            i -> siguiente = p;
        }
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

Nodo *buscarNodo(Nodo *cabeza, char estadoI){
	Nodo *b;

	if(cabeza == NULL){
		b = NULL;
	}else{
		if(cabeza ->estado == estadoI){
			b = cabeza;
		}else{
			b = buscarNodo(cabeza -> siguiente, estadoI);
		}

	}
	return b;
}


void insertarArco(Nodo **cabeza,char datoLeerI, char topePilaI,char  sacarPila1I, char sacarPila2I, char apilar1I,char apilar2I, char y, char z){
	Nodo *a, *b;
	Arco *d, *j;

	a = buscarNodo(*cabeza, y);
	b = buscarNodo(*cabeza, z);
	if(a != NULL && b != NULL){
		d = crearArco(datoLeerI, topePilaI, sacarPila1I, sacarPila2I, apilar1I, apilar2I);
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

Arco *ultimoArco(Arco *arista){
	Arco *u;

	if(arista -> siguiente != NULL){
		u = ultimoArco(arista -> siguiente);
	}else{
		u = arista;
	}

	return u;
}

void mostrarArco(Arco *arista){

	if(arista == NULL){
		return;
	}else{
		printf("[ %c, %c, %c,%c,%c,%c ]-> ", arista ->datoLeer, arista->topePila, arista->sacarPila1, arista->sacarPila2, arista->apilar1, arista->apilar2 );
		mostrarArco(arista -> siguiente);
	}
}


Arco *BuscaArco(Arco *arista){
    Arco *b;

	if(arista != NULL){
		b= arista;
		mostrarArco(arista -> siguiente);
		return b;
	}else{
		return b=NULL;
	}
}

void mostrar(Nodo *cabeza){

	if(cabeza == NULL){
		printf("[ NULL ]\n");
	}else{
		printf("[ %c ]->",cabeza ->estado);
		mostrarArco(cabeza -> adyunto);
		printf("\n");
		mostrar(cabeza -> siguiente);
	}
}

Arco *buscarArco(Arco *arista, char datoLeerI, char topePilaI, char  sacarPila1I, char sacarPila2I, char apilar1I,char apilar2I){
	Arco *b;

	if(arista != NULL){
		if((datoLeerI == arista ->datoLeer) && (topePilaI == arista->topePila)  && (sacarPila1I == arista->sacarPila1) && (sacarPila2I == arista->sacarPila2)){
			b = arista;
		}else{
			b = buscarArco(arista -> siguiente, datoLeerI, topePilaI, sacarPila2I, sacarPila2I, apilar1I, apilar2I);
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

};


class Automata : public Grafo{
    Pila pilaPalabra;
    Pila pilaSistema;
    Grafo grafo;
    char estado;


    public:

    void leerPalabra(Nodo *cabeza, string PalabraI){
        for(int i=0; i<PalabraI.size(); i++){
        	pilaPalabra.Apilar(PalabraI[i]);
        }

          pilaPalabra.VerPila();
    }
    void desapilarPalabra(Pila pilaPalabra){
        pilaPalabra.Desapilar();
    }
    void desapilarSistema(Pila pilaSistema){
        pilaSistema.Desapilar();
    }
    void apilar(Pila pilaSistema, char apilaI){
        pilaSistema.Apilar(apilaI);
    }
    void automta(Arco *arista, Pila pilaPalabra,Pila pilaSistema){

        if(arista->datoLeer=='$'){
                if(arista->sacarPila1!='$'){
                    desapilarSistema(pilaSistema);
                }else if(arista->sacarPila2!='$'){
                    desapilarSistema(pilaSistema);
                }else if (arista->apilar1!='$'){
                    apilar(pilaSistema,(arista->apilar1));
                }else if(arista->apilar2!='$'){
                    apilar(pilaSistema,(arista->apilar2));
                }
        }
        else(arista->datoLeer!='$');{
                desapilarPalabra(pilaPalabra);
                if(arista->sacarPila1!='$'){
                    desapilarSistema(pilaSistema);
                }else if(arista->sacarPila2!='$'){
                    desapilarSistema(pilaSistema);
                }else if (arista->apilar1!='$'){
                    apilar(pilaSistema,(arista->apilar1));
                }else if(arista->apilar2!='$'){
                    apilar(pilaSistema,(arista->apilar2));
                }
        }
        return;

    }
    void validar(Nodo *cabeza){
        if (cabeza->estadoAceptado==1){
            cout<<"la palabra es valida";
        }else{
            cout<<"palabra erronea";
        }
    }

void moverAutomata(Nodo *cabeza, Pila pilaPalabraI){
    Arco *b;
    Pila pilaSistema;
	if(cabeza == NULL){
		printf("[ NULL ]\n");
	}else{
		b=grafo.BuscaArco(cabeza->adyunto);
		if(b==NULL){
            validar(cabeza);
        }else if(b!=NULL){
            if((b->datoLeer==pilaPalabraI.getCima()) && (b->topePila==pilaSistema.getCima())){
                estado= cabeza->estado;
                automta(b, pilaPalabraI, pilaSistema);
                moverAutomata(b ->destino, pilaPalabraI);
            }

        }else {
        validar(cabeza);
    }

	}

}


};

int main(){
    Nodo *lista = NULL;
	Grafo grafo;
	Pila pila;
	Automata automata;
	char estadoI, estadoAceptadoI, datoLeerI, topePilaI, sacarPila1I, sacarPila2I, apilar1I, apilar2I, estadoPartida, estadoLlegada;
	int num;
	string palabraI;

    int salirMenu = 0;
while(salirMenu == 0){
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
switch(num)
{
      case 1:
        cout<<"Ingrese un Estado(si es de aceptacion 1/0): \n";
        cin>>estadoI>>estadoAceptadoI;
        grafo.insertarNodo(&lista,estadoI, estadoAceptadoI);
      break;
      case 2:
          cout<<"Ingrese una regla: Dato a leer, dato en pila, dato desapilar, estado de partida, estado de llegada: \n";
          cin>>datoLeerI >> topePilaI >> sacarPila1I >> sacarPila2I>> apilar1I>> apilar2I>> estadoPartida >> estadoLlegada;
          grafo.insertarArco(&lista, datoLeerI, topePilaI, sacarPila1I, sacarPila2I, apilar1I, apilar2I, estadoPartida, estadoLlegada);

      break;
      case 3:
          grafo.mostrar(lista);
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

