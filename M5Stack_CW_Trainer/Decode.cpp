/*****************************************************************************
 * Morse code decode control
 *
 * 8bit Intermediate Morse code is referred from following. 
 *       http://jh7ubc.web.fc2.com/arduino/CW_decoder.html
 *****************************************************************************/
#include <M5Stack.h>
#include <Arduino.h>

#include "TrainerConfig.h"
#include "Lcd.h"
#include "Decode.h"
#include "Mode.h"

//Parameters for drawing Morse code Objct(Round rectangle)
#define BACK_COLOR_DECODE   TFT_BLACK   //Background color in decode mode
#define M5_TFT_WIDTH        (319)
#define COLOR_CODE_OBJ      WHITE       //color of decoding code object
#define START_X             (60)        //start x position
#define START_Y             (122)       //start y position of TRAINING Mode
#define START_Y_FREE        (24)        //start y position of FREE Decode Mode
//dot, dash object
int startRoundRect_x  = START_X; //start offset
int dotWidth_x        = 16;
int dashWidth_x       = dotWidth_x * 2;
int space_x           = 10;
bool isObjClear       = false;

long mStartLowTime;   //Time of LOW starting
long mStartHighTime;  //Time of HIGH staring
long mLowTime;        //Interval time of LOW（ms）
long mNoSigTime;      //No Signal time(ms)

byte mMcode = 1;     //8bit Intermediate Morse code
byte mData;          //0:dot, 1:dash
byte mBitcount = 0;  //count of 8bit

int mDotTime = DEFAULT_DOT_TIME;  //Time of "dot" period detection(ms) 
int mLtime   = 100;               //Time of "dot" period(ms)

boolean isSpaceNeeded    = false;   //space output flag
int preState = HIGH;


void DECODE_init() {
  SET_DEFAULT_LANG();
}

int DECODE_getInterval(void){
  return mDotTime;
}

void DECODE_setInterval(int interval){
  mDotTime = interval;
}

//Decode English
void decodeEn() {
  switch ( mMcode ) {
    case B00000101:
      LCD_printAscii(65);//"A"
      break;
    case B00011000:
      LCD_printAscii(66);//"B"
      break;
    case B00011010:
      LCD_printAscii(67);//"C"
      break;
    case B00001100:
      LCD_printAscii(68);//"D"
      break;
    case B00000010:
      LCD_printAscii(69);//"E"
      break;
    case B00010010:
      LCD_printAscii(70);//"F"
      break;
    case B00001110:
      LCD_printAscii(71);//"G"
      break;
    case B00010000:
      LCD_printAscii(72);//"H"
      break;
    case B00000100:
      LCD_printAscii(73);//"I"
      break;
    case B00010111:
      LCD_printAscii(74);//"J"
      break;
    case B00001101:
      LCD_printAscii(75);//"K"
      break;
    case B00010100:
      LCD_printAscii(76);//"L"
      break;
    case B00000111:
      LCD_printAscii(77);//"M"
      break;
    case B00000110:
      LCD_printAscii(78);//"N"
      break;
    case B00001111:
      LCD_printAscii(79);//"O"
      break;
    case B00010110:
      LCD_printAscii(80);//"P"
      break;
    case B00011101:
      LCD_printAscii(81);//"Q"
      break;
    case B00001010:
      LCD_printAscii(82);//"R"
      break;
    case B00001000:
      LCD_printAscii(83);//"S"
      break;
    case B00000011:
      LCD_printAscii(84);//"T"
      break;
    case B00001001:
      LCD_printAscii(85);//"U"
      break;
    case B00010001:
      LCD_printAscii(86);//"V"
      break;
    case B00001011:
      LCD_printAscii(87);//"W"
      break;
    case B00011001:
      LCD_printAscii(88);//"X"
      break;
    case B00011011:
      LCD_printAscii(89);//"Y"
      break;
    case B00011100:
      LCD_printAscii(90);//"Z"
      break;
    case B00101111:
      LCD_printAscii(49);//"1"
      break;
    case B00100111:
      LCD_printAscii(50);//"2"
      break;
    case B00100011:
      LCD_printAscii(51);//"3"
      break;
    case B00100001:
      LCD_printAscii(52);//"4"
      break;
    case B00100000:
      LCD_printAscii(53);//"5"
      break;
    case B00110000:
      LCD_printAscii(54);//"6"
      break;
    case B00111000:
      LCD_printAscii(55);//"7"
      break;
    case B00111100:
      LCD_printAscii(56);//"8"
      break;
    case B00111110:
      LCD_printAscii(57);//"9"
      break;
    case B00111111:
      LCD_printAscii(48);//"0"
      break;
    case B00110010:
      LCD_printAscii(47);//"/"
      break;
    case B01001100:
      LCD_printAscii(63);//"?"
      break;
    case B01110011:
      LCD_printAscii(44);//","
      break;
    case B01010101:
      LCD_printAscii(46);//"."
      break;
    case B01011010:
      LCD_printAscii(64);//"@"
      break;
    case B00110110:
      LCD_printAscii(40);//"("
      break;
    case B01101101:
      LCD_printAscii(41);//")"
      break;
    default:
      LCD_printAscii(42);//"*"
  }
}

