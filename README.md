# ASCII Art Generator

## Description
The **ASCII Art Generator** is a C++ program that converts images into ASCII art suitable for display in a terminal. By analyzing the brightness of pixels in the input image, it maps sections of the image to ASCII characters that visually approximate the image when viewed as text.

## Features
- Converts an input image (e.g., PNG, JPG) into ASCII art.
- Supports adjustable resolution for the ASCII output based on user input.
- Calculates brightness using the NTSC luminance formula for realistic conversion.
- Handles images of various sizes and adjusts character blocks dynamically to maintain requested proportions.

## How It Works
1. The program reads an image file specified by the user.
2. The user specifies the desired ASCII resolution (number of characters in X and Y dimensions - limited to 1 character per pixel).
3. The program divides the image into blocks and calculates the average brightness for each block.
4. Each block is represented by a character from an ASCII brightness table.
5. The ASCII representation is printed to the terminal.

## Known Issues
### 1. Aspect Ratio
Characters in the terminal are typically taller than they are wide, which may stretch the image vertically. Adjusting the resolution parameters can help mitigate this.

### 2. Alpha Channel Crashes
Attempting to read the alpha channel in certain images may cause access violations. For now, the program defaults to assuming full opacity (`255`) for all pixels.
