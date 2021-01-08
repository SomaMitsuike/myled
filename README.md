
# ロボットシステム学　課題1 

デバイスドライバの作成

# 内容  

- ロボットシステム学の講義で作成したコードを書き換えて任意のモールス信号を出力できるようにしました。 
- デバイスファイルにaからzの任意の文字列を書き込むと書き込まれた文字列をモールス信号に変換して出力する。  
- aからz以外の入力がされた場合は細かく点滅を繰り返してエラー表示する。

# 実行方法

    $ git clone https://github.com/SomaMitsuike/myled.git
    $ cd myled
    $ make
    $ sudo insmod myled.ko
    $ sudo chmod 666 /dev/myled0  
    $ echo "任意の文字列" > /dev/myled0

# 実演動画

https://www.youtube.com/watch?v=5uHiEc0f4MQ

# 参考

https://github.com/ryuichiueda/robosys_device_drivers

# ライセンス

[GNU General Public License v3.0](https://github.com/SomaMitsuike/myled/blob/main/LICENSE)
