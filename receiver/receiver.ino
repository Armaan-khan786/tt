#define RXD2 16
#define TXD2 17

HardwareSerial uart(2);

void setup() {
  Serial.begin(115200);                     // USB to PC
  uart.begin(115200, SERIAL_8N1, RXD2, TXD2);  // UART2 from sender

  Serial.println("Receiver Ready");
}

void loop() {

  while (uart.available()) {

    String data = uart.readStringUntil('\n');
    data.trim();

    if (data.length() > 0) {
      Serial.println(data);   // Send to PC
    }
  }
}
