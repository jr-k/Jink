#include <Jink.h>

const int led = 13;

void setup(void)
{
	pinMode(led, OUTPUT);
	digitalWrite(led, LOW);
	Jink.begin(115200,8,9); // Baudrate, RX, TX
}

void loop(void)
{
	// Draw some text into e-display screen 
  Jink.persistText("Hello World !");
  Jink.persistTextLn("That's an awesome display !");
  Jink.persistTextLn("You can add some text ");
  Jink.persistText("on the same line");
  Jink.persistTextLn("Or another with 'persistTextLn'");
  Jink.flushText(0, 30, 48); // x, y, fontSize(32, 48, 64)
	
	// Low energy consumption mode
	Jink.enterStopmode();
  
	while (1){
		// Infinite bliking
		digitalWrite(13, HIGH);
		delay(1000);
		digitalWrite(13, LOW);
		delay(1000);
	}
}

