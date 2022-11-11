# Lottery Simulations

This repository houses the code for my blog post
["Does it ever make sense to play the Lottery?"](https://dmsenter89.github.io/post/22-09-lottery/).
This repo consists of several compiled and script implementations simulating
a life-time of lottery playing with a constant 750 million USD jackpot. Each file
produces a results text file containing a single column of all the _final_ amounts 
of money for each simulated player.

This repository contains a devcontainer if you'd like to run the examples without
needing to modify your own environment. A Makefile will take care of building the 
compiled versions. To run a benchmark comparing all implementions using hyperfine,
run `make benchmark`.
