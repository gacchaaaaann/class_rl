#!/bin/sh
<< COMMENTOUT
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
        set terminal x11 enhanced;
        set title 'Changes in the number of acions with {/Symbol a}=${n} {/Symbol g}=${m} {/Symbol e}=${l}';
        set xrange [0:100];
        set yrange [0:STATS_max_y+1];
        set xlabel 'Number of trials';
        set ylabel 'Number of actions';
        unset key;
        plot '100_${n}_${m}_${l}.dat' u 1:2 with line;
        pause -1;
        set terminal pngcairo enhanced;
        set output './PNG/N_100_${n}_${m}_${l}.png';
        replot;
        set terminal x11 enhanced;
        clear;

        reset;
        undefine STATS*;
        stats '100_${n}_${m}_${l}.dat' using 1:3 nooutput;
        set title 'Changes in total reward with {/Symbol a}=${n} {/Symbol g}=${m} {/Symbol e}=${l}';
        set xrange [0:100];
        set yrange [STATS_min_y-1:STATS_max_y+1];
        set xlabel 'Number of trials';
        set ylabel 'Amount of total reward';
        unset key;
        plot '100_${n}_${m}_${l}.dat' u 1:3 with line;
        pause -1;
        set terminal pngcairo enhanced;
        set output './PNG/R_100_${n}_${m}_${l}.png';
        replot;
        set terminal x11 enhanced;
        "

    done
  done
done

gnuplot -e "
  reset;
  set terminal x11 enhanced;
  set title 'Changes in the number of acions';
  set xlabel 'Number of trials';
  set ylabel 'Number of actions';
  set key font 'Arial,8.5';
  plot for [n in '1 9'] for [m in '1 9'] for [l in '1 9'] '100_'.n.'_'.m.'_'.l.'.dat' title '{/Symbol a}='.n.' {/Symbol g}='.m.' {/Symbol e}='.l with line;
  pause -1;
  set terminal pngcairo enhanced;
  set output './PNG/N_TOTAL.png';
  replot;
  set terminal x11 enhanced;
  clear;
"
COMMENTOUT

gnuplot -e "
  reset;
  set terminal x11 enhanced;
  set title 'Changes in total reward';
  set xlabel 'Number of trials';
  set ylabel 'Amount of total reward';
  set key font 'Arial,8.5';
  plot for [n in '1 9'] for [m in '1 9'] for [l in '1 9'] '100_'.n.'_'.m.'_'.l.'.dat' u 1:3 title '{/Symbol a}='.n.' {/Symbol g}='.m.' {/Symbol e}='.l with line;
  pause -1;
  set terminal pngcairo enhanced;
  set output './PNG/R_TOTAL.png';
  replot;
  set terminal x11 enhanced;
  clear;
"
