import serial
import time
import sys

PORT = "COM7"       # Receiver USB port
BAUD = 115200
TIMEOUT = 30

print("Opening Serial Port...")

try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
except Exception as e:
    print(f"Failed to open serial port: {e}")
    sys.exit(1)

time.sleep(3)

print("Starting UART Firmware Validation...\n")

message_count = 0
start_time = time.time()

while message_count < 100:

    if time.time() - start_time > TIMEOUT:
        print("Timeout! Did not receive 100 messages.")
        ser.close()
        sys.exit(1)

    line = ser.readline().decode(errors="ignore").strip()

    if line:
        print(line)
        message_count += 1

ser.close()

if message_count == 100:
    print("\nSUCCESS: Received 100 messages.")
    sys.exit(0)
else:
    print("\nFAILED: Message count mismatch.")
    sys.exit(1)
