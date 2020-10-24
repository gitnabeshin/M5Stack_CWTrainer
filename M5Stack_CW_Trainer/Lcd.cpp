/**************************************************************************
 * LCD display Control
 *
 *************************************************************************/
#include <M5Stack.h>
#include <Arduino.h>

#include "TrainerConfig.h"
#include "Lcd.h"
#include "Decode.h"
#include "Mode.h"
#include "Train.h"
#include "WebIF.h"

#define BACK_COLOR_DECODE   TFT_BLACK   //Background color of decoding area
#define BACK_COLOR_TRAIN    TFT_OLIVE   //Background color of training area
#define BACK_COLOR_MENU     TFT_NAVY    //Background color of menu area

#define TEXT_COLOR_BUTTON   ORANGE      //Lavel color of M5 button ABC

#define NORMAL_TEXT_SIZE    (2)
#define COMFIRM_TEXT_SIZE   (3)
#define M5_TFT_WIDTH        (319)       //0-319
#define M5_TFT_HEIGHT       (239)       //0-239
#define TRAINING_BORDER_Y   (100)       //Border y of training area
#define MAX_MENU_INDEX      (6)         //Max number of Menu item
#define MENU_START_X        (4)         //1st line x of menu item
#define MENU_START_Y        (26)        //1st line y of menu item
#define MENU_2ND_Y          MENU_START_Y + 22  //2nd line y of menu item
#define STR_START_Y_TRAIN   (156)       //Start line y of Training mode
#define STR_START_Y_DECODE  (50)        //Start line y of Free decoding mode

typedef enum MENU_ITEM {
  MENU_SELECT,            //0: Select Menu item
  MENU_LANG,              //1: Select Language
  MENU_TRAINING,          //2: Select entering to TRAINING MODE
  MENU_INTERVAL,          //3: Select interval time of dot period
  MENU_INPUT_METHOD,      //4: Select Input Method
  MENU_ENCODE_URL,        //5: Show Web I/F URL
  MENU_OFF,               //6: POWER OFF
  MENU_NONE,
} MENU_ITEM_T;

//Labels of Menu
String menu[] = {
  "MENU (1-6)",            //0
  "1. LANGUAGE [0-1]",     //1
  "2. TRAINING MODE",      //2
  "3. DECODE CYCLE (ms)",  //3
  "4. INPUT METHOD [0-1]", //4
  "5. WEB I/F URL",        //5
  "6. POWER OFF",          //6
};

MENU_ITEM_T menuItem;             //current mode
MENU_ITEM_T tmpMenuItem;          //selecting parameter in menu
MENU_ITEM_T preMenuItem;          //preSelecting mode in menu loop
INPUT_METHOD_T inputMethod;       //current input method
INPUT_METHOD_T tmpInputMethod;    //selecting parameter in menu
bool tmpIsJapanese      = false;  //selecting parameter in menu
int  tmpDotInterval     = 0;      //selecting parameter in menu
bool tmpIsTrainingMode  = true;   //selecting parameter in menu
bool isTrainingMode     = true;
bool isPowerOffSelected = false;

int batteryLevel    = 0;
int preBatteryLevel = -1;

int mIndex1  = 0;       //Current index of Menu item

void LCD_init() {
  menuItem           = MENU_SELECT;
  preMenuItem        = MENU_SELECT;
  inputMethod        = DEFAULT_INPUT_METHOD;
  isTrainingMode     = true;
  isPowerOffSelected = false;
}

//print startup message
void printStartupLogo() {
  M5.Lcd.fillScreen(BACK_COLOR_DECODE);

  M5.Lcd.setCursor(120, 40);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(7);
  M5.Lcd.print("M5");

  M5.Lcd.setTextSize(5);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(20, 130);
  M5.Lcd.print("CW Trainer"); 
}

//print poweroff message
void printPowerOff() {
  M5.Lcd.fillScreen(BACK_COLOR_DECODE);

  M5.Lcd.setCursor(20, 200);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("Power Off.");
  delay(800);
  M5.Lcd.print(".");
  delay(800);
  M5.Lcd.print(".");
  delay(800);
  M5.Lcd.print(".");
  delay(800);
}

