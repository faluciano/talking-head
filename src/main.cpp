#include <IRremoteESP8266.h>
#include <IRrecv.h>
// Include required libraries
#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"
#include "WiFiMulti.h"

// microSD Card Reader connections
#define SD_CS 5
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_SCK 18

// I2S Connections
#define I2S_DOUT 22
#define I2S_BCLK 26
#define I2S_LRC 25

WiFiMulti wifiMulti;
String ssid = "*";
String password = "*";

Audio audio;
IRrecv irrecv(15);
decode_results results;

void setup()
{
  // pinMode(SD_CS, OUTPUT);
  // digitalWrite(SD_CS, HIGH);

  // Initialize SPI bus for microSD Card
  // SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

  Serial.begin(115200);

  // if (!SD.begin(SD_CS))
  // {
  //   Serial.println("Error accessing microSD card!");
  //   while (true)
  //     ;
  // }
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(ssid.c_str(), password.c_str());
  wifiMulti.run();
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.disconnect(true);
    wifiMulti.run();
  }
  // Setup I2S
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

  // Set Volume
  audio.setVolume(80);
  irrecv.enableIRIn();
}

void loop()
{
  audio.loop();
  if (irrecv.decode(&results))
  {
    switch (results.value)
    {
    case 0xFFA25D:
      Serial.println("One pressed");
      audio.connecttospeech("Hi Felix", "en"); // audio.loop();
      break;
    case 0xFF629D:
      Serial.println("Two pressed");
      audio.connecttospeech("What is this", "en");
      break;
    case 0xFFE21D:
      Serial.println("Three pressed");
      audio.connecttospeech("Hello Binky", "en");
      break;
    case 0xFF22DD:
      Serial.println("Four pressed");
      audio.connecttospeech("Hello Santiago", "en");
      break;
    case 0xFF02FD:
      Serial.println("Five pressed");
      audio.connecttospeech("", "en");
      break;
    case 0xFFC23D:
      Serial.println("Six pressed");
      break;
    case 0xFFE01F:
      Serial.println("Seven pressed");
      break;
    case 0xFFA857:
      Serial.println("Eight pressed");
      break;
    case 0xFF906F:
      Serial.println("Nine pressed");
      break;
    case 0xFF6897:
      Serial.println("* pressed");
      break;
    case 0xFF9867:
      Serial.println("0 pressed");
      break;
    case 0xFFB04F:
      Serial.println("# pressed");
      break;
    case 0xFF18E7:
      Serial.println("Up arrow hit");
      break;
    case 0xFF10EF:
      Serial.println("Left arrow hit");
      break;
    case 0xFF38C7:
      Serial.println("Ok hit");
      audio.connecttospeech("Initiating self destruct sequence", "en");
      break;
    case 0xFF5AA5:
      Serial.println("Right arrow hit");
      break;
    case 0xFF4AB5:
      Serial.println("Down Arrow hit");
      break;
    default:
      Serial.print("Noise? ");
      Serial.println(results.value, HEX);
      break;
    }

    delay(1000);
    irrecv.resume();
  }
}