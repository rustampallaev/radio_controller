
#include "Arduino.h"
#include "radio.hpp"
#include "tft.hpp"
#include "joystick.h"

#define RADIO_SEND_TIME    1000

int radio_send_timestamp = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Start");
    
    tft_init();
    joystick_init();
    radio_init();

    radio_send_timestamp = millis();

    tft_put_string("hello",  tft_width() / 2, tft_height() / 2 );
}

void loop()
{
    tft_turn_off_loop();
    radio_loop();
    joystick_loop();
}