//draw M5 battery level object
void LCD_drawBatteryLevel( bool fForceDisp ){

  int batteryLevel = M5.Power.getBatteryLevel();

  if( preBatteryLevel != batteryLevel || fForceDisp ){
    //Draw battery object in upper right side
    // ------------------------
    // x:280 to 320, y:0 to 16
    // ------------------------

    //battery head
    M5.Lcd.fillRect( 280-4, 4, 4, 8, WHITE );
    //battery body
    M5.Lcd.fillRoundRect( 280, 0, 40, 16, 2, WHITE );
    M5.Lcd.drawRect( 282, 2, 36, 12, BLACK );

    //capacity width = 318 - 282; //36
    int width = 36 - ( 36 * batteryLevel / 100 );
    M5.Lcd.fillRect( 282, 2, width, 12, BLACK );
  }
  preBatteryLevel = batteryLevel;
}

//print app name in top line
void printFirstLine() {
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.setTextColor(LIGHTGREY);
  M5.Lcd.print( "M5 CW Trainer" );
  if( WEBIF_isEnable() ) {
    M5.Lcd.setCursor(225, 1);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print( "WiFi" );   
  }
  LCD_drawBatteryLevel(true); 
}

//print Header of [Training/Free decode] mode
void printDecodeHeader() {
  printFirstLine();
  if( TRAIN_MODE == MODE_getCurrentMode() ){

    //Reference field
    M5.Lcd.setCursor(10, 25 + 1);
    if ( MODE_isJpMode() ) {
      M5.Lcd.fillRoundRect(0, 23, 120, 16 + 20, 8, RED);
      M5.Lcd.fillRoundRect(0, 40, M5_TFT_WIDTH, TRAINING_BORDER_Y -37, 8, RED);
      M5.Lcd.print( "Japanese" );
    } else {
      M5.Lcd.fillRoundRect(0, 23, 120, 16 + 20, 8, BLUE);
      M5.Lcd.fillRoundRect(0, 40, M5_TFT_WIDTH, TRAINING_BORDER_Y -37, 8, BLUE);
      M5.Lcd.print( "English" );
    }
    M5.Lcd.fillRect(10, 45, 36, 54, BACK_COLOR_DECODE);
    M5.Lcd.fillRect(48, 45, M5_TFT_WIDTH -48 -15, 54, BACK_COLOR_DECODE);

    //Decode field(60,110)
    M5.Lcd.fillRoundRect(0, 110, M5_TFT_WIDTH, 40, 8, WHITE);
    M5.Lcd.fillRect(10, 110 +4, M5_TFT_WIDTH -10 -15, 40 -8, BACK_COLOR_DECODE);
    
  } 
  M5.Lcd.setTextColor(WHITE);
}

//print Header of [Menu] mode
void printMenuHeader() {
  printFirstLine();
  //Menu mode outline
  M5.Lcd.drawRoundRect(0, 22, M5_TFT_WIDTH, M5_TFT_HEIGHT -23 -22, 3, LIGHTGREY);
  M5.Lcd.setTextColor(WHITE);
}

