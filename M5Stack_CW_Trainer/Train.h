/**************************************************************************
 * Training Mode Header
 *
 * This interface provides Morse code sound and Dot and Dash object. 
 *************************************************************************/
#ifndef _CW_TRAIN_H_
#define _CW_TRAIN_H_

void TRAIN_init(void);

void TRAIN_printNextChar(void);

//Check inStr(Japanese code) is correct.
bool TRAIN_isMatchedJp( String inStr );

//Check inChar(English code) is correct.
bool TRAIN_isMatchedEn( char inChar );

#endif /* _CW_TRAIN_H_ */
