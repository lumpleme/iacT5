#include <MultiFuncShield.h>
#include <TimerOne.h>
#include <Wire.h>

#define RANGE_MAX_NUMBER 9999
#define RANGE_MIN_NUMBER 0000

enum GeneratorModeValues
{
  GENERATOR_STOPPED,
  GENERATOR_STARTED,
  SETTING_RANGE_MAX_NUM_STARTED,
  SETTING_RANGE_MIN_NUM_STARTED
};

enum RangeStatusValues
{
  RANGE_NOT_SET,
  RANGE_SET
};

enum ledModeValues
{
  LED_ALL_OFF,
  LED_1_ON,
  LED_2_ON,
  LED_3_ON,
  LED_4_ON
};

enum AnimationModeValues
{
  ANIMATION_STOPPED,
  ANIMATION_STARTED,
  ANIMATION_STAGE1,
  ANIMATION_STAGE2,
  ANIMATION_STAGE3,
  ANIMATION_STAGE4,
  ANIMATION_INTERRUPTED
};

void button1short() {
  switch (generator_mode){
    case GENERATOR_STOPPED:
      // sortear numero aleatorio e iniciar a animacao dos displays e leds apenas de configurado max e min
      break;
    case GENERATOR_STARTED:
      // interromper animacoes e mudar resetar os valores max e min e setar o estado de para RANGE_NOT_SET
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // encerrar estado de config, voltar para estado GENERATOR_STOPPED e, se valido: mudar para RANGE_SET, acender LED 1
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // encerrar estado de config, voltar para estado GENERATOR_STOPPED e, se valido: mudar para RANGE_SET, acender LED 2
      break;
  }
}

void button1long() {
  switch (generator_mode){
    case GENERATOR_STOPPED:
      // nada
      break;
    case GENERATOR_STARTED:
      // nada
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // nada
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // nada
      break;
  }
}

void button2short() {
  switch (generator_mode){
    case GENERATOR_STOPPED:
      // mostrar max atual
      break;
    case GENERATOR_STARTED:
      // nada
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // incrementar em 100 unidades o valor maximo e mostrar no display
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // incrementar em 100 unidades o valor minimo e mostrar no display
      break;
  }
}

void button2long() {
  switch (generator_mode){
    case GENERATOR_STOPPED:
      // mudar para estado de configuracao de max
      break;
    case GENERATOR_STARTED:
      // nada
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // incrementar em 100 unidades o valor maximo e mostrar no display
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // incrementar em 100 unidades o valor minimo e mostrar no display
      break;
  }
}

void button3short() {
  switch (generator_mode){
    case GENERATOR_STOPPED:
      // mostrar min
      break;
    case GENERATOR_STARTED:
      // nada
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // decrementar em 100 unidades o valor maximo e mostrar no display
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // decrementar em 100 unidades o valor minimo e mostrar no display
      break;
  }
}

void button3long() {
  switch (generator_mode){
    case GENERATOR_STOPPED:
      // mudar para estado de configurar min
      break;
    case GENERATOR_STARTED:
      // nada
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // decrementar em 100 unidades o valor maximo e mostrar no display
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // decrementar em 100 unidades o valor minimo e mostrar no display
      break;
  }
}



GeneratorModeValues generator_mode;
RangeStatusValues range_status_set_max;
RangeStatusValues range_status_set_min;
int range_max = RANGE_MAX_NUMBER;
int range_min = RANGE_MAX_NUMBER;
ledModeValues led_mode;
AnimationModeValues animation_mode;

void setup() {
  generator_mode = GENERATOR_STOPPED;
  range_status_set_max = RANGE_NOT_SET;
  range_status_set_min = RANGE_NOT_SET;
  led_mode = LED_ALL_OFF;
  animation_mode = ANIMATION_STOPPED;
  
  Timer1.initialize();
  MFS.initialize(&Timer1);                 
  MFS.write("off");
  MFS.writeLeds(LED_ALL, OFF);             

  Serial.begin(9600);
}

void loop() {

  byte btn = MFS.getButton();                            // verifica o status dos botões
 
  if (btn)                                               // se valor <> zero, botão pressionado  
  {
    byte buttonNumber = btn & B00111111;                 // AND bit a bit para identificar o botão
    byte buttonAction = btn & B11000000;                 // AND bit a bit para identificar o evento
 
    Serial.print("BOTAO_");                              // imprime mensagem
    Serial.write(buttonNumber + '0');                    // imprime o caractere da tabela ASCII correspondente ao código fornecido
    Serial.print("_"); 

    if (buttonAction == BUTTON_SHORT_RELEASE_IND)   // compara o evento do botão
    {
      Serial.println("SOLTA RAPIDO");                    // imprime mensagem
    }
    else if (buttonAction == BUTTON_LONG_PRESSED_IND)    // compara o evento do botão
    {
      Serial.println("PRESSIONADO LONGO");               // imprime mensagem
    }
  }

  delay(100);
}