//print Button Label for each Mode
void printLastLine() {

  M5.Lcd.setTextSize(NORMAL_TEXT_SIZE);
  M5.Lcd.setTextColor(TEXT_COLOR_BUTTON);
  int startTextPositionY = M5_TFT_HEIGHT - 20; //Last line

  switch ( MODE_getCurrentMode() ) {
    case MENU_MODE:
      //left button label
      M5.Lcd.setCursor(  10, startTextPositionY );
      M5.Lcd.print( "SAVE&EXT" );
      //middle button label
      M5.Lcd.setCursor( 125, startTextPositionY );
      M5.Lcd.print( "SCROLL" );
      //right button label
      M5.Lcd.setCursor( 225, startTextPositionY );
      M5.Lcd.print( " OK" ); 
      break;
    case DECODE_MODE:
      //left button label
      M5.Lcd.setCursor(  44, startTextPositionY );
      M5.Lcd.print( "MENU" );
      //middle button label
      M5.Lcd.setCursor( 125, startTextPositionY );
      if ( inputMethod == INPUT_M5_BTN_B ) {
        //Button Image
        M5.Lcd.fillRoundRect(145, M5_TFT_HEIGHT -18, 35, 16, 10, YELLOW);
      } else {
        M5.Lcd.print( "  --" );
      }
      //right button label
      M5.Lcd.setCursor( 225, startTextPositionY );
      M5.Lcd.print( "CLEAR" );
      break;
    case TRAIN_MODE:
      //left button label
      M5.Lcd.setCursor(  44, startTextPositionY);
      M5.Lcd.print( "MENU" );
      //middle button label
      M5.Lcd.setCursor( 125, startTextPositionY );
      if ( inputMethod == INPUT_M5_BTN_B ) {
        //Button Image
        M5.Lcd.fillRoundRect(145, M5_TFT_HEIGHT -18, 35, 16, 10, YELLOW);
      } else {
        //Telegraph Key
        M5.Lcd.print( "  --" );
      }
      //right button label
      M5.Lcd.setCursor( 225, startTextPositionY );
      M5.Lcd.print( "NEXT " );
      break;
    default:
      break;
  }

  M5.Lcd.setTextColor(WHITE);
}

//check whether "Scroll" Button was pressed
int wasScrollPressed() {
  if ( M5.BtnB.wasPressed() ) {
    //Serial.println("BUTTON_SCROLL");
    M5.Speaker.tone(1200, 100);
    delay(100);
    M5.Speaker.mute();
    return true;
  }
  return false;
}

//check whether "Select" Button wad pressed
int wasSelectPressed() {
  if ( M5.BtnC.wasPressed() ) {
    //Serial.println("BUTTON_SELECT");
    M5.Speaker.tone(1200, 100);
    delay(100);
    M5.Speaker.mute();
    return true;
  }
  return false;
}

//switch to the [Menu] Mode
void LCD_openMenu() {
  //Initial parameters
  menuItem          = MENU_SELECT;
  tmpMenuItem       = MENU_SELECT;
  tmpIsJapanese     = MODE_isJpMode();
  tmpDotInterval    = DECODE_getInterval();
  tmpInputMethod    = inputMethod;
  tmpIsTrainingMode = isTrainingMode;
  mIndex1           = 0;

  M5.Lcd.fillScreen(BACK_COLOR_MENU);
  printMenuHeader();
  printLastLine();
  M5.Lcd.setCursor(MENU_START_X, MENU_START_Y);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print( menu[ mIndex1 ] );
}

//switch to the [Training/Free decode] Mode
void LCD_openDecode() {

  //Serial.println("LCD_openDecode");
  printStartupLogo();
  delay( 1500 );

  M5.Speaker.tone(700, 180);
  delay(180);
  M5.Speaker.tone(1047, 100);
  delay(100);
  M5.Speaker.mute();

  if(isTrainingMode){
    MODE_setCurrentMode(TRAIN_MODE); //switch to train mode  
  }

  M5.Lcd.fillScreen(BACK_COLOR_DECODE); 
  printLastLine();

  printDecodeHeader();
  if( TRAIN_MODE == MODE_getCurrentMode() ){
    M5.Lcd.setCursor( 0, STR_START_Y_TRAIN ); //Start line of Training Mode
    TRAIN_init();
  } else {
    M5.Lcd.setCursor( 0, STR_START_Y_DECODE ); //Start line of Free decode Mode
  }
}

//Clear menu attribute value field
void clearTmpMenuAttribute() {
  M5.Lcd.fillRect(MENU_START_X, MENU_2ND_Y , M5_TFT_WIDTH - MENU_START_X -2, 60, BACK_COLOR_MENU);
  M5.Lcd.setCursor(MENU_START_X, MENU_2ND_Y );
}

//Clear confirm message field
void clearConfirmField() {
  M5.Lcd.fillRect(20, 110, M5_TFT_WIDTH -24, 50, BACK_COLOR_MENU);
}

