import serial
import time
import sys

PORT = "COM7"
BAUD = 115200
TIMEOUT = 10

EXPECTED_BOOT_MSG = "[Info]: Running Application"

try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
except Exception as e:
    print(f"Port Error: {e}")
    sys.exit(1)

time.sleep(3)

start_time = time.time()
found = False

while time.time() - start_time < TIMEOUT:
    line = ser.readline().decode(errors="ignore").strip()
    if line:
        print("RX:", line)
        if EXPECTED_BOOT_MSG in line:
            found = True
            break

ser.close()

if found:
    print("PASS: Boot message detected.")
    sys.exit(0)
else:
    print("FAIL: Boot message not detected.")
    sys.exit(1)
