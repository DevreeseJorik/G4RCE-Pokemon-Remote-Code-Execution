import json
import os
import argparse

def generate_memory_section(file_path):
    """
    Reads a binary file and returns a dictionary representing
    the memory editor section with the hex content of the file.
    Hexadecimal values are zero-padded to two digits.
    """
    data = {"type": "memory_editor"}

    with open(file_path, "rb") as f:
        data["memory"] = ["0x" + f"{byte:02x}".upper() for byte in f.read()]

    return data

def generate_script(files, base_script_path, output_script_path, game):
    """
    Reads the base script, appends memory sections from the provided files,
    and writes the updated script to the output file.
    """
    with open(base_script_path, "r") as f:
        base_script = json.load(f)

    for file in files:
        base_script[0]["input_fields"].append(generate_memory_section(file))

    base_script[0]["title"] += f" ({game})"

    with open(output_script_path, "w") as f:
        json.dump(base_script, f, indent=4)

def main():
    parser = argparse.ArgumentParser(description="Generate a game script.")
    parser.add_argument("--bin-path", required=True, help="Path to the bin directory")
    parser.add_argument("--base-script-path", required=True, help="Path to the base script JSON file")
    parser.add_argument("--output-script-path", required=True, help="Path to the output script JSON file")
    parser.add_argument("--game", required=True, help="The game name")

    args = parser.parse_args()

    BIN_FILES = [
        os.path.join(args.bin_path, "inject_overlay_payload.bin"),
        os.path.join(args.bin_path, "overlay_payload.bin"),
    ]

    generate_script(BIN_FILES, args.base_script_path, args.output_script_path, args.game)

if __name__ == "__main__":
    main()
