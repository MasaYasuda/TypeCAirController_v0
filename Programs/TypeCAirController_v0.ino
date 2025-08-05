/*============================================================================
Type-C Air Controller v0用プログラム

プログラム作成日：2025/08/05 (MasaYasuda)
最終更新日：2025/08/05 (MasaYasuda)

機能: 4つのボタン入力で4つの出力をトグル制御
対象: ATtiny404
必須ライブラリ: SpenceKonde/megaTinyCore
※ 導入法：【Arduino】新しいATtiny(tinyAVR 0/1/2シリーズ)やmegaAVR 0シリーズなどで採用されたUPDIによる書き込み方法！ Arduino IDEで環境を構築する！ | ぶらり＠web走り書き(https://burariweb.info/electronic-work/arduino-updi-writing-method.html)
配線: ボタンピンは内部プルアップ
補足:
・ピン配置 参照：megaTinyCore/megaavr/extras/ATtiny_x04.gif at master · SpenceKonde/megaTinyCore(https://github.com/SpenceKonde/megaTinyCore/blob/master/megaavr/extras/ATtiny_x04.gif)
============================================================================*/

// ピン定義
const char buttonPins[4] = {0, 1, 2, 3};             // ボタン入力ピン（プルアップ）
const char outputPins[4] = {4, 5, 6, 7};             // 出力ピン
bool outputStates[4] = {false, false, false, false}; // オルタネート状態管理
bool prevButtonStates[4] = {HIGH, HIGH, HIGH, HIGH}; // 前回のボタン状態（初期値は未押下状態）

void setup()
{
  // ボタンピンを入力プルアップに設定
  for (int i = 0; i < 4; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP); // 内部プルアップ抵抗を有効化
  }
  // 出力ピンを出力&初期値LOWに設定
  for (int i = 0; i < 4; i++)
  {
    pinMode(outputPins[i], OUTPUT);   // 出力ピンとして設定
    digitalWrite(outputPins[i], LOW); // 初期状態はLOW（OFF）
  }
}

void loop()
{
  // 各ボタンの状態を監視
  for (int i = 0; i < 4; i++)
  {
    bool currentState = digitalRead(buttonPins[i]); // 現在のボタン状態を取得
    // ボタンが押された瞬間（立下りエッジ）を検出
    if (prevButtonStates[i] == HIGH && currentState == LOW)
    {
      // オルタネート（トグル）動作
      outputStates[i] = !outputStates[i];           // 出力状態を反転
      digitalWrite(outputPins[i], outputStates[i]); // 出力ピンに反映
    }
    prevButtonStates[i] = currentState; // 状態を更新
  }
  delay(10); // チャタリング防止のための短い遅延
}
