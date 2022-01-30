#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define BUTTON_PIN_I_B   0
#define BUTTON_PIN_I_M   1
#define BUTTON_PIN_I_A   A0
#define BUTTON_PIN_M     A5
#define BUTTON_PIN_D_B   4
#define BUTTON_PIN_D_M   5
#define BUTTON_PIN_D_A   6
#define BUTTON_PIN_ENTER   A1
#define PIXEL_PIN_I_B    7
#define PIXEL_PIN_I_M    8
#define PIXEL_PIN_I_A    9
#define PIXEL_PIN_M      10
#define PIXEL_PIN_D_B    11
#define PIXEL_PIN_D_M    12
#define PIXEL_PIN_D_A    13
#define PIXEL_COUNT 6 

Adafruit_NeoPixel strip[]={ 
Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN_I_B, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN_I_M, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN_I_A, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN_M, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN_D_B, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN_D_M, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN_D_A, NEO_GRB + NEO_KHZ800)};

LiquidCrystal_I2C lcd(0x27, 20, 4);

boolean oldState[8];
boolean newState[8];

int encendido=8;
int pulsado=9;
int puntuacion=0;
int T_Comuta=2;
int record=0;
int T_JUEGO=30;

unsigned long centyJUEGO= 0;
unsigned long centy= millis();
 
void setup() {

  //Serial.begin(9600);
  
  pinMode(BUTTON_PIN_I_B, INPUT_PULLUP);
  pinMode(BUTTON_PIN_I_M, INPUT_PULLUP);
  pinMode(BUTTON_PIN_I_A, INPUT_PULLUP);
  pinMode(BUTTON_PIN_M, INPUT_PULLUP);
  pinMode(BUTTON_PIN_D_B, INPUT_PULLUP);
  pinMode(BUTTON_PIN_D_M, INPUT_PULLUP);
  pinMode(BUTTON_PIN_D_A, INPUT_PULLUP);
  pinMode(BUTTON_PIN_ENTER, INPUT_PULLUP);

  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight
  
  for(int i=0;i<7;i++){
      strip[i].begin(); // Initialize NeoPixel strip object (REQUIRED)
      strip[i].show();  // Initialize all pixels to 'off'
    }
  INI();
}//ini

void loop() {
  
  //Timer de fin tiempo pulsacion 
  //Serial.println(puntuacion);      
      if(newState[3]!=oldState[3] || newState[7]!=oldState[7]){  //
        delay (20);                  //
        if(newState[3] == HIGH || newState[7] == HIGH){     //
          centyJUEGO=millis();
          //serial.println(pulsado); //
        }                            //
      }
      
    //--TIEMPO DE JUEGO--//
  centy= millis();
  while(centyJUEGO+(T_JUEGO*1000)>millis()){
    //--LOGICA JUEGO--//
  if((centy+(T_Comuta*1000))>millis()){


  ANTIREB();
  
      switch(pulsado) {           
        case 0:
        if(encendido==pulsado){
          puntuacion=puntuacion+5;
          APAGA();
          encendido=randon();    
          pulsado=9;              
        }else{
          puntuacion--;
          pulsado=9;  
        }
          break;
        case 1:
          if(encendido==pulsado){
            puntuacion=puntuacion+5;
            APAGA();
            encendido= randon();
            pulsado=9;                   
          }else{
            puntuacion--; 
            pulsado=9; 
          }
          break;
        case 2:
          if(encendido==pulsado){
            puntuacion=puntuacion+5;
            APAGA();
            encendido= randon();   
            pulsado=9;                
          }else{
            puntuacion--; 
            pulsado=9; 
          }
          break;
        case 3:
          if(encendido==pulsado){
            puntuacion=puntuacion+5;
            APAGA();
            encendido= randon(); 
            pulsado=9;                  
          }else{
            puntuacion--;    
            pulsado=9;  
          }
          break;
        case 4:
          if(encendido==pulsado){
            puntuacion=puntuacion+5;
            APAGA();
            encendido= randon();  
            pulsado=9;                 
          }else{
            puntuacion--; 
            pulsado=9;     
          }
          break;
        case 5:
          if(encendido==pulsado){
            puntuacion=puntuacion+5;
            APAGA();
            encendido= randon(); 
            pulsado=9;                  
          }else{
            puntuacion--; 
            pulsado=9;            
          }
          break;
        case 6:
          if(encendido==pulsado){
            puntuacion=puntuacion+5;
            APAGA();
            encendido= randon();
            pulsado=9;                   
          }else{
            puntuacion--;
            pulsado=9;             
          }
          break;
        case 9:
          break;
        default:
          APAGA();
          encendido= randon();
          pulsado=9; 
          break;
        }
  }else{ 
    APAGA();
    encendido= randon();
    //Serial.println(encendido);
  }//if((centy+2000)>millis())
  delay(20);
  
 /////////////////
 ACTUALIZA();   //
 SONDEO();      //
 ActualizaLCD();//
 /////////////////

 //--LOGICA JUEGO--//
 
  }//while(TIEMPO DE JUEGO)
  APAGA();
//--TIEMPO DE JUEGO--//
  if(record<puntuacion){
    record=puntuacion;    
  }
 puntuacion=0;
 ACTUALIZA();   //
 SONDEO();
 ActualizaLCD();
 }//loop


