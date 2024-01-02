#!/bin/bash

generate_permutations() {
    local n=$1
    local current_permutation=$2
    local remaining_numbers=$3

    if [ ${#remaining_numbers} -eq 0 ]; then
        echo $current_permutation
        return
    fi

    for digit in $remaining_numbers; do
        local new_permutation="$current_permutation $digit"
        local new_remaining_numbers=$(echo $remaining_numbers | sed "s/$digit//")

        generate_permutations $n "$new_permutation" "$new_remaining_numbers"
    done
}

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <n>"
    exit 1
fi

n=$1

if ! [[ "$n" =~ ^[1-9][0-9]*$ ]]; then
    echo "n must be a positive integer."
    exit 1
fi

initial_numbers=$(seq 1 $n)
generate_permutations $n "" "$initial_numbers"

