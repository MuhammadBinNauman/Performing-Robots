// Performing robot shakespear Play. the robot will perform a Hamlet. the scene that the robot will play will be the fencing match. the robot is preprogrmaed to make certain moves. 
// the robot will spin 180 degrees and move back to its position.
// the robot will then move forward. after that the robot will abruptly move and stop.
// the robot will then shuffle and then the robot will move right and left abruptly

// Muhammad Bin Nauman
// mbn304
// Performing Robots due 26/10/2020 



//***************************************************************************************************************************************************************************************

#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h"                                   //Contains #defines for common SCMD register names and values
#include "Wire.h"
#include <SparkFun_Qwiic_Button.h>                          // importing all the necessary libraries 
#include <SPI.h>
#include <Wire.h>
#include "SparkFun_Qwiic_MP3_Trigger_Arduino_Library.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128              // OLED display width, in pixels
#define SCREEN_HEIGHT 64              // OLED display height, in pixels
#define OLED_RESET     4              // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MP3TRIGGER mp3;
SCMD myMotorDriver;                      //This creates the main object of one motor driver and connected slaves.
QwiicButton button;                       // defining the Qwiic button

int button_state;                         // varible that allows the movements to be triggered


//************************************************************************************************************************************************************************************************

void setup() {
  pinMode(8, INPUT_PULLUP);                                    //Use to halt motor movement (ground)
  Serial.begin(9600);
  Serial.println("Program has started.");
  myMotorDriver.settings.commInterface = I2C_MODE;            //  .commInter face is I2C_MODE
  myMotorDriver.settings.I2CAddress = 0x5D;                   // set address if I2C configuration selected with the config jumpers config pattern is "1000" (default) on board for address 0x5D
  myMotorDriver.settings.chipSelectPin = 10;                  //  set chip select if SPI selected with the config jumpers
  Wire.begin();

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

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D))
  { // Address 0x3D for 128x64 and same as above but for OLED       // check to see if the OLED is connected
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  mp3.setVolume(10);                                                //setting the volume

  mp3.playTrack(1);                                                 //Begin playing the first track on the SD card

  Serial.println("button is ready");
  Serial.println("hamburge3r is ready");                             // telling the user that the devices are ready
  Serial.println("OLED is ready");

  button_state = 0;                                                 // turnning the button pressed state to zero so it can be pressed to trigger movements
}

#define LEFT_MOTOR 0                                                // defining the motors
#define RIGHT_MOTOR 1


//****************************************************************************************************************************************************************

void no_button_press(void) {
  display.clearDisplay();

  display.setTextSize(2);                                                     // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);                                        // Draw white text
  display.setCursor(0, 0);                                                   // Start at top-left corner
  display.println(F("PRESS     BUTTON TO START     Duel"));                // display the text READY on the OLED

  display.display();
}


void loop()
{
  if (button_state == 0)
  {
    no_button_press();
  }

  if (button.isPressed() == true && button_state == 0)
  {
    button_state = 1;                                           // all the movements will occur if the button is pressed
  }

  //-------------------------------
  if (button_state == 1)                                       // the robot will spin 180 degrees and move back to its position.
                                                              // the robot will then move forward. after that the robot will abruptly move and stop.
                                                              //the robot will then shuffle and then the robot will move right and left abruptly
  {
    for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);             
      delay(1);                                               
    }
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(1);
    }

        for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);           
      delay(1);                                               
    }
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      delay(1);
    }
        for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);           
      delay(1);                                               
    }
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      delay(1);
    }
     for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);             
      delay(1);                                               
    }
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(1);
    }
     for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);            
      delay(1);                                              
    }
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(1);
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

    for (int i = 0; i < 5; i ++)
    {
      for (int i = 0; i < 156; i++)
      {
        myMotorDriver.setDrive( LEFT_MOTOR, 0, i / 2);
        myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
        delay(1);
      }
      for (int i = 155; i > 0; i--)
      {
        myMotorDriver.setDrive( LEFT_MOTOR, 0, i / 2);
        myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
        delay(3);
      }


      for (int i = 0; i < 156; i++)
      {
        myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
        myMotorDriver.setDrive( RIGHT_MOTOR, 0, i / 2);
        delay(1);
      }
      for (int i = 155; i > 0; i--)
      {
        myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
        myMotorDriver.setDrive( RIGHT_MOTOR, 0, i / 2);
        delay(3);
      }
    }
    for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, i, 0);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);          
      delay(1);                                               
    }

      myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);

       for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);            
      delay(1);                                               
    }

      myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  }
  button_state = 0;                                                  // reset the button state to zero so everything can be done again
}
