#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file_path>"
    exit 1
fi

file_path=$1

if [ ! -f "$file_path" ]; then
    echo "File not found: $file_path"
    exit 1
fi

while IFS= read -r line; do
	line=$(echo "$line" | tr -d '\n')	
	./push_swap "$line" > test.txt
done < "$file_path"

