#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);
uint8_t success;                          // Flag to check if there was an error with the PN532
uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
uint8_t uidLength;
 
void setup(void)
{
  Serial.begin(115200);
  Serial.print("here we go!");
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
    }
  nfc.SAMConfig();
}
void loop(void)
{
  for(int i = 0; i < sizeof(uid); i++){
    Serial.println(uid[i]);
  }
  Serial.println(uidLength);
  Serial.print("PN532_MIFARE_ISO14443A: ");
  Serial.println(PN532_MIFARE_ISO14443A);
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  Serial.print("Success: ");
  Serial.println(success);
  for(int i = 0; i < sizeof(uid); i++)
  {
    Serial.print(uid[i]);
  }
  Serial.println(uidLength);
  delay(10000);
  
  Serial.println("\n\nSend a character to run the mem dumper again!");
  Serial.flush();
  while (!Serial.available());
  while (Serial.available()) {
  Serial.read();
  }
  Serial.flush();
}
