#!/bin/bash

# Configuration
PORT="/dev/cu.wchusbserial58FC0664511"
BAUD="921600"
CHIP="auto"

# 1. Capture the binary path from argument 1
BIN_PATH=$1

# 2. Validation
if [ -z "$BIN_PATH" ]; then
    echo "Error: No binary file specified."
    echo "Usage: ./flash.sh <path_to_binary>"
    exit 1
fi

if [ ! -f "$BIN_PATH" ]; then
    echo "Error: File not found: $BIN_PATH"
    exit 1
fi

echo "Flashing $BIN_PATH to $PORT..."

# 3. Execution
# Note: Using 'uv tool run' for esptool and 'uv run' for the monitor
uv tool run esptool \
    --port "$PORT" \
    --chip "$CHIP" \
    --baud "$BAUD" \
    --before default_reset \
    --after hard_reset \
    write_flash -u \
    --flash_size detect 0x0 "$BIN_PATH" \
&& echo "Flash successful. Starting monitor..." \
&& uv run python -m esp_idf_monitor --port "$PORT" --baud 115200
