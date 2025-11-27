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
      if (range_max != RANGE_MAX_NUMBER && range_min !== RANGE_MIN_NUMBER)
      {
        random_num = random(range_min, range_max + 1);
        generator_mode = GENERATOR_STARTED;
        animation_mode = ANIMATION_STARTED;
      }
      
      break;
    case GENERATOR_STARTED:
      // interromper animacoes e mudar estado resetar os valores max e min e setar o estado de para RANGE_NOT_SET
      generator_mode = GENERATOR_STOPPED;
      animation_mode = ANIMATION_STOPPED;
      led_mode = LED_MODE_OFF;
      range_status_set_max = RANGE_NOT_SET;
      range_status_set_min = RANGE_NOT_SET;
      range_max = RANGE_MAX_NUMBER;
      range_min = RANGE_MIN_NUMBER;
      current_num = 0;
      
      MFS.write("off");
      MFS.writeLeds(LED_ALL, OFF);   
      
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // encerrar estado de config, voltar para estado GENERATOR_STOPPED e, se valido: mudar para RANGE_SET, acender LED 1
      generator_mode = GENERATOR_STOPPED;
      MFS.writeLeds(LED_1, ON);
      range_status_set_max = RANGE_SET;
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // encerrar estado de config, voltar para estado GENERATOR_STOPPED e, se valido: mudar para RANGE_SET, acender LED 2
      generator_mode = GENERATOR_STOPPED;
      MFS.writeLeds(LED_2, ON);
      range_status_set_min = RANGE_SET;
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
      MFS.write(range_max);
      break;
    case GENERATOR_STARTED:
      // nada
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // incrementar em 100 unidades o valor maximo e mostrar no display
      range_max += 100;
      if (range_max > 9999)
      {
        range_max -= 100;
      }

      MFS.write(range_max);
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // incrementar em 100 unidades o valor minimo e mostrar no display
      range_min += 100;
      if (range_min > 9900 || range_min > range_max)
      {
        range_min -= 100;
      }
      MFS.write(range_min);
      break;
  }
}

void button2long() {
  switch (generator_mode){
    case GENERATOR_STOPPED:
      // mudar para estado de configuracao de max
      generator_mode = SETTING_RANGE_MAX_NUM_STARTED;
      break;
    case GENERATOR_STARTED:
      // nada
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // incrementar em 100 unidades o valor maximo e mostrar no display
      range_max += 100;
      if (range_max > 9999)
      {
        range_max -= 100;
      }

      MFS.write(range_max);
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // incrementar em 100 unidades o valor minimo e mostrar no display
      range_min += 100;
      if (range_min > 9900 || range_min > range_max)
      {
        range_min -= 100;
      }
      MFS.write(range_min);
      break;
  }
}

void button3short() {
  switch (generator_mode){
    case GENERATOR_STOPPED:
      // mostrar min
      MFS.write(range_min);
      break;
    case GENERATOR_STARTED:
      // nada
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // decrementar em 100 unidades o valor maximo e mostrar no display
      range_max -= 100;
      if (range_max < 99 || range_max < range_min)
      {
        range_max += 100;
      }
      MFS.write(range_max);
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // decrementar em 100 unidades o valor minimo e mostrar no display
      range_min -= 100;
      if (range_min < 0)
      {
        range_min += 100;
      }
      MFS.write(range_min);
      break;
  }
}

void button3long() {
  switch (generator_mode){
    case GENERATOR_STOPPED:
      // mudar para estado de configurar min
      generator_mode = SETTING_RANGE_MIN_NUM_STARTED;
      break;
    case GENERATOR_STARTED:
      // nada
      break;
    case SETTING_RANGE_MAX_NUM_STARTED:
      // decrementar em 100 unidades o valor maximo e mostrar no display
      range_max -= 100;
      if (range_max < 99 || range_max < range_min)
      {
        range_max += 100;
      }
      MFS.write(range_max);
      break;
    case SETTING_RANGE_MIN_NUM_STARTED:
      // decrementar em 100 unidades o valor minimo e mostrar no display
      range_min -= 100;
      if (range_min < 0)
      {
        range_min += 100;
      }
      MFS.write(range_min);
      break;
  }
}



GeneratorModeValues generator_mode;
RangeStatusValues range_status_set_max;
RangeStatusValues range_status_set_min;
int range_max;
int range_min;
ledModeValues led_mode;
AnimationModeValues animation_mode;

int random_num;
int current_num;

