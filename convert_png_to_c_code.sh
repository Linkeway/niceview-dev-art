#!/bin/bash

set -e

# Check for dependencies
if ! command -v magick &> /dev/null; then
    echo "Error: ImageMagick is not installed. Please install it to continue."
    exit 1
fi

if ! command -v pngquant &> /dev/null; then
    echo "Error: pngquant is not installed. Please install it to continue."
    echo "  (e.g., sudo apt install pngquant or brew install pngquant)"
    exit 1
fi

LVGL_IMG_SCRIPT="/tmp/LVGLImage.py"
if [ ! -f "$LVGL_IMG_SCRIPT" ]; then
    echo "LVGLImage.py not found, downloading..."
    curl -sL https://raw.githubusercontent.com/lvgl/lvgl/refs/heads/master/scripts/LVGLImage.py -o "$LVGL_IMG_SCRIPT"
fi

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <path_to_png_file>"
    exit 1
fi

INPUT_FILE="$1"
BASENAME=$(basename -- "$INPUT_FILE")
FILENAME="${BASENAME%.*}"
TEMP_PNG="/tmp/${FILENAME}.png"

echo "-------------------------------------------------"
echo "Scaling and rotate $INPUT_FILE..."
# 1. Scale to 68x140, rotate 90 degrees clockwise, and save as monochrome
# magick "$INPUT_FILE" -scale 68x140\! -rotate 90 -monochrome "$TEMP_PNG"
magick "$INPUT_FILE" -scale 68x140\! -rotate 90 "$TEMP_PNG"
echo "Done. Check the scaled and rotated img under ${TEMP_PNG}."
open "${TEMP_PNG}" # open to check visually

echo "-------------------------------------------------"
# 2. Convert to C array using LVGLImage.py
echo "Converting to C array..."
# we don't use the generated code directly, as the LVGL version in ZMK firmware doesn't match the LVGl version that provides LVGLImage.py
# OUTPUT_C_FOLDER="boards/shields/nice_view_custom/widgets/arts/"
OUTPUT_C_FOLDER="/tmp/"
python3 "$LVGL_IMG_SCRIPT" "$TEMP_PNG" --cf I1 --ofmt C -o \
	"$OUTPUT_C_FOLDER"

OUTPUT_C_FILE="$OUTPUT_C_FOLDER/${FILENAME}.c"
echo "Done. C array written to ${OUTPUT_C_FILE}. Printing contents:"

cat "${OUTPUT_C_FILE}"
# rm -f "$TEMP_PNG"
# rm -f "${OUTPUT_C_FILE}"

