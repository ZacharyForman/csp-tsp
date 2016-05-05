all: tsp

tsp: tsp.c makefile
	gcc -O3 -std=c11 tsp.c -o tsp -funroll-loops -ffast-math -fomit-frame-pointer -funsafe-loop-optimizations
