import os
import struct
import argparse

from PIL import Image
from collections import Counter


class ImageConverter:
    def __init__(self, image_path):
        self.image_path = image_path
        self.pixels = []
        self.color_counts = Counter()
        self.color_map = {}
        self.converted_image = []

    def parse_image(self):
        """Reads the image, stores pixel values, color frequencies, and creates a color map."""
        with Image.open(self.image_path) as img:
            img = img.convert("RGBA")

            self.pixels = list(img.getdata())
            self.color_counts = Counter(self.pixels)
            assert len(self.color_counts) <= 16, "Image has more than 16 unique colors."

            sorted_colors = [color for color, _ in self.color_counts.most_common()]
            self.color_map = {color: i for i, color in enumerate(sorted_colors)}

    def convert_image(self):
        """Convert the pixel data into a binary format using 4-bit IDs."""
        byte_data = []
        for i in range(0, len(self.pixels), 2):
            color_id1 = self.color_map[self.pixels[i]]
            color_id2 = self.color_map[self.pixels[i + 1]] if i + 1 < len(self.pixels) else 0
            byte_data.append((color_id2 << 4) | color_id1)

        self.converted_image = bytes(byte_data)

    def rgba_to_rgba5(self, rgba):
        """Convert an RGBA color to a 16-bit color (5 bits per channel)."""
        r, g, b, a = rgba
        r = round((r * 31) / 255)
        g = round((g * 31) / 255)
        b = round((b * 31) / 255)
        a = 1 if a != 0 else 0
        return  (a << 15) | (b << 10) | (g << 5) | r

    def save_converted_image(self, output_path):
        """Saves the converted pixel data to a binary file, including the actual 16-bit colors."""
        with open(output_path, 'wb') as f:
            f.write(self.converted_image)
            for color in self.color_map:
                color_16bit = self.rgba_to_rgba5(color)
                f.write(struct.pack('H', color_16bit))

    def print_palette(self):
        """Prints out all the unique colors sorted by frequency."""
        print("Colors in the Image (sorted by frequency):")
        sorted_colors = self.color_counts.most_common()
        for color, count in sorted_colors:
            print(f"Color {color}: {count} times")


def parse_arguments():
    parser = argparse.ArgumentParser(description="Convert a given image to the ingame binary format used to send to VRAM.")
    parser.add_argument("-input_path", type=str, default="/home/assets/images_in", help="Path to the directory containing images to convert.")
    parser.add_argument("-output_path", type=str, default="/home/assets/images_out", help="Path to the directory the converted image(s) should be saved to.")
    return parser.parse_args()


def process_image(input_path, output_path):
    converter = ImageConverter(input_path)
    converter.parse_image()
    converter.convert_image()

    filename = os.path.splitext(os.path.basename(input_path))[0]
    output_file = os.path.join(output_path, f"{filename}.bin")

    converter.save_converted_image(output_file)
    print(f"Converted image saved to {output_file}")


def process_directory(input_directory, output_directory):
    for filename in os.listdir(input_directory):
        file_path = os.path.join(input_directory, filename)
        if os.path.isfile(file_path) and filename.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif')):
            process_image(file_path, output_directory)


if __name__ == "__main__":
    args = parse_arguments()

    if os.path.isdir(args.input_path):
        print(f"Processing all images in directory: {args.input_path}")
        process_directory(args.input_path, args.output_path)
    elif os.path.isfile(args.input_path):
        print(f"Processing single image: {args.input_path}")
        process_image(args.input_path, args.output_path)
    else:
        print(f"Invalid input path: {args.input_path}")
