/**********************************
Arduino Code for an LED Dimmer for the Specimens Exhibit
Special specimen needs to have limited light exposure

User will press button
light will fade on for set duration
and then the light will fade out.

Developed by Bob Belote for the Field Museum 2017
bbelote@gmail.com
***********************************/


int led = 11; //pin for the LED
int button = 13; //pin for the button
int buttonPressLED = 2;

int brightness; //value between 0 and 255 for PWM led intensity
int fadeAmount = 1; //step to increment the PWM

unsigned long previousMillis = 0; //stores the millis count for the timer function
const long resetTime = 8000; //led on duration in miliseconds

bool lightOn; //gates the light state


void setup() 
{
	//light will be in off mode ar start up
	lightOn = false;

	//define pin states
	pinMode(led, OUTPUT); 
	pinMode(button, INPUT);

	//sets the btightness of the led to zero (off)
	brightness = 0;
	analogWrite(led, brightness);

	Serial.begin(9600);
}

void loop() 
{
	unsigned long currentMillis = millis(); //holds the current millis value

	//Checls for button Hit to start LED fade in
	if (digitalRead(button) == HIGH && lightOn == false) 
	{
		delay(10); //debounce pause for button press
		lightOn = true; //sets light state for on
		previousMillis = currentMillis;
		brightness = 0; //resets brightness to base for smooth fade on
	}

	//when reset duration has elapsed this will set the light state to off
	//and begin the led fadout out process.
	if (lightOn == true && currentMillis - previousMillis >= resetTime)
	{
		lightOn = false;
	}

	//calls led fade on method while brightness is below threshhold
	//set brightness value here (0-255) to determine max brightness
	if (lightOn == true && brightness < 175)
	{
		FadeOn();
	}

	//when lightOn bool is set to false this calls the led fade off method
	if (lightOn == false && brightness >= 0) 
	{
		FadeOff();
	}
}

//method called to increase the brightness value of the PWM
//change the fade amount or delay to adjust fade speed
void FadeOn() 
{
	analogWrite(led, brightness);
	brightness += fadeAmount;
	delay(20);
}

//method called to decrease the brightness value of the PWM
//change the fade amount or delay to adjust fade speed
void FadeOff()
{
	analogWrite(led, brightness);
	brightness -= fadeAmount;
	delay(20);
}
