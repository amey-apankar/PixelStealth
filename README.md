<div align="center">

# 🕵️ PixelStealth 🕵️

**A C++ command-line tool for hiding secret messages in PNG images using LSB steganography.**

</div>

<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/language-C%2B%2B-00599C.svg?style=for-the-badge">
  <img alt="Dependencies" src="https://img.shields.io/badge/dependencies-stb_image-blue.svg?style=for-the-badge">
  <img alt="Platform" src="https://img.shields.io/badge/platform-Windows_|_Linux_|_macOS-lightgrey.svg?style=for-the-badge">
  
</p>

---

## 📖 About This Project

**PixelStealth** is a C++ console application that lets you embed secret text data into a standard PNG image and extract it later. The goal is to make the message's very existence invisible to an observer.

The project was developed for **Code::Blocks** and uses the header-only `stb_image` libraries to handle the complexities of PNG decompression and re-compression.

> **Steganography vs. Cryptography**
>
> * **Cryptography** scrambles a message so it's *unreadable* (but its existence is obvious).
> * **Steganography** hides a message so its *existence* is unknown. PixelStealth does this.

<br>

<div align="center">
  <p><strong>APPLICATION IN ACTION</strong></p>
  <pre>
  <code>
  =====================================
  PixelStealth: C++ Steganography Tool
  =====================================
  [1] Hide Message in a PNG
  [2] Extract Message from a PNG
  [0] Exit
  
  Select an option: 1
  
  --- HIDE MESSAGE ---
  Enter source image file (e.g., source.png): source.png
  Enter output file name (e.g., stego.png): stego.png
  Enter secret message: This is a secret!
  
  Hiding message...
  Success! Message hidden in stego.png
  
  Press Enter to continue...
  </code>
  </pre>
</div>

---

## ✨ Features ✨

* ✅ **Hide Text:** Embeds any string of text into a cover PNG image.
* ✅ **Extract Text:** Recovers the hidden message from a stego-image.
* ✅ **Simple Logic:** Uses simple arithmetic (`% 2`) for LSB manipulation, making the code easy to understand.
* ✅ **End-of-Message Tag:** Uses a `||EOF||` tag to know when the message is complete during extraction.
* ✅ **Robust Error Handling:** Uses `try...catch` blocks to safely handle errors like "file not found" and prevent memory leaks.

---

## 🛠️ How It Works

The core technique is **Least Significant Bit (LSB) Steganography**. Every pixel in a PNG has Red, Green, and Blue values (0-255). The LSB is the last bit of that number, which determines if it's even or odd. Changing it causes a color shift so tiny it's invisible to the human eye.

### The Arithmetic LSB Method

This project uses a simple mathematical trick instead of complex bitwise operators:

* **To Hide a '1' (Make ODD):**
    If the pixel byte is even (e.g., `254`), **add 1** to make it `255`. If it's already odd, do nothing.
* **To Hide a '0' (Make EVEN):**
    If the pixel byte is odd (e.g., `255`), **subtract 1** to make it `254`. If it's already even, do nothing.
* **To Extract a Bit:**
    Just read the byte and check `pixel_byte % 2`. The result (`0` or `1`) *is* the hidden bit.

---

## 🚀 Built With

* **[C++](https://isocpp.org/)** (using `<iostream>`, `<string>`, `<stdexcept>`)
* **[stb_image.h](https://github.com/nothings/stb)** (for loading and decompressing PNGs)
* **[stb_image_write.h](https://github.com/nothings/stb)** (for re-compressing and saving PNGs)
* **[Code::Blocks](https://www.codeblocks.org/)** (as the primary IDE)

---

## 🏁 Getting Started

This project is ready to compile directly from the included Code::Blocks project file.

### Prerequisites

* A C++ compiler (like `g++` or the MinGW compiler bundled with Code::Blocks)

### Installation & Compilation

You have two easy options:

#### Option 1: Using Code::Blocks (Recommended)

1.  Open the `PixelStealth.cbp` file in Code::Blocks.
2.  Press **`F9`** (or go to **Build -> Build and run**).
3.  Code::Blocks will compile the project and run the executable from the `bin/` folder.

#### Option 2: Using the Command Line (g++)

1.  Open your terminal in the project's root folder.
2.  Run the following `g++` command to compile `main.cpp`:
    ```sh
    g++ -std=c++17 main.cpp -o PixelStealth
    ```
    *(On Windows, you may want to name the output `PixelStealth.exe`)*

### Usage

Once compiled, you can run the application.

* **In Code::Blocks:** Just press `F9`.
* **From Windows Terminal:**
    * If you used `g++`, just type the executable name:
        ```sh
        PixelStealth.exe
        ```
    * If you built with Code::Blocks, the `.exe` is in the `bin/Debug/` folder:
        ```sh
        .\bin\Debug\PixelStealth.exe
        ```
* **From Linux/macOS Terminal:**
    ```sh
    ./PixelStealth
    ```

You can test the program using the `source.png` file included in the repository.

---

