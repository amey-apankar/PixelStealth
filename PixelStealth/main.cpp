/*
 * PixelStealth: A Simple C++ Steganography Tool
 * Hides secret text messages in PNG images using
 * Least Significant Bit (LSB) steganography.
 */

#include <iostream>
#include <string>
#include <stdexcept> // For runtime_error
#include <limits>     // For clearing input buffer

using namespace std;

// Define these before including stb_image headers
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// --- Global Variables ---
unsigned char* g_pixel_data = nullptr;
int g_width, g_height, g_channels;
long long g_data_size = 0;
long long g_data_index = 0;

const string END_OF_MESSAGE_TAG = "||EOF||";

// --- Function Prototypes ---
void hideMessage();
void extractMessage();
void clearInputBuffer();
bool canHideMore();
void hideBit(int bit_to_hide);
int extractBit();
void hideByte(char c);
char extractByte();


int main() {
    int choice = -1;

    while (choice != 0) {
        cout << "\n=====================================" << endl;
        cout << "PixelStealth: C++ Steganography Tool" << endl;
        cout << "=====================================" << endl;
        cout << "[1] Hide Message in a PNG" << endl;
        cout << "[2] Extract Message from a PNG" << endl;
        cout << "[0] Exit" << endl;
        cout << "\nSelect an option: ";

        cin >> choice;

        if (cin.fail()) {
            choice = -1;
            clearInputBuffer();
        }

        try {
            switch (choice) {
                case 1:
                    hideMessage();
                    break;
                case 2:
                    extractMessage();
                    break;
                case 0:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
                    break;
            }
        } catch (const runtime_error& e) {
            cerr << "\n!!! An Error Occurred: " << e.what() << " !!!" << endl;

            if (g_pixel_data) {
                stbi_image_free(g_pixel_data);
                g_pixel_data = nullptr;
            }
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            clearInputBuffer();
            cin.get();
        }
    }
    return 0;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool canHideMore() {
    return (g_data_index + 16) < g_data_size;
}

void hideBit(int bit_to_hide) {
    if (g_data_index >= g_data_size) {
        throw runtime_error("Out of space! Image is too small for this message.");
    }

    unsigned char& pixel_byte = g_pixel_data[g_data_index];
    int current_lsb = pixel_byte % 2;

    if (bit_to_hide == 1) {
        if (current_lsb == 0) {
            pixel_byte++; // Make odd
        }
    } else { // bit_to_hide == 0
        if (current_lsb == 1) {
            pixel_byte--; // Make even
        }
    }
    g_data_index++;
}

int extractBit() {
    if (g_data_index >= g_data_size) {
        throw runtime_error("Unexpected end of file. Message tag not found.");
    }

    int bit = g_pixel_data[g_data_index] % 2;
    g_data_index++;
    return bit;
}

void hideByte(char c) {
    for (int i = 0; i < 8; ++i) {
        int bit = (c >> i) & 1;
        hideBit(bit);
    }
}

char extractByte() {
    char c = 0;
    for (int i = 0; i < 8; ++i) {
        int bit = extractBit();
        if (bit == 1) {
            c = c | (1 << i);
        }
    }
    return c;
}

void hideMessage() {
    string inputFile, outputFile, message;

    cout << "\n--- HIDE MESSAGE ---" << endl;
    cout << "Enter source image file (e.g., source.png): ";
    clearInputBuffer();
    getline(cin, inputFile);

    cout << "Enter output file name (e.g., stego.png): ";
    getline(cin, outputFile);

    cout << "Enter secret message: ";
    getline(cin, message);

    if (message.empty()) {
        throw runtime_error("Message cannot be empty.");
    }

    cout << "Loading image..." << endl;
    g_pixel_data = stbi_load(inputFile.c_str(), &g_width, &g_height, &g_channels, 0);
    if (!g_pixel_data) {
        throw runtime_error("Failed to load input image. File not found?");
    }

    g_data_size = g_width * g_height * g_channels;
    g_data_index = 0;

    message += END_OF_MESSAGE_TAG;

    if (message.length() * 8 > g_data_size) {
        stbi_image_free(g_pixel_data);
        g_pixel_data = nullptr;
        throw runtime_error("Image is not large enough to hold this message.");
    }

    cout << "Hiding message..." << endl;
    for (char c : message) {
        hideByte(c);
    }

    cout << "Saving new image..." << endl;
    if (stbi_write_png(outputFile.c_str(), g_width, g_height, g_channels, g_pixel_data, g_width * g_channels) == 0) {
        stbi_image_free(g_pixel_data);
        g_pixel_data = nullptr;
        throw runtime_error("Failed to write output image.");
    }

    stbi_image_free(g_pixel_data);
    g_pixel_data = nullptr;

    cout << "Success! Message hidden in " << outputFile << endl;
}

void extractMessage() {
    string inputFile;
    string extractedMessage = "";

    cout << "\n--- EXTRACT MESSAGE ---" << endl;
    cout << "Enter stego-image file (e.g., stego.png): ";
    clearInputBuffer();
    getline(cin, inputFile);

    cout << "Loading image..." << endl;
    g_pixel_data = stbi_load(inputFile.c_str(), &g_width, &g_height, &g_channels, 0);
    if (!g_pixel_data) {
        throw runtime_error("Failed to load input image. File not found?");
    }

    g_data_size = g_width * g_height * g_channels;
    g_data_index = 0;

    cout << "Extracting message..." << endl;

    while (true) {
        char c = extractByte();
        extractedMessage += c;

        if (extractedMessage.length() > END_OF_MESSAGE_TAG.length()) {
            if (extractedMessage.rfind(END_OF_MESSAGE_TAG) != string::npos) {
                break; // Tag found
            }
        }
    }

    stbi_image_free(g_pixel_data);
    g_pixel_data = nullptr;

    size_t tag_pos = extractedMessage.rfind(END_OF_MESSAGE_TAG);
    string cleanMessage = extractedMessage.substr(0, tag_pos);

    cout << "\n--- SECRET MESSAGE FOUND ---" << endl;
    cout << cleanMessage << endl;
    cout << "------------------------------" << endl;
}
