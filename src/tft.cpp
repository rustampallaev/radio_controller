#include <TFT_eSPI.h>
#include <SPI.h>
#include "bmp.h"

#define TFT_OFF_TIME    5000

#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif

#ifndef TFT_SLPIN
#define TFT_SLPIN   0x10
#endif

#define TFT_MOSI            19
#define TFT_SCLK            18
#define TFT_CS              5
#define TFT_DC              16
#define TFT_RST             23

#define TFT_BL          4  // Display backlight control pin

#define TEXT_BACK_COLOR     TFT_BLACK
#define TEXT_FONT_COLOR     TFT_WHITE

TFT_eSPI tft = TFT_eSPI(135, 240);

int tft_off_timestamp = 0;

void tft_turn_off_loop()
{
    if (millis() - tft_off_timestamp >= TFT_OFF_TIME && digitalRead(TFT_BL) != 0) {
        digitalWrite(TFT_BL, TFT_BACKLIGHT_OFF);
        Serial.println("Turning display off");
    } else if (millis() - tft_off_timestamp < TFT_OFF_TIME && digitalRead(TFT_BL) == 0) {
        digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
        Serial.println("Turning display on");
    }
}

void tft_init()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TEXT_BACK_COLOR);
    tft.setTextSize(2);
    tft.setTextColor(TEXT_FONT_COLOR);
    tft.setCursor(0, 0);
    tft.setTextDatum(TL_DATUM);
    tft.setTextSize(2);

    if (TFT_BL > 0) { // TFT_BL has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
         pinMode(TFT_BL, OUTPUT); // Set backlight pin to output mode
         digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
    }
    
    tft.setSwapBytes(true);
    tft.pushImage(0, 0,  240, 135, ttgo);

    tft_off_timestamp = millis();
}

void tft_put_string(String str, int x, int y) {
    uint16_t cwidth = tft.textWidth(str); // Find the pixel width of the string in the font
    uint16_t cheight = 8 * tft.textsize;
    tft.setTextColor(TEXT_FONT_COLOR, TEXT_BACK_COLOR);
    tft.fillRect(x, y, cwidth, cheight, TEXT_BACK_COLOR);
    tft.drawString(str, x, y);
}

void tft_fill_screen(uint16_t color) {
    tft.fillScreen(color);
}

int16_t tft_width() {
  return tft.width();
}

int16_t tft_height() {
  return tft.height();
}