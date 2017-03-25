#!/bin/bash

# Dette skriptet lager en tabell med informasjon om filer i et filtre.
# Roten til filtreet oppgis som argument.
# Dersom argumentet utelates brukes aktiv katalog som rot.

# - find(1) brukes for å traversere treet.
# - stat(1) brukes for å finne og skrive fil-info
# - xargs(1) brukes for å sende utskriften fra find(1) som 
#   argumenter til stat(1)
# - Separator kan angis med miljøvariabelen S
  
# Thomas Nordli (oktober 2015) 
  
if [ $# -gt 0 ]; then
    cd $1
fi
  
  
if [ "$S" = "" ]; then
    S=";"
fi
  
FORMATSTR="%a$S%b$S%B$S%D$S%F$S%g$S%G$S%h$S%i$S%m$S%n$S%o$S%s$S%u$S%U"
  
#
# Forklaring på formatstrengen, hentet fra stat(1):
#       %a     access rights in octal
#       %b     number of blocks allocated (see %B)
#       %B     the size in bytes of each block reported by %b
#       %D     device number in hex
#       %F     file type
#       %g     group ID of owner
#       %G     group name of owner
#       %h     number of hard links
#       %i     inode number
#       %m     mount point
#       %n     file name
#       %o     optimal I/O transfer size hint
#       %s     total size, in bytes
#       %u     user ID of owner
#       %U     user name of owner
#
  
find $PWD | xargs stat -c $FORMATSTR 2> /dev/null
