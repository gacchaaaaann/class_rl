#!/bin/sh


#!/bin/sh

for n in 1 9
do 
  for m in 1 9
  do
#    for l in  1 9
#     do
      sed -e 's@\ printf@ for(int n=0; n<=NUM_STATE; n++) printf("%lf %lf ", Q[i][0], Q[i][1]);\n    printf("\\n");\n    //printf@' e_100_${n}_${m}_${l}.c > q_100_${n}_${m}_${l}.c
      gcc -o Q_100_${n}_${m}_${l} -DSFMT_MEXP=19937 q_100_${n}_${m}_${l}.c SFMT/SFMT.c env-one_dimension_space.c reward_function.c
#      echo "${n}_${m}_${l}"
#    done
  done
done
