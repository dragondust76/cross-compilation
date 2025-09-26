#!/bin/bash

# Define the MinGW-w64 toolchain prefix
TOOLCHAIN_PREFIX="i686-w64-mingw32"

# Temporarily redirect output to a file to capture user input from dialog
TEMPFILE=$(mktemp)

# Prompt user for a source file using dialog
dialog --title "Select C/C++ file to compile" --fselect "$PWD/" 14 48 2> "$TEMPFILE"

# Capture the selected file path
SELECTED_FILE=$(cat "$TEMPFILE")
rm "$TEMPFILE"

# Check if the user cancelled the dialog
if [ -z "$SELECTED_FILE" ]; then
    echo "No file selected. Exiting."
    exit 1
fi

# Extract the base name for the output file
BASE_NAME=$(basename -- "$SELECTED_FILE")
OUTPUT_NAME="${BASE_NAME%.*}"
OUTPUT_FILE="${OUTPUT_NAME}.exe"

# Determine the correct compiler based on the file extension
if [[ "$SELECTED_FILE" == *.cpp ]]; then
    COMPILER="${TOOLCHAIN_PREFIX}-g++"
else
    COMPILER="${TOOLCHAIN_PREFIX}-gcc"
fi

# Construct the compile command with static linking
COMPILE_COMMAND="$COMPILER -o $OUTPUT_FILE $SELECTED_FILE -static -mwindows -static-libgcc -static-libstdc++"

# Compile and display the result
echo "Compiling $SELECTED_FILE into $OUTPUT_FILE..."
$COMPILE_COMMAND

if [ $? -eq 0 ]; then
    echo "Compilation successful. The program '$OUTPUT_FILE' was created."
else
    echo "Compilation failed. Check above for errors."
fi
