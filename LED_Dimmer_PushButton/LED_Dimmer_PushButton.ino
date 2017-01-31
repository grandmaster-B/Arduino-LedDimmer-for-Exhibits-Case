/**********************************
Arduino Code for an LED Dimmer for the Specimens Exhibit
Special specimen needs to have limited light exposure

User will press button
light will fade on for set duration
and then the light will fade out.

Developed by Bob Belote for the Field Museum 2017
bbelote@gmail.com
***********************************/


int led = 9; //pin for the LED
int button = 8; //pin for the button
int buttonPressLED = 2;

int brightness; //value between 0 and 255 for PWM led intensity
int fadeAmount = 5; //step to increment the PWM

unsigned long previousMillis = 0;
const long resetTime = 12000;

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
}

void loop() 
{
	unsigned long currentMillis = millis();

	//Serial.print(digitalRead(button));

	if (digitalRead(button) == HIGH)
	{
		digitalWrite(buttonPressLED, HIGH);
		//FadeIn();
	}
	else if (digitalRead(button) == LOW)
	{
		digitalWrite(buttonPressLED, LOW);
	}

	//Checls for button Hit to start LED fade in
	if (digitalRead(button) == HIGH && lightOn == false) 
	{
		delay(10);
		lightOn == true;
		previousMillis = currentMillis;
		//Serial.print(" Button Press ");
	}

	if (lightOn == true && currentMillis - previousMillis >= resetTime)
	{
		lightOn == false;
	}

	if (lightOn == true && brightness < 255)
	{
		analogWrite(led, brightness);
		brightness += fadeAmount;
		delay(30);
	}

	if (lightOn == false && brightness > 0) 
	{
		analogWrite(led, brightness);
		brightness -= fadeAmount;
		delay(30);
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
