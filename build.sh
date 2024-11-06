#!/bin/bash

# Get the directory of the script
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Ask for OS type
echo "Choose your OS:"
echo "1) Windows 32"
echo "2) Windows 64"
echo "3) Linux"
# echo "4) macOS"
read -p "Enter your choice (1/2/3): " os_choice

# Ask for build type
echo "Choose build type:"
echo "1) Debug"
echo "2) Release"
read -p "Enter your choice (1/2): " build_type

# Set build type
if [ "$build_type" -eq 1 ]; then
    build_type="Debug"
else
    build_type="Release"
fi

# Create build directory
mkdir -p "$SCRIPT_DIR/build"
cd "$SCRIPT_DIR/build"

rm CMakeCache.txt

# Configure CMake
case "$os_choice" in
    1)
        cmake -DCMAKE_TOOLCHAIN_FILE="$SCRIPT_DIR/toolchains/win32.cmake" -DCMAKE_BUILD_TYPE=$build_type ..
        ;;
    2)
        cmake -DCMAKE_TOOLCHAIN_FILE="$SCRIPT_DIR/toolchains/win64.cmake" -DCMAKE_BUILD_TYPE=$build_type ..
        ;;
    3)
        cmake -DCMAKE_TOOLCHAIN_FILE="$SCRIPT_DIR/toolchains/linux.cmake" -DCMAKE_BUILD_TYPE=$build_type ..
        ;;
    # 4)
        # cmake -DCMAKE_TOOLCHAIN_FILE="$SCRIPT_DIR/toolchains/mac.cmake" -DCMAKE_BUILD_TYPE=$build_type ..
        # ;;
    *)
        echo "Invalid choice!"
        exit 1
        ;;
esac

# Build the project
cmake --build .
