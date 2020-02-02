#!/bin/sh
A="1 9"
G="1 9"
E="05 3"

for a in ${A}
do 
  for g in ${G}
  do
    for e in  ${E}
    do
      sed -e 's/ALPHA 0.1/ALPHA 0.'${a}'/' -e 's/GAMMA 0.9/GAMMA 0.'${g}'/' -e 's/E 0.05/E 0.'${e}'/' e_main.c > e_100_${a}_${g}_${e}.c
      gcc -o E_100_${a}_${g}_${e} -DSFMT_MEXP=19937 e_100_${a}_${g}_${e}.c SFMT/SFMT.c env-one_dimension_space.c reward_function.c
      ./E_100_${a}_${g}_${e} > E/e_100_${a}_${g}_${e}.dat

      gnuplot -e "
        reset;
        set terminal x11 enhanced;
        set title 'Changes in the number of acions with {/Symbol a}=0.${a} {/Symbol g}=0.${g} {/Symbol e}=0.${e}';
        set xrange [0:100];
        set yrange [0:*];
        set xlabel 'Number of trials';
        set ylabel 'Number of actions';
        unset key;
        plot 'E/e_100_${a}_${g}_${e}.dat' u 1:2 with line;
        pause -1;
        set terminal pngcairo enhanced;
        set output 'PNG/E/100_${a}_${g}_${e}_N.png';
        replot;
        set terminal x11 enhanced;
        clear;

        reset;

        undefine STATS*;
        stats 'E/e_100_${a}_${g}_${e}.dat' using 1:3 nooutput;
        set title 'Changes in total reward with {/Symbol a}=0.${a} {/Symbol g}=0.${g} {/Symbol e}=0.${e}';
        set xrange [0:100];
        set yrange [STATS_min_y-1:STATS_max_y+1];
        set xlabel 'Number of trials';
        set ylabel 'Amount of total reward';
        unset key;
        plot 'E/e_100_${a}_${g}_${e}.dat' u 1:3 with line;
        pause -1;
        set terminal pngcairo enhanced;
        set output 'PNG/E/100_${a}_${g}_${e}_R.png';
        replot;
        set terminal x11 enhanced;

        reset;
        set title 'Changes in Q with {/Symbol a}=0.${a} {/Symbol g}=0.${g} {/Symbol e}=0.${e}';
        set xrange [0:100];
        unset yrange;
        set xlabel 'Number of trials';
        set ylabel 'Amount of Q';
        set key;
        plot for [n = 4:17] './E/e_100_${a}_${g}_${e}.dat' u 1:n with linespoints title 'Q['.(n/2-2).']['.(n%2).']';
        pause -1;
        set terminal pngcairo enhanced;
        set output './PNG/E/100_${a}_${g}_${e}_Q.png';
        replot;
        set terminal x11 enhanced;
        "

<< commentout
    printf("%d %d %lf",i,j-1,total_reward);
      printf(" %lf %lf", Q[i][0], Q[i][1]);
    printf("\n");
#!/bin/sh
<< COMMENTOUT
for n in 1 9
do 
  for m in 1 9
  do
    for l in  1 9
    do

    done
  done
done

COMMENTOUT

gnuplot -e "
  reset;
  set terminal x11 enhanced;
  set title 'Changes in total reward';
  set xlabel 'Number of trials';
  set ylabel 'Amount of total reward';
  set key font 'Arial,8.5';
  plot for [n in '1 9'] for [m in '1 9'] for [l in '1 9'] '100_'.n.'_'.m.'_'.l.'.dat' u 1:3 title '{/Symbol a}=0.'.n.' {/Symbol g}=0.'.m.' {/Symbol e}=0.'.l with line;
  pause -1;
  set terminal pngcairo enhanced;
  set output './PNG/R_TOTAL.png';
  replot;
  set terminal x11 enhanced;
  clear;
"
commentout
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
  plot for [a in '${A}'] for [g in '${G}'] for [e in '${E}'] 'E/e_100_'.a.'_'.g.'_'.e.'.dat' title '{/Symbol a}=0.'.a.' {/Symbol g}=0.'.g.' {/Symbol e}=0.'.e with line;
  pause -1;
  set terminal pngcairo enhanced;
  set output 'PNG/E/TOTAL_N.png';
  replot;
  set terminal x11 enhanced;
  clear;
"

gnuplot -e "
  reset;
  set terminal x11 enhanced;
  set title 'Changes in total reward';
  set xlabel 'Number of trials';
  set ylabel 'Number of total reward';
  set key font 'Arial,8.5';
  plot for [a in '${A}'] for [g in '${G}'] for [e in '${E}'] 'E/e_100_'.a.'_'.g.'_'.e.'.dat' title '{/Symbol a}=0.'.a.' {/Symbol g}=0.'.g.' {/Symbol e}=0.'.e with line;
  pause -1;
  set terminal pngcairo enhanced;
  set output 'PNG/E/TOTAL_R.png';
  replot;
  set terminal x11 enhanced;
  clear;
"
