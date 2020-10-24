/************************************************************************** 
 * Morse code decode Header
 *
 **************************************************************************/
#ifndef _CW_DECODE_H_
#define _CW_DECODE_H_

void DECODE_init(void);

//Decode
void DECODE_execDecode( int state );

//Switch to Japanese Mode
void MODE_setJpMode(void);

//Switch to English Mode
void MODE_setEnglishMode(void);

//Return whether current mode is Japanese mode.
boolean MODE_isJpMode(void);

//Get Time(ms) of dot period detection
int DECODE_getInterval(void);

//Set Time(ms) of dot period detection
void DECODE_setInterval(int interval);

#endif /* _CW_DECODE_H_ */
