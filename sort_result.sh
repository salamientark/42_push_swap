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

/usr/bin/awk '
  BEGIN {
    RS = ""       # Set the record separator to an empty line
    ORS = "\n\n"  # Set the output record separator to two new lines
  }
  {
    for (i = 1; i <= NF; i++) {
      lines[NR, i] = $i  # Store each word in a 2D array indexed by record and field number
    }
    line_count[NR] = NF  # Store the number of fields for each record
  }
  END {
    n = asorti(line_count, sorted_indices)  # Sort indices based on the number of fields
    for (i = 1; i <= n; i++) {
      idx = sorted_indices[i]
      for (j = 1; j <= line_count[idx]; j++) {
        printf "%s ", lines[idx, j]  # Print each word in the sorted order
      }
      printf "\n"  # Print a newline after each group
    }
  }
' "$file_path"

