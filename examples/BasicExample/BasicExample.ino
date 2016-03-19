#include <Jink.h>

const int led = 13;

void draw_text(String str, int x, int y)
{
	Jink.setColor(BLACK, WHITE);
	Jink.clear();
	Jink.setEnglishFont(ASCII64);
	Jink.dispString(str, x, y);
	Jink.udpate();
	delay(3000);
}

void setup(void)
{
	pinMode(led, OUTPUT);
	digitalWrite(led, LOW);
	Jink.begin(115200,8,9,10); // Baudrate, RX, TX, WAKEUP
}

void loop(void)
{
	// Draw some text into e-display screen
	draw_text("Hello World !", 200,250);
	draw_text("That's an awesome display !", 20,250);
	
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


