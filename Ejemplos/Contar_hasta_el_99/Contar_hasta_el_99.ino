#include <Matriz.h>
Matriz matriz(6, 9, 5);

int numero=0;

void setup(){
}
void loop(){
  for(numero=0; numero<100; numero++){
    matriz.imprimirNumero(numero, 1);  //imprimimos un nomero durante 1 segundo
  }
}
