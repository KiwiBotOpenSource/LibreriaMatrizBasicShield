/*
Kiwibot - Basic Shield
Libreria para el control del Kiwibot Basic Shield
Creada por Alberto Pumar Jimenez,
El dia 14 de enero de 2015
Modificado el dia 2 de febrero de 2015
*/
#ifndef Matriz_h
#define Matriz_h
#include "Arduino.h"

class Matriz{
public:
Matriz(int setpinLatch, int setpinReloj, int setpinDatos); //Inicializacion de la libreria se definen el pin de datos, reloj y latch y se definen como salida
void printPixel(byte i0, byte j0); //Funcion para imprimir pixel en (i ,j)
void printPixel(byte i0, byte j0, int tiempo); //Funcion para imprimir pixel en (i ,j) durante un tiempo determinado
void printPixel(byte i0, byte j0, double tiempo); //Funcion para imprimir pixel en (i ,j) durante un tiempo determinado
void printNumber(byte valor); //Funcion para imprimir un numero
void printNumber(byte valor, int tiempo); //Funcion para imprimir un numero durante un tiempo determinado
void printNumber(byte valor, double tiempo); //Funcion para imprimir un numero durante un tiempo determinado siendo posible la duracion 1.5 segundos
void printLine(byte i2, byte j2, byte i3, byte j3); //Funcion para imprmir una linea desde Iinicio, Jinicio hasta Ifinal, Ifinal
void clean(); //Funcion para apagar todos los leds
void newPixel(byte i, byte j); //Funcion para añadir un nuevo punto que se encendera en la matriz
void deletePixel(byte i, byte j); //Funcion para eliminar un nuevo punto de los que se encienden en la matriz
void print(); //Funcion para encender los puntos anteriormente definidos
void print(int tiempo); //Funcion para encender los puntos anteriormente definidos durante un tiempo definido
void print(double tiempo); //Funcion para encender los puntos anteriormente definidos durante un tiempo definido siendo posible la duracion 1.5 segundos
void fadeOut(int tiempo); //Funcion para apagar progresivamente los puntos anteriormente añadidos
void fadeIn(int tiempo); //Funcion para encender progresivamente los puntos anteriormente añadidos

private:
void sendData(byte fila, byte columna);
static byte unidad[]; //este byte sirve para imprimir numeros, representa los LEDs que deben encenderse por cada columna en decimal se refiere a las columnas 5-7 donde se imprimira la unidad
static byte decena[]; //este byte sirve para imprimir numeros, representa los LEDs que deben encenderse por cada columna en decimal se refiere a las columnas 1-3 donde se imprimira la decena
static byte j1[7]; //este byte representa la columna en la que queremos encender el LED. Esta en binario
static byte i1[5]; //este byte representa la fila en la que queremos encender el LED. Esta en binario y en logica negativa
static byte estadoMatriz[35]; //en este byte se guarda el estado de cada led
static byte estadoMatrizBinario[5]; //este byte representa el estadoMatriz en binario
// variables
static byte index; //variable auxiliar utilizada para almacenar la decena o unidad de un numero
//variables usadas para almacenar los datos que eviaremos al registro de desplazamiento
static byte fila;
static byte columna;
//Pines para la inicializacion de la libreria
static int pinLatch;
static int pinReloj;
static int pinDatos;
};
#endif