# About the program
      This program is my techknowledge homework.if you needed,you can use and modify the program,but *"do not profit from it"*.The program has three part,ThreeAxisStbilizerDrive,Needed-library and testingcode.ThreeAxisStbilizerDrive is main code,and it is the run in the Arduino board.testingcode store the code of not verification ,so if you could not write code or you could not understand,it is recommended not to move there code to ThreeAxisStbilizerDrive.Needed-library is saving the library that is ThreeAxisStbilizerDrive need.about those library information,you can see the "library information".
# How to use the program
  1. Prepare material of the following list:  
    - a Arduino board(EX:Arduino UNO,Arduino NANO)  
    - a USB wire that can cannect the computer with Arduino Board  
    - a MPU6050  
    - three of servo motor  
    - a lot of dupont lines  
    - it is best to prepare a Arduino shield.  
  2. Assemble the circuit.  
  - it is the circrit diagram as follow
    ![circuit diagram](https://github.com/KANA-exe/Three-axis-stabilizer-with-Arduino/blob/main/Screenshot%202024-12-12%20054618.png?raw=true)
  3. Download the [.zip](https://github.com/KANA-exe/Three-axis-stabilizer-with-Arduino/archive/refs/heads/main.zip) of this program and extract it.
  4. Connect the Arduino board and the computer.
  5. Check the Port of the Arduino board.  
    Steps in Windows11 as following:  
    - Click Windows+R on keyboard.  
    - Input "devmgmt.msc".  
    - Find "Ports (COM & LPT)" and double clict it.  
    - Find port of arduino board,and it may display "Arduno XXXX CH340 (COM?) ".  
    - log port of Arduino board in paper or other space. (it is "com?","?" is a number).
  6. Install and open [Arduino IDE](https://www.arduino.cc/en/software).(About that you can see Arduino's website)  
  7. Open "Three-axis-stabilizer-with-Arduino">"ThreeAxisStabilizerDrive">"ThreeAxisStabilizerDrive.ino".  
  8. Click "Tools">"Board">"Arduino AVR Boards",then find your board's type and click it. 
  9. Click "Tools">"Port",and choice the board's port.
  10. Click "Sketch">"Include Library">"Add .zip Library...",and open "Needed-library.zip" then choice "Wire.zip" and "MPU6050".  
  11. Click "Verify" that is in left upper corner of window.  
  12. If not has error message in terminal,you can click "Upload" that is next to "Verify".
  13. Start using.