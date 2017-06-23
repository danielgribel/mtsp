#!/bin/bash

s=1606
for i in `seq 1 1`;
do
	./mts $((s+i)) 
done