// [MENU_LANG]
//   Select Language [Japanese/English].
void selectLang() {

  //Show tmpValue
  M5.Lcd.setCursor(MENU_START_X, MENU_2ND_Y );
  if ( tmpIsJapanese ) {
    M5.Lcd.print( "   [0] Japanese" );
  } else {
    M5.Lcd.print( "   [1] English " );
  }

  //SCROLL
  if( wasScrollPressed() ){
    if ( tmpIsJapanese ) {
      //switch to English
      tmpIsJapanese = false;

      //clear
      clearTmpMenuAttribute();
      M5.Lcd.print( "   [1] English " );

    } else {
      //switch to Japanese
      tmpIsJapanese = true;

      //clear
      clearTmpMenuAttribute();
      M5.Lcd.print( "   [0] Japanese" );
    }
  }

  //SELECT
  if( wasSelectPressed() ){
    //clear
    M5.Lcd.setCursor(20, 110);
    clearConfirmField();

    //Confirm
    M5.Lcd.setTextSize(COMFIRM_TEXT_SIZE);
    M5.Lcd.setTextColor(RED);
    if ( tmpIsJapanese ) {
      MODE_setJpMode();
      M5.Lcd.print("-> Japanese");
    } else {
      MODE_setEnglishMode();
      M5.Lcd.print("-> English");
    }
  }
}

// [MENU_TRAINING]
//   Select entering to Training mode
void selectTrainingMode() {

  //Show tmpValue
  M5.Lcd.setCursor(MENU_START_X, MENU_2ND_Y );
  if ( tmpIsTrainingMode == true ) {
    M5.Lcd.print(  "   [0] Training Mode" );
  } else {
    M5.Lcd.printf( "   [1] Free Mode" );
  }

  //SCROLL
  if( wasScrollPressed() ){
    if ( tmpIsTrainingMode == true ) {
      //switch to 1:Normal Mode
      tmpIsTrainingMode = false;

      //overwrite text
      clearTmpMenuAttribute();
      M5.Lcd.print( "   [1] Free Mode" );

    } else {
      //switch to 0:Training Mode
      tmpIsTrainingMode = true;

      //overwrite text
      clearTmpMenuAttribute();
      M5.Lcd.print( "   [0] Training Mode" );
    }
  }

  //SELECT
  if( wasSelectPressed() ){
    //clear
    M5.Lcd.setCursor(20, 110);
    clearConfirmField();

    //Confirm
    M5.Lcd.setTextSize(COMFIRM_TEXT_SIZE);
    M5.Lcd.setTextColor(RED);
    if ( tmpIsTrainingMode == true ) {
      M5.Lcd.print("-> Training Mode");
    } else {
      M5.Lcd.print("-> Free Mode");
    }
    isTrainingMode = tmpIsTrainingMode;
  }
}

// [MENU_INTERVAL]
//   Select interval time of dot period.
void selectInterval() {

  //Show tmpValue
  clearTmpMenuAttribute();
  M5.Lcd.printf("  %d ms", tmpDotInterval );
  
  //SCROLL
  if( wasScrollPressed() ){
    //increase interval period
    tmpDotInterval = tmpDotInterval + 10;
    clearTmpMenuAttribute();
    M5.Lcd.printf("  %d ms", tmpDotInterval );
  }

  //SELECT
  if( wasSelectPressed() ){
    DECODE_setInterval(tmpDotInterval);
    M5.Lcd.setTextSize(COMFIRM_TEXT_SIZE);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setCursor(20, 110);
    clearConfirmField();
    M5.Lcd.printf("-> %d ms", tmpDotInterval);
  }
}

