all:
	west build -p always -b esp32s3_devkitc/esp32s3/procpu -- -DDTC_OVERLAY_FILE=boards/esp32s3_devkitc.overlay

flash:
	python -m esptool --port /dev/cu.wchusbserial58FC0664511 --chip auto --baud 921600 --before default_reset --after hard_reset write_flash -u --flash-size detect 0x0 ./build/zephyr/zephyr.bin && uv run python -m esp_idf_monitor --port /dev/cu.wchusbserial58FC0664511 --target esp32s3 build/zephyr/zephyr.elf
