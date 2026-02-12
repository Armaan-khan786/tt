#define RXD2 16
#define TXD2 17

HardwareSerial mySerial(2);

enum State {
  STATE_WAIT_DATA,
  STATE_SEND_ACK
};

State currentState = STATE_WAIT_DATA;
String receivedData = "";

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Receiver Ready");
}

void loop() {

  switch (currentState) {

    case STATE_WAIT_DATA:
      if (mySerial.available()) {
        receivedData = mySerial.readStringUntil('\n');
        receivedData.trim();

        Serial.println("Received: " + receivedData);
        currentState = STATE_SEND_ACK;
      }
      break;

    case STATE_SEND_ACK:
      mySerial.println("ACK");
      currentState = STATE_WAIT_DATA;
      break;
  }
}