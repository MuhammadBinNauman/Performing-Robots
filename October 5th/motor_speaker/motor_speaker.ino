// The robot will the tank made eariler in the class. the robot has two DC motors that are connected to wheels that are in turn powered by a battery. 
//The robot also has a speaker this is powered by the red board and plays music throught the SD card
// The Redboard is powered via battery that will allow it to run fully disconnected form the laptop
// The robot has a button that when pressed will allow it to move in a set patteren before stopping and will start moving the button is pressed again
// The robot will move forward, right, left and forward when ever the button is pressed 


// Muhammad Bin Nauman mbn304
// Performing Robots 
// due 5/10/2020



#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h"                                   //Contains #defines for common SCMD register names and values
#include "Wire.h"
#include <SparkFun_Qwiic_Button.h>                          // importing all the necessary libraries 
#include <SPI.h>
#include <Wire.h>
#include "SparkFun_Qwiic_MP3_Trigger_Arduino_Library.h" 

MP3TRIGGER mp3;
SCMD myMotorDriver;                      //This creates the main object of one motor driver and connected slaves.
QwiicButton button;                       // defining the Qwiic button

int button_state;                         // varible that allows the movements to be triggered

void setup() {
  pinMode(8, INPUT_PULLUP);                                    //Use to halt motor movement (ground)
  Serial.begin(9600);
  Serial.println("Program has started.");
  myMotorDriver.settings.commInterface = I2C_MODE;            //  .commInter face is I2C_MODE
  myMotorDriver.settings.I2CAddress = 0x5D;                   // set address if I2C configuration selected with the config jumpers config pattern is "1000" (default) on board for address 0x5D
  myMotorDriver.settings.chipSelectPin = 10;                  //  set chip select if SPI selected with the config jumpers

  while ( myMotorDriver.begin() != 0xA9 )                     //Wait until a valid ID word is returned
  {
    Serial.println( "ID mismatch, trying again" );
    delay(500);
  }
  Serial.println( "ID matches 0xA9" );
  Serial.print("Waiting for enumeration...");                 //  Check to make sure the driver is done looking for slaves before beginning

  while ( myMotorDriver.ready() == false );

  Serial.println("Done.");
  Serial.println();

  while ( myMotorDriver.busy() );                           //Waits until the SCMD is available.
  myMotorDriver.inversionMode(1, 1);                        //invert motor 1

  while ( myMotorDriver.busy() );
  myMotorDriver.enable();                                   //Enables the output driver hardware


  if (button.begin() == false)
  {
    Serial.println("Device has not been detected! Infinite loop");          // if the button is not properly connecting than go into infinite loop
    while (1);
  }

   if (mp3.begin() == false)
  {
    Serial.println("Qwiic MP3 not connected");                      // check to see if the hamburger is connected
    while (1);
  }

  mp3.setVolume(10);                                                //setting the volume

  mp3.playTrack(1);                                                 //Begin playing the first track on the SD card
  
  Serial.println("button is ready");
  Serial.println("hamburger is ready");                             // telling the user that the devices are ready

  button_state = 0;                                                 // turnning the button pressed state to zero so it can be pressed to trigger movements
}

#define LEFT_MOTOR 0                                                // defining the motors
#define RIGHT_MOTOR 1

void loop() {

  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);                      //Stop motor
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);                     //Stop motor
  while (digitalRead(8) == 0);                                    //Hold if jumper is placed between pin 8 and ground

  if (button.isPressed() == true)
  {
    button_state = 1;                                           // all the movements will occur if the button is pressed
  }

  if (button_state == 1)
  {

    for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);             // the robot will first move forward then left then right and then forward again. it will also jerk in the end to resent the position
      delay(3);
    }
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(3);
    }



    for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i / 2);
      delay(3);
    }
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i / 2);
      delay(3);
    }



    for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i / 2);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(3);
    }
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i / 2);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(3);
    }



    for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(3);
    }
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(3);
    }


    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(3);
    }
    button_state = 0;                                             // stop the loop for occuring again unless the button is pressed again
  }
}
