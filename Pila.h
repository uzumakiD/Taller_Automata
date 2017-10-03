#ifndef _PILA_H
#define _PILA_H


class Pila
{
   private:
           static const int MAX = 100;
           static const int PILAVACIA = '#';
           typedef char TipoDato;
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
          int getCima();
          void setCima();
          bool pilaEstaVacia();

};


#endif // PILA_H
