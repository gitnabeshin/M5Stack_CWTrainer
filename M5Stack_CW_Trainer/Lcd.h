/**************************************************************************
 * LCD Control Header
 *
 *************************************************************************/
#ifndef _CW_LCD_H_
#define _CW_LCD_H_

void LCD_init(void);

//Switch to the Menu Mode
void LCD_openMenu(void);

//Main manu control
void LCD_main(void);

//Switch to the Decode Mode
void LCD_openDecode(void);

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
