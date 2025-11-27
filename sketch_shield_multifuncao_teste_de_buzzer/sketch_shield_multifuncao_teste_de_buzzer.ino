#include <TimerOne.h>                     // Bibliotec TimerOne 
#include <MultiFuncShield.h>              // Biblioteca Multifunction shield
 
void setup()
{
  Timer1.initialize();                    // inicializa o Timer 1
  MFS.initialize(&Timer1);                // initializa a biblioteca Multi função
  Buzzer();                               // toca a campainha 
}
 
void Buzzer()
{
  MFS.beep();                             // Bip curto de 300 milisegundos
  delay(1000);                            // espera de 1 segundo (1000 ms)
 
                                          // 4 bips curtos, repetidos 3 vezes
  MFS.beep(5,       // Define um bip de 50 ms (5 unidades de 10ms)
           5,       // Define um silencio de 50 ms (5 unidades de 10ms)
           4,       // Define o loop de reprodução do bip (4 vezes)
           3,       // Define a quantidade de execuções do loop (3 vezes)
           50);     // Define o tempo de espera entre os loops (500 ms)
                              
 delay(3200);                            // espera de 3,2 segundo (3200 ms)
 MFS.beep();                             // Bip curto de 300 milisegundos
}
 
void loop()
{
}
