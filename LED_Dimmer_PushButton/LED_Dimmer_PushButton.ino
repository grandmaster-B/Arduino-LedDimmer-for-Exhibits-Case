/**********************************
Arduino Code for an LED Dimmer for the Specimens Exhibit
Special specimen needs to have limited light exposure

User will press button
light will fade on for set duration
and then the light will fade out.

requires the SimpleTimer Library
(included in the Git Repo)
https://github.com/grandmaster-B/Arduino-LedDimmer-for-Exhibits-Case

Developed by Bob Belote for the Field Museum 2017
bbelote@gmail.com
***********************************/

#include <SimpleTimer.h>

SimpleTimer timer;

int led = 9; //pin for the LED
int button = 10; //pin for the button

int brightness; //value between 0 and 255 for PWM led intensity
int fadeAmount = 5; //step to increment the PWM

bool lightOn;


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
	timer.setInterval(1000, repeatMe);
}

void loop() 
{
	timer.run(); //Runs Timer Logic from the Library


	//Checls for button Hit to start LED fade in
	if (digitalRead(button) == LOW && lightOn == false) 
	{
		lightOn == true;
		timer.setInterval(10000, LightsOut);
	}

	if (lightOn == true && brightness < 255)
	{
		FadeOn();
	}

	if (lightOn == false && brightness > 0) 
	{
		FadeOff();
	}

}

//method called to increase the brightness value of the PWM
void FadeOn() 
{
	analogWrite(led, brightness);
	brightness += fadeAmount;
	delay(30);
}

//method called to decrease the brightness value of the PWM
void FadeOff()
{
	analogWrite(led, brightness);
	brightness -= fadeAmount;
	delay(30);
}

//method called to change the light state at the end of the Timer
void LightsOut()
{
	lightOn = false;
}

//Method for the Timer Lib
void repeatMe() 
{
	//Serial.print("Uptime (s): ");
	//Serial.println(millis() / 1000);
}
