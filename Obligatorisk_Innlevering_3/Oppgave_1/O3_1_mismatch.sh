#!/bin/bash
while read I; do if ! grep -q $I ./O3_1_ordliste.txt -i; 
then echo $I
fi
done

