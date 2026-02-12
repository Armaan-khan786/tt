#define RXD2 16
#define TXD2 17

HardwareSerial uart(2);

void setup() {
  Serial.begin(115200);
  uart.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Serial.println("Receiver Ready");
}

void loop() {

  if(uart.available()) {
    String msg = uart.readStringUntil('\n');
    msg.trim();
    Serial.print("Received: ");
    Serial.println(msg);
  }
}