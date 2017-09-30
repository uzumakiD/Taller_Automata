#ifndef _PILA_H
#define _PILA_H

class Pila
{
   private:
           static const int MAX = 100;
           typedef int TipoDato;
           TipoDato pila[MAX];
           int cima;

   public:
          Pila();
          bool Apilar(char elemento);
          bool Desapilar();
          bool CimaPila(char elemento);
          void LimpiarPila();
          void VerPila();
          bool PilaVacia();

};


#endif // PILA_H
