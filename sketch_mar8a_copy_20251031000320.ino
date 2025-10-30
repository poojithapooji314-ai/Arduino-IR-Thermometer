#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>
#include <Adafruit_MLX90614.h>

#define OLED_RESET -1  // Set to -1 if OLED reset pin is not used

// Initialize OLED and MLX90614 sensor
Adafruit_SSD1306 display(128, 32, &Wire, OLED_RESET);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(57600);
  Serial.println("Adafruit MLX90614 test");

  // Initialize MLX90614 IR sensor
  mlx.begin();

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.print("IR Thermometer Ready");
  display.display();
  delay(2000);
}

void loop() {
  display.clearDisplay();  // Clear OLED buffer

  // Display Ambient Temperature
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Ambient temp: ");
  display.print(mlx.readAmbientTempC());
  display.print(" C");

  // Display Object Temperature
  display.setCursor(0, 10);
  display.print("Object temp: ");
  display.print(mlx.readObjectTempC());
  display.print(" C");

  display.display();  // Update OLED display
  delay(2000);  // Refresh every 2 seconds
}