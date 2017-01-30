/**********************************
Arduino Code for an LED Dimmer for the Specimens Exhibit
Special specimen needs to have limited light exposure

User will press button
light will fade on for set duration
and then the light will fade out.

Developed by Bob Belote for the Field Museum 2017
bbelote@gmail.com
***********************************/

#include <SimpleTimer.h>

SimpleTimer timer;


int led = 9;
int button = 10;
int resetTimer;

int brightness;
int fadeAmount = 5;

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
	timer.run();


	if (digitalRead(button) == HIGH && lightOn == false) 
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

void FadeOn() 
{
	analogWrite(led, brightness);
	brightness += fadeAmount;
	delay(30);
}

void FadeOff()
{
	analogWrite(led, brightness);
	brightness -= fadeAmount;
	delay(30);
}

void LightsOut()
{
	lightOn = false;
}

void repeatMe() 
{
	Serial.print("Uptime (s): ");
	Serial.println(millis() / 1000);
}
