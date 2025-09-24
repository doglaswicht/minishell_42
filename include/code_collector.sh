#!/bin/bash
# **************************************************************************** #
#                                                                              #
#    Recursive Code Collector Script                                         #
#                                                                              #
#    This script recursively searches for .c files (or any other code format)  #
#    in the project directory and outputs their paths and content to           #
#    all_code.txt. Any folder specified as an argument will be skipped.         #
#                                                                              #
# **************************************************************************** #

# Set the output file name
OUTPUT_FILE="all_code.txt"

# Remove existing output file if it exists
rm -f "$OUTPUT_FILE"

# Define the file extension to search for (change as needed, e.g., "*.c" to "*.py")
FILE_PATTERN="*.h"

# Build exclusion options if any folder names are provided as arguments
EXCLUDE_OPTIONS=()
if [ "$#" -gt 0 ]; then
    for skip_dir in "$@"; do
        # Append the exclusion option: skip this directory and its children
        EXCLUDE_OPTIONS+=( -path "./$skip_dir" -prune -o )
    done
fi

# Informative message 🎉
echo "Collecting files matching pattern \"$FILE_PATTERN\" into $OUTPUT_FILE..."
if [ "${#EXCLUDE_OPTIONS[@]}" -gt 0 ]; then
    echo "Skipping directories: $*"
fi

# Use find to locate files, applying exclusion options if provided
if [ "${#EXCLUDE_OPTIONS[@]}" -gt 0 ]; then
    find . "${EXCLUDE_OPTIONS[@]}" -type f -name "$FILE_PATTERN" -print | while IFS= read -r file; do
        echo "===== File: $file =====" >> "$OUTPUT_FILE"
        cat "$file" >> "$OUTPUT_FILE"
        echo -e "\n\n" >> "$OUTPUT_FILE"
    done
else
    find . -type f -name "$FILE_PATTERN" -print | while IFS= read -r file; do
        echo "===== File: $file =====" >> "$OUTPUT_FILE"
        cat "$file" >> "$OUTPUT_FILE"
        echo -e "\n\n" >> "$OUTPUT_FILE"
    done
fi

echo "✅ Collection complete! Check out [[$OUTPUT_FILE]] for the aggregated code." 