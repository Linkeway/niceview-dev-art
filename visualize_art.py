#!/usr/bin/env python3
import re
import sys
from PIL import Image
import argparse

def parse_c_file(file_path):
    """
    Parses the C art file to extract image dimensions, pixel data, and color palettes.
    """
    with open(file_path, 'r') as f:
        content = f.read()

    # Get width and height from the lv_img_dsc_t struct
    w_match = re.search(r'\.w = (\d+),', content)
    h_match = re.search(r'\.h = (\d+),', content)
    width = int(w_match.group(1)) if w_match else 140  # Default width
    height = int(h_match.group(1)) if h_match else 68  # Default height

    # Extract the content of the _map array
    map_content_match = re.search(r'uint8_t \w+_map\[\] = {([^}]+)};', content, re.DOTALL)
    if not map_content_match:
        raise ValueError("Could not find the pixel map array in the file.")
    map_content = map_content_match.group(1)

    # Extract palettes from the #if/#else block
    inverted_palette_match = re.search(r'#if CONFIG_NICE_VIEW_WIDGET_INVERTED\s*([\s\S]*?)#else', map_content)
    normal_palette_match = re.search(r'#else\s*([\s\S]*?)#endif', map_content)

    if not inverted_palette_match or not normal_palette_match:
        raise ValueError("Could not parse palettes from the C file. Check the #if/#else structure.")

    def parse_palette(palette_str):
        hex_values = re.findall(r'0x([0-9a-fA-F]{1,2})', palette_str)
        byte_values = [int(h, 16) for h in hex_values]
        if len(byte_values) < 8:
            raise ValueError("Palette definition is incomplete.")
        # Palette is two RGBA colors, we only need RGB
        color0 = tuple(byte_values[0:3])
        color1 = tuple(byte_values[4:7])
        return [color0, color1]

    inverted_palette = parse_palette(inverted_palette_match.group(1))
    normal_palette = parse_palette(normal_palette_match.group(1))

    # The pixel data starts after the palette's #endif.
    after_endif_match = re.search(r'#endif(.*)', map_content, re.DOTALL)
    if after_endif_match:
        pixel_data_str = after_endif_match.group(1)
    else:
        raise ValueError("Could not find the end of the palette definition (#endif).")

    # Find all the hex values for the pixel data.
    hex_values = re.findall(r'0x([0-9a-fA-F]{1,2})', pixel_data_str)
    pixel_data = [int(h, 16) for h in hex_values]

    return width, height, pixel_data, normal_palette, inverted_palette

def create_image_from_bitmap(width, height, pixel_data, palette):
    """
    Creates a paletted PIL Image from the raw pixel data, accounting for row padding.
    """
    img = Image.new('P', (width, height))

    # putpalette expects a flat list of [R0, G0, B0, R1, G1, B1, ...]
    flat_palette = [c for color in palette for c in color]
    img.putpalette(flat_palette)

    pixels = img.load()

    bytes_per_row = (width + 7) // 8

    for y in range(height):
        row_byte_start = y * bytes_per_row
        row_byte_end = row_byte_start + bytes_per_row
        row_bytes = pixel_data[row_byte_start:row_byte_end]

        row_bit_stream = ''.join(f'{byte:08b}' for byte in row_bytes)

        for x in range(width):
            bit = int(row_bit_stream[x])
            pixels[x, y] = bit  # The bit value is the index into the palette

    return img

def main():
    parser = argparse.ArgumentParser(description='Visualize a 1-bit bitmap from a C art file.')
    parser.add_argument('file_path', help='Path to the C art file (e.g., boards/shields/nice_view_custom/widgets/arts/cpp.c)')
    parser.add_argument('--inverted', action='store_true', help='Use the inverted palette from the C file (usually for a black background).')
    parser.add_argument('--output', help='Path to save the output image (e.g., output.png). If not provided, the image will be displayed.')

    args = parser.parse_args()

    try:
        width, height, pixel_data, normal_palette, inverted_palette = parse_c_file(args.file_path)

        print(f"Image dimensions: {width}x{height}")
        print(f"Number of bytes in pixel data: {len(pixel_data)}")
        bytes_per_row = (width + 7) // 8
        expected_bytes = bytes_per_row * height
        print(f"Expected number of bytes (with padding): {expected_bytes}")

        if not pixel_data:
            raise ValueError("No pixel data found in the file.")

        # Choose the palette based on the --inverted flag
        palette = inverted_palette if args.inverted else normal_palette

        img = create_image_from_bitmap(width, height, pixel_data, palette)

        # Rotate the image 90 degrees counter-clockwise
        img = img.rotate(90, expand=True)

        # Show and potentially save the image
        if args.output:
            img.save(args.output)
            print(f"Image saved to '{args.output}'")
        img.show()

    except FileNotFoundError:
        print(f"Error: File not found at '{args.file_path}'", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"An error occurred: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()
