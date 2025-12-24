*This current version was merged from the branch *bmpviewer* and is not the final result*

Currently this image viewer is only able to open 32-bit bitmap image files.
Written in C, using SDL for graphics.

# Installation
*Supported on all platforms, but has been tested only on Linux*

## Linux

Clone the repository:
```bash
$ git clone https://github.com/byynine/image-viewer
```
Then compile (using my program [max](https://github.com/byynine/max), make sure to use newer the C version from branch **max-c**):
```bash
$ max build bmpviewer
```
Or more commonly with **gcc**:
```bash
$ gcc -lSDL2 -o dist/bmpviewer src/bmpviewer.c
```
This will create a directory called **dist** and the compiled **bmpviewer** in it.

# Usage
Opening your desired image is simple.

While still in the cloned repository directory and after compiling:
```bash
$ dist/bmpviewer path/to/your/image
```
To test the program I have already provided the necessary images under the **res** directory.

Open the provided image:
```bash
$ dist/bmpviewer res/blue-bmp-32-bit.bmp
```

