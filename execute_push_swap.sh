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

echo "" > 2.txt

while IFS= read -r line; do
	line=$(echo "$line" | tr -d '\n')
	res=$(echo -n "$(./push_swap "$line")")
	printf "$res\n" >> 2.txt
	#echo "$res" | wc -l >> 2.txt
	printf "\n" >> 2.txt
done < "$file_path"

