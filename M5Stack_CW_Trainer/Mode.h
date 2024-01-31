/**************************************************************************
 * Mode.h
 *
 *************************************************************************/
#ifndef _CW_MODE_H_
#define _CW_MODE_H_

//Control Mode
typedef enum CTRL_MODE {
  DECODE_MODE,    //Free decode practice
  TRAIN_MODE,     //Training
  MENU_MODE       //Menu
} CTRL_MODE_T;

typedef enum INPUT_METHOD {
  INPUT_M5_BTN_B,       //M5 BtnB
  INPUT_TELEGRAPH_KEY,  //Telegraph Key
} INPUT_METHOD_T;

CTRL_MODE_T MODE_getCurrentMode(void);
void MODE_setCurrentMode(CTRL_MODE_T ctrlMode);

void MODE_setJpMode(void);
void MODE_setEnglishMode(void);
boolean MODE_isJpMode(void);

void MODE_setInputMethod(INPUT_METHOD_T inputMethod);
INPUT_METHOD_T MODE_getInputMethod(void);

#endif /* _CW_MODE_H_ */
