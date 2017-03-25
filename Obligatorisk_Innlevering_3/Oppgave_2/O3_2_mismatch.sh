#!/bin/bash
if [ ! -e "O3_2_ORDLISTE" ]
then
echo "Databasen eksister ikke" 
sqlite3 O3_2_ORDLISTE <<EOS
create table if not exists main_table (ord text);
.import ./O3_2_ordliste.txt main_table
EOS
fi

while read I
do
J="$(sqlite3 O3_2_ORDLISTE "SELECT ord FROM main_table where ord = '$I'")";
if [ "$J" == "" ]
then
echo "$I"
fi
done
