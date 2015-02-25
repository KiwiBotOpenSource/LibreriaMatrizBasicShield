/*
Kiwibot - Basic Shield
 Libreria para el control del Kiwibot Basic Shield
 Creada por Alberto Pumar Jimenez,
 El dia 14 de enero de 2015
 */
#include "Arduino.h"
#include "Matriz.h"
//este byte representa la fila en la que queremos encender el LED. Esta en binario y en logica negativa
byte Matriz::i1[5] = {
  B1101111, B1110111, B1111011, B1111101, B1111110};
//este byte representa la columna en la que queremos encender el LED. Esta en binario
byte Matriz::j1[7] = {
  B1000000, B0100000, B0010000, B0001000, B0000100, B0000010, B0000001};
//este byte sirve para imprimir numeros, representa los LEDs que deben encenderse por cada columna en decimal
//se refiere a las columnas 5-7 donde se imprimira la unidad
byte Matriz::estadoMatriz[35]={
  0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,
  0,0,0,0,0,0,0};
byte Matriz::estadoMatrizBinario[5] = {
  B0000000,B0000000,B0000000,B0000000,B0000000};
byte Matriz::unidad[] = {
  7, 5, 5, 5, 7,
  2, 6, 2, 2, 7,
  2, 5, 1, 2, 7,
  6, 1, 6, 1, 6,
  5, 5, 7, 1, 1,
  7, 4, 6, 1, 6,
  3, 4, 7, 5, 7,
  7, 1, 1, 2, 2,
  7, 5, 7, 5, 7,
  7, 5, 7, 1, 6};
//este byte sirve para imprimir numeros, representa los LEDs que deben encenderse por cada columna en decimal
//se refiere a las columnas 1-3 donde se imprimira la decena
byte Matriz::decena[]= {
  112, 80, 80, 80, 112,
  32, 96, 32, 32, 112,
  32, 80, 16, 32, 112,
  96, 16, 96, 16, 96,
  80, 80, 112, 16, 16,
  112, 64, 96, 16, 96,
  48, 64, 112, 80, 112,
  112, 16, 16, 32, 32,
  112, 80, 112, 80, 112,
  112, 80, 112, 16, 96};
byte Matriz::index; //variable auxiliar utilizada para almacenar la decena o unidad de un numero
//variables usadas para almacenar los datos que eviaremos al registro de desplazamiento
byte Matriz::fila;
byte Matriz::columna;
//Pines para la inicializacion de la libreria
int Matriz::pinLatch;
int Matriz::pinReloj;
int Matriz::pinDatos;

//########################################################
//#Inicializacion de la libreria, se asignan los pines:
//#      @El pin de datos es el 5
//#      @El pin del reloj es el 9
//#      @El pin latch es el 6
//#Todos estos pines se definen como salida
//########################################################
Matriz::Matriz(int setpinLatch, int setpinReloj, int setpinDatos){
pinLatch = setpinLatch;
pinReloj = setpinReloj;
pinDatos = setpinDatos;
pinMode(pinLatch, OUTPUT);
pinMode(pinReloj, OUTPUT);
pinMode(pinDatos, OUTPUT);
}


//########################################################
//#Funcion para imprimir pixel en (i ,j)
//#      @i selecciona la fila. 
//#Al aumentar la i, la fila seleccionada sera la de abajo a la anterior 
//#Ej: si i=1 la fila seleccionada será la de arriba
//#      @j selecciona la columna. 
//#Al aumentar la j, la columna seleccionada sera la de la derecha a la anterior 
//#Ej: si j=1 la columna seleccionada será la de la derecha
//########################################################
void Matriz::printPixel(byte i0, byte j0){
  byte i=i0;
  byte j=j0;
  sendData(i1[i-1], j1[j-1]); //Imprimimos en la pantalla la fila y columna necesaria para encender el pixel correspondiente
}


//########################################################
//#Funcion para imprimir pixel en (i ,j) durante un tiempo determinado en segundos
//#      @i selecciona la fila. 
//#Al aumentar la i, la fila seleccionada sera la de abajo a la anterior 
//#Ej: si i=1 la fila seleccionada será la de arriba
//#      @j selecciona la columna. 
//#Al aumentar la j, la columna seleccionada sera la de la derecha a la anterior 
//#Ej: si j=1 la columna seleccionada será la de la derecha
//########################################################
void Matriz::printPixel(byte i0, byte j0, int tiempo){
  tiempo=(tiempo*2000)/0.554;
  byte i=i0;
  byte j=j0;
  for(int t=0; t<tiempo; t++){
    sendData(i1[i-1], j1[j-1]); //Imprimimos en la pantalla la fila y columna necesaria para encender el pixel correspondiente
  }
}


