#!/bin/sh

for n in 1 9
do 
  for m in 1 9
  do
    for l in  1 9
    do
      gnuplot -e "
        reset;
        undefine STATS*;
        stats '100_${n}_${m}_${l}.dat' u 1:2 nooutput;
        stats '100_${n}_${m}_${l}.dat' u 1:2 nooutput;
        stats '100_${n}_${m}_${l}.dat' u 1:2 nooutput;
        stats '100_${n}_${m}_${l}.dat' u 1:2 nooutput;
        stats '100_${n}_${m}_${l}.dat' u 1:2 nooutput;
        stats '100_${n}_${m}_${l}.dat' u 1:2 nooutput;
        stats '100_${n}_${m}_${l}.dat' u 1:2 nooutput;
        set terminal x11 enhanced;
        set title 'Changes in the number of acions with {/Symbol a}=${n} {/Symbol b}=${m} {/Symbol g}=${l}';
        set xrange [0:100];
        set yrange [0:STATS_max_y+1];
        set xlabel 'Number of trials';
        set ylabel 'Number of actions';
        unset key;
        plot '100_${n}_${m}_${l}.dat' u 1:2 with line;
        pause -1;
        set terminal pngcairo enhanced;
        set output 'N_100_${n}_${m}_${l}.png';
        replot;
        set terminal x11 enhanced;
        clear;

        reset;
        undefine STATS*;
        stats '100_${n}_${m}_${l}.dat' using 1:3 nooutput;
        set title 'Changes in total reward with {/Symbol a}=${n} {/Symbol b}=${m} {/Symbol g}=${l}';
        set xrange [0:100];
        set yrange [STATS_min_y-1:STATS_max_y+1];
        set xlabel 'Number of trials';
        set ylabel 'Amount of total reward';
        unset key;
        plot '100_${n}_${m}_${l}.dat' u 1:3 with line;
        pause -1;
        set terminal pngcairo enhanced;
        set output 'R_100_${n}_${m}_${l}.png';
        replot;
        set terminal x11 enhanced;
        "

    done
  done
done

