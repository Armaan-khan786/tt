import serial
import time
import sys

PORT = "COM7"
BAUD = 115200
TIMEOUT = 30

EXPECTED_FIRST = "ESP32 Power ON"
EXPECTED_LAST = "System Ready"
EXPECTED_COUNT = 100

print("Opening Serial Port...")

try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
except Exception as e:
    print(f"Port Error: {e}")
    sys.exit(1)

time.sleep(5)

print("Starting UART Validation...\n")

messages = []
start_time = time.time()

while len(messages) < EXPECTED_COUNT:

    if time.time() - start_time > TIMEOUT:
        print("Timeout occurred.")
        ser.close()
        sys.exit(1)

    line = ser.readline().decode(errors="ignore").strip()

    if line:
        print("RX:", line)
        messages.append(line)

ser.close()

print("\nValidating Data...")

# ---- VERDICT LOGIC ----

if len(messages) != EXPECTED_COUNT:
    print("FAIL: Message count mismatch.")
    sys.exit(1)

if messages[0] != EXPECTED_FIRST:
    print("FAIL: First message mismatch.")
    sys.exit(1)

if messages[-1] != EXPECTED_LAST:
    print("FAIL: Last message mismatch.")
    sys.exit(1)

print("PASS: UART Firmware Validation Successful.")
sys.exit(0)
