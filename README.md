# IMPP - Image Format Converter

A C++ application with a drop area for images, which can then be converted into other picture formats.

## Features

- Drag and drop interface for easy image loading
- Support for multiple image formats (PNG, JPEG, BMP, GIF, TIFF, WebP)
- Simple and intuitive user interface
- Image information display (format, dimensions, file size)

## Requirements

- Qt 6.0 or later
- C++17 compatible compiler

## Building the Application

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
```

### Using qmake

```bash
qmake
make
```

## Usage

1. Launch the application
2. Drag and drop an image onto the drop area or use File > Open Image
3. Select the desired output format from the dropdown menu
4. Click the "Convert" button
5. Choose a location to save the converted image

## Supported Formats

The application supports the following image formats:

- PNG
- JPEG
- BMP
- GIF
- TIFF
- WebP

Note: The actual supported formats may vary depending on your Qt installation.
