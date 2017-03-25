#!/bin/bash
while read I; do if ! grep -q $I ./O1_ordliste -i; 
then echo $I
fi
done

