@echo off
REM ============================================================================
REM LibraSys Build Script for Windows
REM ============================================================================

echo.
echo ====================================
echo  LibraSys Build Script
echo ====================================
echo.

REM Check if build directory exists
if exist build (
    echo [INFO] Cleaning existing build directory...
    rmdir /s /q build
)

REM Create build directory
echo [INFO] Creating build directory...
mkdir build
cd build

REM Configure with CMake
echo.
echo [INFO] Configuring project with CMake...
cmake .. -G "MinGW Makefiles"

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] CMake configuration failed!
    echo [HINT] Make sure Qt is installed and CMAKE_PREFIX_PATH is set
    echo [HINT] Example: set CMAKE_PREFIX_PATH=C:\Qt\6.5.0\mingw_64
    pause
    exit /b 1
)

REM Build project
echo.
echo [INFO] Building project...
cmake --build . --config Release

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build failed!
    pause
    exit /b 1
)

echo.
echo ====================================
echo  Build Successful!
echo ====================================
echo.
echo Run the application with:
echo   cd build
echo   LibraSys.exe
echo.
pause
