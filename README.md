# M5Stack_CWTrainer

![IMG_3204D](https://user-images.githubusercontent.com/52347942/97084374-6b1a9b80-1651-11eb-97d7-367e62b92b82.jpg)

# Features
* Selectable input method
  * Telegraph Key / M5Stack button (It can be used M5Stack stand alone).
* Language
  * English / Japanese.
* Training mode
  * Firstly it shows a letter and makes its Morse code sound.
  * Secondary you input Morse code.
  * Then if it is correct, it switches to the next letter automaticaly. 
* Free Training mode
  * You can train inputting Morse code in wide screen.
* WEB Interface for Morse code encoding
  * You can encode English/Japanese words posted from your MobilePhone or Tablet. It's very useful.
  * M5Stack runs as SoftAP mode.(SSID, PASS are defined in TrainerConfig.h)
  * QR code (The Encode page URL) is available in Menu.
* Adjustable Dot period 
  * Dot period is adjustable to slow input for beginers.
* WiFi status & Battery indicator  
* Meticulous Menu mode.
  * You can set these all configurations in Menu mode.
  * Default Mode can be changed in your TrainerConfig.h.

## For Japanese
* A Font file "*.vlw" must be installed in SDCard root.
  * This code uses "genshin-regular-16pt.vlw" is available from http://jikasei.me/font/genshin/.
  * Japanese Katakana font is needed in Japanese Mode. 

## Default Configurations
**TrainerConfig.h**

```
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
```


# Movie
<a href="https://t.co/7TCEXce7e3">pic.twitter.com/7TCEXce7e3</a>


# Photos

![IMG_3198D](https://user-images.githubusercontent.com/52347942/97084387-93a29580-1651-11eb-94f9-501c343226ae.jpg)

![IMG_3200D](https://user-images.githubusercontent.com/52347942/97084396-a6b56580-1651-11eb-87a8-98a988dd668f.jpg)

![IMG_3199D](https://user-images.githubusercontent.com/52347942/97084403-b634ae80-1651-11eb-9822-65cac9831b56.jpg)

![IMG_3201D](https://user-images.githubusercontent.com/52347942/97084423-df553f00-1651-11eb-8629-7d67d1b03678.jpg)

![IMG_3145D](https://user-images.githubusercontent.com/52347942/97084416-cf3d5f80-1651-11eb-8e6d-ca55f4b55ce1.jpg)

