#!/bin/sh

for n in 1 9
do 
  for m in 1 9
  do
    for l in  1 9
    do
      echo "\ne_100_${n}_${m}_${l}.c"
      cat e_100_${n}_${m}_${l}.c | head -n 15 | tail -n 4
    done
  done
done
