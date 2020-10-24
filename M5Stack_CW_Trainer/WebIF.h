/**************************************************************************
 * WEB Encode I/F Header
 *
 *************************************************************************/
#ifndef _CW_WEBIF_H_
#define _CW_WEBIF_H_

void WEBIF_setup_wifi(void);

void WEBIF_handleClient(void);

void WEBIF_enable(void);

void WEBIF_disable(void);

bool WEBIF_isEnable(void);

#endif /* _CW_WEBIF_H_ */
