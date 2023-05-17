# XIAOGYAN 動作確認マニュアル

## 書き込みツールesptoolをインストール

* Windows

    1. 下記リンクにある最新の`esptool-vX.X.X-win64.zip`をダウンロードして解凍してください。

        * [espressif / esptool / Releases / latest](https://github.com/espressif/esptool/releases/latest)

* Linux

    1. Python 3.8以降が必須です。バージョンを確認して、必要に応じてインストール、アップグレードしてください。

        ```
        python3 --version
        ```

    2. esptoolをインストールしてください。

        ```
        sudo pip3 install esptool
        ```

    3. esptoolが起動できるか確認してください。

        ```
        sudo esptool version
        ```

* macOS

    1. Python 3.8以降が必須です。バージョンを確認して、必要に応じてインストール、アップグレードしてください。

        ```
        python3 --version
        ```

    2. esptoolをインストールしてください。

        ```
        pip3 install esptool
        ```

    3. esptoolが起動できるか確認してください。

        ```
        esptool version
        ```

## サンプルのファームウェアをダウンロード

サンプルのファームウェア`HardwareTest.bin`をダウンロードしてください。

* [HardwareTest.bin](HardwareTest.bin)

## サンプルのファームウェアを書き込む

XIAOGYANとPCをUSBで接続しておき、下記コマンドを実行してください。  
書き込みでエラーが発生したときは、XIAO ESP32C3をブートローダーモードに変更（BOOTボタンを押さえながらRESETボタンをクリック）して、下記コマンドを実行してみてください。

* Windows

    ```
    esptool write_flash 0x0 HardwareTest.bin
    ```

* Linux

    Python 3.7以降が必要。

    ```
    sudo esptool.py write_flash 0x0 HardwareTest.bin
    ```

* macOS

    Python 3.7以降が必要。

    ```
    esptool.py write_flash 0x0 HardwareTest.bin
    ```

## 動作確認

1. LEDマトリックスが、赤、緑、オレンジ色が流れるように点灯します。
2. ロータリーエンコーダの中央のLEDが点滅します。
3. ロータリーエンコーダを回すと、LEDマトリックスの点灯の速さが変わります。
4. ボタンAやボタンBを押すと、スピーカーから音が出ます。（音が出ないときは、可変抵抗（青色）を回してみてください。）

## Appendix

<details>
<summary>マージバイナリの作成</summary>

```
esptool --chip esp32c3 merge_bin -o HardwareTest.bin -ff 80m -fm dio -fs 4MB 0x0000 bootloader.bin 0x8000 partitions.bin 0xe000 boot_app0.bin 0x10000 firmware.bin
```

</details>
