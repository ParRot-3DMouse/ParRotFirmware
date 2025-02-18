# Parrot-v1.0-main
オープンソースハードウェア「ParRot」のファームウェアです。MultiAxisControllerとして３次元の動きを出力できます

## 概要
対象のデバイスである「ParRot」はrp2040をメインプロセッサ、センサをPMW3360で作られています。詳しい設計、デバイスは以下のURLを参照してください。


「ParRot」は、3軸360度回転可能なトラックボールを搭載した直感的な3Dマウスです。2つの光学センサにより正確な回転・並行移動を実現し、切り替え操作も可能。DPI調整や回転軸固定機能を備え、細かい操作にも対応します。さらに、ParRotNestでショートカットキーを自由に設定でき、直感性と操作性に優れたこのオープンソースデバイスは、3Dモデリングの効率化を大きく向上させます。

ParRotNest:
https://nest.parrot3dmouse.com/
(対応webブラウザ:Chrome,Edge)

## ハードウェア要件
回路図、設計

rp2040,PWM3360等

## ファームウェアのビルド
このソースフォルダ内のParRot-v1.0-main/ParRot-v1.0-main.inoをArduinoIDEによってビルドし書き込みを行ってください
（ダウンロード、詳しいビルド方法は以下のページ）
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




