#!/bin/bash

#./sparse_lsh 500 1 

for i in 500 1000 1500 2000; do
    ./sparse_lsh $i 1 $1
done