// [MENU_INPUT_METHOD]
//   Select input method [0:M5 Button / 1:Telegraph key]
void selectInputMethod() {

  //Show tmpValue
  M5.Lcd.setCursor(MENU_START_X, MENU_2ND_Y );
  if ( tmpInputMethod == INPUT_M5_BTN_B ) {
    M5.Lcd.print(  "   [0] M5 Button B" );
  } else {
    M5.Lcd.print( "   [1] Telegraph key:" );
    M5.Lcd.setTextColor(RED);
    M5.Lcd.printf( "G%d", TELEGRAPH_KEY_GPIO );
    M5.Lcd.setTextColor(WHITE);
  }

  //SCROLL
  if( wasScrollPressed() ){
    if ( tmpInputMethod == INPUT_M5_BTN_B ) {
      //switch to 1:Telegraph Key
      tmpInputMethod = INPUT_TELEGRAPH_KEY;

      //overwrite text
      clearTmpMenuAttribute();
      M5.Lcd.print( "   [1] Telegraph key" );
    } else {

      //switch to 0:M5BtnB
      tmpInputMethod = INPUT_M5_BTN_B;

      //overwrite text
      clearTmpMenuAttribute();
      M5.Lcd.print( "   [0] M5 Button B" );
    }
  }

  //SELECT
  if( wasSelectPressed() ){
    //clear
    M5.Lcd.setCursor(20, 110);
    clearConfirmField();

    //Confirm
    M5.Lcd.setTextSize(COMFIRM_TEXT_SIZE);
    M5.Lcd.setTextColor(RED);
    if ( tmpInputMethod == INPUT_M5_BTN_B ) {
      M5.Lcd.print("-> M5 Button B");
    } else {
      M5.Lcd.print("-> Telegraph key");
    }
    inputMethod = tmpInputMethod;
  }
}

// [MENU_ENCODE_URL]
//   Show web I/F informations
void showEncodeURL() {

  if( preMenuItem != tmpMenuItem ) {
    M5.Lcd.setCursor(0, MENU_2ND_Y );
    M5.Lcd.printf(  "   SSID:%s\n", TRAINER_SSID );
    M5.Lcd.println( "   PASS:*****" );
    //M5.Lcd.printf( "PASS:%s", TRAINER_PASS );
    M5.Lcd.qrcode( TRAINER_URL, 100, 80, 130, 6);
  }

  //SELECT
  if( wasSelectPressed() ){
    LCD_openMenu();
  }
  preMenuItem = tmpMenuItem;
}

// [MENU_POWER_OFF]
//   Power off
void selectPowerOff() {

  //Show tmpValue
  M5.Lcd.setCursor(MENU_START_X, MENU_2ND_Y );
  if ( isPowerOffSelected ) {
    M5.Lcd.print(  "   [0] Power Off" );
  } else {
    M5.Lcd.printf( "   [1] Continue" );
  }

  //SCROLL
  if( wasScrollPressed() ){
    if ( isPowerOffSelected ) {
      isPowerOffSelected = false;
      clearTmpMenuAttribute();
      M5.Lcd.print( "   [1] Continue" );

    } else {
      isPowerOffSelected = true;
      clearTmpMenuAttribute();
      M5.Lcd.print( "   [0] Power Off" );
    }
  }

  //SELECT
  if( wasSelectPressed() ){
    //clear
    M5.Lcd.setCursor(20, 110);
    clearConfirmField();

    if ( isPowerOffSelected ) {
      printPowerOff();
      M5.Power.powerOFF();
    }
  }
}

// [MENU_SELECT]
//    Select Menu items
void selectMenu() {

  //SCROLL
  if( wasScrollPressed() ){

    if ( mIndex1 + 1 > MAX_MENU_INDEX ) {
      mIndex1 = 0;
    } else {
      mIndex1++;
    }

    //tmpモード切り替え
    switch ( mIndex1 ) {
      case 0:
        tmpMenuItem = MENU_SELECT;
        break;
      case 1:
        tmpMenuItem = MENU_LANG;
        break;
      case 2:
        tmpMenuItem = MENU_TRAINING;
        break;
      case 3:
        tmpMenuItem = MENU_INTERVAL;
        break;
      case 4:
        tmpMenuItem = MENU_INPUT_METHOD;
        break;
      case 5:
        tmpMenuItem = MENU_ENCODE_URL;
        break;
      case 6:
        tmpMenuItem = MENU_OFF;
        break;
      default:
        break;
    }

    //overwrite Menu text
    M5.Lcd.fillRect(MENU_START_X, MENU_START_Y, M5_TFT_WIDTH - MENU_START_X -2, 40, BACK_COLOR_MENU );
    M5.Lcd.setCursor(MENU_START_X, MENU_START_Y);
    M5.Lcd.println( menu[ mIndex1 ] );
  }

  //SELECT
  if( wasSelectPressed() ){
    menuItem = tmpMenuItem;
  }
}

