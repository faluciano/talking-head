#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <unordered_map>

IRrecv irrecv(15);
decode_results results;

void setup()
{
  irrecv.enableIRIn();
  Serial.begin(115200);
}

void loop()
{
  if (irrecv.decode(&results))
  {
    switch (results.value)
    {
    case 0xFFA25D:
      Serial.println("One pressed");
      break;
    case 0xFF629D:
      Serial.println("Two pressed");
      break;
    case 0xFFE21D:
      Serial.println("Three pressed");
      break;
    case 0xFF22DD:
      Serial.println("Four pressed");
      break;
    case 0xFF02FD:
      Serial.println("Five pressed");
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