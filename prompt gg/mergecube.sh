#!/bin/bash

bin=2048

rm -rf cube.root
hadd cube.root  ../pkucube/cube_R*.root

for (( i=0; i<$bin; i++ ))
do
    var=$(printf "%04d" "$i")
    rm -rf cube_$var.root
    hadd cube_$var.root  ../pkucube/cube_$var\_R*.root
    printf "%04d\n" "$i";
done
