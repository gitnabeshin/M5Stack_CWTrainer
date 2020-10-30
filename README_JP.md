# M5Stack_CWTrainer

![IMG_3204D](https://user-images.githubusercontent.com/52347942/97084374-6b1a9b80-1651-11eb-97d7-367e62b92b82.jpg)

# 特徴
* 選べる入力方法
  * 電鍵（M5Stack の入力用GPIO を使用します。）
  * M5Stack Bボタン（M5Stack単体で使えます。電鍵が無くてもお手軽に練習が可能です。）
* 言語
  * 英語
  * 日本語（かな）
* トレーニングモード
  * NEXTボタンを押す度に画面上部に次の文字と信号図形が表示され、そのモールス信号音が出ます。
  * お手本に習い、電鍵、またはM5Stackボタンで信号をインプットします。
  * 正解なら、自動で次の文字に切り替わります。正解するまで何度もリトライできます。
* フリーモード
  * 画面全体を使い、長文のインプットが練習できます。
  * お手本の表示は無いので、慣れた方向けのモードです。 
* WEB画面からのモールス信号変換
  * Wifi接続したPC、スマホ、タブレットで入力した単語をモールス信号に変換できます。
  * 変換可能な文字は、英語、日本語（ひらがな、カタカナ）です。
  * M5StackはSoftAPモードで起動するため、Wifiルータは不要です。
  * アクセスポイント名、パスワードは、TrainerConfig.h で変更可能です。
  * 接続先のURLはメニュー画面からQRコードとして表示されます。
* 単音信号の判定時間が調整可能 
  * ゆっくり練習したい初心者向けに、メニュー画面から単音信号の判定時間を延長することができます。
  * 10ms単位で時間を伸ばすことが可能です。
* メニュー画面
  * 上記は全てメニュー画面から設定出来ます。
  * 初期設定値を変更したい場合は、TrainerConfig.hを書き換えます。

## 日本語モードを使う場合
* 日本語を表示するには、SDカードにフォントファイル"*.vlw"を格納しておく必要があります。
  * こちらのコードでは、フリーの"genshin-regular-16pt.vlw" を使用しています。
  * （こちらから入手可能です。 http://jikasei.me/font/genshin/ ）

## 初期設定
* **TrainerConfig.h**

```
// ------------------------
//  Default configuration 
// ------------------------
#define DEFAULT_INPUT_METHOD  INPUT_M5_BTN_B          //M5Stack Button (or INPUT_TELEGRAPH_KEY)
#define SET_DEFAULT_LANG()    MODE_setEnglishMode()   //MODE_setJpMode();
#define DEFAULT_DOT_TIME      (140)                   //Time of dot period detection(ms)
#define TELEGRAPH_KEY_GPIO    (26)                    //TELEGRAPH_KEY GPIO 26 (for INPUT_TELEGRAPH_KEY)

// --------------------------
// ESP32 SoftAP Configration
// --------------------------
#define TRAINER_SSID          "M5_CWTrainer"
#define TRAINER_PASS          "m5stack"
#define TRAINER_IP_ADDR       192,168,0,12
#define TRAINER_SUBNET        255,255,255,0
```


# Movie
* Twitterにアップした動画が観られます。
  * <a href="https://t.co/7TCEXce7e3">pic.twitter.com/7TCEXce7e3</a>



# Photos

![IMG_3198D](https://user-images.githubusercontent.com/52347942/97084387-93a29580-1651-11eb-94f9-501c343226ae.jpg)

![IMG_3200D](https://user-images.githubusercontent.com/52347942/97084396-a6b56580-1651-11eb-87a8-98a988dd668f.jpg)

![IMG_3199D](https://user-images.githubusercontent.com/52347942/97084403-b634ae80-1651-11eb-9822-65cac9831b56.jpg)

![IMG_3201D](https://user-images.githubusercontent.com/52347942/97084423-df553f00-1651-11eb-8629-7d67d1b03678.jpg)

![IMG_3145D](https://user-images.githubusercontent.com/52347942/97084416-cf3d5f80-1651-11eb-8e6d-ca55f4b55ce1.jpg)

