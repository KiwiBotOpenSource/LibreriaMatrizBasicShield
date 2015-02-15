#include <Matriz.h>
Matriz matriz(6, 9, 5);

void setup(){
}
void loop(){
  //Linea desde (Iinicial, Jinicial) hasta (Ifinal, Jfinal)
  matriz.imprimirLinea(1, 1, 1, 7);
  matriz.imprimirLinea(3, 3, 5, 5);
}

