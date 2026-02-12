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

const char* logs[] = {
"ESP32 Power ON",
"Bootloader Started",
"Flash Detected",
"Flash Size 4MB",
"Firmware Verified",
"Checksum OK",
"Clock Configured",
"RTC Initialized",
"GPIO Ready",
"UART Initialized",
"WiFi Connected",
"LED ON",
"LED OFF",
"Sensor Ready",
"ADC Ready",
"Heap OK",
"Watchdog Enabled",
"System Stable",
"System Rebooting",
"Firmware Flash Done"
};

const int TOTAL_MSG = sizeof(logs) / sizeof(logs[0]);

void setup() {
  Serial.begin(115200);
  uart.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Sender Booted");
}

void loop() {

  switch(state) {

    case S_START:
      indexMsg = 0;
      Serial.println("Sending All Messages...");
      state = S_SEND;
      break;

    case S_SEND:
      if(indexMsg < TOTAL_MSG) {
        uart.println(logs[indexMsg]);
        Serial.print("Sent: ");
        Serial.println(logs[indexMsg]);
        indexMsg++;
        delay(100);
      } else {
        state = S_DONE;
      }
      break;

    case S_DONE:
      Serial.println("Transmission Complete");
      while(true);   // Stop here until EN reset
      break;
  }
}