//########################################################
//#Funcion para imprimir pixel en (i ,j) durante un tiempo determinado en segundos y milisegundos
//#      @i selecciona la fila. 
//#Al aumentar la i, la fila seleccionada sera la de abajo a la anterior 
//#Ej: si i=1 la fila seleccionada será la de arriba
//#      @j selecciona la columna. 
//#Al aumentar la j, la columna seleccionada sera la de la derecha a la anterior 
//#Ej: si j=1 la columna seleccionada será la de la derecha
//########################################################
void Matriz::printPixel(byte i0, byte j0, double tiempo){
  tiempo=(tiempo*2000)/0.554;
  byte i=i0;
  byte j=j0;
  for(int t=0; t<tiempo; t++){
    sendData(i1[i-1], j1[j-1]); //Imprimimos en la pantalla la fila y columna necesaria para encender el pixel correspondiente
  }
}


//########################################################
//#Funcion para imprimir un numero
//#Imprime un numero desde el 0 hasta el 99 durante un instante
//########################################################
void Matriz::printNumber(byte valor){
  index=valor%10; //Extraemos la unidad del numero
  byte i; //byte auxiliar para contar en que fila estamos
  for(i = 0; i < 5; i++){
    sendData(i1[i], unidad[(i+5*index)]); //Imprimimos en la pantalla la fila y la/las columnas indicadas
  }
  index=valor/10; //Extraemos la decena del numero
  for(i = 0; i < 5; i++){
    sendData(i1[i], decena[(i+5*index)]); //Imprimimos en la pantalla la fila y la/las columnas indicadas
  }
  cleanMatrix();
}


//########################################################
//#Funcion para imprimir un numero
//#Imprime un numero desde el 0 hasta el 99
//# durante el tiempo indicado en segundos
//########################################################
void Matriz::printNumber(byte valor, int tiempo){
  tiempo=(tiempo*2000)/5.563;
  //Repetimos esta operacion un numero definido de veces para crear una duracion
  for(int t=0; t<tiempo; t++){
    index=valor%10; //Extraemos la unidad del numero
    byte i; //byte auxiliar para contar en que fila estamos
    for(i = 0; i < 5; i++){
      sendData(i1[i], unidad[(i+5*index)]); //Imprimimos en la pantalla la fila y la/las columnas indicadas
    }
    index=valor/10; //Extraemos la decena del numero
    for(i = 0; i < 5; i++){
      sendData(i1[i], decena[(i+5*index)]); //Imprimimos en la pantalla la fila y la/las columnas indicadas
    }
  }
  cleanMatrix();
}


//########################################################
//#Funcion para imprimir un numero
//#Imprime un numero desde el 0 hasta el 99
//# durante el tiempo indicado en segundos
//#	@es posible la duracion 1.5 segundos
//########################################################
void Matriz::printNumber(byte valor, double tiempo){
  tiempo=(tiempo*2000)/5.563;
  //Repetimos esta operacion un numero definido de veces para crear una duracion
  for(int t=0; t<tiempo; t++){
    index=valor%10; //Extraemos la unidad del numero
    byte i; //byte auxiliar para contar en que fila estamos
    for(i = 0; i < 5; i++){
      sendData(i1[i], unidad[(i+5*index)]); //Imprimimos en la pantalla la fila y la/las columnas indicadas
    }
    index=valor/10; //Extraemos la decena del numero
    for(i = 0; i < 5; i++){
      sendData(i1[i], decena[(i+5*index)]); //Imprimimos en la pantalla la fila y la/las columnas indicadas
    }
  }
  cleanMatrix();
}


//########################################################
//#Funcion para imprmir una linea
//#desde Iinicio, Jinicio hasta Ifinal, Ifinal
//########################################################
void Matriz::printLine(byte i2, byte j2, byte i3, byte j3){
  byte i;
  byte j;
  byte iIni=i2;
  byte iFin=i3;
  byte jIni=j2;
  byte jFin=j3;
  for(j=1; j<8; j++){ //recorremos todas las columnas
    if(j>=jIni && j<=jFin){ //restringimos el recorrido al dominio de la linea
      i=(((iFin-iIni)*(j-jIni))/(jFin-jIni))+iIni; //Ecuacion de una recta en forma vectorial donde hemos despejado i
      printPixel(i, j); //Imprimimos pixel a pixel la linea
    }
  }
}


//########################################################
//#Funcion para limpiar la matriz
//#Esto significa que todos los leds se apagaran,
//#pero mantendra guardados los puntos añadidos a traves 
//#de la funcion nuevoPunto(i, j)
//########################################################
void Matriz::cleanMatrix(){
  sendData(B1111111, 0);  //Ponemos todas las filas a 1 y todas las columnas a 0 para que no se encienda ningun led
}