//Decode Japanese
void decodeJP() {
  switch ( mMcode ) {
    case B00111011:
      LCD_printJp("ア");
      break;
    case B00000101:
      LCD_printJp("イ");
      break;
    case B00001001:
      LCD_printJp("ウ");
      break;
    case B00110111:
      LCD_printJp("エ");
      break;
    case B00101000:
      LCD_printJp("オ");
      break;
    case B00010100:
      LCD_printJp("カ");
      break;
    case B00110100:
      LCD_printJp("キ");
      break;
    case B00010001:
      LCD_printJp("ク");
      break;
    case B00011011:
      LCD_printJp("ケ");
      break;
    case B00011111:
      LCD_printJp("コ");
      break;
    case B00110101:
      LCD_printJp("サ");
      break;
    case B00111010:
      LCD_printJp("シ");
      break;
    case B00111101:
      LCD_printJp("ス");
      break;
    case B00101110:
      LCD_printJp("セ");
      break;
    case B00011110:
      LCD_printJp("ソ");
      break;
    case B00000110:
      LCD_printJp("タ");
      break;
    case B00010010:
      LCD_printJp("チ");
      break;
    case B00010110:
      LCD_printJp("ツ");
      break;
    case B00101011:
      LCD_printJp("テ");
      break;
    case B00100100:
      LCD_printJp("ト");
      break;
    case B00001010:
      LCD_printJp("ナ");
      break;
    case B00011010:
      LCD_printJp("ニ");
      break;
    case B00010000:
      LCD_printJp("ヌ");
      break;
    case B00011101:
      LCD_printJp("ネ");
      break;
    case B00010011:
      LCD_printJp("ノ");
      break;
    case B00011000:
      LCD_printJp("ハ");
      break;
    case B00111001:
      LCD_printJp("ヒ");
      break;
    case B00011100:
      LCD_printJp("フ");
      break;
    case B00000010:
      LCD_printJp("ヘ");
      break;
    case B00001100:
      LCD_printJp("ホ");
      break;
    case B00011001:
      LCD_printJp("マ");
      break;
    case B00100101:
      LCD_printJp("ミ");
      break;
    case B00000011:
      LCD_printJp("ム");
      break;
    case B00110001:
      LCD_printJp("メ");
      break;
    case B00110010:
      LCD_printJp("モ");
      break;
    case B00001011:
      LCD_printJp("ヤ");
      break;
    case B00110011:
      LCD_printJp("ユ");
      break;
    case B00000111:
      LCD_printJp("ヨ");
      break;
    case B00001000:
      LCD_printJp("ラ");
      break;
    case B00001110:
      LCD_printJp("リ");
      break;
    case B00110110:
      LCD_printJp("ル");
      break;
    case B00001111:
      LCD_printJp("レ");
      break;
    case B00010101:
      LCD_printJp("ロ");
      break;
    case B00001101:
      LCD_printJp("ワ");
      break;
    case B00010111:
      LCD_printJp("ヲ");
      break;
    case B00101010:
      LCD_printJp("ン");
      break;
    case B00101101:
      LCD_printJp("ー");
      break;
    case B00000100:
      LCD_printJp("゛");
      break;
    case B00100110:
      LCD_printJp("゜");
      break;
    case B00101111:
      LCD_printAscii(49);//"1"
      break;
    case B00100111:
      LCD_printAscii(50);//"2"
      break;
    case B00100011:
      LCD_printAscii(51);//"3"
      break;
    case B00100001:
      LCD_printAscii(52);//"4"
      break;
    case B00100000:
      LCD_printAscii(53);//"5"
      break;
    case B00110000:
      LCD_printAscii(54);//"6"
      break;
    case B00111000:
      LCD_printAscii(55);//"7"
      break;
    case B00111100:
      LCD_printAscii(56);//"8"
      break;
    case B00111110:
      LCD_printAscii(57);//"9"
      break;
    case B00111111:
      LCD_printAscii(48);//"0"
      break;
    case B01001100:
      LCD_printAscii(63);//"?"
      break;
    case B01010101:
      LCD_printAscii(46);//"."
      break;
    case B01110011:
      LCD_printAscii(44);//","
      break;
    default:
      LCD_printAscii(42);//"*"
  }
}

