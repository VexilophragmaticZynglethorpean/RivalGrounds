@echo off
setlocal

:: Get the directory of the script
set SCRIPT_DIR=%~dp0

:: Ask for OS type
echo Choose your OS:
echo 1) Windows 32
echo 2) Windows 64
echo 3) Linux
REM echo 4) macOS
set /p os_choice="Enter your choice (1/2/3): "

:: Ask for build type
echo Choose build type:
echo 1) Debug
echo 2) Release
set /p build_type="Enter your choice (1/2): "

:: Set build type
if "%build_type%"=="1" (
    set build_type=Debug
) else (
    set build_type=Release
)

:: Create build directory
mkdir "%SCRIPT_DIR%build"
cd "%SCRIPT_DIR%build"

:: Clean previous CMake files
if exist CMakeCache.txt (
    del CMakeCache.txt
)

:: Configure CMake
if "%os_choice%"=="1" (
    cmake -DCMAKE_TOOLCHAIN_FILE="%SCRIPT_DIR%toolchains\win32.cmake" -DCMAKE_BUILD_TYPE=%build_type% ..
) else if "%os_choice%"=="2" (
    cmake -DCMAKE_TOOLCHAIN_FILE="%SCRIPT_DIR%toolchains\win64.cmake" -DCMAKE_BUILD_TYPE=%build_type% ..
) else if "%os_choice%"=="3" (
    cmake -DCMAKE_TOOLCHAIN_FILE="%SCRIPT_DIR%toolchains\linux.cmake" -DCMAKE_BUILD_TYPE=%build_type% ..
REM ) else if "%os_choice%"=="4" (
    REM cmake -DCMAKE_TOOLCHAIN_FILE="%SCRIPT_DIR%toolchains\mac.cmake" -DCMAKE_BUILD_TYPE=%build_type% ..
) else (
    echo Invalid choice!
    exit /b 1
)

:: Build the project
cmake --build .

endlocal

