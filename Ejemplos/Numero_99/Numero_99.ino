#include <Matriz.h>
Matriz matriz(6, 9, 5);

void setup(){
}
void loop(){
  matriz.printNumber(99); //Numero a imprimir (0-99)
  delay(500);
  //Numero a imprimir (0-99) y tiempo que estara mostrandose en segundos
  matriz.printNumber(99, 1);
  delay(500);
  matriz.printNumber(99, 1.63);
}


