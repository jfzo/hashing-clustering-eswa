#!/bin/bash

#./sparse_lsh 500 1 

for i in 500 1000 1500; do
    ./cross_jacc $i $1

done
