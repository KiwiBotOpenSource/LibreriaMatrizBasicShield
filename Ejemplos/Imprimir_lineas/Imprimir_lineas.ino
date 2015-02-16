#include <Matriz.h>
Matriz matriz(6, 9, 5);

void setup(){
}
void loop(){
  //Linea desde (Iinicial, Jinicial) hasta (Ifinal, Jfinal)
  matriz.printLine(1, 1, 1, 7);
  matriz.printLine(3, 3, 5, 5);
}

