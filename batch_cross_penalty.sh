#!/bin/bash

#./sparse_lsh 500 1 

for i in 500 1000 1500 2000; do
    ./cross_penalty $i $1 $2
done
