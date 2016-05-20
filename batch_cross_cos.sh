#!/bin/bash

#./sparse_lsh 500 1 

for i in 500 1000 1500 2000; do
    ./cross_cos $i $1  
done
