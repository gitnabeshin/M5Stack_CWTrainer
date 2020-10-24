/**************************************************************************
 * M5Stack CW Trainer
 *
 *                                                        @author nabeshin
 ***************************************************************************/
#include <M5Stack.h>

#include "TrainerConfig.h"
#include "Mode.h"
#include "Decode.h"
#include "Encode.h"
#include "Lcd.h"
#include "WebIF.h"
#include "Train.h"


//Make a sound of Button Pressing
void M5LocalTone( int frequency ){
  M5.Speaker.tone(frequency, 100);
  delay(100);
  M5.Speaker.mute();
}

void execDecode(){

  int state = HIGH;

  if ( LCD_getInputMethod() == INPUT_M5_BTN_B ) {
    //M5 Stack Button input
    if(M5.BtnB.isPressed()) {
      state = LOW;
    }
  } else {
    //TELEGRAPH_KEY Pin input
    state = digitalRead( TELEGRAPH_KEY_GPIO );
  }

  //Make sound while it is pressed.
  if ( state == HIGH ) {
    M5.Speaker.mute();
  } else {
    M5.Speaker.tone(1000, 30);
    delay(30);
  }

  DECODE_execDecode(state);
}

void setup() {
  Serial.println("setup start.");
  M5.begin();
  M5.Power.begin();
  M5.Speaker.begin();

  //init TELEGRAPH_KEY GPIO pin
  pinMode( TELEGRAPH_KEY_GPIO, INPUT_PULLUP );

  //Don't call Serial.begin that is called in M5.begin().
  //Serial.begin( 115200 );

  //Initialize Wifi setting & Start WebServer
  WEBIF_setup_wifi();

  LCD_init();
  DECODE_init();
  ENCODE_init();
  TRAIN_init();

  //initial mode setting
  MODE_setCurrentMode(TRAIN_MODE);

  M5LocalTone(1000);

  //Show Startup Logo and begin decoding
  LCD_openDecode();

  Serial.println("Initialize done...");
}

void loop() {

  M5.update();
  //Handle HTTP Request
  WEBIF_handleClient();

  LCD_drawBatteryLevel(false);

  int isBtnA_pressed = M5.BtnA.wasPressed();

  switch ( MODE_getCurrentMode() ) {
    case DECODE_MODE:
    case TRAIN_MODE:
      if ( isBtnA_pressed ) {
        //When "Menu" button was Pressed
        //Switch to Menu Mode
        MODE_setCurrentMode(MENU_MODE);
        //Serial.println("-- Go To MENU MODE---");
        M5LocalTone(1319);

        //When switching to MENU mode from Lang "JP" mode, unload external Font.
        if( MODE_isJpMode() ) {
          M5.Lcd.unloadFont();
        }

        //Open Menu
        LCD_openMenu();
        delay(300);
      } else {
        if( M5.BtnC.wasPressed() ){
          if( DECODE_MODE == MODE_getCurrentMode() ){
            //In Decode Mode: "CLEAR" button was pressed
            //Clear text
            M5LocalTone(1200);
            LCD_resetAll();
          } else {
            //In Training Mode: "NEXT" button was pressed
            //Show next char
            M5LocalTone(1200);
            LCD_printNextChar();            
          }
        } else {
          //In DECODE/TRAIN Mode: BtnB or Telegraph key pressed
          //Decode Morse code
          execDecode();
         }
      }
      break;
    case MENU_MODE:
      if ( isBtnA_pressed ) {
        //In MENU Mode: "Save&Exit" Button pressed
        //Go back to Decode Mode
        MODE_setCurrentMode(DECODE_MODE);
        //Serial.println("-- Go To DECODE MODE---");
        M5LocalTone(1319);
        LCD_openDecode();

        //Load Japanese Font. It takes some time so display progress message.
        if( MODE_isJpMode() ) {
          M5.Lcd.setCursor(20, 160);
          M5.Lcd.print("Loading Font...");
          //Serial.println("Loading Font");
          M5.Lcd.loadFont(EXT_JP_FONT_DATA, SD);
          //M5.Lcd.unloadFont();
          M5LocalTone(1400);
          LCD_resetAll();
        }

        delay(300);
      } else {
        //BtnB or BtnC was pressed
        //Serial.println("--MENU MODE---");
        //Choose Menu
        LCD_main();
        delay(100);
      }
      break;
    default:
      break;
  }
}
