#include <TimerOne.h>                     // Bibliotec TimerOne 
#include <Wire.h>                         // Biblioteca Wire 
#include <MultiFuncShield.h>              // Biblioteca Multifunction shield
 
void setup()
{
  Timer1.initialize();                    // inicializa o Timer 1
  MFS.initialize(&Timer1);                // initializa a biblioteca Multi função
}
 
 
void loop()
{
  MFS.write(analogRead(POT_PIN));         // le a tensão no Potenciometro 
                                          // e mostra no display 
  delay(100);                             // atraso de 100 milisegundos 
}
