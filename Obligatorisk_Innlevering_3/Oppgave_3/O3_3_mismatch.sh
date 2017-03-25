#!/bin/bash
if [ ! -e "O3_3_ORDLISTE" ]
then
echo "Databasen eksister ikke" 
sqlite3 O3_3_ORDLISTE <<EOS
create table if not exists main_table (ord text);
.import ./O3_3_ordliste.txt main_table
EOS
fi

while read I
do
J="$(sqlite3 O3_3_ORDLISTE "SELECT ord FROM main_table where ord = '$I'")";
if [ "$J" == "" ]
then
echo "$I"
fi
done
