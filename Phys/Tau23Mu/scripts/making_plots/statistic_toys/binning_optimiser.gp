#!/bin/zsh

gnuplot << TOEND
set terminal postscript eps color enhanced "Helvetica" 20
set output "$1.eps"
set yrange [0:*]
plot "$1"  using 1:4 title "upper 1 {/Symbol s}",\
     "$1"  using 1:3 title "median",\
     "$1"  using 1:2 title "lower 1 {/Symbol s}"

