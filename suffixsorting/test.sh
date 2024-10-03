#!/bin/bash

# Define colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Check if an exact test name is provided
if [ $# -eq 1 ]; then
    test_name=$1
    in_files=("samples/$test_name.in")
else
    # Check if there are any .in files in the samples directory
    shopt -s nullglob
    in_files=(samples/*.in)
    if [ ${#in_files[@]} -eq 0 ]; then
        echo "No .in files found in the samples directory!"
        exit 1
    fi
fi


# Iterate over all .in files in the "samples" directory
for in_file in "${in_files[@]}"; do
    # Check if the input file exists
    if [ ! -f "$in_file" ]; then
        echo "Input file $in_file not found!"
        exit 1
    fi

    # Extract the base name without extension
    s=$(basename "$in_file" .in)

    # Print the input content
    echo -e "Running test \"$s.in\":${BLUE}"
    cat $in_file
    echo -e "${NC}"

    # Run the command and store the output
    output=$(cat $in_file | ./run.sh -q)

    # Read the expected output from the corresponding .ans file
    expected_output=$(< "samples/$s.ans")

    # Compare the output with the expected output
    if [ "$output" == "$expected_output" ]; then
        echo -e "\"$s.in\": ${GREEN}Success - Output matches expected.${NC}"
        echo "Expected:"
        echo -e "${BLUE}$expected_output${NC}"
        echo
    else
        echo -e "\"$s.in\": ${RED}Failure - Output does not match expected.${NC}"
        echo -e "${BLUE}Expected:"
        echo -e "$expected_output${NC}"
        echo
        echo -e "${YELLOW}Got:"
        echo -e "$output${NC}"
        echo
    fi

    echo "--------------------------------------"
done


