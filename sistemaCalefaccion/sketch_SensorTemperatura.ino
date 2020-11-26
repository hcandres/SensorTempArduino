/*
  Visualizacion en pantalla TFT bus SPI ILI9341 de temperatura desde LM35
  desde iniciado el programa. Requiere librerias Adafruit ILI9341 y Adafruit GFX

  Autor: Andres Hoyos  
*/

#include <SPI.h>    // incluye libreria bus SPI
#include <Adafruit_GFX.h> // incluye libreria para manejo de graficos
#include <Adafruit_ILI9341.h> // incluye libreria para controlador ILI9341
 
#define TFT_DC 9    // define constante TFT_DC con numero 9
#define TFT_CS 10   // define constante TFT_CS con numero 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);  // crea objeto
int SENSOR; //variable para leer sensor
int TEMPERATURA; //variable para la temperatura real
int VENTILADOR = 6; //ventilador conectado al puerto 6
String ESVEN; //variable estado ventilador

void setup(){
  pinMode(VENTILADOR, OUTPUT); //establecer salida ventilador
  tft.begin();        // inicializa pantalla
  tft.setRotation(3);     // establece posicion horizontal con pines hacia abajo
  tft.fillScreen(ILI9341_BLACK);    // relleno de pantalla en color negro
  tft.setTextColor(ILI9341_WHITE);  // color de texto en blanco
  tft.setTextSize(2);     // escala de texto en 2
  tft.setCursor(2,15);     // ubica cursor en esquina superior izquierda
  tft.print("La temperatura es:");  // imprime texto 
}

void loop(){
  SENSOR = analogRead(A0); //lee lo que hay en la entrada análoga
  TEMPERATURA = ((SENSOR * 5000.0) / 1023) / 10; //conversion de la lectura analogica
                                                 //10mV por cada °C, 5V = 1023
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);  // texto blanco en fondo negro
  tft.setTextSize(8);     // escala de texto en 8
  tft.setCursor(20,100);    // ubica cursor
  tft.print(TEMPERATURA);   // imprime la temperatura leida
  tft.print(" C");          // y coloca el tipo de dato °C
  
  if(TEMPERATURA > 20.0){ //establece un valor de referencia para encender ventilador
    digitalWrite(VENTILADOR, HIGH); //enciende ventilador, si la temperatura>20
    ESVEN = "Ventilador: ON "; //estado ventilador
  }else{
    digitalWrite(VENTILADOR, LOW);//apaga si no se cumple la anterior condicion
    ESVEN = "Ventilador: OFF"; //estado ventilador
  }
  tft.setTextSize(2); //establece tamaño del texto
  tft.setCursor(20,200);    // ubica cursor
  tft.print(ESVEN); //imprime el estado del ventilador
  delay(1000);        // retardo
}
