// The circuit has two buttons that will turn on LED's in a certain way. Thw LED's will also turn on a 
// RGB LED when one of the normal LED's is turned on

// Muhammad Bin Nauman mbn304
// Performing Robots 
// due 14/09/2020

void setup()
{
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);	// all the pins that corrospond to the LED and RGB LED
  pinMode(8, OUTPUT);	// have been assigned as output
  
  pinMode(2, INPUT);	// all the pins that corrospond to the buttons have been assigned as input 
  pinMode(3, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  
  int switch1 = digitalRead(2);	// the two variable will read whether or not the one of the buttons is pressed
  int switch2 = digitalRead(3);
  
  Serial.println(switch1 + "  " + switch2);	// printing out each value of the digital read
  
  if (switch1== HIGH)
  {
    delay(500);
    digitalWrite(8, HIGH);		// if the first switch is pressed
    digitalWrite(9, LOW);		// each of the LEDs will turn on one by one 
    digitalWrite(10,LOW);		// while turing off the previous LED
    
    delay(500);
  	digitalWrite(8, LOW);
    digitalWrite(9, HIGH);		// Whenever one the LED turns on a corrosponding color
    digitalWrite(10,LOW);		// on the RGB LED will turn on 
    delay(500);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10,HIGH);
  }
  
  if (switch2 == HIGH)
  {
  	digitalWrite(8, HIGH);	// if the second switch is pressed all the LEDs will turn on
    digitalWrite(9, HIGH);	// The RGB LED will also turn on all its color resulting in the color white
    digitalWrite(10,HIGH);
    
  }
  if (switch1 == LOW && switch2 == LOW)
  {
  	digitalWrite(8, LOW);
    digitalWrite(9, LOW);		// if none of the switch is pressed no LED will turn on
    digitalWrite(10,LOW);		// same goes for the RGB LED
  }

}