# PixelStealth 🕵️

[cite_start]A simple C++ command-line tool for hiding secret messages inside PNG images using steganography. [cite: 17, 18]

![Language](https://img.shields.io/badge/language-C%2B%2B-00599C.svg?style=for-the-badge)
![License](https://img.shields.io/badge/license-MIT-green.svg?style=for-the-badge)
![Dependencies](https://img.shields.io/badge/dependencies-stb_image-blue.svg?style=for-the-badge)
![Platform](https://img.shields.io/badge/platform-cross--platform-lightgrey.svg?style=for-the-badge)

## 📖 About The Project

[cite_start]PixelStealth is a console application that implements **Least Significant Bit (LSB) Steganography**. [cite: 39] It provides a simple menu to:

* [cite_start]**Hide** a secret text message within a source PNG image, creating a "stego-image". [cite: 40]
* [cite_start]**Extract** a hidden text message from a modified "stego-image". [cite: 40]

[cite_start]The goal of steganography is to hide data in plain sight, making the *existence* of the message invisible. [cite: 30, 31] [cite_start]This is different from cryptography, which just makes the message *unreadable* (but still visible). [cite: 34, 35, 36]

## ✨ Features

* [cite_start]✅ **Hide Text in PNGs:** Embeds any string of text into a cover image. [cite: 18, 40]
* [cite_start]✅ **Extract Text from PNGs:** Recovers the hidden message from a stego-image. [cite: 18, 40]
* [cite_start]✅ **Simple C++ Implementation:** Uses standard C++ libraries and is beginner-friendly. [cite: 22]
* [cite_start]✅ **Unique Arithmetic Logic:** Implements LSB manipulation using simple math (`% 2`) instead of complex bitwise operators. [cite: 20]
* [cite_start]✅ **Robust Error Handling:** Safely handles file-not-found errors and prevents memory leaks using `try...catch` blocks. [cite: 129, 131, 133]

## 🛠️ How It Works

[cite_start]The core of PixelStealth is the LSB technique, but with a simple arithmetic twist for clarity. [cite: 19, 20]

### The Arithmetic Method

[cite_start]Instead of using complex bitwise operators, the tool uses basic math to change the LSB of a pixel's color byte: [cite: 52]

* **To Hide a '1' (Make Odd):**
    [cite_start]If the pixel byte is even (e.g., `254`), **add 1** to make it `255`. [cite: 55, 56] [cite_start]If it's already odd, do nothing. [cite: 58]
* **To Hide a '0' (Make Even):**
    [cite_start]If the pixel byte is odd (e.g., `255`), **subtract 1** to make it `254`. [cite: 61, 62] [cite_start]If it's already even, do nothing. [cite: 63]
* **To Extract a Bit:**
    [cite_start]Simply check `pixel_byte % 2`. [cite: 66] [cite_start]The result (`0` or `1`) *is* the hidden bit. [cite: 67]

### Hiding a Message

1.  [cite_start]The program takes your source image, output filename, and secret message. [cite: 105, 106]
2.  [cite_start]A special End-of-Message tag (`||EOF||`) is appended to the secret message. [cite: 110]
3.  [cite_start]The tool iterates through each character of this new string, converting it to its 8 bits. [cite: 111, 99]
4.  [cite_start]Each bit is hidden, one by one, in the image's sequential pixel bytes (R, G, B, R, G, B...) using the arithmetic method. [cite: 70, 95]
5.  [cite_start]A new PNG file is saved with the modified pixel data. [cite: 112]

### Extracting a Message

1.  [cite_start]The tool loads the stego-image. [cite: 116, 117]
2.  [cite_start]It reads the pixel data, extracting one bit at a time (`pixel_byte % 2`). [cite: 97, 98]
3.  [cite_start]It assembles the bits back into bytes (characters) [cite: 100, 120]
4.  [cite_start]It keeps appending characters to a string until the `||EOF||` tag is found. [cite: 121, 123]
5.  [cite_start]The tag is removed, and the final, clean message is displayed. [cite: 126, 127]

## 🚀 Built With

* [cite_start]**[C++](https://isocpp.org/)**: The core language. [cite: 17]
* [cite_start]**C++ Standard Libraries:** [cite: 76]
    * [cite_start]`<iostream>` [cite: 77]
    * [cite_start]`<string>` [cite: 78]
    * [cite_start]`<stdexcept>` [cite: 79]
    * [cite_start]`<limits>` [cite: 80]
* [cite_start]**[stb_image.h](https://github.com/nothings/stb)**: For reading and decompressing PNG files. [cite: 85, 87]
* [cite_start]**[stb_image_write.h](https://github.com/nothings/stb)**: For re-compressing and writing new PNG files. [cite: 85, 89]

## 🏁 Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

* A C++ compiler (like `g++` / MinGW) or a C++ IDE.
* The project is ready to be compiled directly using the **Code::Blocks** project file (`PixelStealth.cbp`).

### Compilation

You have two main options to compile this project:

#### 1. Using Code::Blocks (Recommended)

1.  Open the `PixelStealth.cbp` project file in Code::Blocks.
2.  Go to **Build -> Build** (or press `F9`) to compile and run the project. The executable will be created in the `bin/` folder.

#### 2. Using the Command Line (g++)

If you don't have Code::Blocks, you can compile it from your terminal.

1.  Navigate to your project's root directory.
2.  Run the following `g++` command:
    ```sh
    # This compiles main.cpp and links the math library
    g++ -std=c++17 -o PixelStealth main.cpp -lm
    ```

### Usage

Once compiled, run the executable:
```sh
# From the command line
./PixelStealth

# Or by pressing "Run" in Code::Blocks
