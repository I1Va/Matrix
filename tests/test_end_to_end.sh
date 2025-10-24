#!/bin/bash

mkdir temp_files

for size in 2 3 4 5 10 20 30 40 50 60 70 80 90 100; do
    expected_determinant=$(awk -v seed=$RANDOM 'BEGIN{srand(seed); printf "%.1f\n", (rand()*20 - 10)}')

    build/tests/MatrixGenerator "$size" "$expected_determinant" > temp_files/test1.txt
    actual_determinant=$(build/Matrix < temp_files/test1.txt)

    diff=$(echo "$actual_determinant - $expected_determinant" | bc -l)
    abs_diff=$(echo "$diff" | awk '{if($1<0) $1=-$1; print $1}')

    if (( $(echo "$abs_diff > 0.1" | bc -l) )); then
        echo "FAIL: size=$size, expected=$expected_determinant, actual=$actual_determinant"
    else
        echo "OK: size=$size, expected=$expected_determinant, actual=$actual_determinant"
    fi
done

rm -rf temp_files