void DECODE_execDecode( int state ) {

  int obj_y = 0;
  if( TRAIN_MODE == MODE_getCurrentMode() ) {
    obj_y = START_Y;
  } else {
    obj_y = START_Y_FREE;
  }

  if(isObjClear) {
    //clear
    M5.Lcd.fillRect(10, obj_y -2, M5_TFT_WIDTH -10 -15, 16 + 2, BACK_COLOR_DECODE);
    startRoundRect_x = START_X;
    isObjClear = false;
  }

  // LOW --> HIGH
  if ( state == HIGH && preState == LOW ) {
    mStartHighTime = millis();
    mLowTime = millis() - mStartLowTime;
    if (mLowTime < mDotTime) {
      mData = 0;         // 0:dot
      mLtime = mLowTime;

      //draw dot
      M5.Lcd.fillRoundRect(startRoundRect_x, obj_y, dotWidth_x, 16, 8, COLOR_CODE_OBJ);
      startRoundRect_x = startRoundRect_x + dotWidth_x + space_x;
    } else {
      mData = 1;         // 1:dash

      //draw dash
      M5.Lcd.fillRoundRect(startRoundRect_x, obj_y, dashWidth_x, 16, 8, COLOR_CODE_OBJ);
      startRoundRect_x = startRoundRect_x + dashWidth_x + space_x;
    }
    mBitcount++;
    mMcode = mMcode << 1;
    mMcode = mMcode | mData;

    //error case
    if ( mBitcount > 8 ) {
      mMcode = 1;
      mBitcount = 0;
    }
  }

  // HIGH --> LOW
  if ( state == LOW && preState == HIGH ) {
    mStartLowTime = millis();
  }

  // If input is completed, execute Decoding
  if ( state == HIGH && preState == HIGH ) {
    mNoSigTime = millis() - mStartHighTime;
    if ( mBitcount != 0 ) {
      // Detect completion of input
      // If no signal time is over base time( dot time * 3)
      if ( mNoSigTime > (3 * mLtime) ) {
        if ( MODE_isJpMode() ) {
          decodeJP();
        } else {
          decodeEn();
        }
        //reset params
        mMcode = 1;
        mBitcount = 0;
        isSpaceNeeded = true;   //enable space output
        isObjClear = true;
      }
    }

    //Output only one space for each word
    if ( isSpaceNeeded == true && mNoSigTime > 7 * mLtime ) {
      if( MODE_isJpMode() ) {
        LCD_printJp("  "); //"  "
      } else {
        LCD_printAscii(32); //" "
      }
      isSpaceNeeded = false;
    }
  }

  preState = state;
}
