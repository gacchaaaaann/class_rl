#!/bin/sh

for n in 1 9
do 
  for m in 1 9
  do
    for l in  1 9
    do
      gcc -o E_100_${n}_${m}_${l} -DSFMT_MEXP=19937 e_100_${n}_${m}_${l}.c SFMT/SFMT.c env-one_dimension_space.c reward_function.c
#      echo "${n}_${m}_${l}"
    done
  done
done
