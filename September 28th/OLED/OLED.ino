// This program uses the Qwiic OLED screen and Qwiic Button. The program will check is both of the devices are connected to the redboard and 
//if one of the devices is missing it will run a infinite loop while giving a missing device message
// if all the devices are ready it will give a ready message for each device and will display the text ready on the OLED
// if the user presses the button the OLED will change the text to is pressed
// after the user lets go of the button the OLED will display a sentence telling the number of times the button is pressed/detected in the period of time
// pressing the button again the OLED will again display the Pressed text and again letting go of the button will tell how many times it is pressed


// Muhammad Bin Nauman mbn304
// Performing Robots 
// due 28/09/2020


//---------------------------------------------------------------------------------------------------------------------------------------------------------

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>             // importing the necessary libraries needed to run the program
#include <Adafruit_SSD1306.h>
#include <SparkFun_Qwiic_Button.h>

#define SCREEN_WIDTH 128              // OLED display width, in pixels
#define SCREEN_HEIGHT 64              // OLED display height, in pixels
#define OLED_RESET     4              // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0                // defined colors that can be used by the OLED but dont seem to work 
#define CYAN 0x07FF
#define YELLOW 0xFFE0

QwiicButton button;                 // defining the Qwiicbutton

int count = 0;                      // global variable for counting the amount of times the button was pressed

void setup() {
  Serial.begin(9600);  
  Wire.begin();                                           // join I2C bus


  if (button.begin() == false)
  {
    Serial.println("Device has not been detected! Infinite loop");          // if the button is not properly connecting than go into infinite loop
    while (1);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {                       // Address 0x3D for 128x64 and same as above but for OLED
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  Serial.println("button is ready");                                    // printing the ready status for both the OLED and Button
  Serial.println("OLED is ready");
}

void loop()
{
  Serial.println(count);
  if (button.isPressed() == true)
  {
    button_press();                                               // calling the function that displays READY on the OLED
  }

  if (button.isPressed() == false && count == 0)
  {
    no_button_press();                                          // calling the function that display Pressed on the OLED when button is pressed
  }
  if (button.isPressed()== false && count!=0)
  {
    button_num_pressed();                                       // calling the function that displays the number of times the button is presssed when the button is not being pressed
  }
}

void no_button_press(void) {
  display.clearDisplay();

  display.setTextSize(2);                     // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);                    // Start at top-left corner
  display.println(F("READY"));                // display the text READY on the OLED

  display.display();
}

void button_press(void) {
  display.clearDisplay();

  display.setTextSize(2);                     // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);                    // Start at top-left corner
  display.println(F("PRESSED"));              // display the text PRESSED on OLED

  count++;
  
  display.display();
}

void button_num_pressed(void) {
  display.clearDisplay();

  display.setTextSize(1);                           // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);              // Draw white text
  display.setCursor(0, 0);                          // Start at top-left corner
  display.println("The Button is Pressed " + String(count) + " amount of times");       // display the number of times the button press was detected when the button was pressed
  
  display.display();
}
