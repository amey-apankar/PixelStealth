# PixelStealth 🕵️

A simple C++ command-line tool for hiding secret messages inside PNG images using steganography.

![Language](https://img.shields.io/badge/language-C%2B%2B-00599C.svg?style=for-the-badge)
![License](https://img.shields.io/badge/license-MIT-green.svg?style=for-the-badge)
![Dependencies](https://img.shields.io/badge/dependencies-stb_image-blue.svg?style=for-the-badge)
![Platform](https://img.shields.io/badge/platform-cross--platform-lightgrey.svg?style=for-the-badge)

## 📖 About The Project

PixelStealth is a console application that implements **Least Significant Bit (LSB) Steganography**. It provides a simple menu to:

* **Hide** a secret text message within a source PNG image.
* **Extract** a hidden text message from a modified "stego-image".

The goal of steganography is to hide data in plain sight, making the *existence* of the message invisible. This is different from cryptography, which just makes the message *unreadable* (but still visible).

## ✨ Features

* ✅ **Hide Text in PNGs:** Embeds any string of text into a cover image.
* ✅ **Extract Text from PNGs:** Recovers the hidden message from a stego-image.
* ✅ **Simple C++ Implementation:** Uses standard libraries and no complex external dependencies.
* ✅ **Unique Arithmetic Logic:** Implements LSB manipulation using simple math (`% 2`) instead of complex bitwise operators.
* ✅ **Robust Error Handling:** Safely handles file-not-found errors and prevents memory leaks.

## 🛠️ How It Works

The core of PixelStealth is the LSB technique, but with a simple arithmetic twist for clarity.

### The Arithmetic Method

Instead of using complex bitwise operators, the tool uses basic math to change the LSB of a pixel's color byte:

* **To Hide a '1' (Make Odd):**
    If the pixel byte is even (e.g., `254`), **add 1** to make it `255`. If it's already odd, do nothing.
* **To Hide a '0' (Make Even):**
    If the pixel byte is odd (e.g., `255`), **subtract 1** to make it `254`. If it's already even, do nothing.
* **To Extract a Bit:**
    Simply check `pixel_byte % 2`. The result (`0` or `1`) *is* the hidden bit.

### Hiding a Message

1.  The program takes your secret message (e.g., `"Hello"`).
2.  A special End-of-Message tag (`||EOF||`) is appended, resulting in `"Hello||EOF||"`.
3.  The tool iterates through each character of this new string, converting it to its 8 bits.
4.  Each bit is hidden, one by one, in the image's sequential pixel bytes (R, G, B, R, G, B...) using the arithmetic method.
5.  A new PNG file is saved with the modified pixel data.

### Extracting a Message

1.  The tool loads the stego-image.
2.  It reads the pixel data, extracting one bit at a time (`pixel_byte % 2`).
3.  It assembles the bits back into bytes (characters).
4.  It keeps appending characters to a string until the `||EOF||` tag is found.
5.  The tag is removed, and the final, clean message is displayed.

## 🚀 Built With

* **[C++](https://isocpp.org/)**: The core language.
* **[stb_image.h](https://github.com/nothings/stb)**: For reading and decompressing PNG files.
* **[stb_image_write.h](https://github.com/nothings/stb)**: For re-compressing and writing new PNG files.

## 🏁 Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

You will need a C++ compiler (like `g++` or `clang++`). The `stb_image` libraries are header-only, so you just need to download them and place them in your project directory.

### Compilation

1.  Clone the repo:
    ```sh
    git clone [https://github.com/YOUR_USERNAME/PixelStealth.git](https://github.com/YOUR_USERNAME/PixelStealth.git)
    cd PixelStealth
    ```
2.  Make sure `stb_image.h` and `stb_image_write.h` are in the same folder as your `.cpp` file.
3.  Compile the program (assuming your main file is `pixelstealth.cpp`):
    ```sh
    g++ -std=c++17 -o pixelstealth pixelstealth.cpp
    ```

### Usage

Once compiled, run the executable from your terminal:
```sh
./pixelstealth
