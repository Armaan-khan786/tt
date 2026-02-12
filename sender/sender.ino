#define RXD2 16
#define TXD2 17

HardwareSerial uart(2);

enum SenderState {
  S_START,
  S_SEND,
  S_DONE
};

SenderState state = S_START;
int indexMsg = 0;

const char* logs[100] = {
"ESP32 Power ON",
"Bootloader Started",
"Chip Revision Detected",
"Flash Initialization",
"Flash Size 4MB",
"Partition Table Loaded",
"Firmware Image Verified",
"Checksum Validation OK",
"Clock Configuration Done",
"RTC Initialization Complete",
"GPIO Initialization Done",
"UART Driver Started",
"I2C Bus Initialized",
"SPI Bus Initialized",
"WiFi Stack Init",
"WiFi Connected",
"IP Address Assigned",
"Bluetooth Init",
"BLE Stack Ready",
"NVS Flash Init",
"EEPROM Ready",
"Heap Memory OK",
"PSRAM Detected",
"ADC Calibration Done",
"ADC Channel Ready",
"DAC Channel Ready",
"PWM Module Init",
"Timer0 Started",
"Timer1 Started",
"Interrupts Enabled",
"Watchdog Timer Enabled",
"FreeRTOS Scheduler Start",
"Task1 Created",
"Task2 Created",
"Queue Initialized",
"Semaphore Created",
"Mutex Locked",
"Mutex Released",
"Filesystem Mounted",
"SPIFFS Ready",
"SD Card Mounted",
"Sensor1 Detected",
"Sensor2 Detected",
"Temperature Sensor Ready",
"Humidity Sensor Ready",
"Pressure Sensor Ready",
"IMU Initialization",
"Gyroscope Calibrated",
"Accelerometer Calibrated",
"Magnetometer Calibrated",
"LED GPIO Configured",
"LED ON",
"LED OFF",
"Button GPIO Configured",
"Button Interrupt Enabled",
"UART RX Buffer Ready",
"UART TX Buffer Ready",
"Serial Communication OK",
"CAN Bus Init",
"CAN Bus Ready",
"Modbus Init",
"Modbus Ready",
"MQTT Client Init",
"MQTT Connected",
"HTTP Server Started",
"WebSocket Init",
"WebSocket Connected",
"OTA Update Service Ready",
"Security Keys Loaded",
"Encryption Engine Init",
"Decryption Engine Init",
"CRC Module Ready",
"DMA Controller Init",
"DMA Transfer Complete",
"Low Power Mode Disabled",
"Sleep Mode Configured",
"Deep Sleep Wakeup Source Set",
"Battery Level Checked",
"Charging Status OK",
"Power Management Init",
"Brownout Detector Enabled",
"System Health Check OK",
"Diagnostics Mode Enabled",
"Error Log Cleared",
"Event Loop Started",
"Background Task Running",
"Foreground Task Running",
"Communication Stable",
"Memory Usage Normal",
"Stack Usage Normal",
"CPU Frequency Set",
"Peripheral Scan Complete",
"System Status OK",
"Runtime Monitoring Active",
"Safety Checks Passed",
"Firmware Flash Done",
"System Ready"
};

#define TOTAL_MSG 100

void setup() {
  Serial.begin(115200);
  uart.begin(115200, SERIAL_8N1, RXD2, TXD2);

  delay(2000);  // Allow receiver to boot
}

void loop() {

  switch(state) {

    case S_START:
      indexMsg = 0;
      state = S_SEND;
      break;

    case S_SEND:
      if(indexMsg < TOTAL_MSG) {

        uart.println(logs[indexMsg]);
        Serial.println(logs[indexMsg]);   // Debug monitor

        indexMsg++;
        delay(50);

      } else {
        state = S_DONE;
      }
      break;

    case S_DONE:
      while(true);   // Stop after sending 100 messages
      break;
  }
}
