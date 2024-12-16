# About the program
  This program is my technology homework.if you needed,you can use and modify the program,but "do not profit from it".The program has three part:  
  - ThreeAxisStbilizerDrive,Needed-library and testingcode.ThreeAxisStbilizerDrive is main code,and it is the run in the Arduino board.  
  - testingcode store the code of not verification ,so if you could not write code or you could not understand,it is recommended not to modify and move there code to ThreeAxisStbilizerDrive.  
  - Needed-library is saving the library that is ThreeAxisStbilizerDrive needed.about those library information,you can see the [library information](https://github.com/KANA-exe/Three-axis-stabilizer-with-Arduino/tree/main?tab=readme-ov-file#Library-information).
# The program function
  - Calculate rotation angle with angular velocity,which has camera or phone stable.
# Install the program
  1. Prepare material of the following list:  
    - A Arduino board(EX:Arduino UNO,Arduino NANO)  
    - A USB wire that can cannect the computer with Arduino Board  
    - A MPU6050  
    - Three of servo motor  
    - A lot of dupont lines  
    - It is best to prepare a Arduino shield.  
  2. Assemble the circuit.  
    - Information of material is in [Material information](https://github.com/KANA-exe/Three-axis-stabilizer-with-Arduino/tree/main?tab=readme-ov-file#Matetial-information).  
    - It is the circrit diagram as follow.(the board is Arduino NANO)
    ![circuit diagram](https://github.com/KANA-exe/Three-axis-stabilizer-with-Arduino/blob/main/circuit%20diagram.png?raw=true)
  3. Download the [.zip](https://github.com/KANA-exe/Three-axis-stabilizer-with-Arduino/archive/refs/heads/main.zip) of this program and extract it.
  4. Connect the Arduino board to the computer.
  5. Check the Port of the Arduino board.  
    Steps in Windows11 as following:  
    - Click Windows+R on keyboard.  
    - Input "devmgmt.msc".  
    - Find "Ports (COM & LPT)" and double clict it.  
    - Find port of arduino board,and it may display "Arduno XXXX CH340 (COM?) ".  
    - log port of Arduino board in paper or other space. (it is "com?","?" is a number).
  6. Install and open [Arduino IDE](https://www.arduino.cc/en/software).
  7. Open "Three-axis-stabilizer-with-Arduino">"ThreeAxisStabilizerDrive">"ThreeAxisStabilizerDrive.ino".  
  8. Click "Tools">"Board">"Arduino AVR Boards",then find your board's type and click it. 
  9. Click "Tools">"Port",and choice the board's port.
  10. Click "Sketch">"Include Library">"Add .zip Library...",and open "Needed-library.zip" then choice "Wire.zip" and "MPU6050".  
  11. Click "Verify" that is in left upper corner of window.  
  12. If not has error message in terminal,you can click "Upload" that is next to "Verify".
  13. Start using.
# Matetial information
  - About servo moter:  
      - The Servo moter has wires of three coler:    
        |coloer of line|definition|  
        |-------|---------|  
        |ORANGE|SIGNAL|  
        |RED|VCC(+5V)|  
        |BROWN|GND(-)|
      - The definition of pin of servo is in ThreeAxisStabilizerDrive.ino **13ln** "
      `int16_t servopin[3]={3,5,6};//the servo pin in Arduino,definition is x,y,z`".if you want to change the pin,please change the value of the array.  
      - The pin of servo motor need support PWM signal output.if you do not know what pin is support PWM output,you see the [Arduino document](https://docs.arduino.cc/hardware/).
      - Genral servo only can rotate between 0 to 180 degrees;
  - About MPU6050:
    - The sencer use I2C protocol.(About pin of I2C defintion and detail of I2C,please see[Arduino document](https://docs.arduino.cc/language-reference/en/functions/communication/wire/) )
    - About it founctions and more information,please see [I2Cdecv](https://www.i2cdevlib.com/docs/html/class_m_p_u6050.html).
# Library information
  There is display detail information of library.if you have time,I am highly recommended to go to see.library of Needed-library is from there.
  - [Wire](https://github.com/esp8266/Arduino/tree/master/libraries/Wire)
  - [MPU6050](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050)
  - [Servo](https://github.com/arduino-libraries/Servo)