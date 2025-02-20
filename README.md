# ParRotFirmware
オープンソースハードウェア「ParRot」のファームウェアです。MultiAxisControllerとして３次元の動きを出力できます。

ParRotは、以下のリポジトリを元に製作することができます。



また、今後BOOTH等のサービスで基板等の頒布を行う予定です。

頒布等のお知らせは、[ParRot公式Discordサーバ](https://discord.gg/6GQAw36ZpH)にて行います！ぜひご参加ください！

## 事前準備

1. ParRotの接続
まず、用意したParRotをPCに接続してください。

2. Arduino IDEのインストール
Arduino IDEをまだお持ちでない場合は、下記リンクからダウンロードし、インストールしてください。
    
    https://www.arduino.cc/en/software
    


## Arduino IDEの設定

3. ボードマネージャの設定
Arduino IDEを起動し、メニューの「ファイル」→「環境設定」を開きます。
「追加のボードマネージャのURL」に以下のURLを入力し、「OK」を押して設定を保存してください。

    https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json


4. Raspberry Pi Pico用ボードのインストール
次に、メニューの「ツール」→「ボード」→「ボードマネージャ」を開き、「RP2040」または「Raspberry Pi Pico」で検索します。
「Raspberry Pi RP2040 Boards by Earle F. Philhower」を選択し、「インストール」をクリックしてください。
インストール完了後、メニューの「ツール」→「ボード」から「Raspberry Pi Pico」を選択してください。

5. 必要なライブラリのインストール
ファームウェアの動作には、以下のライブラリが必要です。Arduino IDEの「ツール」→「ライブラリマネージャ」を使用して、それぞれ検索・インストールしてください。
- Adafruit TinyUSB: https://github.com/adafruit/Adafruit_TinyUSB_Arduino
- PMW3360: https://github.com/zephray/PMW3360
- Adafruit GFX: https://github.com/adafruit/Adafruit-GFX-Library
- Adafruit SSD1306: https://github.com/adafruit/Adafruit_SSD1306
- Adafruit NeoPixel: https://github.com/adafruit/Adafruit_NeoPixel

## ファームウェアのダウンロードと書き込み
6. ソースコードのダウンロード
前提環境の設定が完了したら、下記URLからファームウェアのソースコード [ParRotFirmware/ParRot-v1.0-main.ino] をダウンロードしてください。

    https://github.com/ParRot-3DMouse/ParrotFirmware/blob/main/ParRot-v1.0-main/ParRot-v1.0-main.ino


8. ビルドと書き込み
Arduino IDEでダウンロードしたソースコードを開き、ビルド（コンパイル）を行った後、ParRotにファームウェアを書き込んでください。


 
## デバイスの使用方法
ファームウェアを書き込んだ後、ParRotのトラックボールはすぐにご利用いただけます。BlenderはMultiAxisControllerに標準対応しているため、デバイスの動作確認や稼働テストに最適です。

Fusionはアドインを利用して対応する形になります。詳細は以下のURLで確認ください。

    近日公開

また、Unityでは現在ゲームコントローラーとして利用可能です（利用方法の詳細も近日公開予定となっています）。

MultiAxisControllerに対応している場合、動作する可能性が高いですが、当方での動作確認は行っておりません。動作確認済みのソフトウェアがございましたら、ご連絡いただけると助かります。

なお、拡張キーボードはParRotNestを使用して設定が可能です。以下のURLから設定用サイトにアクセスしてください。

   https://nest.parrot3dmouse.com/


## トラブルシューティング

- デバイスに書き込みができない
  ボードをRasberry pi picoに設定しましたか？他の、rp2040系列ボードとして書き込むとコンパイルできないことがあります。

- OLEDはついているのに動かない
  電源を付けたまま長時間放置しているとデバイスが反応しなくなることがあります。その場合は、USBをもう一度さしなおしてください。

- ボールの回転方向と逆向きに動いてしまう。（Blender）
  Blenderの設定でコントローラーを反転していませんか？現在このデバイスは「Edit」→「Preference」の「Input」→「NDOF」Invert Axis PanとOrbitを全部青色にした状態で設計しています。状況に応じて設計を変更してください。



