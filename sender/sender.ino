#define RXD2 16
#define TXD2 17

HardwareSerial mySerial(2);

enum State {
  STATE_IDLE,
  STATE_SEND,
  STATE_WAIT_ACK,
  STATE_DONE
};

State currentState = STATE_IDLE;

int messageCount = 0;
const int totalMessages = 100;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Sender Ready");
}

void loop() {

  switch (currentState) {

    case STATE_IDLE:
      messageCount = 0;
      currentState = STATE_SEND;
      break;

    case STATE_SEND:
      if (messageCount < totalMessages) {
        mySerial.print("Firmware ");
        mySerial.println(messageCount + 1);
        Serial.println("Sent: Firmware " + String(messageCount + 1));
        currentState = STATE_WAIT_ACK;
      } else {
        currentState = STATE_DONE;
      }
      break;

    case STATE_WAIT_ACK:
      if (mySerial.available()) {
        String ack = mySerial.readStringUntil('\n');
        ack.trim();

        if (ack == "ACK") {
          messageCount++;
          currentState = STATE_SEND;
        }
      }
      break;

    case STATE_DONE:
      Serial.println("All 100 Messages Sent Successfully ✅");
      while (1);  // Stop here
      break;
  }
}