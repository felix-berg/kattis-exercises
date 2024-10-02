#!/bin/bash

# Check if the first argument is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <PROBLEM>"
    exit 1
fi

PROBLEM=$1
TEMPLATE_DIR="template"
DEST_DIR="$PROBLEM"

# Check if the destination directory already exists
if [ -d "$DEST_DIR" ]; then
    echo "Error: Directory '$DEST_DIR' already exists. Aborting."
    exit 1
fi

# Copy template directory to the new problem directory
if [ -d "$TEMPLATE_DIR" ]; then
    cp -r "$TEMPLATE_DIR" "$DEST_DIR"
else
    echo "Error: Template directory '$TEMPLATE_DIR' not found."
    exit 1
fi

# Fetch the problem page
URL="https://open.kattis.com/problems/$PROBLEM"
PAGE=$(curl -s "$URL")

# Check if the page contains "404: not found"
if [[ "$PAGE" == *"404: not found"* ]]; then
    echo "Error: Problem '$PROBLEM' not found on Kattis."
    exit 1
fi

# Fetch the samples zip file
SAMPLES_URL="https://open.kattis.com/problems/$PROBLEM/file/statement/samples.zip"
curl -s -o "$PROBLEM/samples.zip" "$SAMPLES_URL"

# Unzip the samples into the problem directory
mkdir -p "$PROBLEM/samples"
unzip -o "$PROBLEM/samples.zip" -d "$PROBLEM/samples"

# Clean up
rm "$PROBLEM/samples.zip"

echo "Problem '$PROBLEM' setup completed successfully."