//---------------------------------------------------//
int randon(){
  
  int R= random(0,7);
  //Serial.println(R);

      switch(R) {           
        case 0:
            for(int i=0; i<6; i++) { // For each pixel in strip...
              strip[0].setPixelColor(i, 0,255,100);         //  Set pixel's color (in RAM)
              strip[0].show();                          //  Update strip to match
              delay(1); //  Pause for a moment
            }//for
            return R;
        break;
        case 1:
            for(int i=0; i<6; i++) { // For each pixel in strip...
              strip[1].setPixelColor(i, 0,255,100);         //  Set pixel's color (in RAM)
              strip[1].show();                          //  Update strip to match
              delay(1); 
            }//for
            return R;//  Pause for a moment
        break;        
        case 2:
            for(int i=0; i<6; i++) { // For each pixel in strip...
              strip[2].setPixelColor(i, 0,255,100);         //  Set pixel's color (in RAM)
              strip[2].show();                          //  Update strip to match
              delay(1); 
            }//for
            return R;//  Pause for a moment
        break;
        case 3:
            for(int i=0; i<6; i++) { // For each pixel in strip...
              strip[3].setPixelColor(i, 0,255,100);         //  Set pixel's color (in RAM)
              strip[3].show();                          //  Update strip to match
              delay(1);    
            }//for
            return R;//  Pause for a moment
        break;
        case 4:
            for(int i=0; i<6; i++) { // For each pixel in strip...
              strip[4].setPixelColor(i, 0,255,100);         //  Set pixel's color (in RAM)
              strip[4].show();                          //  Update strip to match
              delay(1);
            }//for
            return R;//  Pause for a moment
        break;
        case 5:
            for(int i=0; i<6; i++) { // For each pixel in strip...
              strip[5].setPixelColor(i, 0,255,100);         //  Set pixel's color (in RAM)
              strip[5].show();                          //  Update strip to match
              delay(1);
            }//for
            return R;//  Pause for a moment
            break;
        case 6:
            for(int i=0; i<6; i++) { // For each pixel in strip...
              strip[6].setPixelColor(i, 0,255,100);         //  Set pixel's color (in RAM)
              strip[6].show();                          //  Update strip to match
              delay(1);                           //  Pause for a moment
            }//for
            return R;
        break;
 
  }}
//---------------------------------------------------//
  void APAGA(){
    for(int j=0; j<7;j++){
    for(int i=0; i<6; i++) { // For each pixel in strip...
       strip[j].setPixelColor(i, 0,0,0);         //  Set pixel's color (in RAM)
       strip[j].show();                          //  Update strip to match
       delay(1);                           //  Pause for a moment
    }//for
    }
    centy=millis();
  }
//---------------------------------------------------//

  void ANTIREB(){
   for(int i=0; i<7;i++){       
      /*Serial.print(oldState[i]);   //
      Serial.print(" ");             //
      Serial.println(newState[i]);*/ //
      if(newState[i]!=oldState[i]){  //
        delay (20);                  //
        if(newState[i] == HIGH){     //
          pulsado=i;                 //
          //serial.println(pulsado); //
        }                            //
      }                              //
    }  
    }
//---------------------------------------------------//
  void SONDEO(){
    
  newState[0] = digitalRead(BUTTON_PIN_I_B);
  newState[1] = digitalRead(BUTTON_PIN_I_M);
  newState[2] = digitalRead(BUTTON_PIN_I_A);
  newState[3] = digitalRead(BUTTON_PIN_M);
  newState[4] = digitalRead(BUTTON_PIN_D_B);
  newState[5] = digitalRead(BUTTON_PIN_D_M);
  newState[6] = digitalRead(BUTTON_PIN_D_A);  
  newState[7] = digitalRead(BUTTON_PIN_ENTER); 
    }
//---------------------------------------------------//
  void ACTUALIZA(){
    for(int i=0; i<8; i++){
      /*Serial.print(oldState[i]);
      Serial.print(" ");
      Serial.println(newState[i]);*/
      oldState[i] = newState[i];
    }  
  }
//---------------------------------------------------//
  void INI(){
    for(int j=0; j<7;j++){
    for(int i=0; i<6; i++) { // For each pixel in strip...
       strip[j].setPixelColor(i, 255,0,0);         //  Set pixel's color (in RAM)
       strip[j].show();                          //  Update strip to match
       delay(1);                           //  Pause for a moment
    }//for
    delay(500);
    }
    delay(500);
    APAGA();   
    }
//----------------------------------------------------//
    void ActualizaLCD(){
      delay(100);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Record: ");
      lcd.print(record, DEC);
      lcd.setCursor(0,2);
      lcd.print("Puntuacion: ");
      lcd.print(puntuacion, DEC);
    }
