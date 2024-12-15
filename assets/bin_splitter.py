import os
import argparse

DEFAULT_SIZE = 7 * 292 - 16

def parse_arguments():
    parser = argparse.ArgumentParser(description="Split a binary file into chunks based on a specified size.")
    parser.add_argument("--file_path", type=str, default="/home/assets/images_out", help="Path to the input binary file or directory.")
    parser.add_argument("--output_path", type=str, default="/home/assets/bins_out", help="Path to the output directory.")
    parser.add_argument("--size", type=int, default=DEFAULT_SIZE, help=f"Chunk size in bytes (default: {DEFAULT_SIZE}).")
    return parser.parse_args()

def write_chunks_to_bins(binary_data, chunk_size, output_path, base_filename):
    """Split binary data into chunks and write each chunk to a binary file."""
    os.makedirs(output_path, exist_ok=True)

    for i in range(0, len(binary_data), chunk_size):
        chunk = binary_data[i:i + chunk_size]
        bin_filename = f"{base_filename}_chunk_{i // chunk_size}.bin"
        bin_filepath = os.path.join(output_path, bin_filename)

        with open(bin_filepath, "wb") as bin_file:
            bin_file.write(chunk)
        print(f"Written: {bin_filepath}")

def process_file(file_path, output_path, chunk_size):
    """Process a single file and split it into chunks."""
    with open(file_path, "rb") as input_file:
        binary_data = input_file.read()

    base_filename = os.path.splitext(os.path.basename(file_path))[0]
    write_chunks_to_bins(binary_data, chunk_size, output_path, base_filename)

def process_directory(directory_path, output_path, chunk_size):
    """Process all files in a directory and split each into chunks."""
    for filename in os.listdir(directory_path):
        file_path = os.path.join(directory_path, filename)
        if os.path.isfile(file_path):  # Only process files, ignore directories
            print(f"Processing: {file_path}")
            process_file(file_path, output_path, chunk_size)

def main():
    args = parse_arguments()
    file_path = args.file_path
    output_path = args.output_path
    chunk_size = args.size

    if os.path.isdir(file_path):
        print(f"Processing all files in directory: {file_path}")
        process_directory(file_path, output_path, chunk_size)
    elif os.path.isfile(file_path):
        print(f"Processing single file: {file_path}")
        process_file(file_path, output_path, chunk_size)
    else:
        print(f"Invalid file path: {file_path}")

if __name__ == "__main__":
    main()
