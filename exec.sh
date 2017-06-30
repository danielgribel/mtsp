#!/bin/bash

s=1606

FILES=/home/dgribel/PUC-Doc/Metaheuristics/MTSP/data/E-15-20-12/*
for f in $FILES
do
  # echo "$f"
  for i in `seq 1 1`;
	do
		./mts $((s+i)) $f
	done
done
