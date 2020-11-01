/**************************************************************************
 * Configuration Header
 *
 * Ver.1.0
 **************************************************************************/
#ifndef _CW_TRAINER_CONFIG_H_
#define _CW_TRAINER_CONFIG_H_

// ------------------------
//  Default configuration 
// ------------------------
#define DEFAULT_INPUT_METHOD  INPUT_M5_BTN_B          //M5Stack Button (or INPUT_TELEGRAPH_KEY)
#define SET_DEFAULT_LANG()    MODE_setEnglishMode()   //MODE_setJpMode();
#define DEFAULT_DOT_TIME      (140)                   //Time of dot period detection(ms)
#define TELEGRAPH_KEY_GPIO    (26)                    //TELEGRAPH_KEY GPIO 26 (for INPUT_TELEGRAPH_KEY)

// --------------------------
// ESP32 SoftAP Configuration
// --------------------------
#define TRAINER_SSID          "M5_CWTrainer"
#define TRAINER_PASS          "m5stack"
#define TRAINER_IP_ADDR       192,168,0,12
#define TRAINER_SUBNET        255,255,255,0
#define TRAINER_URL           "http://192.168.0.12"

// ---------------------------------------------------------------------------------
// For Japanese: 
//   Font file "*.vlw" must be installed in SDCard root.
//   "genshin-regular-16pt.vlw" is available from http://jikasei.me/font/genshin/
// ---------------------------------------------------------------------------------
#define EXT_JP_FONT_DATA "genshin-regular-16pt"


#endif /* _CW_TRAINER_CONFIG_H_ */
