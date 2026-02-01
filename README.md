# OpenCV Image Loader (C++ & MinGW)

A simple C++ starter project that demonstrates how to load and display an image using the OpenCV library. This project is optimized for **VS Code** using the **MinGW (UCRT64)** toolchain on Windows.

## Prerequisites

Before running this project, ensure you have the following installed:
* [VS Code](https://code.visualstudio.com/)
* [C/C++ Extension for VS Code](https://marketplace.visualstudio.com/items?itemName=msys2.cpptools)
* [MSYS2](https://www.msys2.org/) (installed and configured for UCRT64)

## Environment Setup

### 1. Install Dependencies
Open your **MSYS2 UCRT64 Terminal** and run the following command to install OpenCV and the required Qt6 graphics backend:

```bash
pacman -S mingw-w64-ucrt-x86_64-opencv mingw-w64-ucrt-x86_64-qt6-base
```
### 2. Configure Windows System Path
To allow the `.exe` to find the required `.dll` files at runtime, you must add the MinGW `bin` folder to your system variables:

1. Search Windows for **"Edit the system environment variables"**.
2. Click **Environment Variables** > Find **Path** in System Variables > **Edit**.
3. Click **New** and add the following path:
   ```text
   D:\mingw\ucrt64\bin
   ```
## Project Structure

To ensure the compiler finds your headers and the executable finds your images, organize your files as follows:

```text
ComputerVision/
├── .vscode/
│   ├── tasks.json             # Build/Linker instructions for g++
│   └── c_cpp_properties.json   # IntelliSense settings for VS Code
├── Images/
│   └── test.jpg               # Your input image (referenced in code)
├── CVTest.cpp                 # Main C++ source code
└── CVTest.exe                 # Compiled executable (generated after build)
```
### 📄 File Descriptions

* **`.vscode/tasks.json`**
    The "Build Recipe." It tells the compiler exactly which OpenCV libraries to link (`core`, `imgcodecs`, `highgui`) and where to find them on your `D:` drive. This is currently only for those who have it in an external drive if you only have one replace D: with C:
    
* **`.vscode/c_cpp_properties.json`**
    The "Editor Intelligence." This file configures VS Code's IntelliSense so that autocomplete works for `cv::` functions and red "include" squiggles are removed.

* **`Images/`**
    The Asset Folder. This directory must contain the image files your code intends to load. The path in your code (`Images/test.jpg`) is relative to where the executable runs.

* **`CVTest.cpp`**
    The Source Code. This is your C++ logic. It uses the OpenCV headers to read image data into a `cv::Mat` object and display it in a GUI window.

* **`CVTest.exe`**
    The Executable. This is the final Windows application generated after a successful build. It requires the OpenCV `.dll` files in your System Path to run.
## How to Build and Run

Follow these steps to compile your code and launch the application.

### 1. Build the Project
1. Open the **`CVTest.cpp`** file in VS Code.
2. Press `Ctrl + Shift + B` on your keyboard.
3. Check the **Terminal** window at the bottom. It should say:
   `Build finished successfully.`



### 2. Run the Application
You can run the program directly from the VS Code terminal.

**For PowerShell (Default):**
```powershell
.\CVTest.exe
```
## Configuration Files

These files are located in the `.vscode/` folder and are essential for the compiler and editor to recognize OpenCV.

### 1. tasks.json
This file tells VS Code how to run the `g++` compiler with the correct OpenCV linking flags.

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe build active file",
            "command": "D:\\mingw\\ucrt64\\bin\\g++.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-I", "D:/mingw/ucrt64/include/opencv4",
                "-I", "D:/mingw/ucrt64/include",
                "-L", "D:/mingw/ucrt64/lib",
                "-lopencv_core",
                "-lopencv_imgcodecs",
                "-lopencv_highgui"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```
### 3. c_cpp_properties.json
This file manages **IntelliSense**. It ensures that VS Code can find the OpenCV headers so you get autocomplete suggestions and no red error squiggles while writing code.

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "D:/mingw/ucrt64/include/opencv4",
                "D:/mingw/ucrt64/include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "D:/mingw/ucrt64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
