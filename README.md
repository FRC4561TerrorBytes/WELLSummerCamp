# Wade Edwards Learning Lab BabyBots

 * ``BaseBabyBot.ino`` is for making a babybot wired over USB, no match timers.
 * ``BaseBabyBotBluetooth.ino`` is for making a babybot wired over USB, no match timers.
 * ``MatchBabyBot.ino`` is for use in matches for USB bots, and stops bots automatically after a specified time.
 * ``MatchBabyBotBluetooth.ino`` is for use in matches for Bluetooth-controlled bots.
 * ``MotorDrive.ino`` makes two motors drive forward at full speed. No input needed.

Physical Requirements:
 * [An Arduino](https://www.arduino.cc/)
 * [Adafruit Motor Shield V1](https://www.adafruit.com/product/81)(now discontinued)
 * Serial connection to Arduino (usually over USB)
 * (Optional) [HC-06 Bluetooth Module](https://www.amazon.com/Pass-Through-Communication-Compatible-Atomic-Market/dp/B00TNOO438) for wireless communication

Software Requirements:
 * [Arduino](https://www.arduino.cc/en/Main/Software)
 * [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html)
 * [Adafruit Motor Shield V1 Library](https://github.com/adafruit/Adafruit-Motor-Shield-library)

###Quick Start Instructions
1. Upload the file to the Arduino, plugged in via USB.
2. Figure out the COM port currently assigned to your Arduino (the correct one will usually have a label saying it's an Arduino. If one fails, try another):
![Find your COM port](http://oi67.tinypic.com/2njhrx5.jpg)
3. Open PuTTY and switch to Serial. Input the correct COM port and hit "Open".
![Connect with PuTTY](http://i67.tinypic.com/2njhrx5.jpg)
This will open up a command prompt-style window where you can input letters like Serial Monitor in Arduino.