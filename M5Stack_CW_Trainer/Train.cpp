/********************************************************************************************
 * Training Mode
 *
 * This interface provides Morse code sound and Dot and Dash object. 
 * 8bit Intermediate code is referred from http://jh7ubc.web.fc2.com/arduino/CW_decoder.html
 ********************************************************************************************/
#include <M5Stack.h>
#include <Arduino.h>

#include "Decode.h"
#include "Mode.h"
#include "Train.h"

#define COLOR_CODE_OBJ  YELLOW
#define START_Y   (65)

int m_CharIndex = 0;

//Current Word for Matching
String  mCurrentJpStr;
char    mCurrentEnStr;

//English Morse code map
typedef struct {
  char str;       //English Ascii
  byte encByte;   //8bit encoded Morse code
} CW_Code_T;

//Japanese Morse code map
typedef struct {
  byte jp2Byte;   //JP Kana 2nd byte
  byte jp3Byte;   //JP Kana 3rd byte
  byte encByte;   //8bit encoded Morse code
} CW_JPCode_T;

CW_Code_T cwCodeArray[] = {
  { 'A', B00000101 },
  { 'B', B00011000 },
  { 'C', B00011010 },
  { 'D', B00001100 },
  { 'E', B00000010 },
  { 'F', B00010010 },
  { 'G', B00001110 },
  { 'H', B00010000 },
  { 'I', B00000100 },
  { 'J', B00010111 },
  { 'K', B00001101 },
  { 'L', B00010100 },
  { 'M', B00000111 },
  { 'N', B00000110 },
  { 'O', B00001111 },
  { 'P', B00010110 },
  { 'Q', B00011101 },
  { 'R', B00001010 },
  { 'S', B00001000 },
  { 'T', B00000011 },
  { 'U', B00001001 },
  { 'V', B00010001 },
  { 'W', B00001011 },
  { 'X', B00011001 },
  { 'Y', B00011011 },
  { 'Z', B00011100 },
  { '1', B00101111 },
  { '2', B00100111 },
  { '3', B00100011 },
  { '4', B00100001 },
  { '5', B00100000 },
  { '6', B00110000 },
  { '7', B00111000 },
  { '8', B00111100 },
  { '9', B00111110 },
  { '0', B00111111 },
  { '/', B00110010 },
  { '?', B01001100 },
  { ',', B01110011 },
  { '.', B01010101 },
  { '@', B01011010 },
  { '(', B00110110 },
  { ')', B01101101 }
};

CW_JPCode_T cwJPCodeArray[] = {
  { 0x82, 0xa2, B00111011 },  //ア
  { 0x82, 0xa4, B00000101 },  //イ
  { 0x82, 0xa6, B00001001 },  //ウ
  { 0x82, 0xa8, B00110111 },  //エ
  { 0x82, 0xaa, B00101000 },  //オ
  { 0x82, 0xab, B00010100 },  //カ
  { 0x82, 0xad, B00110100 },  //キ
  { 0x82, 0xaf, B00010001 },  //ク
  { 0x82, 0xb1, B00011011 },  //ケ
  { 0x82, 0xb3, B00011111 },  //コ
  { 0x82, 0xb5, B00110101 },  //サ
  { 0x82, 0xb7, B00111010 },  //シ
  { 0x82, 0xb9, B00111101 },  //ス
  { 0x82, 0xbb, B00101110 },  //セ
  { 0x82, 0xbd, B00011110 },  //ソ
  { 0x82, 0xbf, B00000110 },  //タ
  { 0x83, 0x81, B00010010 },  //チ
  { 0x83, 0x84, B00010110 },  //ツ
  { 0x83, 0x86, B00101011 },  //テ
  { 0x83, 0x88, B00100100 },  //ト
  { 0x83, 0x8a, B00001010 },  //ナ
  { 0x83, 0x8b, B00011010 },  //ニ
  { 0x83, 0x8c, B00010000 },  //ヌ
  { 0x83, 0x8d, B00011101 },  //ネ
  { 0x83, 0x8e, B00010011 },  //ノ
  { 0x83, 0x8f, B00011000 },  //ハ
  { 0x83, 0x92, B00111001 },  //ヒ
  { 0x83, 0x95, B00011100 },  //フ
  { 0x83, 0x98, B00000010 },  //ヘ
  { 0x83, 0x9b, B00001100 },  //ホ
  { 0x83, 0x9e, B00011001 },  //マ
  { 0x83, 0x9f, B00100101 },  //ミ
  { 0x83, 0xa0, B00000011 },  //ム
  { 0x83, 0xa1, B00110001 },  //メ
  { 0x83, 0xa2, B00110010 },  //モ
  { 0x83, 0xa4, B00001011 },  //ヤ
  { 0x83, 0xa6, B00110011 },  //ユ
  { 0x83, 0xa8, B00000111 },  //ヨ
  { 0x83, 0xa9, B00001000 },  //ラ
  { 0x83, 0xaa, B00001110 },  //リ
  { 0x83, 0xab, B00110110 },  //ル
  { 0x83, 0xac, B00001111 },  //レ
  { 0x83, 0xad, B00010101 },  //ロ
  { 0x83, 0xaf, B00001101 },  //ワ
  { 0x83, 0xb2, B00010111 },  //ヲ
  { 0x83, 0xb3, B00101010 },  //ン
  { 0x82, 0x9b, B00000100 },  //゛
  { 0x82, 0x9c, B00100110 },  //゜
  { 0x83, 0xbc, B00101101 }   //ー
};

