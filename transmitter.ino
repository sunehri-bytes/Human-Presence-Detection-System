#include <SPI.h>
#include <RF24.h>
#include <HardwareSerial.h>

HardwareSerial radar(2);  // C1001 on UART2: RX=16, TX=17

RF24 radio(5, 4);         // CE=GPIO5, CSN=GPIO4
const byte address[6] = "00001";  // Must match receiver exactly
bool humanDetected = false;
bool prevHumanDetected = false;
unsigned long lastHumanSeen = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== Transmitter Started - Human Detection  = = =\n");
  radar.begin(115200, SERIAL_8N1, 16, 17);

  if (!radio.begin()) {
    Serial.println("nRF24L01 failed to initialize! Check wiring/power");
    while (1);
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);       // Max range
  radio.setDataRate(RF24_250KBPS);     // Better penetration through walls
  radio.setRetries(15, 15);            // Reliable delivery
  radio.stopListening();               // Transmitter mode

  Serial.println("Radio ready - listening for sensor...");
}

void loop() {
  // Read from C1001
  while (radar.available()) {
    radar.read();                    // Consume bytes
    lastHumanSeen = millis();
  }

  // Update detection state
  humanDetected = (millis() - lastHumanSeen < 1500);

  // Send only when state changes (saves airtime & power)
  if (humanDetected != prevHumanDetected) {
    char message = humanDetected ? 'H' : 'N';
    bool success = radio.write(&message, sizeof(message));

    Serial.print(humanDetected ? "HUMAN DETECTED" : "NO HUMAN");
    Serial.print(" -> Sending '");
    Serial.print(message);
    Serial.print("'  ");
    Serial.println(success ? "OK" : "FAILED");

    prevHumanDetected = humanDetected;
  }

  delay(200);  // Loop about 5 times per second
}
