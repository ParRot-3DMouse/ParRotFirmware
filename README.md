# ParRotFirmware
オープンソースハードウェア「ParRot」のファームウェアです。MultiAxisControllerとして３次元の動きを出力できます。

## ParRotを用意する

まずはParRotを手元に用意してください。
自分で製作できる人は、以下のリポジトリを元に製作することができます。
また、今後BOOTH等のサービスで基板等の頒布を行う予定です。
お知らせ等は、[ParRot公式Discordサーバ](https://discord.gg/6GQAw36ZpH)にて行います。

## ファームウェアのビルド

用意したParRotをPCに繋いでください。

次に、このソースフォルダ内の[ParRotFirmware/ParRot-v1.0-main.ino](https://github.com/ParRot-3DMouse/ParrotFirmware/blob/main/ParRot-v1.0-main/ParRot-v1.0-main.ino)をダウンロードし、ArduinoIDEによってビルドし書き込みを行ってください

ArduinoIDEをお持ちでない方は以下のリンクからダウンロードできます。
https://www.arduino.cc/en/software

このデバイスにはRaspberry Pi Picoの書き込み機能が必要です。

メニューの 「ファイル」→「環境設定」 を開く。
「追加のボードマネージャのURL」に以下を入力：

https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

「OK」を押して設定を保存。

「ツール」→「ボード」→「ボードマネージャ」 を開く。
「RP2040」または「Raspberry Pi Pico」で検索。
「Raspberry Pi RP2040 Boards by Earle F. Philhower」 を選び、「インストール」をクリック。

「ツール」→「ボード」 で「Raspberry Pi Pico」を選択。

また、動作には以下のライブラリを必要とします

    Adafruit TinyUSB: https://github.com/adafruit/Adafruit_TinyUSB_Arduino

    PMW3360: https://github.com/zephray/PMW3360

    Adafruit GFX: https://github.com/adafruit/Adafruit-GFX-Library

    Adafruit SSD1306: https://github.com/adafruit/Adafruit_SSD1306

    Adafruit NeoPixel: https://github.com/adafruit/Adafruit_NeoPixel

ArduinoIDEから、「ツール」→「ライブラリマネージャ」を開き検索してインストールしてください。

## デバイスの使用方法
デバイスの書き込み後、トラックボールはお使いいただけます。blenderは標準でMultiAxisControllerに対応しているので、デバイスの稼働テストにお勧めです。

Fusionはアドインを利用して対応する形になります。詳細は以下のURLで確認ください。

    近日公開

Unityは現在ゲームコントローラーとして、利用することができます。利用方法は近日公開予定です

その他のデバイスは、こちら側で対応確認できておりませんが、MultiAxisControllerに対応しているならば、使える可能性が高いです。もし、動作確認できたソフトがありましたら連絡をいただけると助かります。

拡張キーボードはParRotNestを利用して設定することができます。

    https://nest.parrot3dmouse.com/

詳しい使用法は以下のURLを確認ください。

## トラブルシューティング
・デバイスに書き込みができない

ボードをRasberry pi picoに設定しましたか？他の、rp2040系列ボードとして書き込むとコンパイルできないことがあります。
・OLEDはついているのに動かない

電源を付けたまま長時間放置しているとデバイスが反応しなくなることがあります。その場合は、USBをもう一度さしなおしてください。

・ボールの回転方向と逆向きに動いてしまう。（blender）
Blenderの設定でコントローラーを反転していませんか？現在このデバイスは「Edit」→「Preference」の「Input」→「NDOF」Invert Axis PanとOrbitを全部青色にした状態で設計しています。状況に応じて設計を変更してください。



