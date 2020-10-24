/**************************************************************************
 * LCD Control Header
 *
 *************************************************************************/
#ifndef _CW_LCD_H_
#define _CW_LCD_H_

typedef enum INPUT_METHOD {
  INPUT_M5_BTN_B,       //M5 BtnB
  INPUT_TELEGRAPH_KEY,  //Telegraph Key
} INPUT_METHOD_T;

void LCD_init(void);

//Switch to the Menu Mode
void LCD_openMenu(void);

//Main manu control
void LCD_main(void);

//Switch to the Decode Mode
void LCD_openDecode(void);

//Get current Input Method
INPUT_METHOD_T LCD_getInputMethod(void);

//Print an Ascii character
void LCD_printAscii(int asciiNumber);

//Print a Japanese Kana character
void LCD_printJp(String str);

//Clear input characters
void LCD_resetAll(void);

//Print next training character
void LCD_printNextChar(void);

//Draw M5Stack battery level
void LCD_drawBatteryLevel(bool fForceDisp);

#endif /* _CW_LCD_H_ */
