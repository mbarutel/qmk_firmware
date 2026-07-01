#!/usr/bin/env bash
set -euo pipefail

TIMEOUT_SECONDS=60

if [ $# -lt 1 ]; then
  echo "Usage: $0 <keyboard> [keymap]"
  echo "Example: $0 cheapino default"
  exit 1
fi

KEYBOARD="$1"
KEYMAP="${2:-default}"

# Ensure QMK CLI is present
if ! command -v qmk >/dev/null 2>&1; then
  echo "Error: QMK CLI not found. Install it with: python3 -m pip install qmk"
  exit 1
fi

# Ensure picotool is present for the new flashing engine
if ! command -v picotool >/dev/null 2>&1; then
  echo "Error: picotool not found. Install it via Homebrew with: brew install picotool"
  exit 1
fi

# Locate build directory safely on macOS
QMK_DIR="${HOME}/.config/qmk_firmware"
BUILD_DIR="${QMK_DIR}/.build"

echo "=== Step 1: Compiling QMK firmware ==="
rm -f "${BUILD_DIR}"/*.uf2 "${QMK_DIR}"/*.uf2 || true

if ! qmk compile -kb "$KEYBOARD" -km "$KEYMAP"; then
  echo "Error: Compilation failed. Check your keymap configuration."
  exit 1
fi

echo
echo "=== Step 2: Locating the newly-built UF2 file ==="
# Locate the absolute newest .uf2 in either folder natively on macOS
UF2_FILE=$(
  set +e
  find "$QMK_DIR" "$BUILD_DIR" -maxdepth 1 -name "*.uf2" -type f 2>/dev/null | while read -r file; do
    stat -f "%m %N" "$file"
  done | sort -rn | head -1 | cut -d' ' -f2-
)

if [ -z "${UF2_FILE:-}" ] || [ ! -f "$UF2_FILE" ]; then
  echo "Error: No UF2 file produced by this build." >&2
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
echo "Scanning USB bus for an RP2040 device (timeout: ${TIMEOUT_SECONDS}s)..."

ELAPSED=0
DEVICE_FOUND=0

while [ $ELAPSED -lt $TIMEOUT_SECONDS ]; do
  # picotool info returns status text if a device is connected in BOOTSEL mode
  if picotool info >/dev/null 2>&1; then
    DEVICE_FOUND=1
    break
  fi

  if [ $((ELAPSED % 2)) -eq 0 ] && [ $ELAPSED -gt 0 ]; then
    echo -n "."
  fi
  sleep 0.5
  ELAPSED=$((ELAPSED + 1))
done
echo

if [ $DEVICE_FOUND -eq 0 ]; then
  echo "Error: Could not locate RP2040 in BOOTSEL mode via picotool." >&2
  echo "Trying a fallback direct QMK flash instead..."
  qmk flash -kb "$KEYBOARD" -km "$KEYMAP"
  exit 0
fi

echo "✓ Found RP2040 bootloader device via raw USB interface."

echo
echo "=== Step 4: Flashing firmware ==="
echo "Loading ${UF2_FILE} directly to flash and executing..."

# -x flag reboots the board automatically after the upload finishes
if picotool load -x "$UF2_FILE"; then
  echo "Success! The board has been flashed and rebooted into your new firmware."
else
  echo "Picotool upload failed. Passing off execution to raw QMK flash wrapper..."
  qmk flash -kb "$KEYBOARD" -km "$KEYMAP"
fi

