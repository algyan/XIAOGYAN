# XIAOGYAN ソフトウェア開発マニュアル

## 1. はじめに

XIAOGYANのサンプルのソフトウェアは[PlatformIO](https://platformio.org/)で開発しています。
PlatformIO開発環境はみんな大好きVisual Studio Codeの拡張機能でも提供されていて、これを使うと簡単に開発環境を用意できます。

* [Visual Studio Code](https://azure.microsoft.com/ja-jp/products/visual-studio-code)
* [PlatformIO IDE for VSCode](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

また、XIAOGYANのサンプルのソフトウェアはGitHubで管理しています。GitとVisual Studio Code拡張機能のGit Graphも使えるようになりましょう。

* [Git](https://git-scm.com/)
* [Git Graph extension for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=mhutchie.git-graph)

## 2. 開発ツールのインストール

### 2.1. Visual Studio Code

1. ブラウザで[Download Visual Studio Code](https://code.visualstudio.com/download)ページを開いてください。
2. `Windows`をクリックしてください。インストールファイルがダウンロードされます。
3. インストールファイルを実行してください。Visual Studio Codeのセットアップ画面が表示されます。
4. 画面の指示にしたがってセットアップを完了してください。
    * **使用許諾契約書の同意** - `同意する`を選択
    * **追加タスクの選択** - `PATHへの追加(再起動後に使用可能)`を選択

> [画面ショット](screenshot/install/vscode.md)

### 2.2. Git

1. ブラウザで[Download Git](https://git-scm.com/downloads)ページを開いてください。
2. `Windows`をクリックしてください。Download for Windowsページが表示されます。
3. `64-bit Git for Windows Setup`をクリックしてください。インストールファイルがダウンロードされます。
4. インストールファイルを実行してください。Gitのセットアップ画面が表示されます。
5. 画面の指示にしたがってセットアップを完了してください。
    * **Select Components** - `Git LFS`と`Scalar`を選択
    * **Choosing the default editor used by Git** - `Use Visual Studio Code as Git's default editor`を選択
    * **Adjusting your PATH environment** - `Git from the command line and also from 3rd-party software`を選択

> [画面ショット](screenshot/install/git.md)

### 2.3. Visual Studio Code拡張

1. Visual Studio Codeを起動してください。
2. EXTENSIONS画面で`MS-CEINTL.vscode-language-pack-ja`（Japanese Language Pack for Visual Studio Code）を検索してインストールしてください。
3. Visual Studio Codeを再起動してください。
4. 拡張機能画面で`mhutchie.git-graph`（Git Graph）を検索してインストールしてください。
5. 拡張機能画面で`platformio.platformio-ide`（PlatformIO IDE）を検索してインストールしてください。
6. Visual Studio Codeを再起動してください。

> [画面ショット](screenshot/install/vscodeext.md)

## 3. サンプルのソフトウェアをビルド、書き込み

1. ソース管理画面で`リポジトリのクローン`をクリックして実行してください。
    * **リポジトリのURL** - `https://github.com/algyan/xiaogyan_examples`
    * **複製するフォルダー** -- デスクトップを指定
2. 「クローンしたリポジトリを開きますか？画面で`開く`をクリックしてください。
3. ファイルの作成者を信頼する確認画面が表示されたときは`はい、作成者を信頼します`をクリックしてください。
4. ソース管理画面にある`View Git Graph`ボタンをクリックして、コミット一覧が表示されることを確認してください。
5. PLATFORMIO画面で`Pick a folder`をクリックして、`platformio/HardwareTest`フォルダーを選択してください。
6. XIAOGYANをUSB接続しておき、PLATFORMIO画面で`seeed_xiao_esp32c3/General/Upload`をクリックしてください。

> [画面ショット](screenshot/install/upload.md)
