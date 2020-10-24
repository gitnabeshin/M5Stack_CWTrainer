/*****************************************************************************
 * Morse code encode control
 *
 * This I/F has normalize character function inputed from WebI/F
 * 8bit Intermediate Morse code is referred from following. 
 *       http://jh7ubc.web.fc2.com/arduino/CW_decoder.html
 *****************************************************************************/
#include <Arduino.h>
#include <M5Stack.h>

void ENCODE_init(void) {
  return;
}

//Output Encoded Morse code to the speaker.
// @encByte: 8bit Intermediate Morse code
void toneEncodeSignal( byte encByte ){
  //8bit counter
  int bitcount =0;
  byte tmpByte = encByte;
  bool foundFirstBit = false;

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
      M5.Speaker.tone(1200, 300);
      delay(300);//The duration of a dash is three times the duration of a dot
    } else {
      //Serial.print(" :0");
      //1: ignore until first find bit 1
      if( foundFirstBit == false ){
        //Serial.println("");
        continue;
      }
      // 2: Then make sound 0:dot
      //Serial.println(" : *");
      M5.Speaker.tone(1200, 100);
      delay(100);
    }
    M5.Speaker.mute();
    delay(100);
  }
}

//compare 3byte UTF-8 Kana word, returns true if str1/str2 are same.
bool compareMultiByteStr(String str1, String str2) {
  if( (str1[0] == str2[0]) && (str1[1] == str2[1]) && (str1[2] == str2[2])) {
    return true;
  }
  return false;
}

//Encode ASCII to Morse code.
void encodeEn( byte encByte ) {

  //Normalize to uppercase
  switch (encByte) {
    case 'A':
    case 'a':
      toneEncodeSignal(B00000101);
      break;
    case 'B':
    case 'b':
      toneEncodeSignal(B00011000);
      break;
    case 'C':
    case 'c':
      toneEncodeSignal(B00011010);
      break;
    case 'D':
    case 'd':
      toneEncodeSignal(B00001100);
      break;
    case 'E':
    case 'e':
      toneEncodeSignal(B00000010);
      break;
    case 'F':
    case 'f':
      toneEncodeSignal(B00010010);
      break;
    case 'G':
    case 'g':
      toneEncodeSignal(B00001110);
      break;
    case 'H':
    case 'h':
      toneEncodeSignal(B00010000);
      break;
    case 'I':
    case 'i':
      toneEncodeSignal(B00000100);
      break;
    case 'J':
    case 'j':
      toneEncodeSignal(B00010111);
      break;
    case 'K':
    case 'k':
      toneEncodeSignal(B00001101);
      break;
    case 'L':
    case 'l':
      toneEncodeSignal(B00010100);
      break;
    case 'M':
    case 'm':
      toneEncodeSignal(B00000111);
      break;
    case 'N':
    case 'n':
      toneEncodeSignal(B00000110);
      break;
    case 'O':
    case 'o':
      toneEncodeSignal(B00001111);
      break;
    case 'P':
    case 'p':
      toneEncodeSignal(B00010110);
      break;
    case 'Q':
    case 'q':
      toneEncodeSignal(B00011101);
      break;
    case 'R':
    case 'r':
      toneEncodeSignal(B00001010);
      break;
    case 'S':
    case 's':
      toneEncodeSignal(B00001000);
      break;
    case 'T':
    case 't':
      toneEncodeSignal(B00000011);
      break;
    case 'U':
    case 'u':
      toneEncodeSignal(B00001001);
      break;
    case 'V':
    case 'v':
      toneEncodeSignal(B00010001);
      break;
    case 'W':
    case 'w':
      toneEncodeSignal(B00001011);
      break;
    case 'X':
    case 'x':
      toneEncodeSignal(B00011001);
      break;
    case 'Y':
    case 'y':
      toneEncodeSignal(B00011011);
      break;
    case 'Z':
    case 'z':
      toneEncodeSignal(B00011100);
      break;
    case '1':
      toneEncodeSignal(B00101111);
      break;
    case '2':
      toneEncodeSignal(B00100111);
      break;
    case '3':
      toneEncodeSignal(B00100011);
      break;
    case '4':
      toneEncodeSignal(B00100001);
      break;
    case '5':
      toneEncodeSignal(B00100000);
      break;
    case '6':
      toneEncodeSignal(B00110000);
      break;
    case '7':
      toneEncodeSignal(B00111000);
      break;
    case '8':
      toneEncodeSignal(B00111100);
      break;
    case '9':
      toneEncodeSignal(B00111110);
      break;
    case '0':
      toneEncodeSignal(B00111111);
      break;
    case '/':
      toneEncodeSignal(B00110010);
      break;
    case '?':
      toneEncodeSignal(B01001100);
      break;
    case ',':
      toneEncodeSignal(B01110011);
      break;
    case '.':
      toneEncodeSignal(B01010101);
      break;
    case '@':
      toneEncodeSignal(B01011010);
      break;
    case '(':
      toneEncodeSignal(B00110110);
      break;
    case ')':
      toneEncodeSignal(B01101101);
      break;
    default:
      Serial.println("NO MATCH...");
  }
}

