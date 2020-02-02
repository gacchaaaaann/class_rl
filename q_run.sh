
#!/bin/sh

for n in 1 9
do 
  for m in 1 9
  do
    for l in  1 9
    do
      ./Q_100_${n}_${m}_${l} > q_100_${n}_${m}_${l}.dat
#      echo "${n}_${m}_${l}"
    done
  done
done
