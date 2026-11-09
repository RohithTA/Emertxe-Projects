# LSB Image Steganography

A command-line tool in C that hides a secret file inside a BMP image using Least Significant Bit (LSB) encoding, and extracts it again.

> Developed as part of the Emertxe training program.

## Features
- Encode any file (text, etc.) into a 24-bit BMP image
- Decode the hidden file back from the stego image
- Capacity check: verifies the image can hold the secret file before encoding
- Magic string signature to detect whether an image contains hidden data
- Stores the secret file's extension, size, and data inside the image
- Input validation with clear INFO messages

## Tech Stack
C, GCC, Make, File I/O, Bitwise operations

## Project Structure
lsb-image-steganography/
├── src/
│ ├── test_encode.c # main driver (argument handling)
│ ├── encode.c / encode.h
│ ├── decode.c / decode.h
│ ├── common.h
│ └── types.h
├── samples/
│ ├── beautiful.bmp # sample cover image
│ └── secret.txt # sample secret message
├── Makefile
└── README.md

## Build
```bash
make
```
Or without Make:
```bash
gcc src/*.c -o stego
```

## Usage

**Encode**
```bash
./stego -e <source.bmp> <secret_file> [output.bmp]
./stego -e samples/beautiful.bmp samples/secret.txt stego.bmp
```
If no output name is given, `default_steged.bmp` is created.

**Decode**
```bash
./stego -d <stego.bmp> [output_name]
./stego -d stego.bmp decode
```
If no output name is given, the file is saved as `default_decoded`. The extension is restored automatically from the data stored in the image, so any extension you type in the output name is ignored.

## How It Works
1. The 54-byte BMP header is copied unchanged.
2. A magic string, then the secret file's extension size, extension, file size, and file data are written one bit at a time into the least significant bit of successive image bytes.
3. The remaining image bytes are copied as-is, so the image looks visually identical.
4. Decoding reads the same fields back in order and rebuilds the secret file.

## What I Learned
- Bitwise operations (masking and shifting) for bit-level data embedding
- Binary file I/O and the BMP file format
- Structuring a C project with multiple modules and header files
- Command-line argument handling and input validation

## Author
Rohith T A
