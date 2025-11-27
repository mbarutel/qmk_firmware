#!/usr/bin/env bash
set -euo pipefail

TIMEOUT_SECONDS=60

if [ $# -lt 1 ]; then
  echo "Usage: $0 <keyboard> [keymap]"
  echo "Example: $0 cheapino2 default"
  exit 1
fi

KEYBOARD="$1"
KEYMAP="${2:-default}"

SUDO=""
if [ "$(id -u)" -ne 0 ]; then
  SUDO="sudo"

  # Validate sudo access early
  echo "Checking sudo access (required for flashing)..."
  if ! $SUDO -v; then
    echo "Error: sudo access required to flash the device."
    echo "Please ensure you have sudo privileges or run this script as root."
    exit 1
  fi
  echo "✓ sudo access confirmed"
  echo
fi

if ! command -v qmk >/dev/null 2>&1; then
  echo "Error: QMK CLI not found. Install it with: python3 -m pip install qmk"
  exit 1
fi

# QMK build directory - use SUDO_USER's home if running with sudo
if [ -n "${SUDO_USER:-}" ]; then
  USER_HOME=$(eval echo ~"${SUDO_USER}")
else
  USER_HOME="${HOME}"
fi
BUILD_DIR="${USER_HOME}/qmk_firmware/.build"

echo "=== Cleaning old UF2s to avoid conflicts ==="
rm -f "${BUILD_DIR}"/*.uf2 || true

echo
echo "=== Step 1: Compiling QMK firmware for ${KEYBOARD}:${KEYMAP} ==="
if ! qmk compile -kb "$KEYBOARD" -km "$KEYMAP"; then
  echo "Error: Compilation failed. Check your keymap configuration."
  exit 1
fi

echo
echo "=== Step 2: Locating the newly-built UF2 file ==="
echo "Searching in: ${BUILD_DIR}"
# Find the most recently modified UF2 file
UF2_FILE=$(find "${BUILD_DIR}" -maxdepth 1 -name "*.uf2" -type f -printf '%T@ %p\n' 2>/dev/null | sort -rn | head -1 | cut -d' ' -f2-)

if [ -z "$UF2_FILE" ] || [ ! -f "$UF2_FILE" ]; then
  echo "Error: No UF2 file produced by this build."
  echo "Build directory: ${BUILD_DIR}"
  echo "Available files:"
  ls -lh "${BUILD_DIR}"/*.uf2 2>/dev/null || echo "  (no .uf2 files found)"
  exit 1
fi

echo "✓ Found UF2: $UF2_FILE"
echo

echo "=== Step 3: Waiting for RP2040 in BOOTSEL mode ==="
echo "Instructions:"
echo "  1. Unplug the keyboard"
echo "  2. Hold the BOOTSEL button"
echo "  3. Plug in the keyboard while holding BOOTSEL"
echo "  4. Release the BOOTSEL button"
echo
echo "Waiting for 'RPI RP2' device to appear (timeout: ${TIMEOUT_SECONDS}s)..."

RP_DEV=""
ELAPSED=0

# Detect block device by MODEL/VENDOR with timeout and progress
while [ $ELAPSED -lt $TIMEOUT_SECONDS ]; do
  RP_DEV=$(lsblk -S -o NAME,MODEL,VENDOR 2>/dev/null \
    | awk '$2=="RP2" && $3=="RPI" {print $1; exit}')
  if [ -n "$RP_DEV" ]; then
    break
  fi

  # Show progress dots every 2 seconds
  if [ $((ELAPSED % 2)) -eq 0 ] && [ $ELAPSED -gt 0 ]; then
    echo -n "."
  fi

  sleep 0.4
  ELAPSED=$((ELAPSED + 1))
done

echo

if [ -z "$RP_DEV" ]; then
  echo "Error: Timed out waiting for RP2040 device."
  echo "Make sure you're following the BOOTSEL instructions correctly."
  echo "Try running 'lsblk -S' manually to verify the device appears."
  exit 1
fi

echo "Found RP2040: /dev/${RP_DEV}"
echo

echo "=== Step 4: Flashing firmware ==="
echo "Copying ${UF2_FILE} -> /dev/${RP_DEV} ..."

if ! $SUDO cp "$UF2_FILE" "/dev/${RP_DEV}"; then
  echo "Error: Failed to copy firmware to device."
  echo "You may need to run this script with sudo or adjust udev rules."
  exit 1
fi

$SUDO sync

echo
echo "Success! The board should reboot into your new firmware."
echo "If the keyboard doesn't respond, try unplugging and replugging it."
