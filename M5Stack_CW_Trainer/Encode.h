/************************************************************************** 
 * Morse code encode Header
 *
 * This I/F has normalize character function inputed from WebI/F
 **************************************************************************/
#ifndef _CW_ENCODE_H_
#define _CW_ENCODE_H_

void ENCODE_init(void);

//Encode (ASCII or UTF-8 Japanese Kana)
void ENCODE_execEncode( String str );

#endif /* _CW_ENCODE_H_ */
