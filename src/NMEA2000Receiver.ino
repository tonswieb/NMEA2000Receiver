// Demo: NMEA2000 library. Sends NMEA2000 to WiFi in NMEA0183 and SeaSmart format.
//
// The code has been tested with ESP32.

#define ESP32_CAN_TX_PIN GPIO_NUM_12
#define ESP32_CAN_RX_PIN GPIO_NUM_13
#include <NMEA2000_CAN.h>

// Set the information for other bus devices, which messages we support
const unsigned long ReceiveMessages[] PROGMEM={130310L,130311L,130312L,0};

void setup() {
  Serial.begin(115200);
  NMEA2000.SetN2kCANMsgBufSize(8);
  NMEA2000.SetN2kCANReceiveFrameBufSize(100);
  NMEA2000.SetForwardStream(&Serial);  // PC output on due native port
  NMEA2000.SetForwardType(tNMEA2000::fwdt_Text); // Show in clear text
  NMEA2000.ExtendReceiveMessages(ReceiveMessages);
  NMEA2000.Open();
  Serial.println("NMEA200 initialized.");
}

void loop() {
  NMEA2000.ParseMessages();
  // Dummy to empty input buffer to avoid board to stuck with e.g. NMEA Reader
  if ( Serial.available() ) { Serial.read(); } 
}