//Print an Ascii character
void LCD_printAscii(int asciiNumber) {
  M5.Lcd.printf( "%c", asciiNumber );
  if( TRAIN_MODE == MODE_getCurrentMode() && TRAIN_isMatchedEn( (char)asciiNumber ) ) {
    M5.Speaker.tone(800, 100);
    delay(100);
    M5.Speaker.tone(1000, 100);
    delay(200);
    M5.Speaker.mute();
    delay(300);
    LCD_printNextChar();
  }  
}

//Print a Japanese Kana character
void LCD_printJp(String str){
  M5.Lcd.print( str );
  if( TRAIN_MODE == MODE_getCurrentMode() && TRAIN_isMatchedJp( str ) ) {
    M5.Speaker.tone(800, 100);
    delay(100);
    M5.Speaker.tone(1000, 100);
    delay(200);
    M5.Speaker.mute();
    delay(300);
    LCD_printNextChar();
  } 
}

//Clear input characters
void LCD_resetAll() {
  //Keep Firstline, Lastline area
  if( TRAIN_MODE == MODE_getCurrentMode() ){
    //Clear Decode Field
    M5.Lcd.fillRect(10, 110 +4, M5_TFT_WIDTH -10 -15, 40 -8, BACK_COLOR_DECODE);    //clear object
    M5.Lcd.fillRect(0, STR_START_Y_TRAIN -1, M5_TFT_WIDTH, M5_TFT_HEIGHT -STR_START_Y_TRAIN -40, BACK_COLOR_DECODE);  //clear string
    M5.Lcd.setCursor( 0, STR_START_Y_TRAIN ); //Start line of Training Mode
  } else {
    //Clear Decode Field
    M5.Lcd.fillRect(0, 16, M5_TFT_WIDTH, M5_TFT_HEIGHT -40, BACK_COLOR_DECODE);     //clear string
    M5.Lcd.setCursor( 0, STR_START_Y_DECODE ); //Start line of Free decode Mode
  }
}

//Print Next training character
void LCD_printNextChar() {
  //Clear
  LCD_resetAll();
  //Reference field
  M5.Lcd.fillRect(10, 45, 36, 54, BACK_COLOR_DECODE); //Clear string
  M5.Lcd.fillRect(48, 45, M5_TFT_WIDTH - 48 - 15, 54, BACK_COLOR_DECODE); //Clear object

  //printNext
  TRAIN_printNextChar();
  M5.Lcd.setCursor( 0, STR_START_Y_TRAIN ); //Start line of Training Mode
}

//Get Current Input Method
INPUT_METHOD_T LCD_getInputMethod() {
  return inputMethod;
}

//Main menu control
void LCD_main() {

  //defalut setting
  M5.Lcd.setTextSize( NORMAL_TEXT_SIZE );
  M5.Lcd.setTextColor( WHITE );

  switch ( menuItem ) {
    case MENU_SELECT:
      //Serial.println("    --MENU SELECT---");
      selectMenu();
      break;
    case MENU_LANG:
      //Serial.println("    --MENU LANG---");
      selectLang();
      break;
    case MENU_TRAINING:
      //Serial.println("    --MENU TRAINING---");
      selectTrainingMode();
      break;   
    case MENU_INTERVAL:
      //Serial.println("    --MENU INTERVAL---");
      selectInterval();
      break;
    case MENU_INPUT_METHOD:
      //Serial.println("    --MENU INPUT METHOD---");
      selectInputMethod();
      break;
    case MENU_ENCODE_URL:
      //Serial.println("    --MENU ENCODE URL---");
      showEncodeURL();
      break;   
    case MENU_OFF:
      //Serial.println("    --MENU POWER OFF---");
      selectPowerOff();
      break;   
    default:
      break;
  }
}