//Encode UTF-8 Japanese Kana to Morse code
void encodeJp( String inStr ) {

  //Normalize to full-width KataKana
  if( compareMultiByteStr( inStr, "あ") || compareMultiByteStr( inStr, "ア") ) {
    toneEncodeSignal(B00111011);  //ア
  } else if( compareMultiByteStr( inStr, "い") || compareMultiByteStr( inStr, "イ") ) {
    toneEncodeSignal(B00000101);  //イ
  } else if( compareMultiByteStr( inStr, "う") || compareMultiByteStr( inStr, "ウ") ) {
    toneEncodeSignal(B00001001);  //ウ
  } else if( compareMultiByteStr( inStr, "え") || compareMultiByteStr( inStr, "エ") ) {
    toneEncodeSignal(B00110111);  //エ
  } else if( compareMultiByteStr( inStr, "お") || compareMultiByteStr( inStr, "オ") ) {
    toneEncodeSignal(B00101000);  //オ
  } else if( compareMultiByteStr( inStr, "か") || compareMultiByteStr( inStr, "カ") ) {
    toneEncodeSignal(B00010100);  //カ
  } else if( compareMultiByteStr( inStr, "き") || compareMultiByteStr( inStr, "キ") ) {
    toneEncodeSignal(B00110100);  //キ
  } else if( compareMultiByteStr( inStr, "く") || compareMultiByteStr( inStr, "ク") ) {
    toneEncodeSignal(B00010001);  //ク
  } else if( compareMultiByteStr( inStr, "け") || compareMultiByteStr( inStr, "ケ") ) {
    toneEncodeSignal(B00011011);  //ケ
  } else if( compareMultiByteStr( inStr, "こ") || compareMultiByteStr( inStr, "コ") ) {
    toneEncodeSignal(B00011111);  //コ
  } else if( compareMultiByteStr( inStr, "さ") || compareMultiByteStr( inStr, "サ") ) {
    toneEncodeSignal(B00110101);  //サ
  } else if( compareMultiByteStr( inStr, "し") || compareMultiByteStr( inStr, "シ") ) {
    toneEncodeSignal(B00111010);  //シ
  } else if( compareMultiByteStr( inStr, "す") || compareMultiByteStr( inStr, "ス") ) {
    toneEncodeSignal(B00111101);  //ス
  } else if( compareMultiByteStr( inStr, "せ") || compareMultiByteStr( inStr, "セ") ) {
    toneEncodeSignal(B00101110);  //セ
  } else if( compareMultiByteStr( inStr, "そ") || compareMultiByteStr( inStr, "ソ") ) {
    toneEncodeSignal(B00011110);  //ソ
  } else if( compareMultiByteStr( inStr, "た") || compareMultiByteStr( inStr, "タ") ) {
    toneEncodeSignal(B00000110);  //タ
  } else if( compareMultiByteStr( inStr, "ち") || compareMultiByteStr( inStr, "チ") ) {
    toneEncodeSignal(B00010010);  //チ
  } else if( compareMultiByteStr( inStr, "つ") || compareMultiByteStr( inStr, "ツ") ) {
    toneEncodeSignal(B00010110);  //ツ
  } else if( compareMultiByteStr( inStr, "て") || compareMultiByteStr( inStr, "テ") ) {
    toneEncodeSignal(B00101011);  //テ
  } else if( compareMultiByteStr( inStr, "と") || compareMultiByteStr( inStr, "ト") ) {
    toneEncodeSignal(B00100100);  //ト
  } else if( compareMultiByteStr( inStr, "な") || compareMultiByteStr( inStr, "ナ") ) {
    toneEncodeSignal(B00001010);  //ナ
  } else if( compareMultiByteStr( inStr, "に") || compareMultiByteStr( inStr, "ニ") ) {
    toneEncodeSignal(B00011010);  //ニ
  } else if( compareMultiByteStr( inStr, "ぬ") || compareMultiByteStr( inStr, "ヌ") ) {
    toneEncodeSignal(B00010000);  //ヌ
  } else if( compareMultiByteStr( inStr, "ね") || compareMultiByteStr( inStr, "ネ") ) {
    toneEncodeSignal(B00011101);  //ネ
  } else if( compareMultiByteStr( inStr, "の") || compareMultiByteStr( inStr, "ノ") ) {
    toneEncodeSignal(B00010011);  //ノ
  } else if( compareMultiByteStr( inStr, "は") || compareMultiByteStr( inStr, "ハ") ) {
    toneEncodeSignal(B00011000);  //ハ
  } else if( compareMultiByteStr( inStr, "ひ") || compareMultiByteStr( inStr, "ヒ") ) {
    toneEncodeSignal(B00111001);  //ヒ
  } else if( compareMultiByteStr( inStr, "ふ") || compareMultiByteStr( inStr, "フ") ) {
    toneEncodeSignal(B00011100);  //フ
  } else if( compareMultiByteStr( inStr, "へ") || compareMultiByteStr( inStr, "ヘ") ) {
    toneEncodeSignal(B00000010);  //ヘ
  } else if( compareMultiByteStr( inStr, "ほ") || compareMultiByteStr( inStr, "ホ") ) {
    toneEncodeSignal(B00001100);  //ホ
  } else if( compareMultiByteStr( inStr, "ま") || compareMultiByteStr( inStr, "マ") ) {
    toneEncodeSignal(B00011001);  //マ
  } else if( compareMultiByteStr( inStr, "み") || compareMultiByteStr( inStr, "ミ") ) {
    toneEncodeSignal(B00100101);  //ミ
  } else if( compareMultiByteStr( inStr, "む") || compareMultiByteStr( inStr, "ム") ) {
    toneEncodeSignal(B00000011);  //ム
  } else if( compareMultiByteStr( inStr, "め") || compareMultiByteStr( inStr, "メ") ) {
    toneEncodeSignal(B00110001);  //メ
  } else if( compareMultiByteStr( inStr, "も") || compareMultiByteStr( inStr, "モ") ) {
    toneEncodeSignal(B00110010);  //モ
  } else if( compareMultiByteStr( inStr, "や") || compareMultiByteStr( inStr, "ヤ") ||
             compareMultiByteStr( inStr, "ゃ") || compareMultiByteStr( inStr, "ャ") ) {
    toneEncodeSignal(B00001011);  //ヤ
  } else if( compareMultiByteStr( inStr, "ゆ") || compareMultiByteStr( inStr, "ユ") ||
             compareMultiByteStr( inStr, "ゅ") || compareMultiByteStr( inStr, "ュ") ) {
    toneEncodeSignal(B00110011);  //ユ
  } else if( compareMultiByteStr( inStr, "よ") || compareMultiByteStr( inStr, "ヨ") ||
             compareMultiByteStr( inStr, "ょ") || compareMultiByteStr( inStr, "ョ")   ) {
    toneEncodeSignal(B00000111);  //ヨ
  } else if( compareMultiByteStr( inStr, "ら") || compareMultiByteStr( inStr, "ラ") ) {
    toneEncodeSignal(B00001000);  //ラ
  } else if( compareMultiByteStr( inStr, "り") || compareMultiByteStr( inStr, "リ") ) {
    toneEncodeSignal(B00001110);  //リ
  } else if( compareMultiByteStr( inStr, "る") || compareMultiByteStr( inStr, "ル") ) {
    toneEncodeSignal(B00110110);  //ル
  } else if( compareMultiByteStr( inStr, "れ") || compareMultiByteStr( inStr, "レ") ) {
    toneEncodeSignal(B00001111);  //レ
  } else if( compareMultiByteStr( inStr, "ろ") || compareMultiByteStr( inStr, "ロ") ) {
    toneEncodeSignal(B00010101);  //ロ
  } else if( compareMultiByteStr( inStr, "わ") || compareMultiByteStr( inStr, "ワ") ) {
    toneEncodeSignal(B00001101);  //ワ
  } else if( compareMultiByteStr( inStr, "を") || compareMultiByteStr( inStr, "ヲ") ) {
    toneEncodeSignal(B00010111);  //ヲ
  } else if( compareMultiByteStr( inStr, "ん") || compareMultiByteStr( inStr, "ン") ) {
    toneEncodeSignal(B00101010);  //ン
  } else if( compareMultiByteStr( inStr, "が") || compareMultiByteStr( inStr, "ガ") ) {
    toneEncodeSignal(B00010100);  //カ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ぎ") || compareMultiByteStr( inStr, "ギ") ) {
    toneEncodeSignal(B00110100);  //キ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ぐ") || compareMultiByteStr( inStr, "グ") ) {
    toneEncodeSignal(B00010001);  //ク
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "げ") || compareMultiByteStr( inStr, "ゲ") ) {
    toneEncodeSignal(B00011011);  //ケ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ご") || compareMultiByteStr( inStr, "ゴ") ) {
    toneEncodeSignal(B00011111);  //コ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ざ") || compareMultiByteStr( inStr, "ザ") ) {
    toneEncodeSignal(B00110101);  //サ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "じ") || compareMultiByteStr( inStr, "ジ") ) {
    toneEncodeSignal(B00111010);  //シ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ず") || compareMultiByteStr( inStr, "ズ") ) {
    toneEncodeSignal(B00111101);  //ス
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ぜ") || compareMultiByteStr( inStr, "ゼ") ) {
    toneEncodeSignal(B00101110);  //セ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ぞ") || compareMultiByteStr( inStr, "ゾ") ) {
    toneEncodeSignal(B00011110);  //ソ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "だ") || compareMultiByteStr( inStr, "ダ") ) {
    toneEncodeSignal(B00000110);  //タ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ぢ") || compareMultiByteStr( inStr, "ヂ") ) {
    toneEncodeSignal(B00010010);  //チ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "づ") || compareMultiByteStr( inStr, "ヅ") ) {
    toneEncodeSignal(B00010110);  //ツ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "で") || compareMultiByteStr( inStr, "デ") ) {
    toneEncodeSignal(B00101011);  //テ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ど") || compareMultiByteStr( inStr, "ド") ) {
    toneEncodeSignal(B00100100);  //ト
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ば") || compareMultiByteStr( inStr, "バ") ) {
    toneEncodeSignal(B00011000);  //ハ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "び") || compareMultiByteStr( inStr, "ビ") ) {
    toneEncodeSignal(B00111001);  //ヒ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ぶ") || compareMultiByteStr( inStr, "ブ") ) {
    toneEncodeSignal(B00011100);  //フ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "べ") || compareMultiByteStr( inStr, "ベ") ) {
    toneEncodeSignal(B00000010);  //ヘ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ぼ") || compareMultiByteStr( inStr, "ボ") ) {
    toneEncodeSignal(B00001100);  //ホ
    toneEncodeSignal(B00000100);  //゛濁点
  } else if( compareMultiByteStr( inStr, "ぱ") || compareMultiByteStr( inStr, "パ") ) {
    toneEncodeSignal(B00011000);  //ハ
    toneEncodeSignal(B00100110);  //゜半濁点
  } else if( compareMultiByteStr( inStr, "ぴ") || compareMultiByteStr( inStr, "ピ") ) {
    toneEncodeSignal(B00111001);  //ヒ
    toneEncodeSignal(B00100110);  //゜半濁点
  } else if( compareMultiByteStr( inStr, "ぷ") || compareMultiByteStr( inStr, "プ") ) {
    toneEncodeSignal(B00011100);  //フ
    toneEncodeSignal(B00100110);  //゜半濁点
  } else if( compareMultiByteStr( inStr, "ぺ") || compareMultiByteStr( inStr, "ペ") ) {
    toneEncodeSignal(B00000010);  //ヘ
    toneEncodeSignal(B00100110);  //゜半濁点
  } else if( compareMultiByteStr( inStr, "ぽ") || compareMultiByteStr( inStr, "ポ") ) {
    toneEncodeSignal(B00001100);  //ホ
    toneEncodeSignal(B00100110);  //゜半濁点
  } else if( compareMultiByteStr( inStr, "ー") ) {
    toneEncodeSignal(B00101101);  //ー :長音
  } else {
    Serial.println("NO MATCH...");
  }
}

//Public Encode function
//Japanese charset must be UTF-8.
void ENCODE_execEncode( String srcStr ) {

  int i=0;
  char jpStr[3];
  String SingleJPStr;

  //Serial.printf("1[%x]", srcStr[0] );
  //Serial.printf("1[%x]", srcStr[1] );
  //Serial.printf("1[%x]\n", srcStr[2] );

  for(i=0; i<srcStr.length(); i++) {
    SingleJPStr = "";
    if( srcStr[i] == 0xe3 ){
      //Japanese Multibyte(UTF-8 Japanese Character starts with 0xe3)
      jpStr[0] = srcStr[i];
      jpStr[1] = srcStr[i+1];
      jpStr[2] = srcStr[i+2];
      SingleJPStr = jpStr;
      encodeJp( SingleJPStr );
      i=i+2; //jump to next JP Character
    } else {
      //English ASCII
      encodeEn( srcStr[i] );
    }
    delay(700);
  }
}
