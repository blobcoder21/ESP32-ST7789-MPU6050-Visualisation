#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TFT_eSPI.h>  // For the ST7789 screen
#include <SPI.h>

Adafruit_MPU6050 mpu;

// Create TFT instance
TFT_eSPI tft = TFT_eSPI();  // TFT instance

// Define custom I2C pins
#define SDA_PIN 21
#define SCL_PIN 22

void setup() {
  // Start serial for debugging
  Serial.begin(115200);

  // Initialize the TFT screen
  tft.init();
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK);

  // Initialize the I2C communication with custom pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize the MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  Serial.println("MPU6050 found!");

  // Configure the accelerometer and gyroscope range
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);  // ±2g
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);  // ±250 degrees/s
}

void loop() {
  // Get sensor data
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;

  // Get the accelerometer, gyroscope, and temperature readings
  mpu.getEvent(&accel, &gyro, &temp);

  // Clear the screen
  tft.fillScreen(TFT_BLACK);

  // Display Accelerometer values
  tft.setCursor(10, 20);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.print("Accel X: ");
  tft.println(accel.acceleration.x, 2);
  tft.print("Accel Y: ");
  tft.println(accel.acceleration.y, 2);
  tft.print("Accel Z: ");
  tft.println(accel.acceleration.z, 2);

  // Display Gyroscope values
  tft.setCursor(10, 100);
  tft.print("Gyro X: ");
  tft.println(gyro.gyro.x, 2);
  tft.print("Gyro Y: ");
  tft.println(gyro.gyro.y, 2);
  tft.print("Gyro Z: ");
  tft.println(gyro.gyro.z, 2);

  // Display Temperature value
  tft.setCursor(10, 180);
  tft.print("Temp: ");
  tft.println(temp.temperature, 2);

  // Wait for a bit before refreshing the display
  delay(500);
}
