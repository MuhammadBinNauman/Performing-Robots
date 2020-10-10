// THE PARTY TANK
// The robot will the tank made eariler in the class. the robot has two DC motors that are connected to wheels that are in turn powered by a battery.
//The robot also has a speaker this is powered by the red board and plays music throught the SD card
// The Redboard is powered via battery that will allow it to run fully disconnected form the laptop
// The robot has a button that when pressed will allow it to move in a set patteren before stopping and will start moving the button is pressed again
// The robot also has a OLED that displays visuals similar to party visual effects
// The robot will move forward, spin clockwise, then spin counter clockwise, then do a little dance, then spin again and do a little dance again.


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
  display.println(F("PRESS     BUTTON TO START     PARTY"));                // display the text READY on the OLED

  display.display();
}

void line()
{
  int16_t i;

  display.clearDisplay(); // Clear display buffer

  for (i = 0; i < display.width(); i += 2)
  {
    display.drawLine(i, 0, i, display.height() - 1, SSD1306_WHITE);             // draw vertical lines across the screen followed by horozontal and then add the text GO in inc=verse color
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for (i = 0; i < display.height(); i += 2)
  {
    display.drawLine(0, i, display.width() - 1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  display.setTextSize(4);                     // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_INVERSE);        // Draw white text
  display.setCursor(32, 16);                    // Start at top-left corner
  display.println(F("GO!!"));                // display the text READY on the OLED
  display.display();
  delay(400);
}

void curve_line()
{
  int16_t i;                                                                    // draw curved lines at two opposite edges of the OLED and then display the charecters #$%&

  display.clearDisplay();                                                       // Clear display buffer

  for (i = 0; i < display.width(); i += 5)
  {
    display.drawLine(0, i, i, display.height() - 1, SSD1306_WHITE);
    display.display();                                                        // Update screen with each newly-drawn line
    delay(1);
  }
  for (i = 0; i < display.height(); i += 5)
  {
    display.drawLine(i, 0, display.width() - 1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  display.setTextSize(3);                     // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(32, 16);                    // Start at top-left corner
  display.println(F("#$%&"));                // display the text READY on the OLED
  display.display();
  delay(400);
}


void grow_circle()
{
  int16_t i;
  display.clearDisplay();

  for (int16_t i = 10; i < max(display.width(), display.height()) / 2; i += 2)
  {
    display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);          // draw a circle that pulses across the screen making a circle with each pulse that will grow bigger with each pulse
    display.display();
    delay(1);
    for (int16_t i = 10; i < max(display.width(), display.height()) / 2; i += 2)
    {
      display.drawCircle(display.width() / 2, display.height() / 2, i - 1, SSD1306_INVERSE);
      display.display();
      delay(1);
    }
  }
}

void grow_circle2()
{
  int16_t i;
  display.clearDisplay();

  for (int16_t i = 10; i < max(display.width(), display.height()) / 2; i += 2)
  {
    display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);
    display.display();
    delay(1);
    for (int16_t i = 10; i < max(display.width(), display.height()) / 2; i += 2)                // same as above
    {
      display.drawCircle(display.width() / 2, display.height() / 2, i - 1, SSD1306_INVERSE);
      display.display();
      delay(1);
    }
  }
}


void tri_rec()
{
  display.clearDisplay();

  for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 5)
  {
    display.drawTriangle(
      display.width() / 2  , display.height() / 2 - i,
      display.width() / 2 - i, display.height() / 2 + i,
      display.width() / 2 + i, display.height() / 2 + i, SSD1306_WHITE);                    // draw a rectangle that has incverse colors that will pulse in the opposite direction and will create a triangle with each pulse that will grow larger with each pulse
    display.display();
    delay(1);
    for (int16_t i = 0; i < display.height() / 2 - 2; i += 2)
    {
      display.fillRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
      display.height() / 4, SSD1306_INVERSE);
      display.display();
      delay(1);
    }
  }
}
//***********************************************************************************************************************************************************

void loop() {

  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);                      //Stop motor
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);                     //Stop motor
  while (digitalRead(8) == 0);                                    //Hold if jumper is placed between pin 8 and ground


  if (button_state == 0)
  {
    no_button_press();
  }

  if (button.isPressed() == true)
  {
    button_state = 1;                                           // all the movements will occur if the button is pressed
  }

  if (button_state == 1)
  {
    line();
    for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);             // The robot will move forward, spin clockwise, then spin counter clockwise, then do a little dance, then spin again and do a little dance again.
      delay(1);                                               // while also displaying the visuals on the OLED
    }
    curve_line();
    for (int i = 255; i > 0; i--)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(1);
    }



    for (int i = 0; i < 256; i++)
    {
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i / 2);
      delay(3);
    }
    grow_circle();
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
    grow_circle2();
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
      myMotorDriver.setDrive( LEFT_MOTOR, 0, i / 2);
      myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
      delay(3);
    }
    tri_rec();
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
  }
  button_state = 0;   // reset the button state to zero so everything can be done again                                  
}