void setup() {
  generator_mode = GENERATOR_STOPPED;
  range_status_set_max = RANGE_NOT_SET;
  range_status_set_min = RANGE_NOT_SET;
  range_max = RANGE_MAX_NUMBER;
  range_min = RANGE_MIN_NUMBER;
  led_mode = LED_ALL_OFF;
  animation_mode = ANIMATION_STOPPED;

  current_num = 0;
  
  Timer1.initialize();
  MFS.initialize(&Timer1);                 
  MFS.write("off");
  MFS.writeLeds(LED_ALL, OFF);             

  Serial.begin(9600);

  randomSeed(123);
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
      Serial.println("SOLTA RAPIDO");  
      
      switch (buttonNumber + '0') 
      {
        case '1':
          button1short();
          break;
        case '2':
          button2short();
          break;
        case '3':
          button3short();
          break;
        
      }                  // imprime mensagem
    }
    else if (buttonAction == BUTTON_LONG_PRESSED_IND)    // compara o evento do botão
    {
      Serial.println("PRESSIONADO LONGO"); 

      switch (buttonNumber + '0') 
      {
        case '1':
          button1long();
          break;
        case '2':
          button2long();
          break;
        case '3':
          button3long();
          break;
        
      }                 // imprime mensagem
    }
  }

  if (generator_mode == GENERATOR_STARTED)
  { 
    if (animation_mode == ANIMATION_STARTED){
      // acabou de começar a animação
      MFS.writeLeds(LED_ALL, OFF);
      animation_mode = ANIMATION_STAGE1;
    }
    else if (animation_mode == ANIMATION_STOPPED)
    {
      // acabou
      MFS.writeLeds(LED_ALL, OFF);
      led_mode = LED_ALL_OFF
      // os displays de 7 segmentos devem piscar
      MFS.blinkDisplay(DIGIT_ALL, ON);
      // tocar três beeps longos de 500 ms intercalados por um silêncio de 500 ms.
      MFS.beep(50,     // Define um bip de 500 ms (50 unidades de 10ms)
              50,      // Define um silencio de 500 ms (50 unidades de 10ms)
              3,       // Define o loop de reprodução do bip (3 vezes)
              1,       // Define a quantidade de execuções do loop (1 vezes)
              0);      // Define o tempo de espera entre os loops (0 ms)
                                  
      delay(3000);     // espera de 3 segundos (3000 ms)
      //MFS.blinkDisplay(DIGIT_ALL, OFF);
      continue;
    }
    if (current_num == 10)
    {
      // atualiza um novo numero no display
      switch (animation_mode)
      {
        case ANIMATION_STAGE1:
          animation_mode = ANIMATION_STAGE2;
          break;
        case ANIMATION_STAGE2:
          animation_mode = ANIMATION_STAGE3;
          break;
        case ANIMATION_STAGE3:
          animation_mode = ANIMATION_STAGE4;
          break;
        case ANIMATION_STAGE4:
          animation_mode = ANIMATION_STOPPED;
          break;
      }

      current_num = 0;
    }
    
    switch (animation_mode)
    {
      case ANIMATION_STAGE1:
        MFS.write(sprintf("%04d", current_num * 1111));
        break;
      case ANIMATION_STAGE2:
        MFS.write(sprintf("%04d", current_num * 1110 + random_num % 10));
        break;
      case ANIMATION_STAGE3:
        MFS.write(sprintf("%04d", current_num * 1100 + random_num % 100));
        break;
      case ANIMATION_STAGE4:
        MFS.write(sprintf("%04d", current_num * 1000 + random_num % 1000));
        break;
    }  
    current_num++;   
     

    switch (led_mode)
    {
      case LED_ALL_OFF:
        // acabou de começar a animação
        MFS.writeLeds(LED_1, ON);
        led_mode = LED_1_ON;
        break;
      case LED_1_ON:
        MFS.writeLeds(LED_1, OFF);
        MFS.writeLeds(LED_2, ON);
        led_mode = LED_2_ON;
        break;
      case LED_2_ON:
        MFS.writeLeds(LED_2, OFF);
        MFS.writeLeds(LED_3, ON);
        led_mode = LED_3_ON;
        break;
      case LED_3_ON:
        MFS.writeLeds(LED_3, OFF);
        MFS.writeLeds(LED_4, ON);
        led_mode = LED_4_ON;
        break;
      case LED_4_ON:
        MFS.writeLeds(LED_3, OFF);
        MFS.writeLeds(LED_1, ON);
        led_mode = LED_1_ON;
        break;
    }
  }
}
