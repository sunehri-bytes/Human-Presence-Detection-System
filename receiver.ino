#include <SPI.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RF24 radio(5, 4);  // CE=GPIO5, CSN=GPIO4
const byte address[6] = "00001";  // Must match transmitter

String currentStatus = "Waiting...";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== Receiver Started ===\n");

  // OLED initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed! Check SDA=D21, SCL=D22, address (try 0x3D)");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("Waiting...");
  display.display();

  // nRF24L01
  if (!radio.begin()) {
    Serial.println("nRF24L01 failed! Check wiring/power");
    while (1);
  }

  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(15, 15);

  radio.startListening();
  Serial.println("Listening for messages...");
}

void loop() {
  if (radio.available()) {
    char message;
    radio.read(&message, sizeof(message));

    Serial.print("Received: '");
    Serial.print(message);
    Serial.println("'");

    String newStatus = (message == 'H') ? "HUMAN DETECTED" : "NO HUMAN";

    if (newStatus != currentStatus) {
      display.clearDisplay();
      display.setTextSize(2);

      if (message == 'H') {
        digitalWrite(BUZZER, HIGH);

        display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
        display.setTextColor(SSD1306_BLACK);
        display.setCursor(5, 15);
        display.println("HUMAN");
        display.setCursor(5, 40);
        display.println("DETECTED");
      } else {
        digitalWrite(BUZZER, LOW);

        display.setTextColor(SSD1306_WHITE);
        display.setCursor(10, 20);
        display.println("NO HUMAN");
      }

      display.display();
      currentStatus = newStatus;
    }
  }
}
