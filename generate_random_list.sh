#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <size>"
    exit 1
fi

size=$1

# Check if size is a positive integer
if ! [[ "$size" =~ ^[1-9][0-9]*$ ]]; then
    echo "Size must be a positive integer."
    exit 1
fi

# Generate a random list of unique numbers
random_list=$(seq 1 $size | shuf| tr '\n' ' ') 

echo "$random_list"

