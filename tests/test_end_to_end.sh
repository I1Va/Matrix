#!/bin/bash

mkdir temp_files

for size in 1 2 3 4 5 10 20 30 40 50 60 70 80 90 100; do
    expected=$(awk -v seed=$RANDOM 'BEGIN{srand(seed); printf "%.4f\n", (rand()*200 - 100)}')

    build/tests/generate $size $expected > temp_files/test1.txt
    actual=$(build/Matrix < temp_files/test1.txt)

    diff=$(echo "$actual - $expected" | bc -l)
    abs_diff=$(echo "$diff" | awk '{if($1<0) $1=-$1; print $1}')

    if (( $(echo "$abs_diff > 0.00001" | bc -l) )); then
        echo "FAIL: size=$size, expected=$expected, actual=$actual"
    fi
done

rm -rf temp_files
