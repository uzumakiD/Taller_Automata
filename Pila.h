#ifndef _PILA_H
#define _PILA_H


class Pila {
 char vector[50];
  // indicePila:  -1 -> pila vacia     0 -> posicion del dato
int indicePila;
public:
 Pila() {   indicePila = -1; }; // constructor
  // funciones analizadoras
 void mostrarDatos();
 int cuantosDatos();
  // funciones modificadoras
 void entrarDato(char dato);
 char sacarDato();
 char mostrarTope();
};



#endif // PILA_H
