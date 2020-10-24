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

CTRL_MODE_T MODE_getCurrentMode(void);
CTRL_MODE_T MODE_setCurrentMode(CTRL_MODE_T ctrlMode);

void MODE_setJpMode(void);
void MODE_setEnglishMode(void);
boolean MODE_isJpMode(void);

#endif /* _CW_MODE_H_ */