//########################################################
//#Funcion para añadir un nuevo punto que se encendera en la matriz
//#una vez llamado al metodo imprimirMatriz()
//########################################################
void Matriz::newPixel(byte i, byte j){
  estadoMatriz[7*(i-1)+(j-1)]=1; //Almacenamos un nuevo punto en un array
}


//########################################################
//#Funcion para eliminar un nuevo punto de los que se encienden en la matriz
//#una vez llamado al metodo imprimirMatriz()
//########################################################
void Matriz::deletePixel(byte i, byte j){
  estadoMatriz[7*(i-1)+(j-1)]=0;  //Eliminamos un punto existente del array
}


//########################################################
//#Funcion para encender los puntos anteriormente definidos
//########################################################
void Matriz::printMatrix(){
  //Pasamos la informacion del array a binario
  for(byte i=0; i<5; i++){
    for(byte j=0; j<7; j++){
      estadoMatrizBinario[i]=(estadoMatrizBinario[i]<<1)|estadoMatriz[7*i+j];
    }
  }
  //Recorremos el array de los binarios imprimiendo la imformacion el la matriz
  for(byte i = 0; i < 5; i++){
    sendData(i1[i], estadoMatrizBinario[i]);
  }
}


//########################################################
//#Funcion para encender los puntos anteriormente definidos
//#durante un periodo de tiempo definido en segundos
//########################################################
void Matriz::printMatrix(int tiempo){
  float time=(tiempo*1000)/1.407;
  //Repetimos esta operacion un numero definido de veces para crear una duracion
  for(int t=0; t<time; t++){
    //Pasamos la informacion del array a binario
    for(byte i=0; i<5; i++){
      for(byte j=0; j<7; j++){
        estadoMatrizBinario[i]=(estadoMatrizBinario[i]<<1)|estadoMatriz[7*i+j];
      }
    }
    //Recorremos el array de los binarios imprimiendo la imformacion el la matriz
    for(byte i = 0; i < 5; i++){
      sendData(i1[i], estadoMatrizBinario[i]);
    }
  }
}


//########################################################
//#Funcion para encender los puntos anteriormente definidos
//#durante un periodo de tiempo definido en segundos
//#	@Es posible utilizar la duracion 1.5 segundos
//########################################################
void Matriz::printMatrix(double tiempo){
  tiempo=(tiempo*1000)/1.407;
  //Repetimos esta operacion un numero definido de veces para crear una duracion
  for(int t=0; t<tiempo; t++){
    //Pasamos la informacion del array a binario
    for(byte i=0; i<5; i++){
      for(byte j=0; j<7; j++){
        estadoMatrizBinario[i]=(estadoMatrizBinario[i]<<1)|estadoMatriz[7*i+j];
      }
    }
    //Recorremos el array de los binarios imprimiendo la imformacion el la matriz
    for(byte i = 0; i < 5; i++){
      sendData(i1[i], estadoMatrizBinario[i]);
    }
  }
}



//########################################################
//#Funcion para apagar progresivamente los puntos anteriormente añadidos
//#Mediante el tiempo elegimos la intensidad del fadeOut
//########################################################
void Matriz::fadeOut(int tiempo){
  //Recorremos las 5 filas encendiendo y apagando los leds para disminuir la intensida de estos
  float t;
  for(byte i=0; i<500; i++){
   t=i/100;
    //Repetimos esta operacion un numero definido de veces para crear una duracion
    for(int j=0; j<t/5; j++){
      printMatrix();
      cleanMatrix();
      delay(t*t);  //El delay entre el encendido y el apagado va aumentando
    }
  }
}


//########################################################
//#Funcion para encender progresivamente los puntos anteriormente añadidos
//#Mediante el tiempo elegimos la intensidad del fadeIn
//########################################################
void Matriz::fadeIn(int tiempo){
 float t;
  //Recorremos las 5 filas encendiendo y apagando los leds para aumentar la intensida de estos

  for(byte i=500; i>0; i--){
    t=i/100;  
  //Repetimos esta operacion un numero definido de veces para crear una duracion
    for(int j=0; j<t/5; j++){
      printMatrix();
      cleanMatrix();
      delay(t*t);  //El delay entre el encendido y el apagado va disminuyendo
    }
  }
}


//########################################################
//#Funcion para mandar valores a la placa
//#a traves del registro de desplazamiento
//########################################################
void Matriz::sendData(byte fila, byte columna){
  //Como usamos un regirtro de desplazamiento utilizamos la funcion shiftOut para enviarle los datos enviando primero el bit mas significativo
  digitalWrite(pinLatch, LOW);
  shiftOut(pinDatos, pinReloj, MSBFIRST, fila);
  shiftOut(pinDatos, pinReloj, MSBFIRST, columna);
  digitalWrite(pinLatch, HIGH);
}