void TRAIN_init(void) {
  m_CharIndex = 0;
  mCurrentJpStr = '0';
  mCurrentEnStr = '0';
  return;
}

void showCharAndCWCode( byte encByte ){
  //8bit counter
  int bitcount =0;
  byte tmpByte = encByte;
  bool foundFirstBit = false;

  //dot, dash object
  int startRoundRect_x = 60; //start x offset
  int dotWidth_x = 16;
  int dashWidth_x = dotWidth_x * 2;
  int space_x = 10;

  //Check 8bit Intermediate code from upper bit to lower bit
  // 1: ignore until first find bit 1
  // 2: Then make sound for 0:dot, 1:dash
  for( bitcount=7; bitcount>=0; bitcount-- ){
    tmpByte = encByte;
    tmpByte = tmpByte >> bitcount;
    //Serial.printf("%d: tmpByte[%x] ", bitcount, tmpByte);
    if( tmpByte & 0x01 == 1 ) {
      //Serial.print(" :1");

      //1: ignore until firstly found bit 1
      if( foundFirstBit == false ){
        foundFirstBit = true;
        //Serial.println(" :--first bit--");
        continue;
      }
      // 2: Then make sound for 1:dash
      //Serial.println(" :----");

      //draw dash
      M5.Lcd.fillRoundRect(startRoundRect_x, START_Y, dashWidth_x, 16, 8, COLOR_CODE_OBJ);
      startRoundRect_x = startRoundRect_x + dashWidth_x + space_x;

      //make a sound
      M5.Speaker.tone(1200, 300);
      delay(300);
    } else {
      //Serial.print(" :0");

      //1: ignore until first find bit 1
      if( foundFirstBit == false ){
        //Serial.println("");
        continue;
      }
      // 2: Then make sound 0:dot
      //Serial.println(" : *");

      //draw dot
      M5.Lcd.fillRoundRect(startRoundRect_x, START_Y, dotWidth_x, 16, 8, COLOR_CODE_OBJ);
      startRoundRect_x = startRoundRect_x + dotWidth_x + space_x;

      //make a sound
      M5.Speaker.tone(1200, 100);
      delay(100);
    }
    M5.Speaker.mute();
    delay(100);
  }
}

void TRAIN_printNextChar() {

  M5.Lcd.setCursor(20, START_Y);
  char jpStr[4];

  if( MODE_isJpMode() ) {
    //UTF-8 Japanese Kana byte
    jpStr[0] = 0xe3; //UTF-8 first byte;
    jpStr[1] = cwJPCodeArray[ m_CharIndex ].jp2Byte;
    jpStr[2] = cwJPCodeArray[ m_CharIndex ].jp3Byte;
    jpStr[3] = '\0';
    mCurrentJpStr = jpStr;

    //Show Encode Word
    M5.Lcd.print( mCurrentJpStr );
    delay(500);
    //Make and Draw a sound in Display.
    showCharAndCWCode( cwJPCodeArray[ m_CharIndex ].encByte );

    //reset index
    if ( m_CharIndex + 1 >= sizeof(cwJPCodeArray)/sizeof(CW_JPCode_T) ) {
      m_CharIndex = 0;
    } else {
      m_CharIndex++;
    }
  } else {

    mCurrentEnStr = cwCodeArray[ m_CharIndex ].str;

    //Show Encode Word
    M5.Lcd.print( mCurrentEnStr );
    delay(500);

    //Make a sound and show Character in Display.
    showCharAndCWCode( cwCodeArray[ m_CharIndex ].encByte );

    //reset index
    if ( m_CharIndex + 1 >= sizeof(cwCodeArray)/sizeof(CW_Code_T) ) {
      m_CharIndex = 0;
    } else {
      m_CharIndex++;
    }
  }
}

bool TRAIN_isMatchedJp( String inStr ) {
  if( (inStr[0] == mCurrentJpStr[0]) && (inStr[1] == mCurrentJpStr[1]) && (inStr[2] == mCurrentJpStr[2])) {
    return true;
  }
  return false;
}

bool TRAIN_isMatchedEn( char inChar ) {
  if( inChar == mCurrentEnStr ) {
    return true;
  }
  return false;
}
