#include "Pila.h"
#include <iostream>
using namespace std;
 // Esta función sale del cuerpo de la clase porque usa un ciclo.
void Pila::mostrarDatos() {
 cout << endl << "DATOS EN LA PILA" << endl;
 for (int i=0; i<=indicePila; i++)
  cout << "Dato No. " << i << " : " << vector[i] << endl;
 cout << endl;
}

char Pila::mostrarTope() {
  char tope;
  tope = vector[indicePila];
}

int Pila::cuantosDatos() {
 return indicePila + 1;
}
void Pila::limpiarPila() {
 indicePila=0;
}

void Pila::entrarDato(char dato) {
 if (indicePila < 49) {
  indicePila ++;
  vector[indicePila] = dato;
 } else
  cout << "Pila desbordada: no se añadio valor" << endl;
}

char Pila::sacarDato() {
 if (indicePila > -1) {
  indicePila --;
  return vector[indicePila + 1];
 }
 return -1;
}
