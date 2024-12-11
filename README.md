# About the program
      This program is my techknowledge homework.if you needed,you can use and modify the program,but *"do not profit from it"*.The program has three part,ThreeAxisStbilizerDrive,Needed-library and testingcode.ThreeAxisStbilizerDrive is main code,and it is the run in the Arduino board.testingcode store the code of not verification ,so if you could not write code or you could not understand,it is recommended not to move there code to ThreeAxisStbilizerDrive.Needed-library is saving the library that is ThreeAxisStbilizerDrive need.about those library information,you can see the "library information".
# How to use the program
  - Prepare material of the following list:  
    - a Arduino board(EX:Arduino UNO,Arduino NANO)  
    - a USB wire that can cannect the computer with Arduino Board  
    - a MPU6050  
    - three of servo motor  
    - a lot of dupont lines  
    - it is best to prepare a Arduino shield.  
  - Assemble the circuit.  
    - 
  - Download the .zip of this program and extract it.
  - Connect the Arduino board and the computer.
  - Check the Port of the Arduino board.  
    Steps in Windows11 as following:  
    - Click Windows+R on keyboard.  
    - Input "devmgmt.msc".  
    - Find "Ports (COM & LPT)" and double clict it.  
    - Find port of arduino board,and it may display "Arduno XXXX CH340 (COM?) ".  
    - log port of Arduino board in paper or other space. (it is "com?","?" is a number).
  - Install and open Arduino IDE.(About that you can see Arduino's website)  
  - Open "Three-axis-stabilizer-with-Arduino">"ThreeAxisStabilizerDrive">"ThreeAxisStabilizerDrive.ino".  
  - Click "Tools">"Board">"Arduino AVR Boards",then find your board's type and click it. 
  - Click "Tools">"Port",and choice the board's port.
  - Click "Sketch">"Include Library">"Add .zip Library...",and open "Needed-library.zip" then choice "Wire.zip" and "MPU6050".  
  - Click "Verify" that is in left upper corner of window.  
  - If not has error message in terminal,you can click "Upload" that is next to "Verify".
  - Start using.